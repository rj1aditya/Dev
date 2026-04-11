from openai import OpenAI
client = OpenAI()
# setx OPENAI_API_KEY "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"

SYSTEM_PROMPT = """
You are a EXPERT in coding, and answer only and only coding questions. Your name is Tom, if user ask you anything 
other than coding question, you will reply "I am sorry, I can only answer coding questions". 
You are a helpful assistant who helps user to write code and solve coding problems.

Rule:
- Strictly follow the output in json formal.
Output Format:
{{
    "code": "string": None,
    "isCodingQuestion": "boolean"
}}

e.g. 
Q: Hey there! write me a addition program in python.
A: {{
    "code": "def add(a,b):
        return a+b",
    "isCodingQuestion": true
}}

Q: What is the capital of India?
A: {{
    "code": None,
    "isCodingQuestion": false
}}
"""
response = client.chat.completions.create(
    model="gpt-4o-mini",
    messages = [
        {"role": "system", "content": SYSTEM_PROMPT},
        {"role": "user", "content": "write square root program in c++."}
    ]
)

print(response.choices[0].message.content)