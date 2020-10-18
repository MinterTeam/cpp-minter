cmake_minimum_required(VERSION 3.10)
project(minter-pretty)

set(CMAKE_CXX_STANDARD 14)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR}/../../modules)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../modules)

add_executable(${PROJECT_NAME} main.cpp)

# If you are using Conan, so just add remotes and resolve packages
if (ENABLE_CONAN)
	include(ConanInit)

	add_conan_remote(bincrafters https://api.bintray.com/conan/bincrafters/public-conan)
	add_conan_remote(scatter https://api.bintray.com/conan/edwardstock/scatter)
	add_conan_remote(minter https://api.bintray.com/conan/minterteam/minter)
	add_conan_remote(edwardstock https://api.bintray.com/conan/edwardstock/conan-public)
	conan_init()

	target_link_libraries(${PROJECT_NAME} CONAN_PKG::minter_tx)
	target_link_libraries(${PROJECT_NAME} CONAN_PKG::boost)
	target_link_libraries(${PROJECT_NAME} CONAN_PKG::toolbox)
else ()
	# But if you don't, you should install libs directly to your system:
	# - boost
	# - minter_tx from minterteam debian/redhat repository
	# - toolbox from edwardstock debian/redhat repository

	# use no-debug boost configuration
	set(Boost_DEBUG OFF)
	# use "-mt" libraries instead of basic
	set(Boost_USE_MULTITHREADED ON)
	# use static ".a" libraries instead of dynamic
	set(Boost_USE_STATIC_LIBS ON)

	find_package(Boost REQUIRED COMPONENTS program_options)
	target_link_libraries(${PROJECT_NAME} Boost::program_options)

	find_package(toolbox REQUIRED)
	target_link_libraries(${PROJECT_NAME} toolbox::toolbox)

	find_package(minter_tx REQUIRED)
	target_link_libraries(${PROJECT_NAME} minter_tx::minter_tx)
endif ()

