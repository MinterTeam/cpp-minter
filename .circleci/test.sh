#!/usr/bin/env bash

set -e

mkdir -p _build && cd _build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DWITH_TEST=On
cmake --build . --target minter-test
./bin/minter-test