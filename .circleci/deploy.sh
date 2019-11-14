#!/usr/bin/env bash
set -e
set -x
VERS=`git rev-parse --short HEAD`
if [ -f "version" ]
then
    VERS=`cat version | tr -d "\n"`
fi

if [ -f "../version" ]
then
    VERS=`cat ../version | tr -d "\n"`
fi

if [ "${1}" != "" ]
then
    VERS=${1}
fi

sysname=$(uname)

stdlibname="libstdc++"
if [ "${sysname}" == "Darwin" ]
then
  stdlibname="libc++"
fi

## Deploy in latest channel
if [ "${sysname}" == "Linux" ]
then
  CONAN_LOCAL=1 conan create . minter/latest -s compiler.libcxx=${stdlibname}11 -s build_type=Debug --build=missing
  CONAN_LOCAL=1 conan create .  minter/latest -s compiler.libcxx=${stdlibname}11 -s build_type=Release --build=missing
fi

## Deploy in latest channel
CONAN_LOCAL=1 conan create . minter/latest -s compiler.libcxx=${stdlibname} -s build_type=Debug --build=missing
CONAN_LOCAL=1 conan create . minter/latest -s compiler.libcxx=${stdlibname} -s build_type=Release --build=missing -s build_type=Release

if [ "${NOUPLOAD}" != "1" ]
then
	CONAN_LOCAL=1 conan upload minter_tx/${VERS}@minter/latest --all -r=minter
fi
