from ollama import Client
from  fastapi import FastAPI, Body

app = FastAPI()
client = Client(
    host = "http://localhost:11434",#this is the default host and port for ollama, you can change it if you have configured it differently
)


@app.post("/chat")
def chat(
        message: str = Body(..., description="The message to send to the model")
):
    response = client.chat(
        model="gemma:2b",#replace with your actual model name
        messages=[{"role": "user", "content": message}]
    )
    return {"response": response.choices[0].message.content}

#how to run
#b4 running in the venv 
#install the required libraries
#pip install openai ollama fastapi[standard] uvicorn 
#fastapi dev ollama_openai.py --reload