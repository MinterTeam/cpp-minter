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
#include <minter/tx/tx_declare_candidacy.h>

TEST(TxDeclareCandidacy, TestEncode) {
    const char* expected = "f8960c01018006b845f8439467691076548b20234461ff6fd2bc9c64393eb8fca00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe00a808a021e19e0c9bab2400000808001b845f8431ba0997dfdb7b07c38bcb9fba27a6a65e20a087f79642c34d9f7b2ff41a7f83457f1a0476e4605a29757715835d6a1d1e20215e3987f0d96a864d63ff84978246dc476";
    minter::privkey_t priv_key = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";
    minter::address_t address = "Mx67691076548b20234461ff6fd2bc9c64393eb8fc";
    minter::pubkey_t pub_key = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0";

    auto tx = minter::new_tx();
    tx->set_gas_coin_id(dev::bigint("0"));
    tx->set_nonce(dev::bigint("12"));
    tx->set_gas_price(dev::bigint("1"));
    tx->set_chain_id(minter::mainnet);
    auto data = tx->tx_declare_candidacy();
    data->set_pub_key(pub_key);
    data->set_address(address);
    data->set_coin_id(dev::bigint("0"));
    data->set_stake("10000");
    data->set_commission(10);
    auto tx_result = data->build();
    auto signature = tx_result->sign_single(priv_key);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxDeclareCandidacy, TestDecode) {
    const char* encoded = "f8960c01018006b845f8439467691076548b20234461ff6fd2bc9c64393eb8fca00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe00a808a021e19e0c9bab2400000808001b845f8431ba0997dfdb7b07c38bcb9fba27a6a65e20a087f79642c34d9f7b2ff41a7f83457f1a0476e4605a29757715835d6a1d1e20215e3987f0d96a864d63ff84978246dc476";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_declare_candidacy>();

    minter::address_t address = "Mx67691076548b20234461ff6fd2bc9c64393eb8fc";
    minter::pubkey_t pub_key = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe0";

    ASSERT_EQ(dev::bigint("0"), data->get_coin_id());
    ASSERT_EQ(10, data->get_commission());
    ASSERT_EQ(dev::bigdec18("10000"), data->get_stake());
    ASSERT_EQ(pub_key, data->get_pub_key());
    ASSERT_EQ(address, data->get_address());
}