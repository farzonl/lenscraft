FROM ubuntu:16.04
WORKDIR /src
COPY . /src
RUN apt update && \
    apt install -y build-essential git wget unzip cmake pkg-config gcc-multilib libopencv-dev libglm-dev libglfw-dev libglew-dev

RUN make