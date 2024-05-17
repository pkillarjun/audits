# -----------------------------------------------------------------------------
# Builder image for C binaries and Magma proto files
# -----------------------------------------------------------------------------
ARG CPU_ARCH=x86_64
ARG DEB_PORT=amd64
ARG OS_DIST=ubuntu
ARG OS_RELEASE=focal
ARG EXTRA_REPO=https://linuxfoundation.jfrog.io/artifactory/magma-packages-test
ARG CLANG_VERSION=3.8
ARG FEATURES=mme_oai

FROM $OS_DIST:$OS_RELEASE AS builder
ARG CPU_ARCH
ARG DEB_PORT
ARG OS_DIST
ARG OS_RELEASE
ARG EXTRA_REPO
ARG CLANG_VERSION

ENV MAGMA_ROOT /magma
ENV C_BUILD /build/c
ENV OAI_BUILD $C_BUILD/oai
ENV TZ=Europe/Paris

ENV CCACHE_DIR ${MAGMA_ROOT}/.cache/gateway/ccache
ENV MAGMA_DEV_MODE 0
ENV XDG_CACHE_HOME ${MAGMA_ROOT}/.cache

RUN apt-get update && \
  # Setup necessary tools for adding the Magma repository
  apt-get install -y apt-utils software-properties-common apt-transport-https gnupg wget && \
  # Download Bazel
  wget -P /usr/sbin --progress=dot:giga https://github.com/bazelbuild/bazelisk/releases/download/v1.10.0/bazelisk-linux-"${DEB_PORT}" && \
  chmod +x /usr/sbin/bazelisk-linux-"${DEB_PORT}" && \
  ln -s /usr/sbin/bazelisk-linux-"${DEB_PORT}" /usr/sbin/bazel

# Install dependencies required for building
RUN apt-get update && apt-get install -y \
  autoconf \
  autogen \
  build-essential \
  ccache \
  check \
  cmake \
  curl \
  git \
  libboost-chrono-dev \
  libboost-context-dev \
  libboost-program-options-dev \
  libboost-filesystem-dev \
  libboost-regex-dev \
  libc++-dev \
  libconfig-dev \
  libcurl4-openssl-dev \
  libczmq-dev \
  libdouble-conversion-dev \
  libgflags-dev \
  libgmp3-dev \
  libgoogle-glog-dev \
  libmnl-dev \
  libpcap-dev \
  libprotoc-dev \
  libsctp-dev \
  libsqlite3-dev \
  libssl-dev \
  libtspi-dev \
  libtool \
  libxml2-dev \
  libxslt-dev \
  libyaml-cpp-dev \
  ninja-build \
  nlohmann-json3-dev \
  pkg-config \
  protobuf-compiler \
  python3-pip \
  sudo \
  unzip \
  uuid-dev

# Add the magma apt repo
COPY keys/linux_foundation_registry_key.asc /etc/apt/trusted.gpg.d/magma.asc
RUN echo "deb https://linuxfoundation.jfrog.io/artifactory/magma-packages-test focal-ci main" > /etc/apt/sources.list.d/magma.list
RUN apt-get update
RUN apt-get install -y grpc-dev
RUN apt-get install -y libfolly-dev
RUN apt-get install -y liblfds710
RUN apt-get install -y magma-cpp-redis
RUN apt-get install -y magma-libfluid
RUN apt-get install -y oai-asn1c
RUN apt-get install -y oai-freediameter
RUN apt-get install -y oai-gnutls
RUN apt-get install -y oai-nettle
RUN apt-get install -y prometheus-cpp-dev
RUN apt-get update && apt-get install -y \
  grpc-dev \
  libfolly-dev \
  liblfds710 \
  magma-cpp-redis \
  magma-libfluid \
  oai-asn1c \
  oai-freediameter \
  oai-gnutls \
  oai-nettle \
  prometheus-cpp-dev

# Download Extra
RUN git clone --depth=1 https://github.com/magma/magma.git
RUN git clone --depth=1 https://github.com/AFLplusplus/AFLplusplus.git

ENV MAGMA_ROOT /magma
WORKDIR /magma

RUN echo "export MAGMA_ROOT=/magma" >> /root/.bashrc
RUN echo "export C_BUILD=/build/c" >> /root/.bashrc
RUN echo "export OAI_BUILD=$C_BUILD/oai" >> /root/.bashrc
RUN echo "export TZ=Europe/Paris" >> /root/.bashrc
RUN echo "export CCACHE_DIR=${MAGMA_ROOT}/.cache/gateway/ccache" >> /root/.bashrc
RUN echo "export MAGMA_DEV_MODE=0" >> /root/.bashrc
RUN echo "export XDG_CACHE_HOME=${MAGMA_ROOT}/.cache" >> /root/.bashrc

# Build external dependencies first. This will help not rebuilt all dependencies triggered by Magma changes.
RUN bazel build \
  @com_github_grpc_grpc//:grpc++ \
  @com_google_protobuf//:protobuf \
  @prometheus_cpp//:prometheus-cpp \
  @yaml-cpp//:yaml-cpp \
  @github_nlohmann_json//:json \
  @sentry_native//:sentry

RUN bazel build --dynamic_mode=off \
  //lte/gateway/c/sctpd/src:sctpd \
  //lte/gateway/c/connection_tracker/src:connectiond \
  //lte/gateway/c/li_agent/src:liagentd \
  //lte/gateway/c/session_manager:sessiond \
  //lte/gateway/c/core:agw_of

# Test-fuzzing
RUN apt-get install -y libfdcore6
RUN bazel build //:bazel-diff

# Clang
RUN apt-get install -y llvm llvm-dev llvm-runtime
RUN apt-get install -y clang libclang-dev clangd
RUN apt-get install -y libfuzzer-10-dev
RUN apt-get install -y libc++-dev libc++abi-dev
RUN echo "export CC=clang" >> /root/.bashrc
RUN echo "export CXX=clang++" >> /root/.bashrc

# Patch
COPY patch/amf_config.hpp.patch amf_config.hpp.patch
RUN patch -d ./lte/gateway/c/core/oai/include/ < amf_config.hpp.patch

COPY patch/test_auth_service_client.cpp.patch test_auth_service_client.cpp.patch
RUN patch -d ./lte/gateway/c/core/oai/test/n11/ < test_auth_service_client.cpp.patch

#Script
COPY build.sh build.sh
COPY fuzzing/ ./lte/gateway/c/core/oai/fuzzing/
