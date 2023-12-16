from fastapi import FastAPI, Depends, HTTPException, status

from . import schemas, crud
from .database import engine, Session
from .models import Base
from .listeners import *
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI()
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

Base.metadata.create_all(bind=engine)


def get_db():
    db = Session()
    try:
        yield db
    finally:
        db.close()


@app.post(
    "/signin",
    response_model=schemas.User,
    responses={
        404: {
            "model": schemas.HTTPExceptionSchema,
            "description": "Invalid password",
        }
    },
)
def sign_in(credentials: schemas.UserCredentials, db: Session = Depends(get_db)):
    user = crud.get_user(db, credentials)
    if user is None:
        raise HTTPException(
            status.HTTP_404_NOT_FOUND,
            detail={
                "message": f"User {credentials.name} \
                    and password {credentials.password} does not exist"
            },
        )
    return user


@app.get(
    "/lockers/{id}",
    response_model=schemas.Locker,
    responses={
        404: {
            "model": schemas.HTTPExceptionSchema,
            "description": "Invalid ID",
        }
    },
)
def get_locker(id: int, db: Session = Depends(get_db)):
    locker = crud.get_locker(db, id)
    if locker is None:
        raise HTTPException(
            status.HTTP_404_NOT_FOUND,
            detail={"message": f"Locker with ID {id} does not exist"},
        )
    return locker


@app.post(
    "/lockers/{id}",
    response_model=schemas.Locker,
    responses={
        404: {
            "model": schemas.HTTPExceptionSchema,
            "description": "Invalid ID",
        },
        401: {
            "model": schemas.HTTPExceptionSchema,
            "descritpion": "Insufficient Rights",
        },
    },
)
def update_locker(
    id: int, data: schemas.LockerUpdateData, db: Session = Depends(get_db)
):
    credentials = {
        "name": data.username,
        "password": data.password,
    }
    user = crud.get_user(
        db,
        schemas.UserCredentials(**credentials),
    )
    if user is None:
        raise HTTPException(
            status.HTTP_404_NOT_FOUND,
            detail={
                "message": f"User {data.username} with password {data.password} does not exist"
            },
        )
    if not (user.admin and user.locker_id == id):  # TODO Add more exceptions
        raise HTTPException(
            status.HTTP_401_UNAUTHORIZED,
            detail={"message": f"User {data.username} does not have admin rights"},
        )
    locker = crud.update_locker(
        db,
        schemas.Locker(
            id=id,
            name=data.name,
            blocked=data.blocked,
            locked=data.locked,
            status=data.status,
        ),
    )
    if locker is None:
        raise HTTPException(
            status.HTTP_404_NOT_FOUND,
            detail={"message": f"Locker with ID {id} does not exist"},
        )

    return locker
