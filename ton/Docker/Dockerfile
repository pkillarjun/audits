FROM ubuntu:22.04

RUN apt-get update
RUN apt-get -y upgrade
RUN apt-get install -y git cmake zlib1g-dev libssl-dev
RUN apt-get install -y lcov gdb cmake-curses-gui vim
RUN apt-get install -y clang llvm-dev libclang-14-dev libfuzzer-14-dev libc++-14-dev libc++abi-14-dev

WORKDIR /root/
RUN git clone https://github.com/ton-blockchain/ton.git
RUN git clone --depth 1 https://github.com/AFLplusplus/AFLplusplus.git

WORKDIR /root/ton/
RUN git submodule update --init --depth 1 third-party/crc32c
RUN git submodule update --init --depth 1 third-party/rocksdb

WORKDIR /root/
COPY build.sh build.sh
COPY patch/ patch/
