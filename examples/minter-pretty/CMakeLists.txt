cmake_minimum_required(VERSION 3.10)
project(minter-pretty)

set(CMAKE_CXX_STANDARD 14)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR}/../../modules)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../modules)
include(ConanInit)

add_conan_remote(bincrafters https://api.bintray.com/conan/bincrafters/public-conan)
add_conan_remote(scatter https://api.bintray.com/conan/edwardstock/scatter)
add_conan_remote(minter https://api.bintray.com/conan/minterteam/minter)
add_conan_remote(edwardstock https://api.bintray.com/conan/edwardstock/conan-public)
conan_init()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} CONAN_PKG::minter_tx)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::boost)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::toolboxpp)

