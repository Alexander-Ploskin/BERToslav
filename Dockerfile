FROM ubuntu:latest

RUN apt update && apt install -y \
    build-essential \
    curl \
    vim \
    nano \
    cmake

WORKDIR /app

COPY src /app/src
COPY model /app/model
