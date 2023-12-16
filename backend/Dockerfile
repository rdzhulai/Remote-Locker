FROM python:3.10-slim-bullseye

WORKDIR /app

COPY requirements.txt .

RUN pip3 install --no-cache-dir -r requirements.txt

COPY remotelocker ./remotelocker

EXPOSE 8000

CMD [ "uvicorn", "remotelocker.main:app", "--host", "0.0.0.0" ]