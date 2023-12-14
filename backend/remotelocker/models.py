from sqlalchemy import Boolean, Column, ForeignKey, Integer, String
from .database import Base


class Locker(Base):
    __tablename__ = "lockers"
    id = Column("id", Integer, primary_key=True)
    name = Column("name", String(50), nullable=False, unique=True)
    locked = Column("locked", Boolean, nullable=False)
    blocked = Column("blocked", Boolean, nullable=False)
    status = Column("status", String(32), nullable=True)


class User(Base):
    __tablename__ = "users"
    id = Column("id", Integer, primary_key=True)
    name = Column("name", String(50), nullable=False, unique=True)
    password = Column("password", String(16), nullable=False)
    admin = Column("admin", Boolean, nullable=False)
    locker_id = Column(Integer, ForeignKey("lockers.id"), nullable=False)
