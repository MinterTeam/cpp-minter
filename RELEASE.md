# Release notes

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