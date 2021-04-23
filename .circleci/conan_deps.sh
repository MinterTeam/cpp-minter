#!/usr/bin/env bash

conan install toolbox/3.2.2@edwardstock/latest -s build_type=Debug --build=missing
conan install toolbox/3.2.2@edwardstock/latest -s build_type=Release --build=missing

conan install bip39/2.1.1@edwardstock/latest -s build_type=Debug --build=missing
conan install bip39/2.1.1@edwardstock/latest -s build_type=Release --build=missing

conan install bigmath/1.0.2@edwardstock/latest -s build_type=Debug --build=missing
conan install bigmath/1.0.2@edwardstock/latest -s build_type=Release --build=missing

conan install secp256k1_java/1.0.0@edwardstock/latest -s build_type=Debug --build=missing
conan install secp256k1_java/1.0.0@edwardstock/latest -s build_type=Release --build=missing

conan install gtest/1.10.0@ -s build_type=Debug --build=missing
