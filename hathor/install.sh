#!/bin/bash

apt update && apt upgrade -y

# Install hathor-core
apt install -y git curl vim
apt install -y build-essential liblz4-dev libbz2-dev libsnappy-dev librocksdb-dev

# Install Python dependencies
apt-get -yq install \
    build-essential \
    pkg-config \
    autoconf-archive \
    ccache \
    gdb \
    lcov \
    libb2-dev \
    libbz2-dev \
    libffi-dev \
    libgdbm-dev \
    libgdbm-compat-dev \
    liblzma-dev \
    libncurses5-dev \
    libreadline6-dev \
    libsqlite3-dev \
    libssl-dev \
    lzma \
    lzma-dev \
    strace \
    tk-dev \
    uuid-dev \
    xvfb \
    zlib1g-dev

# Install pyenv
curl https://pyenv.run | bash

echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
echo 'eval "$(pyenv init -)"' >> ~/.bashrc
echo 'eval "$(pyenv virtualenv-init -)"' >> ~/.bashrc
source ~/.bashrc
exec "$SHELL"

# Install Python 3.11.0
pyenv install 3.11.0
pyenv global 3.11.0

# Install Poetry and Atheris
pip install poetry

# hathor-core
cd home/
git clone https://github.com/HathorNetwork/hathor-core.git
cd hathor-core/

# Run hathor-core tests
poetry install
poetry add atheris

poetry run make check
poetry run make tests
