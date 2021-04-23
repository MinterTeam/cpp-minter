/*!
 * minter_tx.
 * tx_liquidity_add_remove_test.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include <gtest/gtest.h>
#include <minter/public_key.h>
#include <minter/tx.hpp>
#include <minter/tx/signature_data.h>
#include <minter/tx/tx.h>
#include <minter/tx/tx_add_liquidity.h>
#include <minter/tx/tx_remove_liquidity.h>

TEST(TxAddLiquidity, Encode) {
    const char* expected = "f8670d0201801597d68001890d8d726b7177a80000891b1ae4d6e2ef500000808001b845f8431ba0a213c7ac638e399cc4f85047bfab2da6ace86fa77e0497a3592737cb2ddcfff3a00a261dcbfa6ec0f51028756a8eec571464828a53f1c09666b6d45b7a9c617259";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("13");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_add_liquidity();
    data->set_coin_0("0");
    data->set_coin_1("1");
    data->set_volume_0("250");
    data->set_max_volume_1("500");
    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxAddLiquidity, Decode) {
    const char* encoded = "f8670d0201801597d68001890d8d726b7177a80000891b1ae4d6e2ef500000808001b845f8431ba0a213c7ac638e399cc4f85047bfab2da6ace86fa77e0497a3592737cb2ddcfff3a00a261dcbfa6ec0f51028756a8eec571464828a53f1c09666b6d45b7a9c617259";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_add_liquidity>();

    ASSERT_EQ(minter::tx_add_liquidity_type.type(), decoded->get_type());
    ASSERT_EQ(dev::bigint("0"), data->get_coin_0());
    ASSERT_EQ(dev::bigint("1"), data->get_coin_1());
    ASSERT_EQ(dev::bigdec18("250"), data->get_volume_0());
    ASSERT_EQ(dev::bigdec18("500"), data->get_max_volume_1());
}

TEST(TxRemoveLiquidity, Encode) {
    const char* expected = "f8700602018016a0df800189056bc75e2d6310000089015af1d78b58c4000088d02ab486cedc0000808001b845f8431ba0566d458644b591b770f9dd65be6edba084a16564c0a73f182d3412585bff1688a01887bdd283e4aaae59a3dc10b5c9d12d239bde89d989040b29454a000fa1a001";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("6");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_remove_liquidity();
    data->set_coin_0("0");
    data->set_coin_1("1");
    data->set_liquidity("100");
    data->set_min_volume_0("25");
    data->set_min_volume_1("15");
    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxRemoveLiquidity, Decode) {
    const char* encoded = "f8700602018016a0df800189056bc75e2d6310000089015af1d78b58c4000088d02ab486cedc0000808001b845f8431ba0566d458644b591b770f9dd65be6edba084a16564c0a73f182d3412585bff1688a01887bdd283e4aaae59a3dc10b5c9d12d239bde89d989040b29454a000fa1a001";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_remove_liquidity>();

    ASSERT_EQ(minter::tx_remove_liquidity_type.type(), decoded->get_type());
    ASSERT_EQ(dev::bigint("0"), data->get_coin_0());
    ASSERT_EQ(dev::bigint("1"), data->get_coin_1());
    ASSERT_EQ(dev::bigdec18("25"), data->get_min_volume_0());
    ASSERT_EQ(dev::bigdec18("15"), data->get_min_volume_1());
}