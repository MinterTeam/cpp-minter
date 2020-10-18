//
// Created by edwardstock on 26.04.19.
//
#include <gtest/gtest.h>
#include <iostream>
#include <minter/tx.hpp>
#include <minter/tx/tx_buy_coin.h>

TEST(TxBuy, TestEncode) {

    const char* expected = "f865020101800495d40187038d7ea4c680008089056bc75e2d63100000808001b845f8431ca0f64de1594ea6ea7717a2161771a429a2202e78ae4f1bf628a8c2e12a2df13e4aa04b8eb64ef9e7574983cc66960e98829fd93ab61fd2d7794c3e8810970e9e3693";

    minter::data::private_key pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_nonce("2")
                  .set_gas_price("1")
                  .set_gas_coin_id(minter::def_coin_id)
                  .set_chain_id(minter::mainnet)
                  .tx_buy_coin()
                  ->set_coin_id_to_buy(dev::bigint("1"))
                  .set_coin_id_to_sell(minter::def_coin_id)
                  .set_value_to_buy("0.001")
                  .set_max_value_to_sell("100")
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxBuy, TestDecode) {
    const char* encoded = "f865020101800495d40187038d7ea4c680008089056bc75e2d63100000808001b845f8431ca0f64de1594ea6ea7717a2161771a429a2202e78ae4f1bf628a8c2e12a2df13e4aa04b8eb64ef9e7574983cc66960e98829fd93ab61fd2d7794c3e8810970e9e3693";
    auto decoded = minter::tx::decode(encoded);

    ASSERT_EQ(dev::bigint("2"), decoded->get_nonce());
    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_EQ(minter::mainnet, decoded->get_chain_id());
    auto data = decoded->get_data<minter::tx_buy_coin>();
    ASSERT_EQ(dev::bigint("1"), data->get_coin_id_to_buy());
    ASSERT_EQ(dev::bigint("0"), data->get_coin_id_to_sell());
    ASSERT_EQ(dev::bigdec18("0.001"), data->get_value_to_buy());
    ASSERT_EQ(dev::bigdec18("100"), data->get_max_value_to_sell());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
}

TEST(TxBuy, TestValuePrecisionEncodeDecode) {
    minter::data::private_key pk = "07bc17abdcee8b971bb8723e36fe9d2523306d5ab2d683631693238e0f9df142";

    auto tx = minter::new_tx()
                  ->set_nonce("1")
                  .set_gas_price("1")
                  .set_gas_coin_id(dev::bigint("0"))
                  .set_chain_id(minter::testnet)
                  .tx_buy_coin()
                  ->set_coin_id_to_buy(dev::bigint("1"))
                  .set_coin_id_to_sell(minter::def_coin_id)
                  .set_value_to_buy("0.001")
                  .set_max_value_to_sell("1.102030405060708090")
                  .build();
    auto signature = tx->sign_single(pk);

    auto decoded = minter::tx::decode(signature.get());
    std::shared_ptr<minter::tx_buy_coin> data = decoded->get_data<minter::tx_buy_coin>();
    ASSERT_EQ(dev::bigdec18("1.102030405060708090"), data->get_max_value_to_sell());
}
