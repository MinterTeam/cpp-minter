import os
from conans import ConanFile, CMake, tools


def get_version():
    with open(os.path.join(os.path.dirname(__file__), 'version'), 'r') as f:
        content = f.read()
        try:
            content = content.decode()
        except AttributeError:
            pass
        return content.strip()

class MinterTxConan(ConanFile):
    name = "minter_tx"
    version = get_version()
    license = "MIT"
    author = "Eduard Maximovich edward.vstock@gmail.com"
    url = "https://github.com/MinterTeam/cpp-minter"
    description = "Minter C++ SDK: build and sign any transaction, generate mnemonic with private and public key"
    topics = ("minter", "minter-network", "minter-blockchain", "blockchain", "tendermint")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {
        "shared": False,
        "boost_system:shared": False,
        "boost_filesystem:shared": False,
        "boost_thread:shared": False
    }
    exports = "version"
    exports_sources = (
        "modules/*",
        "include/*",
        "tests/*",
        "src/*",
        "libs/*",
        "CMakeLists.txt",
        "conanfile.py",
        "conanfile.txt",
        "LICENSE",
        "README.md",
    )
    generators = "cmake"
    default_user = "minter"
    default_channel = "latest"

    build_requires = (
        "toolboxpp/2.2.0@scatter/latest",
        "boost_multiprecision/1.69.0@bincrafters/stable",
        "boost_system/1.69.0@bincrafters/stable",
        "boost_filesystem/1.69.0@bincrafters/stable",
        "boost_thread/1.69.0@bincrafters/stable",
        "gtest/1.8.1@bincrafters/stable",
    )

    def source(self):
        if "CONAN_LOCAL" not in os.environ:
            self.run("rm -rf *")
            self.run("git clone --recursive https://github.com/MinterTeam/cpp-minter.git .")

    def build(self):
        cmake = CMake(self, parallel=False)
        cmake.configure(defs={'WITH_TEST': 'Off', 'CMAKE_BUILD_TYPE': 'Release'})
        cmake.build()

    def package(self):
        self.copy("*", dst="include", src="include", keep_path=True)
        self.copy("*minter_tx.lib", dst="lib", keep_path=False)
        self.copy("*minter_tx.so", dst="lib", keep_path=False)
        self.copy("*minter_tx.dylib", dst="lib", keep_path=False)
        self.copy("*minter_tx.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["minter_tx"]
