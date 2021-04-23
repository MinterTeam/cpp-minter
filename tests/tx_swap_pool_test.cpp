/*!
 * minter_tx.
 * tx_swap_pool_test.cpp.c
 *
 * \date 03/23/2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/public_key.h>
#include <minter/tx.hpp>
#include <minter/tx/signature_data.h>
#include <minter/tx/tx.h>
#include <minter/tx/tx_buy_swap_pool.h>
#include <minter/tx/tx_create_swap_pool.h>
#include <minter/tx/tx_sell_all_swap_pool.h>
#include <minter/tx/tx_sell_swap_pool.h>

TEST(TxSellSwapPool, Encode) {
    const char* expected = "f867050201801797d6c201808901158e460913d00000881bc16d674ec80000808001b845f8431ba0611042d1f370f47b75eace3257b834cc2f375830cb197c04a2228e73a538c4d6a0240c53f61c9b1672deff03945ecacfc40b7c884608a1e9d9b38bd3a7bd97a42b";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("5");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_sell_swap_pool();
    data->add_coin(dev::bigint("1"));
    data->set_value_to_sell("20");
    data->add_coin(dev::bigint("0"));
    data->set_min_value_to_buy("2");
    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxSellSwapPool, Decode) {
    const char* encoded = "f867050201801797d6c201808901158e460913d00000881bc16d674ec80000808001b845f8431ba0611042d1f370f47b75eace3257b834cc2f375830cb197c04a2228e73a538c4d6a0240c53f61c9b1672deff03945ecacfc40b7c884608a1e9d9b38bd3a7bd97a42b";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_sell_swap_pool>();

    ASSERT_EQ(0x17, decoded->get_type());

    ASSERT_EQ(2, data->get_coins().size());
    ASSERT_EQ(dev::bigint("1"), data->get_coins()[0]);
    ASSERT_EQ(dev::bigint("0"), data->get_coins()[1]);
    ASSERT_EQ(dev::bigdec18("20"), data->get_value_to_sell());
    ASSERT_EQ(dev::bigdec18("2"), data->get_min_value_to_buy());
}

TEST(TxBuySwapPool, Encode) {
    const char* expected = "f8680e0201801898d7c201808829a2241af62c00008a010f0cf064dd59200000808001b845f8431ba093595885945dd86ea07a12b8b529818e18540ae1634b1e89cdeb2ce4208e3df4a0564379c69603715b511bc4f890cf9212751c21c9b99257c7a58070f469e1c399";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("14");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_buy_swap_pool();
    data->add_coin(dev::bigint("1"));
    data->set_value_to_buy("3");
    data->add_coin(dev::bigint("0"));
    data->set_max_value_to_sell("5000");
    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxBuySwapPool, Decode) {
    const char* encoded = "f8680e0201801898d7c201808829a2241af62c00008a010f0cf064dd59200000808001b845f8431ba093595885945dd86ea07a12b8b529818e18540ae1634b1e89cdeb2ce4208e3df4a0564379c69603715b511bc4f890cf9212751c21c9b99257c7a58070f469e1c399";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_buy_swap_pool>();

    ASSERT_EQ(minter::tx_buy_swap_pool_type.type(), decoded->get_type());

    ASSERT_EQ(2, data->get_coins().size());
    ASSERT_EQ(dev::bigint("1"), data->get_coins()[0]);
    ASSERT_EQ(dev::bigint("0"), data->get_coins()[1]);
    ASSERT_EQ(dev::bigdec18("3"), data->get_value_to_buy());
    ASSERT_EQ(dev::bigdec18("5000"), data->get_max_value_to_sell());
}

TEST(TxSellAllSwapPool, Encode) {
    const char* expected = "f85f10020180198fcec301040589056bc75e2d63100000808001b845f8431ca095651bdd2afa8964213f7bc064898b0edeb67fa39f3a0c71b52934f6463412afa0604ced9ff973bf1de6b252c9582982780cf1de4fd2b2e3814bfa8185d10bd6f5";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("16");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_sell_all_swap_pool();
    data->add_coin(dev::bigint("1"));
    data->add_coin(dev::bigint("4"));
    data->add_coin(dev::bigint("5"));
    data->set_min_value_to_buy("100");
    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxSellAllSwapPool, Decode) {
    const char* encoded = "f85f10020180198fcec301040589056bc75e2d63100000808001b845f8431ca095651bdd2afa8964213f7bc064898b0edeb67fa39f3a0c71b52934f6463412afa0604ced9ff973bf1de6b252c9582982780cf1de4fd2b2e3814bfa8185d10bd6f5";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_sell_all_swap_pool>();

    ASSERT_EQ(minter::tx_sell_all_swap_pool_type.type(), decoded->get_type());

    ASSERT_EQ(3, data->get_coins().size());
    ASSERT_EQ(dev::bigint("1"), data->get_coins()[0]);
    ASSERT_EQ(dev::bigint("4"), data->get_coins()[1]);
    ASSERT_EQ(dev::bigint("5"), data->get_coins()[2]);
    ASSERT_EQ(dev::bigdec18("100"), data->get_min_value_to_buy());
}

TEST(TxCreateSwapPool, Encode) {
    const char* expected = "f8691a0201802299d803048a010f0cf064dd592000008a021e19e0c9bab2400000808001b845f8431ca0ba14d8ae3bb24ea063470a63185e4f590e624babd5767b294f49b8a645279d4da048737a80238a4b5e3e1218f7e70b964929c2ca0337ca4b8a8710550c83acf6d3";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("26");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_create_swap_pool();
    data->set_coin_0("3");
    data->set_coin_1("4");
    data->set_volume_0("5000");
    data->set_volume_1("10000");

    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxCreateSwapPool, Decode) {
    const char* encoded = "f8691a0201802299d803048a010f0cf064dd592000008a021e19e0c9bab2400000808001b845f8431ca0ba14d8ae3bb24ea063470a63185e4f590e624babd5767b294f49b8a645279d4da048737a80238a4b5e3e1218f7e70b964929c2ca0337ca4b8a8710550c83acf6d3";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_create_swap_pool>();

    ASSERT_EQ(minter::tx_create_swap_pool_type.type(), decoded->get_type());

    ASSERT_EQ(dev::bigint("3"), data->get_coin_0());
    ASSERT_EQ(dev::bigint("4"), data->get_coin_1());
    ASSERT_EQ(dev::bigdec18("5000"), data->get_volume_0());
    ASSERT_EQ(dev::bigdec18("10000"), data->get_volume_1());
}