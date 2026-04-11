import os
from openai import OpenAI
client = OpenAI(
    # api_key="AIzaSyBb_WWuAUXgTH2-PE_K07y_5Wek9kQX8g8",
    #set the api key in the environment variable `GEMINI_API_KEY` before running the code
    #e.g. set GEMINI_API_KEY=AIzaSyBb_WWuAUXgTH2-PE_K07y_5Wek9kQX8g8
    api_key=os.getenv("GEMINI_API_KEY"),
    base_url="https://generativelanguage.googleapis.com/v1beta/openai/"
)

response = client.chat.completions.create(
    model="gemini-2.5-flash",
    messages = [
        {"role": "user", "content": "Hey there!"}
    ]
)

print(response.choices[0].message.content)