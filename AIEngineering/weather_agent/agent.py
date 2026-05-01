from openai import OpenAI
import json
import requests
from dotenv import load_dotenv

load_dotenv()
client = OpenAI()
# setx OPENAI_API_KEY "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"

def get_weather(location: str):
    url = f"https://wttr.in/{location.lower()}?format=j1"
    response = requests.get(url)
    if response.status_code == 200:
        return f"The current weather in {location} is {response.json()['current_condition'][0]['temp_C']}°C with {response.json()['current_condition'][0]['weatherDesc'][0]['value']}."
    return f"Sorry, I couldn't fetch the weather for {location}."

available_tools = {
    "get_weather": get_weather,
}

SYSTEM_PROMPT = """
You are an expert AI assistant in helping user queries using chain of thought.
You work on START, PLAN, OUTPUT steps.
You need to PLAN what needs to be done. Plan can be multiple steps.
Once you think enough PLAN has been done, finally you can OUTPUT the answer to the user query.
You can also use TOOL step to call any tool if you think that is required. But remember to give the final answer in OUTPUT step only.
For every tool call wait for the observe step which is the output from the called tool.

RULES:
- Strictly follow, the JSON output format.
- Only run one step at a time.
- The sequence of steps is START(where user gives an input), PLAN(That can be multiple steps), 
    OUTPUT(That is the final answer to the user query, that is going to be displayed to the user).

OUTPUT JSON FORMAT:
    {
        "step": "START" | "PLAN" | "OUTPUT" | "TOOL", "content": "string", "tool": "string", "input": "string"
        "content": "string"
    }

    Available tools:
    get_weather(location: str) -> str: This tool takes a location as input and returns the current weather information for that location.
    Example1:
    START. can you solve, 2 + 2*5/10
    PLAN: {"step": "PLAN", "content": "Seems like user is interested in solving a math problem"}
    PLAN: {"step": "PLAN", "content": "I think we should use here BODMAS rule to solve the problem"}
    PLAN: {"step": "PLAN", "content": "First we need to solve 5/10, then multiply the result with 2, then add 2 to the result"}
    OUTPUT: {"step": "OUTPUT", "content": "The answer to the problem is 3"}

    Example2:
    START. What is the current weather in New York?
    PLAN: {"step": "PLAN", "content": "Seems like user is interested in fetching weather information"}
    PLAN: {"step": "PLAN", "content": "I think we should use get_weather tool to fetch the weather information for New York"}
    PLAN: {"step": "PLAN", "content": "I will call TOOL step to call get_weather tool with New York as input"}
    PLAN: {"step": "PLAN", "content": "After getting the output from TOOL step, I will give the final answer to user in OUTPUT step"}
    TOOL: {"step": "TOOL", "tool": "get_weather", "input": "New York"}
    OUTPUT: {"step": "OUTPUT", "content": "The current weather in New York is 15°C with Partly cloudy."}

"""


message_history = [
    {"role": "system", "content": SYSTEM_PROMPT}
]

while True:
    user_query = input("▶️ Enter your query: ")
    message_history.append({"role": "user", "content": user_query})
    print("\n🤖 AI Assistant is thinking...\n")
    while True:
        response = client.chat.completions.create(
            model="gpt-4o-mini",
            response_format={"type": "json_object"},
            messages = message_history
        )

        raw_results = response.choices[0].message.content
        message_history.append({"role": "assistant", "content": raw_results})
        parsed_result = json.loads(raw_results)

        if parsed_result.get("step") == "START":
            print("User Query:", parsed_result.get("content"))
            continue
        elif parsed_result.get("step") == "PLAN":
            print("Planning:", parsed_result.get("content"))
            continue
        elif parsed_result.get("step") == "OUTPUT":
            print("Final Output:", parsed_result.get("content"))
            break
        elif parsed_result.get("step") == "TOOL":
            tool_to_call = parsed_result.get("tool")
            tool_input = parsed_result.get("input")
            print(f"Calling tool: {tool_to_call} with input: {tool_input}")
            tool_response = available_tools[tool_to_call](tool_input)
            message_history.append({"role": "developer", "content": json.dumps(
                {
                    "step": "OBSERVE",
                    "tool": tool_to_call,
                    "input": tool_input,
                    "output": tool_response
                }
            )})
            print(f"Tool response: {tool_response}")
            continue
        



print("✅ Done!")


