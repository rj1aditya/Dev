import json

from openai import OpenAI
import os
client = OpenAI()

SYSTEM_PROMT = """
    you are expert in maths, and only and only reply the maths related query, if other topic related query come you simply ignore it.
    e.g.
    Q. Give me idea about what goes on in summar?
    A. Sorry, I donno about it.

    But if user ask query about maths related question, you first plan, and reply back as chain of though process.
    e.g.
    Q. what will be the output of following expression: 3+8*10/2+90
    PLAN: this is a match problem
    PLAN: I should apply bodmos formula
    PLAN: As per bodmos first I should sholve high priority mult, then divide then summation and substraction
    PLAN: finally the output.

RULES:
    - Must follow the json object output
    {
        "step": "START"|"PLAN"|"OUTPUT",
        "content": "xyz"

    }
    e.g.
    START - what will be the output of this expression - 3+8*10/2+90
    PLAN - {"step":"PLAN", "content":"xyz"}
    PLAN - {"step":"PLAN", "content":"xyz"}
    PLAN - {"step":"PLAN", "content":"xyz"}
    OUTPUT - {"step":"OUTPUT", "content":"zyz"}
"""
message_history = [{
    "role":"system",
    "content": SYSTEM_PROMT,
}]

user_input = input("Ask your query: ")
message_history.append({    "role":"user",
    "content": user_input
})

while True:
    response = client.chat.completions.create(
        response_format={"type":"json_object"},
        model = "gpt-4o-mini",
        messages = message_history
    );

    raw_response = response.choices[0].message.content
    message_history.append({
        "role":"assistant",
        "content": raw_response
    })

    parsed_response = json.loads(raw_response)
    if parsed_response["step"] == "OUTPUT":
        print("Final output: ", parsed_response["content"])
        break
    elif parsed_response["step"] == "PLAN":
        print("Plan: ", parsed_response["content"])
        continue
    else:
        print("User Query: ", parsed_response["content"])
        continue



print(response.choices[0].message.content)