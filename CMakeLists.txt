cmake_minimum_required(VERSION 3.12)
project(minter_tx
        VERSION 1.0.0
        DESCRIPTION "Minter Transaction SDK for C++"
        LANGUAGES CXX
        )

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/version ${CMAKE_PROJECT_VERSION})

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(ENABLE_SHARED OFF CACHE BOOL "Build shared lib instead of static")
set(ENABLE_CONAN ON CACHE BOOL "Enable conan dep manager")

set(DISABLE_JNI ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_PDB_OUTPUT_DIRECTORY lib)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2 /MP")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DEBUG /Od")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
	string(REGEX REPLACE "\\/W3" " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	add_compile_options(/wd4068)
	add_compile_options(/wd4319)
	add_compile_options(/wd4251)
	add_compile_options(/wd4275)
	add_compile_options(/wd4834)
elseif (MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -Wno-unknown-pragmas -Wno-shift-count-overflow")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else ()
	#-fvisibility=hidden
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -Wextra -pedantic -Wno-unknown-pragmas -Wno-unused-parameter -Wno-shift-count-overflow")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif ()


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
include(modules/FindLinuxPlatform.cmake)
include(conan_fallback)


if (ENABLE_CONAN)
	include(ConanInit)
	add_conan_remote(bincrafters https://api.bintray.com/conan/bincrafters/public-conan)
	add_conan_remote(minter https://api.bintray.com/conan/minterteam/minter)
	add_conan_remote(edwardstock https://api.bintray.com/conan/edwardstock/conan-public)
	conan_init()
else ()
	# toolbox
	find_package(Toolbox 3.2.0 REQUIRED)
	set_target_properties(toolbox::toolbox PROPERTIES IMPORTED_GLOBAL TRUE)
	add_library(CONAN_PKG::toolbox ALIAS toolbox::toolbox)

	#bip39
	find_package(bip3x 2.1.0 REQUIRED)
	set_target_properties(bip3x::bip39 PROPERTIES IMPORTED_GLOBAL TRUE)
	add_library(CONAN_PKG::bip39 ALIAS bip3x::bip39)

	#secp256k1
	find_package(secp256k1_java REQUIRED)
	set_target_properties(secp256k1_java::secp256k1_core PROPERTIES IMPORTED_GLOBAL TRUE)
	add_library(CONAN_PKG::secp256k1_java ALIAS secp256k1_java::secp256k1_core)


	# bigmath
	find_package(bigmath 1.0.0 REQUIRED)
	set_target_properties(bigmath::bigmath PROPERTIES IMPORTED_GLOBAL TRUE)
	add_library(CONAN_PKG::bigmath ALIAS bigmath::bigmath)
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
    include/minter/eth/vector_ref.h
    include/minter/eth/types.h)

set(ETH_SOURCES
    ${ETH_HEADERS}
    src/eth/RLP.cpp
    )

set(HEADERS
    include/minter/tx/tx.h
    include/minter/tx/tx_send_coin.h
    include/minter/tx/tx_fwd.h
    include/minter/tx/tx_data.h
    include/minter/tx/tx_sell_coin.h
    include/minter/tx/tx_sell_all_coins.h
    include/minter/tx/tx_buy_coin.h
    include/minter/tx/tx_create_coin.h
    include/minter/tx/tx_recreate_coin.h
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
    include/minter/crypto/cxx_secp256k1.h
    include/minter/tx/tx_builder.h
    include/minter/public_key.h
    include/minter/hash.h
    include/minter/address.h
    include/minter/private_key.h
    include/minter/minter_tx_config.h
    include/minter/tx/check_tx.h
    include/minter/check.h
    include/minter/tx/tx_deeplink.h
    include/minter/tx/tx_set_halt_block.h
    include/minter/tx/tx_edit_coin_owner.h
    include/minter/tx/tx_edit_multisig.h
    include/minter/tx/tx_price_vote.h
    include/minter/tx/tx_edit_candidate_public_key.h
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
    src/tx/tx_recreate_coin.cpp
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
    src/data/private_key.cpp
    src/tx/tx_data.cpp
    src/tx/check_tx.cpp
    src/data/check.cpp
    src/tx/tx_deeplink.cpp
    src/tx/tx_set_halt_block.cpp
    src/tx/tx_edit_coin_owner.cpp
    src/tx/tx_edit_multisig.cpp
    src/tx/tx_price_vote.cpp
    src/tx/tx_edit_candidate_public_key.cpp
    )

set(MINTER_TX_EXPORTING 1)
if (ENABLE_SHARED)
	set(MINTER_EXPORT_SHARED 1)
endif ()

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cfg/minter_tx_config.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/include/minter/minter_tx_config.h
)

if (ENABLE_SHARED)
	add_library(${PROJECT_NAME} SHARED ${SOURCES})
	set_property(TARGET ${PROJECT_NAME} PROPERTY
	             MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else ()
	add_library(${PROJECT_NAME} STATIC ${SOURCES})
	set_property(TARGET ${PROJECT_NAME} PROPERTY
	             MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>)

target_link_libraries(${PROJECT_NAME} CONAN_PKG::secp256k1_java)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::bigmath)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::bip39)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::toolbox)


if (ENABLE_PVS)
	include(PVS-Studio)
	pvs_studio_add_target(TARGET ${PROJECT_NAME}.analyze ALL
	                      OUTPUT FORMAT errorfile
	                      CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/pvs.cfg
	                      ANALYZE ${PROJECT_NAME}
	                      SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include
	                      LOG target.err)
endif ()

if (ENABLE_TEST)
	set(gtest_force_shared_crt ${ENABLE_SHARED} CACHE BOOL "" FORCE)
	set(PROJECT_NAME_TEST ${PROJECT_NAME}-test)

	if (APPLE)
		add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
		add_definitions(-D__GLIBCXX__)
	endif ()
	if (MSVC)
		string(REGEX REPLACE "\\/W4" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	endif ()

	#gtest
	if (NOT ENABLE_CONAN)
		add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/gtest)
		add_library(CONAN_PKG::gtest ALIAS gtest)
	endif ()

	enable_testing()

	set(TEST_SOURCES
	    tests/main.cpp
	    tests/tx_send_test.cpp
	    tests/tx_buy_coin_test.cpp
	    tests/tx_create_coin_test.cpp
	    tests/tx_recreate_coin_test.cpp
	    tests/utils_test.cpp
	    tests/tx_sell_coin_test.cpp
	    tests/tx_delegate_test.cpp
	    tests/tx_set_candidate_on_off.cpp
	    tests/tx_declare_candidacy_test.cpp
	    tests/tx_edit_candidate_test.cpp
	    tests/priv_key_test.cpp
	    tests/tx_multisend_test.cpp
	    tests/tx_multisig_test.cpp
	    tests/tx_redeem_check_test.cpp
	    tests/rlp_test.cpp
	    tests/address_test.cpp
	    tests/pub_key_test.cpp
	    tests/check_tx_test.cpp
	    tests/tx_create_multisig_address_test.cpp
	    tests/tx_deeplink_test.cpp
	    tests/tx_set_halt_block_test.cpp
	    tests/tx_edit_coin_owner_test.cpp
	    tests/tx_edit_multisig_test.cpp
	    tests/tx_edit_candidate_public_key_test.cpp
	    )

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

	add_test(
		NAME test-all
		COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin/${PROJECT_NAME_TEST}
	)
endif ()

include(package)

