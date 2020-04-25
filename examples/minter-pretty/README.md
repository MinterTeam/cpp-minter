Minter Pretty Address
=====================

Concurrent high-performance Minter pretty address generator.

## Presequences
**Conan** must be installed to build this example.

## Usage
Generator by default, uses simple hex dictionary with a real words:
```
abba,
face,
cafe,
cafe,
fade,
feed,
beef,
dead,
added,
decaf,
faded,
decade,
facade,
deadbeef
```

You can find one of this, or your own word at address start, at end or both sides,


**Case 1** - find some of dictionary word at start (default position) of address like this

`Mxbeef000000000000000000000000000000000000`

args:
```bash
./bin/minter-pretty
```


**Case 2** - find "beef" at end of address:

`Mx000000000000000000000000000000000000beef`

args:
```bash
./bin/minter-pretty --whence end --word beef --nodict
```

**Case 3** - find "beef" at both sides of address:

`Mxbeef00000000000000000000000000000000beef`

args:
```bash
./bin/minter-pretty --whence both
```


**Case 4** - find your phone number at start like this:

 `Mx9165556677000000000000000000000000000000`
 
args:
```bash
./bin/minter-pretty --word 9165556677 --nodict
```

## Build
```bash
git clone --recursive https://github.com/MinterTeam/cpp-minter.git
cd examples/minter-pretty
mkdir build && cd build
CONAN_LOCAL=1 cmake .. -DCMAKE_BUILD_TYPE=Debug
CONAN_LOCAL=1 cmake --build . -- -j4
```

## Limitations

- Word can contain only hexadecimal symbols: **^[0-9a-fA-F]+$**
- Complex and long word can take very much time to find it, so, use 3-4 symbols


## License
[MIT License](LICENSE)

Copyright (c) 2019 Minter

Author: [Eduard Maximovich](https://github.com/edwardstock)


