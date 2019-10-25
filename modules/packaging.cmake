install(
	TARGETS ${PROJECT_NAME} secp256k1_core
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/minter
	DESTINATION include/minter
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/minter
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        )

if (ENABLE_CONAN)
	install(DIRECTORY ${CONAN_INCLUDE_DIRS_BIP39}/minter
	        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
	        )
else ()
	install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/bip39/include/minter
	        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
	        )
endif ()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/secp256k1/include/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        )