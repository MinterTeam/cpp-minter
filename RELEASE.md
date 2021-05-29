# Release notes

## 2.0.1
- Updated `bigmath` as it has major fix for windows builds

## 2.0.0

- Added transactions:
    - AddLiquidity (`tx_add_liquidity`)
    - RemoveLiquidity (`tx_remove_liquidity`)
    - BuySwapPool (`tx_buy_swap_pool`)
    - SellSwapPool (`tx_sell_swap_pool`)
    - SellAllSwapPool (`tx_sell_all_swap_pool`)
    - CreateSwapPool (`tx_create_swap_pool`)
    - CreateToken (`tx_create_token`)
    - RecreateToken (`tx_recreate_token`)
    - MintToken (`tx_mint_token`)
    - BurnToken (`tx_burn_token`)
    - EditCandidateCommission (`tx_edit_candidate_commission`)
    - VoteCommission (`tx_vote_commission`)
    - VoteUpdate (`tx_vote_update`)

- Passing simple (not exactly) types by value instead of by const reference: dev::bigint, dev::bigdec18 etc
- Added method overrides with `std::string` argument (float or integer representation) where by default
  passing `dev::bigdec18` or `dev::bigint`

## 1.0.0 **Breaking changes**

- Now coins represented by its ID. It means, all methods like `set_coin(std::string)` or `set_gas_coin(std::string)`
  was renamed to `set_coin_id()` and same, with 2 types as arguments: `dev::bigint` and `std::string`. String represents
  numeric coin ID (for convenience)
- Added transactions:
    - SetHaltBlock (`tx_set_halt_block`)
    - Recreate Coin (`tx_recreate_coin`)
    - EditCoinOwner (`tx_edit_coin_owner`)
    - EditMultisig (`tx_edit_multisig`)
    - PriceVote (`tx_price_vote`)
    - EditCandidatePublicKey (`tx_edit_candidate_public_key`)
- Removed **boost** at all
- Updated tests
- Updated examples
- Removed dependencies as submodules, now to build library without conan, you should build all dependencies by yourself,
  guide will be attached to README

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