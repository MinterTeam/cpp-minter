# cpp-minter
Minter C++ SDK: build and sign any transaction, generate mnemonic with private and public key

[![CircleCI](https://circleci.com/gh/MinterTeam/cpp-minter/tree/master.svg?style=svg)](https://circleci.com/gh/MinterTeam/cpp-minter/tree/master)
[![Download](https://api.bintray.com/packages/minterteam/minter/minter_tx%3Aminter/images/download.svg) ](https://bintray.com/minterteam/minter/minter_tx%3Aminter/_latestVersion)

## Features:
 * Transaction Builder
 * Signing any supported transaction
 * Working with private and public keys
 * Generating mnemonic (with low-predictable [PCG](http://www.pcg-random.org/) random generator)

## Requirements:
 * GCC 4.9+/CLang/AppleClang
 * Boost (Multiprecision) 1.69.0 (if using raw library without **Conan**)
 * CMake 3.10+
 * Python with PIP
 * Conan
 
## Conan setup:
```bash
conan remote add scatter https://api.bintray.com/conan/edwardstock/scatter
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add minter https://api.bintray.com/conan/minterteam/minter
```

See conan [docs](https://docs.conan.io/en/latest/getting_started.html)

## Build with conan
You can just add to your conanfile.txt dependency:

`minter_tx/0.1.0@minter/latest`

CMakeLists.txt
```cmake
add_executable(my_program my_program.cpp)
target_link_libraries(my_program CONAN_PKG::minter_tx)
```

## Build system-wide:
```bash
git clone --recursive https://github.com/MinterTeam/cpp-minter.git
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DWITH_TEST=On -DCMAKE_INSTALL_PREFIX=/usr
cmake --build . -- -j4
cmake --build . --target install
```

Then in your build script add lib:
```bash
g++ my_program.cpp -lminter_tx
```

## Examples:
See here [link](examples)

