import tiktoken

enc = tiktoken.encoding_for_model("gpt-3.5-turbo")

text = "Hello, how are you doing today? I hope you're having a great day!"
tokens = enc.encode(text)
print("Tokens:", tokens)

print("Decoded text:", enc.decode(tokens))