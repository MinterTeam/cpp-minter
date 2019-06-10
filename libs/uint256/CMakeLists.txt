cmake_minimum_required(VERSION 3.10)
project(mintex_uint256
        VERSION 0.0.1
        DESCRIPTION "Minter Big integer"
        LANGUAGES C
        )

add_library(${PROJECT_NAME} uint256.h uint256.c)