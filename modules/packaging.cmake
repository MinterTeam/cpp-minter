install(
	FILES ${CMAKE_BINARY_DIR}/lib/libminter_tx.a ${CMAKE_BINARY_DIR}/lib/libethcore.a ${CMAKE_BINARY_DIR}/lib/libsecp256k1_core.a
	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	COMPONENT minter-sdk
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/minter
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        COMPONENT minter-sdk
        )

install(DIRECTORY ${CONAN_INCLUDE_DIRS_BIP39}/minter
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        COMPONENT minter-sdk
        )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/secp256k1/include/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        COMPONENT minter-sdk
        )