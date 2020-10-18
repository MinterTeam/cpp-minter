#!/usr/bin/env bash

if [ ! -f "/usr/bin/g++" ]; then
  sudo apt-get update
  sudo apt-get install -y python python3 python3-pip gcc g++ gdb git make curl wget
fi

if [ ! -d "/tmp/pkgs" ]; then
  mkdir -p /tmp/pkgs
fi

# fetching cmake

if [ ! -f "/usr/bin/cmake" ]; then
  if [ ! -f "/tmp/pkgs/cmake.sh" ]; then
    wget -O /tmp/pkgs/cmake.sh https://github.com/Kitware/CMake/releases/download/v3.14.5/cmake-3.14.5-Linux-x86_64.sh
  fi
  sh /tmp/pkgs/cmake.sh --skip-license --prefix=/usr
fi
