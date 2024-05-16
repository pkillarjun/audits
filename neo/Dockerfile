FROM ubuntu:18.04

# Base
RUN apt-get update
RUN apt-get install -y screen libleveldb-dev sqlite3 libsqlite3-dev libunwind8-dev
RUN apt-get install -y gcc make wget git vim clang llvm

# DotNet
RUN wget https://packages.microsoft.com/config/ubuntu/18.04/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
RUN dpkg -i packages-microsoft-prod.deb
RUN rm packages-microsoft-prod.deb
RUN apt-get update && apt-get install -y dotnet-sdk-7.0 aspnetcore-runtime-7.0 dotnet-runtime-7.0
RUN apt-get install -y powershell

# Fuzzing
RUN wget https://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz
RUN git clone --depth=1 https://github.com/Metalnem/sharpfuzz.git
RUN git clone --depth=1 https://github.com/AFLplusplus/AFLplusplus.git

RUN dotnet tool install --global SharpFuzz.CommandLine
RUN echo 'export PATH="${PATH}:/root/.dotnet/tools"' >> ~/.bashrc

# Neo
RUN git clone --depth=1 https://github.com/neo-project/neo.git
RUN git clone --depth=1 https://github.com/neo-project/neo-vm.git

# Copy
COPY neo-fuzz    neo-fuzz
COPY neo-vm-fuzz neo-vm-fuzz

# AFL
RUN tar -xvf afl-latest.tgz && cd afl-2.52b/ && make install && cd ../

# AFL++
RUN cd AFLplusplus/ && make && make install && cd ../
