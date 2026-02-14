FROM ubuntu:jammy AS builder

ARG DEBIAN_FRONTEND=noninteractive
ARG SDL_REF=release-3.4.0

# Setup repos and keyrings
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        software-properties-common ca-certificates gnupg wget curl git file nano htop && \
    add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    mkdir -p /etc/apt/keyrings && \
    curl -fsSL https://apt.kitware.com/keys/kitware-archive-latest.asc \
        | gpg --dearmor -o /etc/apt/keyrings/kitware-archive-keyring.gpg && \
    echo "deb [signed-by=/etc/apt/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main" \
        > /etc/apt/sources.list.d/kitware.list && \
    apt-get update

# Install build tools and libraries
RUN apt-get install -y --no-install-recommends \
        build-essential ninja-build pkg-config sudo \
        gcc-13 g++-13 cmake \
        gnome-desktop-testing libasound2-dev libpulse-dev libaudio-dev \
        libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
        libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
        libxtst-dev libxkbcommon-dev libdrm-dev libgbm-dev \
        libgl1-mesa-dev libgles2-mesa-dev libegl1-mesa-dev \
        libdbus-1-dev libibus-1.0-dev libudev-dev \
        libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev && \
    rm -rf /var/lib/apt/lists/*

# Set default GCC compiler version
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 \
        --slave /usr/bin/g++ g++ /usr/bin/g++-13

# Build and install SDL3 from source
RUN git clone --depth 1 --branch ${SDL_REF} https://github.com/libsdl-org/SDL /tmp/SDL && \
    cmake -S /tmp/SDL -B /tmp/SDL/build \
          -DCMAKE_BUILD_TYPE=Release \
          -DSDL_SHARED=ON -DSDL_STATIC=OFF -DSDL_TEST=OFF \
          -G Ninja && \
    cmake --build /tmp/SDL/build -j$(nproc) && \
    cmake --install /tmp/SDL/build && \
    rm -rf /tmp/SDL

# Update linker 
RUN ldconfig

# Create vscode user
RUN useradd -m vscode \
    && echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers \
    && usermod -s /bin/bash vscode

USER vscode

WORKDIR /workspaces
