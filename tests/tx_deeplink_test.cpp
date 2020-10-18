/*!
 * minter_tx.
 * tx_deeplink_test.cpp
 *
 * \date 04/25/2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <iostream>
#include <minter/tx.hpp>
#include <minter/tx/tx_deeplink.h>
#include <minter/tx/tx_send_coin.h>
#include <toolbox/data/base64.h>
#include <toolbox/strings.hpp>

TEST(TxDeeplink, TestDecode) {
    //https://testnet.bip.to/tx/5gGg34CU7tphu-mSm_iDr2si9XluS5JWO6SIiscjBInoAACAwAHA
    const std::string deeplinkRaw = "5gGg34CU7tphu-mSm_iDr2si9XluS5JWO6SIiscjBInoAACAwAHA";

    dev::bytes_data deepLinkData = dev::bytes_data::from_string_raw(deeplinkRaw);
    deepLinkData.switch_map(minter::utils::from_base64_web);

    std::shared_ptr<minter::tx_deeplink> deeplink = minter::tx_deeplink::decode(deepLinkData);
    std::shared_ptr<minter::tx> tx = deeplink->get_tx();
    std::shared_ptr<minter::tx_send_coin> tx_data = tx->get_data<minter::tx_send_coin>();

    // nonce actually is null
    ASSERT_EQ(dev::bigint("0"), tx->get_nonce());
    ASSERT_EQ(dev::bigint("1"), tx->get_gas_price());
    // even if gas coin id is undefined, it will be set to 0, as we can't handle 'undefined' or 'null' value
    ASSERT_EQ(dev::bigint("0"), tx->get_gas_coin_id());

    ASSERT_STREQ("Mxeeda61bbe9929bf883af6b22f5796e4b92563ba4", tx_data->get_to().to_string().c_str());
    ASSERT_EQ(dev::bigint("0"), tx_data->get_coin_id());
    ASSERT_EQ(dev::bigdec18("10"), tx_data->get_value());
}

TEST(TxDeeplink, TestEncode) {
    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce(dev::bigint("0"));
    tx_builder->set_gas_price(dev::bigint("1"));
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to("Mx8d008dffe2f9144a39a2094ebdedadad335e814f");
    data->set_value("1");
    data->set_coin_id("0");
    auto tx = data->build();

    ASSERT_STREQ(
        "fe6a1358106abbd3c4cf5d0f15569886c6eb3703528b4a369c5b808c5ad6283c",
        tx->get_unsigned_hash().to_hex().c_str());

    auto tx_deeplink = minter::tx_deeplink(std::move(tx));
    dev::bytes_data deeplinkRaw = tx_deeplink.encode();
    deeplinkRaw.switch_map(minter::utils::to_base64_web);

    // output is base64 for web
    //    std::cout << deeplinkRaw.to_string() << std::endl;

    ASSERT_STREQ("5gGg34CUjQCN_-L5FEo5oglOve2trTNegU-IDeC2s6dkAACAgAGA", deeplinkRaw.to_string().c_str());

    ASSERT_STREQ(
        "https://testnet.bip.to/tx/5gGg34CUjQCN_-L5FEo5oglOve2trTNegU-IDeC2s6dkAACAgAGA",
        tx_deeplink.to_url("https://testnet.bip.to").c_str());

    ASSERT_STREQ(
        "https://testnet.bip.to/tx/5gGg34CUjQCN_-L5FEo5oglOve2trTNegU-IDeC2s6dkAACAgAGA",
        tx_deeplink.to_url("https://testnet.bip.to/").c_str());

    ASSERT_STREQ(
        "https://bip.to/tx/5gGg34CUjQCN_-L5FEo5oglOve2trTNegU-IDeC2s6dkAACAgAGA",
        tx_deeplink.to_url().c_str());
}