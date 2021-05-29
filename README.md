# cpp-minter
Minter C++ SDK: build and sign any transaction, generate mnemonic with private and public key

[![CircleCI](https://circleci.com/gh/MinterTeam/cpp-minter/tree/master.svg?style=svg)](https://circleci.com/gh/MinterTeam/cpp-minter/tree/master)
[![Download](https://api.bintray.com/packages/minterteam/minter/minter_tx%3Aminter/images/download.svg) ](https://bintray.com/minterteam/minter/minter_tx%3Aminter/_latestVersion)

## Features:

* Transaction Builder
* Signing any supported transaction
* Working with private and public keys
* Generating mnemonic (with low-predictable [PCG](http://www.pcg-random.org/) random generator)

## Download

### RPM (redhat-based)

Supported distributions:

- centos 7, 8
- fedora 32-34

Steps:

* Create `edwardstock.repo` file inside `/etc/yum.repos.d`
* Add below to this file

```ini
[edwardstock]
name=edwardstock
baseurl=https://edwardstock.jfrog.io/artifactory/rhel/[centos or fedora]/$releasever/$basearch
enabled=1
gpgcheck=0
gpgkey=https://edwardstock.jfrog.io/artifactory/rhel/[centos or fedora]/$releasever/$basearch/repodata/repomd.xml.key
repo_gpgcheck=1
```

* Update repository `yum -y update` or `dnf update`
* Install `yum install minter_tx-devel` or `dnf install minter_tx-devel`

### Debian & Ubuntu (-based)

Supported distributions:

- debian: jessie, stretch, buster
- ubuntu: xenial, bionic, focal, groovy

If you using other distribution, just find what your system based on, for example, latest Kali-Rolling is a Debian
Buster. In this case just change distribution name in `/etc/apt/sources.list` by yourself.

```bash
echo "deb https://edwardstock.jfrog.io/artifactory/debian $(lsb_release -c -s) main" | tee -a /etc/apt/sources.list
curl -s https://edwardstock.jfrog.io/artifactory/api/gpg/key/public | apt-key add -
apt update && apt install libminter_tx-dev
```

If you got error **lsb_release: command not found** then just install `apt install lsb-release`. It can happened on
naked Docker images.

<br/><br/>
After installing package from repository, you can use cmake-find module to find library:

```cmake
find_package(minter_tx 2.0.1 REQUIRED)
target_link_libraries(MY_PROJECT minter_tx::minter_tx)
```

## Using via Conan (very useful dependency manager for C++)

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
conan remote add minter https://minter.jfrog.io/artifactory/api/conan/conan
conan remote add edwardstock https://edwardstock.jfrog.io/artifactory/api/conan/conan
```

For more information, see official [docs](https://docs.conan.io/en/latest/getting_started.html)

<br/>

**Add to project**

You can just add to your conanfile.txt dependency:

`minter_tx/2.0.1@minter/latest`

CMakeLists.txt

```cmake
add_executable(my_program my_program.cpp)
target_link_libraries(my_program CONAN_PKG::minter_tx)
```

See [guide](https://docs.conan.io/en/latest/howtos/cmake_launch.html) how to use conan with cmake or just research my
CMakeLists.txt [here](https://github.com/MinterTeam/cpp-minter/blob/master/examples/minter-pretty/CMakeLists.txt)

## Build library:

**Build using conan dependencies:**<br/>
In this case we will build library and install into system /usr prefix: /usr/lib/libminter_tx.a and
/usr/include/minter/**headers here**. Just change `-DCMAKE_INSTALL_PREFIX=` value if you want to choose another place.

```bash
git clone --recursive https://github.com/MinterTeam/cpp-minter.git
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make -j4
make install
```

**Build using dependencies resolved by your favorite package manager:**

First of all, don't forget to add repository (see [**download**](#download) section)

For debian/ubuntu you have to install packages:

```bash
apt-get install libtoolboxpp-dev libsecp256k1_java-dev libbigmath-dev libbip3x-dev
```

For Centos or Fedora:

```bash
yum install toolboxpp-devel secp256k1_java-devel bigmath-devel bip3x-devel
```

Last step: build library

```bash
mkdir -p _build && cd _build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make -j4
make install
```

Then just link library:

```bash
g++ my_program.cpp -lminter_tx
```

## Build with Microsoft compiler

**! This sections deprecated and needs to be updated. Soon i'll do this. !**

Before build, you should install Visual Studio 2019 (i'm just tested only on this version), at least Community version
Also building can be only completed WITH conan. If you don't want it, you have to manually find MPIR and mpdecimal and
build it (or find pre-built binaries). In future, i'll add all required dependencies in pre-built format.

**Attention**! For now, it's pretty recommended to build static Windows library, because DLL have some unresolved
issues.

Step 2:

- **Git** for Windows
- **CMake** for Windows

Step 3:
- Add binaries to system PATH

```cmd
git clone --recursive https://github.com/MinterTeam/cpp-minter.git
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_CONAN=Off -DENABLE_SHARED=Off
cmake --build . --config Debug
```

Then find **minter_tx.lib** and **minter_tx.pdb** in **Debug** folder

To build other configurations, just change `--config Debug` to one of: Release, RelWithDebInfo, MinSizeRel

## Examples:

#### Simple example how to use transaction-builder

[link](examples/tx-send/main.cpp)

Also don't forget about tests, it's quite informative: [link](tests)

#### Bucket mnemonic generator

[link](examples/generate/README.md)

#### Pretty address generator

[link](examples/minter-pretty/README.md)

## License

[MIT License](LICENSE)

Copyright (c) 2020 Minter Author: [Eduard Maximovich](https://github.com/edwardstock)

