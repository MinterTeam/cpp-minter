import os
from conans import ConanFile, CMake, tools


class MinterTxConan(ConanFile):
    name = "minter_generator"
    version = "1.0.0"
    license = "MIT"
    author = "Eduard Maximovich edward.vstock@gmail.com"
    url = "https://github.com/MinterTeam/cpp-minter"
    description = "Example how to generate a bucket of minter wallets"
    topics = ("minter", "minter-network", "minter-blockchain", "blockchain", "tendermint")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {
        "shared": False,
        "bip39:shared": False,
        "bip39:enableC": False,
        "bip39:enableJNI": False,
    }
    generators = "cmake"
    default_user = "minter"
    default_channel = "latest"

    requires = (
        'minter_tx/1.0.0@minter/latest'
    )
