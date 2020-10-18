/*!
 * minter_tx.
 * tx_declare_candidacy_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx/tx_builder.h>
#include <minter/tx/tx_edit_candidate.h>

TEST(TxEditCandidate, TestEncode) {
    const char* expected =
        "f8b3100101800eb862f860a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe094d82558ea00eb81d35f2654953598f5d51737d31d94d82558ea00eb81d35f2654953598f5d51737d31d94d82558ea00eb81d35f2654953598f5d51737d31d808001b845f8431ba021c0f2da522422607325e32fa3915ea29d23559f0e20464da688bb45b04a59a8a06e235dc9fe780dfa4cb349062041be95d7bc656c7ff52a571507de7989c4a8b1";

    minter::privkey_t priv_key = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";
    minter::address_t address = "Mxd82558ea00eb81d35f2654953598f5d51737d31d";
    minter::pubkey_t pub_key = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0";
    minter::pubkey_t n_pub_key = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe1";

    auto tx = minter::new_tx()
                  ->set_gas_coin_id("0")
                  .set_nonce("16")
                  .set_gas_price("1")
                  .set_chain_id(minter::mainnet)
                  .tx_edit_candidate()
                  ->set_public_key(pub_key)
                  .set_reward_address(address)
                  .set_owner_address(address)
                  .set_control_address(address)
                  .build();

    auto signature = tx->sign_single(priv_key);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxEditCandidate, TestDecode) {
    const char* encoded =
        "f8b3100101800eb862f860a00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe094d82558ea00eb81d35f2654953598f5d51737d31d94d82558ea00eb81d35f2654953598f5d51737d31d94d82558ea00eb81d35f2654953598f5d51737d31d808001b845f8431ba021c0f2da522422607325e32fa3915ea29d23559f0e20464da688bb45b04a59a8a06e235dc9fe780dfa4cb349062041be95d7bc656c7ff52a571507de7989c4a8b1";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_edit_candidate>();

    minter::privkey_t priv_key = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";
    minter::address_t address = "Mxd82558ea00eb81d35f2654953598f5d51737d31d";
    minter::pubkey_t pub_key = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0";

    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
    ASSERT_EQ(pub_key, data->get_public_key());
    ASSERT_EQ(address, data->get_reward_address());
    ASSERT_EQ(address, data->get_owner_address());
    ASSERT_EQ(address, data->get_control_address());
}