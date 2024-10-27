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

RUN python3 -m venv venv

RUN --mount=type=cache,target=/root/.cache/pip ./venv/bin/pip install -r /app/model/requirements.txt

COPY Makefile.build Makefile.build
COPY Makefile.run Makefile.run

RUN make -f Makefile.build all

ENTRYPOINT ["make", "-f", "Makefile.run"]
