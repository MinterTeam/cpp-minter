#!/usr/bin/env bash

if [ ! -f "/usr/bin/g++" ]
then
    apt-get update
    apt-get install -y python python3 python3-pip gcc g++ gdb git make curl wget
fi

if [ ! -d "/tmp/pkgs" ]
then
    mkdir -p /tmp/pkgs
fi

# fetching cmake
CMAKE_VERS="3.14.5"
if [ ! -f "/tmp/pkgs/cmake.sh" ]
then
    wget -O /tmp/pkgs/cmake.sh https://cmake.org/files/v${CMAKE_VERS}/cmake-${CMAKE_VERS}-Linux-x86_64.sh
fi

if [ ! -f "/usr/bin/cmake" ]
then
    sh /tmp/pkgs/cmake.sh --skip-license --prefix=/usr
fi



