FROM ubuntu:26.04

RUN apt update && apt install -y \
    g++ \
    clang \
    gdb \
    make \
    nasm \
    binutils-x86-64-linux-gnu \
    ghc \
    cabal-install \
    curl \
    git \
    python3 \
    python3-pip

# Rust setup
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# Install competitive programming tools
# RUN pip install online-judge-tools verification-helper