from fastapi import FastAPI

app = FastAPI()


@app.get("/")
async def hello():
    return {"message": "Hello from FastAPI!"}
