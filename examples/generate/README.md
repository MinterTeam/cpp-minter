Minter bucket mnemonic generator
-------------------------

## Presequences
**Conan** must be installed to build this example.

## Build
```bash
git clone --recursive https://github.com/MinterTeam/cpp-minter.git
cd examples/generate
mkdir build && cd build
CONAN_LOCAL=1 cmake .. -DCMAKE_BUILD_TYPE=Debug
CONAN_LOCAL=1 cmake --build . -- -j4
```

## Run
```bash
./bin/minter-gen
```

Or run with simple argument:
```bash
./bin/minter-gen 300
```
Generates 300 mnemonics and print it to stdout