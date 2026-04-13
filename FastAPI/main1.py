#local data stored here

from fastapi import FastAPI
from models import Product
from database import SessionLocal

app = FastAPI()
products = [
    Product(id=1, name="Laptop", description="A high-performance laptop", price=999.99, quantity=10),
    Product(id=2, name="Smartphone", description="A latest model smartphone", price=499.99, quantity=15),
    Product(id=3, name="Headphones", description="Noise-cancelling headphones", price=199.99, quantity=20)
]
@app.get("/")
def greet():
    return "Welcome to Aditya's Tech lab!"

@app.get("/products")
def get_all_products():
    return products


@app.get("/product")
def get_product():
    return products[0]

@app.get("/product/{product_id}")
def get_product_by_id(product_id: int):
    for product in products:
        if product.id == product_id:
            return product
    return {"error": "Product not found"}


@app.post("/product")
def add_product(product: Product):
    products.append(product)
    return {"message": "Product added successfully", "product": product}



@app.put("/product")
def update_product(id: int, product: Product):
    for i in range(len(products)):
        if products[i].id == id:
            products[i] = product
            return {"message": "Product updated successfully", "product": product}
    return {"error": "Product not found"}

@app.delete("/product")
def delete_product(id:int):
    for i in range(len(products)):
        if products[i].id == id:
            deleted_product = products.pop(i) #alternative: del products[i]
            return {"message": "Product deleted successfully", "product": deleted_product}
    return {"error": "Product not found"}
