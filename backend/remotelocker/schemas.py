from pydantic import BaseModel


class UserCredentials(BaseModel):
    name: str
    password: str


class User(BaseModel):
    id: int
    name: str
    password: str
    admin: bool
    locker_id: int

    class Confg:
        from_attributes = True


class LockerUpdateData(BaseModel):
    username: str
    password: str
    locked: bool
    blocked: bool
    status: str | None
    name: str


class Locker(BaseModel):
    id: int
    name: str
    locked: bool
    blocked: bool
    status: str | None

    class config:
        from_attributes = True


class HTTPExceptionMessage(BaseModel):
    message: str


class HTTPExceptionSchema(BaseModel):
    detail: HTTPExceptionMessage


class PasswordSchema(BaseModel):
    password: str
