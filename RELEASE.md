# Release notes

## 0.6.1
 - Added max supply to create coin transaction
 - Unified strings in transactions. No more c-style strings, now only std::string

## 0.6.0
 - Fixed build for macos (removed LIBCPP_DEBUG flag)
 - Updated examples:
   - minter-pretty:
     - fixed searching by single word
   - minter-generator:
     - updated dependencies, using conanfile.py instead of conanfile.txt
 - Added multisig send test
 - Added test for CreateMultisigAddress transaction
 - Added external multisig and sign-only function to get only transaction signature without transaction hash
 - Added deeplink generator and parser
## 0.5.1
 - Set boost version to 1.70 for compatibility 

## 0.5.0
 - Checks support (with texasnet gas coin)
 - Clean-up leading zeroes in signature
 - clang-format
 - Less macros, more templates
 - Refactoring

## 0.4.2
 - Fixes for MacOS

## 0.4.1
 - Added ostream operator to pubkey_t

## 0.4.0
 - Added 100% code coverage for data types
 - Refactored data containers using improved byte-buffer api
 - 

## 0.3.0
 - Updated dependencies
 - Added ability to get unsigned transaction hash to sign it with external private key:
    - `minter::tx::get_unsigned_hash(minter::signature_type)` to get hash
    - `minter::tx::sign_external(minter::signature)` to encode transaction with passed signature
 - Added couple callback methods to sign transaction with external signer:
    - `minter::tx::sign_external(minter::tx::signer_func_c_t)`
    - `minter::tx::sign_external(minter::tx::signer_func_t)`
 - Added multi-signature implementation

## 0.2.0
 - Make library compatible with Windows compilers: MinGW, Cygwin, MSVC
 - Fixed some pedantic warnings
 - Added ability to build library without conan. Use `git submodule update --init --recursive` to download all required dependencies
 - Boost version required for lib: 1.70.0+ (for Windows, you can build it manually or download my [pre-built archive](https://drive.google.com/file/d/1u8bXeNayY_9ARtsqQKgLqqxRV0BPhrCf/view?usp=sharing) 