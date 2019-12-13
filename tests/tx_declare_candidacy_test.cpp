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
    const char* expected = "f8a80102018a4d4e540000000000000006b84df84b949f7fd953c2c69044b901426831ed03ee0bd0597aa00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a430a8a4d4e5400000000000000884563918244f40000808001b845f8431ca0c379230cbe09103b31983402c9138ad29d839bcecee70e11ac9bf5cfe70850d9a06c92bfb9a627bfaefc3ad46fc60ff1fdc42efe0e8805d57f20795a403c91e8bd";
    minter::privkey_t priv_key = "6e1df6ec69638d152f563c5eca6c13cdb5db4055861efc11ec1cdd578afd96bf";
    minter::address_t address = "Mx9f7fd953c2c69044b901426831ed03ee0bd0597a";
    minter::pubkey_t pub_key = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";

    auto tx = minter::new_tx()
                  ->set_gas_coin("MNT")
                  .set_nonce("1")
                  .set_gas_price("1")
                  .set_chain_id(minter::testnet)
                  .tx_declare_candidacy()
                  ->set_pub_key(pub_key)
                  .set_address(address)
                  .set_coin("MNT")
                  .set_commission(10)
                  .set_stake("5")
                  .build();

    auto signature = tx->sign_single(priv_key);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxDeclareCandidacy, TestDecode) {
    const char* encoded = "f8a80102018a4d4e540000000000000006b84df84b949f7fd953c2c69044b901426831ed03ee0bd0597aa00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a430a8a4d4e5400000000000000884563918244f40000808001b845f8431ca0c379230cbe09103b31983402c9138ad29d839bcecee70e11ac9bf5cfe70850d9a06c92bfb9a627bfaefc3ad46fc60ff1fdc42efe0e8805d57f20795a403c91e8bd";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_declare_candidacy>();

    minter::address_t address = "Mx9f7fd953c2c69044b901426831ed03ee0bd0597a";
    minter::pubkey_t pub_key = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";

    ASSERT_STREQ("MNT", data->get_coin().c_str());
    ASSERT_EQ(10, data->get_commission());
    ASSERT_EQ(dev::bigdec18("5"), data->get_stake());
    ASSERT_EQ(pub_key, data->get_pub_key());
    ASSERT_EQ(address, data->get_address());
}