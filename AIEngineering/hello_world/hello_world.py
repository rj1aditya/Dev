from openai import OpenAI
client = OpenAI()

response = client.chat.completions.create(
    model="gpt-4o-mini",
    messages = [
        #{"role": "system", "content": "You are a mathematician experts who answer only and only math questions."},
        {"role": "user", "content": "hello there!."}
    ]
)

print(response.choices[0].message.content)