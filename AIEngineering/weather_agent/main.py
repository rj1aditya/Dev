from openai import OpenAI
from dotenv import load_dotenv
import requests

load_dotenv()


client = OpenAI()


def main():
    query = input(">>")
    response = client.chat.completions.create(
        model="gpt-4o",
        messages = [
            {
            "role": "user",
            "content": query
            }
        ]
    )
    print(response.choices[0].message.content)

main()
#print(get_weather("New York"))