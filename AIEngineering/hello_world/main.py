from openai import OpenAI
client = OpenAI()
# setx OPENAI_API_KEY "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"
response = client.chat.completions.create(
    model="gpt-4o-mini",
    messages = [
        {"role": "system", "content": "You are a mathematician experts who answer only and only math questions."},
        {"role": "user", "content": "Hey there! write me a addition program in python."}
    ]
)

print(response.choices[0].message.content)