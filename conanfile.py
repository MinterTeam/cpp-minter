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
        "boost:shared": False,
        "bip39:shared": False,
        "bip39:enableC": False,
        "bip39:enableJNI": False,
    }
    exports = "version"
    exports_sources = (
        "modules/*",
        "include/*",
        "cfg/*",
        "tests/*",
        "src/*",
        "libs/*",
        "CMakeLists.txt",
        "conanfile.py",
        "conanfile.txt",
        "LICENSE",
        "README.md",
        "merge_libs.sh"
    )
    generators = "cmake"
    default_user = "minter"
    default_channel = "latest"

    requires = (
        'bip39/2.0.0@edwardstock/latest',
        'toolbox/3.1.0@edwardstock/latest',
        'boost/1.70.0@conan/stable',
    )

    build_requires = (
        "gtest/1.8.1@bincrafters/stable",
    )

    # def imports(self):
    #     self.copy("*.dll", "bin", "bin")
    #     self.copy("*.dll", "bin", "lib")
    #     self.copy("*.dylib", "lib", "lib")

    def source(self):
        if "CONAN_LOCAL" not in os.environ:
            self.run("rm -rf *")
            self.run("git clone --recursive https://github.com/MinterTeam/cpp-minter.git .")

    def configure(self):
        if self.settings.compiler == "Visual Studio":
            del self.settings.compiler.runtime

    def build(self):
        cmake = CMake(self)
        cmake.configure(defs={'CMAKE_BUILD_TYPE': self.settings.build_type})
        cmake.build(target="minter_tx")

    def package(self):
        self.copy("*", dst="include", src="include", keep_path=True)
        self.copy("*", dst="include", src="libs/secp256k1/include", keep_path=True)
        self.copy("*", dst="include", src="include", keep_path=True)
        dir_types = ['bin', 'lib', 'Debug', 'Release', 'RelWithDebInfo', 'MinSizeRel']
        file_types = ['lib', 'dll', 'dll.a', 'a', 'so', 'exp', 'pdb', 'ilk', 'dylib']

        for dirname in dir_types:
            for ftype in file_types:
                self.copy("*." + ftype, src=dirname, dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ['minter_tx', 'secp256k1_core']
