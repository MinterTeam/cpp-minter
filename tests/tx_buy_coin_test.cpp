//
// Created by edwardstock on 26.04.19.
//
#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <iostream>

TEST(TxBuy, TestEncode) {

    const char* expected = "f8830102018a4d4e540000000000000004a9e88a54455354000000000000880de0b6b3a76400008a4d4e5400000000000000880de0b6b3a7640000808001b845f8431ca04ee095a20ca58062a5758e2a6d3941857daa8943b5873c57f111190ca88dbc56a01148bf2fcc721ca353105e4f4a3419bec471d7ae08173f443a28c3ae6d27018a";

    minter::data::private_key pk = "07bc17abdcee8b971bb8723e36fe9d2523306d5ab2d683631693238e0f9df142";

    auto tx = minter::new_tx()
            ->set_nonce("1")
            .set_gas_price("1")
            .set_gas_coin("MNT")
            .set_chain_id(minter::testnet)
            .tx_buy_coin()
            ->set_coin_to_buy("TEST")
            .set_coin_to_sell("MNT")
            .set_value_to_buy("1")
            .set_max_value_to_sell("1")
            .build();

    auto signature = tx->sign_single(pk);



    ASSERT_STREQ(expected, signature.toHex().c_str());

}

TEST(TxBuy, TestDecode) {
    const char* encoded = "f8830102018a4d4e540000000000000004a9e88a54455354000000000000880de0b6b3a76400008a4d4e5400000000000000880de0b6b3a7640000808001b845f8431ca04ee095a20ca58062a5758e2a6d3941857daa8943b5873c57f111190ca88dbc56a01148bf2fcc721ca353105e4f4a3419bec471d7ae08173f443a28c3ae6d27018a";
    auto decoded = minter::tx::decode(encoded);

    ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
    ASSERT_STREQ("MNT", decoded->get_gas_coin().c_str());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_EQ(minter::testnet, decoded->get_chain_id());
    auto data = decoded->get_data<minter::tx_buy_coin>();
    ASSERT_STREQ("TEST", data->get_coin_to_buy().c_str());
    ASSERT_STREQ("MNT", data->get_coin_to_sell().c_str());
    ASSERT_EQ(dev::bigdec18("1"), data->get_value_to_buy());
    ASSERT_EQ(dev::bigdec18("1"), data->get_max_value_to_sell());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
}

TEST(TxBuy, TestValuePrecisionEncodeDecode) {
    minter::data::private_key pk = "07bc17abdcee8b971bb8723e36fe9d2523306d5ab2d683631693238e0f9df142";

    auto tx = minter::new_tx()
            ->set_nonce("1")
            .set_gas_price("1")
            .set_gas_coin("MNT")
            .set_chain_id(minter::testnet)
            .tx_buy_coin()
            ->set_coin_to_buy("TEST")
            .set_coin_to_sell("MNT")
            .set_value_to_buy("1")
            .set_max_value_to_sell("1.102030405060708090")
            .build();
    auto signature = tx->sign_single(pk);

    auto decoded = minter::tx::decode(signature.get());
    std::shared_ptr<minter::tx_buy_coin> data = decoded->get_data<minter::tx_buy_coin>();
    ASSERT_EQ(dev::bigdec18("1.102030405060708090"), data->get_max_value_to_sell());

}
