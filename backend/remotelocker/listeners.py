from .models import User, Locker
from sqlalchemy.event import listens_for
from sqlalchemy.sql import insert


@listens_for(Locker.__table__, "after_create")
def receive_after_create(target, connection, **kw):
    connection.execute(
        insert(Locker.__table__).values(
            name="Locker", locked=False, blocked=False, status=None
        )
    )


@listens_for(User.__table__, "after_create")
def receive_after_create(target, connection, **kw):
    connection.execute(
        insert(User.__table__).values(
            name="Admin", password="0000", admin=True, locker_id=1
        )
    )
