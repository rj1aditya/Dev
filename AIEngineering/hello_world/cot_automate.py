from openai import OpenAI
import json
client = OpenAI()
# setx OPENAI_API_KEY "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"

SYSTEM_PROMPT = """
You are an expert AI assistant in helping user queries using chain of thought.
You work on START, PLAN, OUTPUT steps.
You need to PLAN what needs to be done. Plan can be multiple steps.
Once you think enough PLAN has been done, finally you can OUTPUT the answer to the user query.

RULES:
- Strictly follow, the JSON output format.
- Only run one step at a time.
- The sequence of steps is START(where user gives an input), PLAN(That can be multiple steps), 
    OUTPUT(That is the final answer to the user query, that is going to be displayed to the user).

OUTPUT FORMAT:
    {
        "step": "START" | "PLAN" | "OUTPUT",
        "content": "string"
    }

    Example:
    START. can you solve, 2 + 2*5/10
    PLAN: {"step": "PLAN", "content": "Seems like user is interested in solving a math problem"}
    PLAN: {"step": "PLAN", "content": "I think we should use here BODMAS rule to solve the problem"}
    PLAN: {"step": "PLAN", "content": "First we need to solve 5/10, then multiply the result with 2, then add 2 to the result"}
    OUTPUT: {"step": "OUTPUT", "content": "The answer to the problem is 3"}


"""


message_history = [
    {"role": "system", "content": SYSTEM_PROMPT}
]

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

print("✅ Done!")