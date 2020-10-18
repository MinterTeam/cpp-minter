/*!
 * minter_tx.
 * tx_create_coin_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_create_coin.h>

TEST(TxCreateCoin, TestEncode) {
    const char* expected = "f88b0901018005b83af8388a535550455220544553548a535550455254455354318a021e19e0c9bab24000008a021e19e0c9bab2400000638a021e27c1806e59a40000808001b845f8431ba03c4678e9549256b9413827dc617de9b054b3c02ea72eb5b99d038ad49c600dcca02c54da56153d766ed1c9bc1917d82b6c56029e9f889e4d0d1e945eafeca9991b";
    minter::privkey_t pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_gas_coin_id(dev::bigint("0"))
                  .set_nonce(dev::bigint("9"))
                  .set_gas_price("1")
                  .set_chain_id(minter::mainnet)
                  .tx_create_coin()
                  ->set_name("SUPER TEST")
                  .set_ticker("SUPERTEST1")
                  .set_initial_amount("10000")
                  .set_initial_reserve("10000")
                  .set_max_supply("10001")
                  .set_crr(99)
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxCreateCoin, TestDecode) {
    const char* encoded = "f88b0901018005b83af8388a535550455220544553548a535550455254455354318a021e19e0c9bab24000008a021e19e0c9bab2400000638a021e27c1806e59a40000808001b845f8431ba03c4678e9549256b9413827dc617de9b054b3c02ea72eb5b99d038ad49c600dcca02c54da56153d766ed1c9bc1917d82b6c56029e9f889e4d0d1e945eafeca9991b";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_create_coin>();

    ASSERT_STREQ("SUPERTEST1", data->get_ticker().c_str());
    ASSERT_STREQ("SUPER TEST", data->get_name().c_str());
    ASSERT_EQ(dev::bigdec18("10000"), data->get_initial_amount());
    ASSERT_EQ(dev::bigdec18("10000"), data->get_initial_reserve());
    ASSERT_EQ((uint32_t) 99, data->get_crr());
    ASSERT_EQ(dev::bigdec18("10001"), data->get_max_supply());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
}