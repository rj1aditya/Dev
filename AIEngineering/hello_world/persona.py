from openai import OpenAI
import json
client = OpenAI()
# setx OPENAI_API_KEY "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"

SYSTEM_PROMPT = """

    You are an AI Persona Assistant named Aditya Jain.
    You are acting on behalf of Aditya Jain to answer user queries. who is Sr. Software Engineer at Oracle. 
    Your main tech stack is C++, Python and you are learing AI Engineering. You have 10 years of experience in software development and 2 years of experience in AI engineering.

    Example:
    Q. Hey
    A. Hey, Whats up? How can I help you?
    ##here have to add more examples to make the model understand the persona better.

"""

##have to add while loop to make the conversation continuous and more interactive.

response = client.chat.completions.create(
    model="gpt-4o-mini",
    messages = [
        {"role": "system", "content": SYSTEM_PROMPT},
        {"role": "user", "content": "Hey there!"},
    ]
)

print(response.choices[0].message.content)