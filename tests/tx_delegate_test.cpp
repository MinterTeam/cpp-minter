/*!
 * minter_tx.
 * tx_delegate_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/public_key.h>
#include <minter/tx.hpp>
#include <minter/tx/signature_data.h>
#include <minter/tx/tx_delegate.h>
#include <minter/tx/tx_unbond.h>
#include <minter/tx/utils.h>

TEST(TxDelegate, TestEncode) {
    const char* expected = "f87e0501018007aeeda00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe8808a021e19e0c9bab2400000808001b845f8431ba0b23e03cb8d8f87dc0716ce4a42f6fbad50c173562e29fc2ee4610691c6d131eda022593f96278c49319b28b4651201ae6ae8777a34739841ac55c40c3bcae96a07";
    minter::privkey_t pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";
    minter::pubkey_t pub = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe8";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("5");
    tx_builder->set_chain_id(minter::mainnet);
    auto data = tx_builder->tx_delegate();
    data->set_pub_key(pub);
    data->set_coin_id("0");
    data->set_stake("10000");
    auto tx_result = data->build();

    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxDelegate, TestDecode) {
    const char* encoded = "f87e0501018007aeeda00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe8808a021e19e0c9bab2400000808001b845f8431ba0b23e03cb8d8f87dc0716ce4a42f6fbad50c173562e29fc2ee4610691c6d131eda022593f96278c49319b28b4651201ae6ae8777a34739841ac55c40c3bcae96a07";
    minter::pubkey_t pub = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe8";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_delegate>();

    ASSERT_EQ(dev::bigint("0"), data->get_coin_id());
    ASSERT_EQ(dev::bigdec18("10000"), data->get_stake());
    ASSERT_EQ(pub, data->get_pub_key());
}

TEST(TxUnbond, TestEncode) {
    const char* expected = "f87c0701018008aceba00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe880880e92596fd6290000808001b845f8431ba00d60995f30fccc40de871a7264c748a21220ee3cd8f88e8bc893163f4f735d04a0103498704eeb2368a9b95b7baf60a2c92f949aa98be9acd78b0fb8999b75a8fd";
    minter::pubkey_t pub = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe8";
    minter::privkey_t pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    auto tx = minter::new_tx()
                  ->set_nonce("7")
                  .set_gas_price("1")
                  .set_gas_coin_id("0")
                  .set_chain_id(minter::mainnet)
                  .tx_unbond()
                  ->set_pub_key(pub)
                  .set_coin_id("0")
                  .set_value("1.05")
                  .build();

    auto signature = tx->sign_single(pk);
    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxUnbond, TestDecode) {
    const char* encoded = "f87c0701018008aceba00208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe880880e92596fd6290000808001b845f8431ba00d60995f30fccc40de871a7264c748a21220ee3cd8f88e8bc893163f4f735d04a0103498704eeb2368a9b95b7baf60a2c92f949aa98be9acd78b0fb8999b75a8fd";
    minter::pubkey_t pub = "Mp0208f8a2bd535f65ecbe4b057b3b3c5fbfef6003b0713dc37b697b1d19153fe8";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_unbond>();

    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_EQ(minter::mainnet, decoded->get_chain_id());
    ASSERT_EQ(dev::bigint("7"), decoded->get_nonce());
    ASSERT_EQ((uint8_t) 0x08, decoded->get_type());
    ASSERT_EQ(dev::bytes(0), decoded->get_service_data());
    ASSERT_EQ(dev::bytes(0), decoded->get_payload());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());

    ASSERT_EQ(dev::bigint("0"), data->get_coin_id());
    ASSERT_EQ(dev::bigdec18("1.05"), data->get_value());
    ASSERT_EQ(pub, data->get_pub_key());

    const char* R = "0d60995f30fccc40de871a7264c748a21220ee3cd8f88e8bc893163f4f735d04";
    const char* S = "103498704eeb2368a9b95b7baf60a2c92f949aa98be9acd78b0fb8999b75a8fd";
    const char* V = "1b";

    auto sign_data = decoded->get_signature_data<minter::signature_single_data>();
    dev::bytes_data r = sign_data->get_r();
    dev::bytes_data s = sign_data->get_s();
    dev::bytes_data v = sign_data->get_v();
    ASSERT_STREQ(R, r.to_hex().c_str());
    ASSERT_STREQ(S, s.to_hex().c_str());
    ASSERT_STREQ(V, v.to_hex().c_str());
}