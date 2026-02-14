FROM ubuntu:jammy AS builder

ARG DEBIAN_FRONTEND=noninteractive
ARG SDL_REF=release-3.4.0

# Base build dependencies & tools
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates gnupg wget curl git file nano htop \
        build-essential ninja-build pkg-config \
        software-properties-common sudo && \
    \
    # Add toolchain + Kitware repos
    add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    mkdir -p /etc/apt/keyrings && \
    curl -fsSL https://apt.kitware.com/keys/kitware-archive-latest.asc \
      | gpg --dearmor -o /etc/apt/keyrings/kitware-archive-keyring.gpg && \
    echo "deb [signed-by=/etc/apt/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main" \
      > /etc/apt/sources.list.d/kitware.list && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
        gcc-13 g++-13 cmake \
        gnome-desktop-testing libasound2-dev libpulse-dev libaudio-dev \
        libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
        libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
        libxtst-dev libxkbcommon-dev libdrm-dev libgbm-dev \
        libgl1-mesa-dev libgles2-mesa-dev libegl1-mesa-dev \
        libdbus-1-dev libibus-1.0-dev libudev-dev \
        libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev && \
    \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 \
        --slave /usr/bin/g++ g++ /usr/bin/g++-13 && \
    rm -rf /var/lib/apt/lists/*

# -------------------------
# Build SDL3 from source
# -------------------------
RUN git clone --depth 1 --branch ${SDL_REF} https://github.com/libsdl-org/SDL /tmp/SDL && \
    cmake -S /tmp/SDL -B /tmp/SDL/build \
          -DCMAKE_BUILD_TYPE=Release \
          -DSDL_SHARED=ON -DSDL_STATIC=OFF -DSDL_TEST=OFF \
          -G Ninja && \
    cmake --build /tmp/SDL/build -j && \
    cmake --install /tmp/SDL/build && \
    rm -rf /tmp/SDL && \
    ldconfig
