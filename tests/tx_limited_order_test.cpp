/*!
 * minter_tx.
 * tx_limited_order_test.cpp
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_add_limited_order.h>
#include <minter/tx/tx_remove_limited_order.h>

TEST(TxLimitedOrder, AddEncode) {
    const char* expected = "f866010101802396d58089056bc75e2d6310000001888ac7230489e80000808001b845f8431ba0f82dc29e01144885b8118d779003232de17ba5b8977d2f4f9092c9bb820ec543a05628e1418fc5497409c30c77035b2709b62a8f37b285dc3129afa5793e768ddb";

    minter::data::private_key pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_nonce("1")
                  .set_gas_price("1")
                  .set_gas_coin_id(minter::def_coin_id)
                  .set_chain_id(minter::mainnet)
                  .tx_add_limited_order()
                  ->set_coin_id_to_sell("0")
                  .set_coin_id_to_buy("1")
                  .set_value_to_sell("100")
                  .set_value_to_buy("10")
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxLimitedOrder, AddDecode) {
    const char* encoded = "f866010101802396d58089056bc75e2d6310000001888ac7230489e80000808001b845f8431ba0f82dc29e01144885b8118d779003232de17ba5b8977d2f4f9092c9bb820ec543a05628e1418fc5497409c30c77035b2709b62a8f37b285dc3129afa5793e768ddb";
    auto decoded = minter::tx::decode(encoded);

    ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_EQ(minter::mainnet, decoded->get_chain_id());
    auto data = decoded->get_data<minter::tx_add_limited_order>();
    ASSERT_EQ(dev::bigint("0"), data->get_coin_id_to_sell());
    ASSERT_EQ(dev::bigint("1"), data->get_coin_id_to_buy());
    ASSERT_EQ(dev::bigdec18("100"), data->get_value_to_sell());
    ASSERT_EQ(dev::bigdec18("10"), data->get_value_to_buy());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
}

TEST(TxLimitedOrder, RemoveEncode) {
    const char* expected = "f855010101802485c48301e240808001b845f8431ca05e9d0fbe963c86ac9a851c9a1eb3bf40b61f7e88b1a4c4366cf9912a9cc8f292a06f871d2d4cebe385b1374ad964cfdeec1cf8965b93b7a6317aaf4503fe6f293b";

    minter::data::private_key pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_nonce("1")
                  .set_gas_price("1")
                  .set_gas_coin_id(minter::def_coin_id)
                  .set_chain_id(minter::mainnet)
                  .tx_remove_limited_order()
                  ->set_id("123456")
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxLimitedOrder, RemoveDecode) {
    const char* encoded = "f855010101802485c48301e240808001b845f8431ca05e9d0fbe963c86ac9a851c9a1eb3bf40b61f7e88b1a4c4366cf9912a9cc8f292a06f871d2d4cebe385b1374ad964cfdeec1cf8965b93b7a6317aaf4503fe6f293b";
    auto decoded = minter::tx::decode(encoded);

    ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_EQ(minter::mainnet, decoded->get_chain_id());
    auto data = decoded->get_data<minter::tx_remove_limited_order>();
    ASSERT_EQ(dev::bigint("123456"), data->get_id());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
}