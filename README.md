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
 * GCC 5+/Clang/AppleClang
 * CMake 3.10+
 * Python with PIP
 * Conan
 
## Install Conan (dependency manager for C++)

**Debian**
```bash
apt-get install python3 python3-pip
pip3 install setuptools -U
pip3 install conan
```

**Centos**
```bash
yum install python pip
pip install --upgrade pip
pip install setuptools -U
pip install conan
```

**Fedora (or like)**
```bash
dnf install python3 python3-pip
pip3 install setuptools -U
pip3 install conan
```

**Setup repositories**

```bash
conan remote add scatter https://api.bintray.com/conan/edwardstock/scatter
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add minter https://api.bintray.com/conan/minterteam/minter
```

For more information, see official [docs](https://docs.conan.io/en/latest/getting_started.html)

## Use as conan dependency without manually build
You can just add to your conanfile.txt dependency:

`minter_tx/0.6.1@minter/latest`

CMakeLists.txt
```cmake
add_executable(my_program my_program.cpp)
target_link_libraries(my_program CONAN_PKG::minter_tx)
```

See [guide](https://docs.conan.io/en/latest/howtos/cmake_launch.html) how to use conan with cmake

## Build library:
```bash
git clone --recursive https://github.com/MinterTeam/cpp-minter.git
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DMINTER_TX_TEST=On -DCMAKE_INSTALL_PREFIX=/usr
cmake --build . -- -j4
cmake --build . --target install
```

Then in your build script add lib:
```bash
g++ my_program.cpp -lminter_tx
```

## Build WITHOUT Conan
```bash
git clone --recursive https://github.com/MinterTeam/cpp-minter.git
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_CONAN=Off \
    -DMINTER_TX_TEST=On \
    -DBOOST_ROOT=/path/to/boost \
    -DCMAKE_INSTALL_PREFIX=/path/to/install/dir

cmake --build . -- -j4
cmake --build . --target install
```

## Build with Microsoft compiler (without Conan)
Before build, you should install Visual Studio 2019, at least Community version

**Attention**! For now, it's pretty recommended to build static Windows library, because DLL have some unresolved issues.

Step 2:
- **Git** for Windows
- **CMake** for Windows
- **Boost 1.70.0+** library. You can build it by yourself, download from official repo or download my [pre-built archive](https://drive.google.com/file/d/1u8bXeNayY_9ARtsqQKgLqqxRV0BPhrCf/view?usp=sharing)

Step 3:
- Add binaries to system PATH

```cmd
git clone --recursive https://github.com/MinterTeam/cpp-minter.git
mkdir build
cd build
cmake .. -DBOOST_ROOT="C:\boost" -DCMAKE_BUILD_TYPE=Debug -DENABLE_CONAN=Off -DENABLE_SHARED=Off
cmake --build . --config Debug
```
Then find **minter_tx.lib** and **minter_tx.pdb** in **Debug** folder

To build other configurations, just change `--config Debug` to one of: Release, RelWithDebInfo, MinSizeRel

## Examples:
See here [link](examples)

#### Bucket mnemonic generator
```bash
git clone --recursive https://github.com/MinterTeam/cpp-minter.git
cd examples/generate
mkdir build && cd build
CONAN_LOCAL=1 cmake .. -DCMAKE_BUILD_TYPE=Debug
CONAN_LOCAL=1 cmake --build . -- -j4
```

Run:
```bash
./bin/minter-gen
```

Or run with simple argument:
```bash
./bin/minter-gen 300
```
Generates 300 mnemonics and print it to stdout

#### Pretty address generator
[link](examples/minter-pretty/README.md)

## License
[MIT License](LICENSE)

Copyright (c) 2019 Minter
Author: [Eduard Maximovich](https://github.com/edwardstock)

