cmake_minimum_required(VERSION 3.10)
project(minter
        VERSION 0.1.2
        DESCRIPTION "Minter Transaction Maker"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 14)

execute_process(
	COMMAND bash -c "echo ${CMAKE_PROJECT_VERSION} > ${CMAKE_CURRENT_SOURCE_DIR}/version"
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
include(ConanInit)
include(modules/FindLinuxPlatform.cmake)

add_conan_remote(bincrafters https://api.bintray.com/conan/bincrafters/public-conan)
add_conan_remote(scatter https://api.bintray.com/conan/edwardstock/scatter)
add_conan_remote(minter https://api.bintray.com/conan/minterteam/minter)
add_conan_remote(edwardstock https://api.bintray.com/conan/edwardstock/conan-public)
conan_init()

set(ENABLE_SHARED OFF CACHE BOOL "Build shared lib instead of static")

set(DISABLE_JNI ON)
option(ENABLE_JNI OFF)
option(ENABLE_GO OFF)

if(APPLE)
	set(CMAKE_MACOSX_RPATH OFF)
endif(APPLE)

# ARCH
if (WITH_ARCH)
	set(PROJECT_ARCH ${WITH_ARCH})
else ()
	include(modules/FindLinuxPlatform.cmake)
	if (IS_DEBIAN)
		if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
			set(PROJECT_ARCH "amd64")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
		elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "unknown")
			set(PROJECT_ARCH "i386")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
		else ()
			set(PROJECT_ARCH ${CMAKE_SYSTEM_PROCESSOR})

			if (CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
				set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
			else ()
				set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
			endif ()
		endif ()
	else ()
		set(PROJECT_ARCH ${CMAKE_SYSTEM_PROCESSOR})
		if (CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
		else ()
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
		endif ()
	endif ()
endif ()
message(STATUS "Build arch: ${PROJECT_ARCH}")

set(ETH_HEADERS
    include/minter/eth/RLP.h
    include/minter/eth/Common.h
    include/minter/eth/CommonData.h
    include/minter/eth/FixedHash.h
    include/minter/eth/vector_ref.h
    )

set(ETH_SOURCES
    ${ETH_HEADERS}
    src/eth/RLP.cpp
    src/eth/Common.cpp
    src/eth/CommonData.cpp
    src/eth/FixedHash.cpp
    )

if (ENABLE_SHARED)
	add_library(ethcore SHARED ${ETH_SOURCES})
else ()
	add_library(ethcore STATIC ${ETH_SOURCES})
endif ()
target_compile_options(ethcore PUBLIC -fPIC)
target_include_directories(ethcore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(ethcore PUBLIC CONAN_PKG::boost)

set(HEADERS
    include/minter/tx/tx.h
    include/minter/tx/rlp_encodable.h
    include/minter/tx/tx_send_coin.h
    include/minter/tx/tx_fwd.h
    include/minter/tx/tx_data.h
    include/minter/tx/tx_sell_coin.h
    include/minter/tx/tx_sell_all_coins.h
    include/minter/tx/tx_buy_coin.h
    include/minter/tx/tx_create_coin.h
    include/minter/tx/tx_declare_candidacy.h
    include/minter/tx/tx_delegate.h
    include/minter/tx/tx_unbond.h
    include/minter/tx/tx_redeem_check.h
    include/minter/tx/tx_set_candidate_on_off.h
    include/minter/tx/tx_create_multisig_address.h
    include/minter/tx/tx_multisend.h
    include/minter/tx/tx_edit_candidate.h
    include/minter/tx/tx_type.h
    include/minter/tx/signature_data.h
    include/minter/tx/signature.h
    include/minter/tx/utils.h
    include/minter/tx/secp256k1_raii.h
    include/minter/tx/tx_builder.h
    include/minter/public_key.h
    include/minter/hash.h
    include/minter/address.h
    include/minter/private_key.h
    include/minter/tx.hpp)

set(SOURCES
    ${HEADERS}
    src/tx/tx.cpp
    src/tx/tx_send_coin.cpp
    src/tx/tx_sell_coin.cpp
    src/tx/tx_sell_all_coins.cpp
    src/tx/tx_buy_coin.cpp
    src/tx/tx_create_coin.cpp
    src/tx/tx_declare_candidacy.cpp
    src/tx/tx_delegate.cpp
    src/tx/tx_unbond.cpp
    src/tx/tx_redeem_check.cpp
    src/tx/tx_set_candidate_on_off.cpp
    src/tx/tx_create_multisig_address.cpp
    src/tx/tx_multisend.cpp
    src/tx/tx_edit_candidate.cpp
    src/data/address.cpp
    src/tx/signature_data.cpp
    src/utils.cpp
    src/tx/tx_type.cpp
    src/tx/tx_builder.cpp
    src/data/public_key.cpp
    src/data/hash.cpp
    src/data/private_key.cpp)

if (ENABLE_SHARED)
	add_library(${PROJECT_NAME} SHARED ${SOURCES})
else ()
	add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif ()
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                      PUBLIC_HEADER "${HEADERS}")

target_compile_options(${PROJECT_NAME} PUBLIC -Wno-shift-count-overflow -fPIC) #-static-libstdc++
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#secp256k1
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/secp256k1 ${CMAKE_BINARY_DIR}/secp256k1)

target_link_libraries(${PROJECT_NAME} ethcore)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::bip39)
target_link_libraries(${PROJECT_NAME} secp256k1_core)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs)


add_custom_target(minter_tx_merge
                  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/merge_libs.sh ${CMAKE_BINARY_DIR}/lib minter_tx
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  DEPENDS ${CMAKE_PROJECT_NAME})

add_library(minter_tx STATIC IMPORTED)
set_target_properties(minter_tx PROPERTIES
                      IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/lib/libminter_tx.a"
                      PUBLIC_HEADER "${HEADERS}")


if (WITH_TEST)
	add_definitions(-DTEST_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/tests")
	set(PROJECT_NAME_TEST ${PROJECT_NAME}-test)

	if (WIN32)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
	elseif (APPLE)
		add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
		add_definitions(-D__GLIBCXX__)
	endif ()

	set(TEST_SOURCES
	    tests/tx_send_test.cpp
	    tests/tx_buy_coin_test.cpp
	    tests/tx_create_coin_test.cpp
	    tests/utils_test.cpp
	    tests/tx_sell_coin_test.cpp
	    tests/tx_delegate_test.cpp
	    tests/tx_set_candidate_on_off.cpp
	    tests/tx_declare_candidacy_test.cpp
	    tests/tx_edit_candidate_test.cpp
	    tests/priv_key_test.cpp
	    tests/tx_multisend_test.cpp
	    tests/tx_multisig_test.cpp
	    tests/tx_check_test.cpp
	    tests/rlp_test.cpp
	    )

	add_executable(${PROJECT_NAME_TEST} ${TEST_SOURCES})
	target_compile_options(${PROJECT_NAME_TEST} PUBLIC -Wno-unused-parameter)
	target_link_libraries(${PROJECT_NAME_TEST} PRIVATE CONAN_PKG::gtest)
	target_link_libraries(${PROJECT_NAME_TEST} PUBLIC ${PROJECT_NAME})

	if (WITH_COVERAGE)
		set(COVERAGE_LCOV_EXCLUDES
		    '${CMAKE_CURRENT_SOURCE_DIR}/libs/*'
		    '${CMAKE_CURRENT_SOURCE_DIR}/tests/*'
		    'boost/*'
		    '/usr/include/*'
		    '/usr/local/*'
		    'v1'
		    )
		set(COVERAGE_TARGET_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/)
		include(cmake-modules/CodeCoverage.cmake)
		append_coverage_compiler_flags()
		setup_target_for_coverage_lcov(
			NAME ${PROJECT_NAME}-coverage
			EXECUTABLE ${PROJECT_NAME_TEST}
			DEPENDENCIES ${PROJECT_NAME_TEST}
		)
	endif ()
endif ()


#add_executable(minter_pretty main.cpp)
#add_dependencies(minter_pretty ${CMAKE_PROJECT_NAME})
#target_link_libraries(minter_pretty ${CMAKE_PROJECT_NAME})
#target_link_libraries(minter_pretty CONAN_PKG::toolboxpp)
#target_link_libraries(minter_pretty CONAN_PKG::boost_program_options)

include(modules/packaging.cmake)