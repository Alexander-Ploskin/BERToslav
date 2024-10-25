FROM ubuntu:latest

RUN apt update && apt update -y

WORKDIR /app

COPY src model data ./
