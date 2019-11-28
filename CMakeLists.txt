cmake_minimum_required(VERSION 3.10)
project(minter_tx
        VERSION 0.4.2
        DESCRIPTION "Minter Transaction Maker"
        LANGUAGES CXX
        )

if (WIN32)
	execute_process(
		COMMAND cmd /C "echo ${CMAKE_PROJECT_VERSION} > ${CMAKE_CURRENT_SOURCE_DIR}/version"
	)
else ()
	execute_process(
		COMMAND bash -c "echo ${CMAKE_PROJECT_VERSION} > ${CMAKE_CURRENT_SOURCE_DIR}/version"
	)
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(ENABLE_SHARED OFF CACHE BOOL "Build shared lib instead of static")
set(ENABLE_CONAN ON CACHE BOOL "Enable conan dep manager")

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2 /MP")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DEBUG /Od")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
	string(REGEX REPLACE "\\/W3" " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	add_compile_options(/wd4068)
	add_compile_options(/wd4319)
	add_compile_options(/wd4251)
	add_compile_options(/wd4275)

	if (NOT ENABLE_SHARED)
		foreach (flag_var
		         CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
		         CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			if (${flag_var} MATCHES "/MD")
				string(REGEX REPLACE "MD" "MT" ${flag_var} "${${flag_var}}")
			endif (${flag_var} MATCHES "/MD")
		endforeach (flag_var)
	endif ()

	foreach (flag_var
	         CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
	         CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
		if (${flag_var} MATCHES "/MD")
			string(REGEX REPLACE "MD" "MDd" ${flag_var} "${${flag_var}}")
		endif (${flag_var} MATCHES "/MD")
		if (${flag_var} MATCHES "/MT")
			string(REGEX REPLACE "MT" "MTd" ${flag_var} "${${flag_var}}")
		endif (${flag_var} MATCHES "/MT")
	endforeach (flag_var)

	message(STATUS ${CMAKE_CXX_FLAGS})
	message(STATUS ${CMAKE_CXX_FLAGS_DEBUG})
	message(STATUS ${CMAKE_CXX_FLAGS_RELEASE})
	message(STATUS ${CMAKE_CXX_FLAGS_MINSIZEREL})
	message(STATUS ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

elseif (MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -Wno-unknown-pragmas -Wno-shift-count-overflow")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -Wextra -pedantic -Wno-unknown-pragmas -Wno-unused-parameter -Wno-shift-count-overflow")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif ()


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
include(modules/FindLinuxPlatform.cmake)


if (ENABLE_CONAN)
	include(ConanInit)
	add_conan_remote(bincrafters https://api.bintray.com/conan/bincrafters/public-conan)
	add_conan_remote(scatter https://api.bintray.com/conan/edwardstock/scatter)
	add_conan_remote(minter https://api.bintray.com/conan/minterteam/minter)
	add_conan_remote(edwardstock https://api.bintray.com/conan/edwardstock/conan-public)
	if (ENABLE_SHARED)
		set(CONAN_OPTIONS bip39:shared=True)
	else ()
		set(CONAN_OPTIONS bip39:shared=False)
	endif ()
	conan_init()
else ()
	message(STATUS "Boost root: ${BOOST_ROOT}")
	# Boost
	set(Boost_DEBUG OFF)
	set(Boost_USE_STATIC_LIBS ON)
	set(Boost_USE_MULTITHREADED ON)
	if (WIN32)
		find_package(Boost 1.70.0 REQUIRED)
	else ()
		find_package(Boost 1.70.0 COMPONENTS program_options math exception REQUIRED)
	endif ()

	add_library(CONAN_PKG::boost INTERFACE IMPORTED)
	set_property(TARGET CONAN_PKG::boost PROPERTY INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
	set_property(TARGET CONAN_PKG::boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

	# toolbox
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/toolboxpp)
	add_library(CONAN_PKG::toolboxpp INTERFACE IMPORTED)
	set_property(TARGET CONAN_PKG::toolboxpp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/libs/toolboxpp/include)

	#bip39
	set(ENABLE_BIP39_JNI OFF CACHE BOOL "" FORCE)
	set(ENABLE_BIP39_SHARED ${ENABLE_SHARED} CACHE BOOL "" FORCE)
	set(ENABLE_BIP39_C OFF CACHE BOOL "" FORCE)
	set(ENABLE_BIP39_CONAN OFF CACHE BOOL "" FORCE)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/bip39)
	add_library(CONAN_PKG::bip39 ALIAS bip39)

	#gtest
	if (MINTER_TX_TEST)
		add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/gtest)
		add_library(CONAN_PKG::gtest ALIAS gtest)
	endif ()
endif ()

if (APPLE)
	set(CMAKE_MACOSX_RPATH OFF)
endif (APPLE)

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
	elseif (MSVC)
		# nothing
	elseif (NOT MSVC AND WIN32)
		set(PROJECT_ARCH ${CMAKE_SYSTEM_PROCESSOR})
		if (CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
		else ()
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
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
    include/minter/eth/common.h
    include/minter/eth/vector_ref.h
    )

set(ETH_SOURCES
    ${ETH_HEADERS}
    src/eth/RLP.cpp
    src/eth/common.cpp)

set(HEADERS
    include/minter/tx/tx.h
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
    include/minter/crypto/secp256k1_raii.h
    include/minter/tx/tx_builder.h
    include/minter/public_key.h
    include/minter/hash.h
    include/minter/address.h
    include/minter/private_key.h
    include/minter/minter_tx_core.h
    )

set(SOURCES
    ${HEADERS}
    ${ETH_SOURCES}
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

set(MINTER_TX_EXPORTING 1)
if (ENABLE_SHARED)
	set(MINTER_EXPORT_SHARED 1)
endif ()

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cfg/minter_tx_core.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/include/minter/minter_tx_core.h
)

if (ENABLE_SHARED)
	add_library(${PROJECT_NAME} SHARED ${SOURCES})
else ()
	add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif ()
#set_target_properties(${PROJECT_NAME} PROPERTIES
#                      PUBLIC_HEADER "${HEADERS}")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#secp256k1
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/secp256k1 ${CMAKE_BINARY_DIR}/secp256k1)

target_link_libraries(${PROJECT_NAME} secp256k1_core)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::boost)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::bip39)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::toolboxpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs)

if (ENABLE_PVS)
	include(PVS-Studio)
	pvs_studio_add_target(TARGET ${PROJECT_NAME}.analyze ALL
	                      OUTPUT FORMAT errorfile
	                      CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/pvs.cfg
	                      ANALYZE ${PROJECT_NAME}
	                      SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include
	                      LOG target.err)
endif ()

if (MINTER_TX_TEST)
	set(gtest_force_shared_crt ${ENABLE_SHARED} CACHE BOOL "" FORCE)
	add_definitions(-DTEST_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/tests")
	set(PROJECT_NAME_TEST ${PROJECT_NAME}-test)

	if (APPLE)
		add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
		add_definitions(-D__GLIBCXX__)
	endif ()
	if (MSVC)
		string(REGEX REPLACE "\\/W4" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	endif ()

	set(TEST_SOURCES
	    tests/main.cpp
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
	    tests/address_test.cpp tests/pub_key_test.cpp)

	add_executable(${PROJECT_NAME_TEST} ${TEST_SOURCES})
	if (NOT MSVC)
		target_compile_options(${PROJECT_NAME_TEST} PUBLIC -Wno-unused-parameter)
	endif ()
	target_include_directories(${PROJECT_NAME_TEST} PRIVATE tests)
	target_link_libraries(${PROJECT_NAME_TEST} PRIVATE CONAN_PKG::gtest)
	target_link_libraries(${PROJECT_NAME_TEST} PUBLIC ${PROJECT_NAME})


	if (WITH_COVERAGE)
		set(COVERAGE_LCOV_EXCLUDES
		    'libs/*'
		    '/usr/include/*'
		    'tests/*'
		    'boost/*'
		    '/usr/include/*'
		    '/usr/local/*'
		    'v1'
		    '4.9'
		    )
		include(modules/CodeCoverage.cmake)
		append_coverage_compiler_flags()
		setup_target_for_coverage_lcov(
			NAME ${PROJECT_NAME_TEST}-coverage
			EXECUTABLE ${PROJECT_NAME_TEST}
			DEPENDENCIES ${PROJECT_NAME}
		)
	endif ()
endif ()

include(modules/packaging.cmake)