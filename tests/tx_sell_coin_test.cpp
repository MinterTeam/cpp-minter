/*!
 * minter_tx.
 * tx_sell_coin_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_sell_all_coins.h>
#include <minter/tx/tx_sell_coin.h>

TEST(TxSell, TestEncode) {
    const char* expected = "f864030101800294d380893635c9adc5dea00000018609184e72a000808001b845f8431ba036361e8cdfe662af2285c98fbeb9aa6af1037711fbe47f580777e14ed13575eaa062ff5ce42bec17732db635c85ccf101b4faad5abd9eb9730a78247d12fc1aa34";
    minter::data::private_key pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_gas_coin_id("0")
                  .set_gas_price("1")
                  .set_nonce("3")
                  .set_chain_id(minter::mainnet)
                  .tx_sell_coin()
                  ->set_coin_id_to_sell("0")
                  .set_coin_id_to_buy("1")
                  .set_value_to_sell("1000")
                  .set_min_value_to_buy("0.00001")
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxSell, TestDecode) {
    const char* encoded = "f864030101800294d380893635c9adc5dea00000018609184e72a000808001b845f8431ba036361e8cdfe662af2285c98fbeb9aa6af1037711fbe47f580777e14ed13575eaa062ff5ce42bec17732db635c85ccf101b4faad5abd9eb9730a78247d12fc1aa34";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_sell_coin>();

    ASSERT_EQ(dev::bigint("1"), data->get_coin_id_to_buy());
    ASSERT_EQ(dev::bigint("0"), data->get_coin_id_to_sell());
    ASSERT_EQ(dev::bigdec18("1000"), data->get_value_to_sell());
    ASSERT_EQ(dev::bigdec18("0.00001"), data->get_min_value_to_buy());
}

TEST(TxSellAll, TestEncode) {
    const char* expected = "f85c04010180038ccb01808801b4fbd92b5f8000808001b845f8431ba0c3a668f479a9a9ee25bc98915877e50b5b91fd38ae53a17142b85919dc9f0baba040617eccdc0b28bc8b182ae9d6cb1d1935358973cf48ebf012c0284ed2898ff9";
    minter::data::private_key pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_gas_coin_id("0")
                  .set_gas_price("1")
                  .set_nonce("4")
                  .set_chain_id(minter::mainnet)
                  .tx_sell_all_coins()
                  ->set_coin_id_to_sell("1")
                  .set_coin_id_to_buy("0")
                  .set_min_value_to_buy("0.123")
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxSellAll, TestDecode) {
    const char* encoded = "f85c04010180038ccb01808801b4fbd92b5f8000808001b845f8431ba0c3a668f479a9a9ee25bc98915877e50b5b91fd38ae53a17142b85919dc9f0baba040617eccdc0b28bc8b182ae9d6cb1d1935358973cf48ebf012c0284ed2898ff9";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_sell_all_coins>();

    ASSERT_EQ(dev::bigint("4"), decoded->get_nonce());
    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_EQ(minter::mainnet, decoded->get_chain_id());
    ASSERT_EQ(dev::bytes(0), decoded->get_payload());

    ASSERT_EQ(dev::bigint("0"), data->get_coin_id_to_buy());
    ASSERT_EQ(dev::bigint("1"), data->get_coin_id_to_sell());
    ASSERT_EQ(dev::bigdec18("0.123"), data->get_min_value_to_buy());
}
