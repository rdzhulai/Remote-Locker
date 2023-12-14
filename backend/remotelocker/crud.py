from . import models, schemas
from sqlalchemy.orm import Session


def get_user(
    db: Session,
    credentials: schemas.UserCredentials,
) -> models.User | None:
    return (
        db.query(models.User)
        .filter(
            models.User.name == credentials.name
            and models.User.password == credentials.password
        )
        .first()
    )


def update_locker(
    db: Session,
    updatedLocker: schemas.Locker,
) -> models.Locker | None:
    locker = (
        db.query(models.Locker).filter(models.Locker.id == updatedLocker.id).first()
    )
    if locker is None:
        return None
    if (
        locker.name == updatedLocker.name
        and locker.locked == updatedLocker.locked
        and locker.blocked == updatedLocker.blocked
        and locker.status == updatedLocker.status
    ):
        return locker

    locker.name = updatedLocker.name
    locker.locked = updatedLocker.locked
    locker.blocked = updatedLocker.blocked
    locker.status = updatedLocker.status

    db.commit()
    db.refresh(locker)

    return locker


def get_locker(
    db: Session,
    id: int,
) -> models.Locker | None:
    return db.query(models.Locker).filter(models.Locker.id == id).first()
