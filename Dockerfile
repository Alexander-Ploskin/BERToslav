FROM ubuntu:latest

RUN apt update && apt install -y \
    build-essential \
    curl \
    vim \
    nano \
    cmake \
    python3 \
    python3-pip \
    python3-venv

WORKDIR /app

COPY src /app/src
COPY model /app/model

RUN cd src && make all

ENTRYPOINT [ "make all" ]
