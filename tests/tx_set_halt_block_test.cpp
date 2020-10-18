/*!
 * minter_tx.
 * tx_recreate_coin_test.cpp
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_set_halt_block.h>

TEST(TxSetHaltBlock, TestEncode) {
    const char* expected = "f873020101800fa3e2a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe87b808001b845f8431ba0d48744fee3dbcabca03d495c4dffe57a67e8e44b547812d6d72e26f0322d3928a0322d7276f56b4cda3ab6c586a27edb5af01b011e313c0c8e2996b6a8e0f3397c";
    minter::privkey_t pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_gas_coin_id(dev::bigint("0"))
                  .set_nonce(dev::bigint("2"))
                  .set_gas_price("1")
                  .set_chain_id(minter::mainnet)
                  .tx_set_halt_block()
                  ->set_public_key(minter::pubkey_t("Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe8"))
                  .set_height("123")
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxSetHaltBlock, TestDecode) {
    const char* encoded = "f873020101800fa3e2a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe87b808001b845f8431ba0d48744fee3dbcabca03d495c4dffe57a67e8e44b547812d6d72e26f0322d3928a0322d7276f56b4cda3ab6c586a27edb5af01b011e313c0c8e2996b6a8e0f3397c";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_set_halt_block>();

    ASSERT_EQ(minter::pubkey_t("Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe8"), data->get_public_key());
    ASSERT_EQ(dev::bigint("123"), data->get_height());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
}