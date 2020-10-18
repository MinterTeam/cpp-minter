/*!
 * minter_tx.
 * tx_multisig_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx.hpp>
#include <minter/tx/tx_builder.h>
#include <minter/tx/tx_send_coin.h>

TEST(TxMultisig, TestSimpleMultiSign) {
    const char* expectedTx = "f901130101018001a0df8094d82558ea00eb81d35f2654953598f5d51737d31d880de0b6b3a7640000808002b8e8f8e694db4f4b6942cb927e8d7e3a1f602d0f1fb43b5bd2f8cff8431ba0029ec2170c2d90684c155371f203ae3d74e4c1d509217cab9b22874243f8cf17a022f8699efde34f462a3791702a0d4f574b01a30947ad109aacd2f84c2e2ea2c3f8431ca06cfcd1bcd6d098361954dc7e863252203bbac403df5ca9bae291ef725e1c5130a060f13e16070c5cecd58307b1ebea51eca3efa35bbb029820dcc9ecf31eb08191f8431ca03c915c5e55bd306be2e23d78aa47ad73bfd2b37dbbe844dd971c165d61102e5ca016383167ad10fbe1ae0a7d15b92d75ae3ab2206047055eb15f96184845026c6a";
    minter::address_t sender("Mxdb4f4b6942cb927e8d7e3a1f602d0f1fb43b5bd2");
    minter::privkey_t pk1("b354c3d1d456d5a1ddd65ca05fd710117701ec69d82dac1858986049a0385af9");
    minter::privkey_t pk2("38b7dfb77426247aed6081f769ed8f62aaec2ee2b38336110ac4f7484478dccb");
    minter::privkey_t pk3("94c0915734f92dd66acfdc48f82b1d0b208efd544fe763386160ec30c968b4af");

    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("1");
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_chain_id(minter::mainnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to("Mxd82558ea00eb81d35f2654953598f5d51737d31d");
    data->set_value("1");
    data->set_coin_id("0");
    auto tx = data->build();

    dev::bytes_data sign = tx->sign_multiple(sender, {pk1, pk2, pk3});
    ASSERT_STREQ(expectedTx, sign.to_hex().c_str());

    // Decode
    std::shared_ptr<minter::tx> decoded = minter::tx::decode(sign);
    ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
    ASSERT_EQ(dev::bigint("0"), decoded->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_EQ(minter::mainnet, decoded->get_chain_id());
    std::shared_ptr<minter::tx_send_coin> dec_data = decoded->get_data<minter::tx_send_coin>();
    ASSERT_EQ(minter::address_t("Mxd82558ea00eb81d35f2654953598f5d51737d31d"), dec_data->get_to());
    ASSERT_EQ(dev::bigdec18("1"), dec_data->get_value());
    ASSERT_EQ(dev::bigint("0"), dec_data->get_coin_id());

    auto sig_data = decoded->get_signature_data<minter::signature_multi_data>();
    ASSERT_EQ(3, sig_data->get_signs().size());
    ASSERT_EQ(sender, sig_data->get_address());
    ASSERT_EQ(tx->get_signature_data<minter::signature_multi_data>()->get_signs().at(0), sig_data->get_signs().at(0));
    ASSERT_EQ(tx->get_signature_data<minter::signature_multi_data>()->get_signs().at(1), sig_data->get_signs().at(1));
    ASSERT_EQ(tx->get_signature_data<minter::signature_multi_data>()->get_signs().at(2), sig_data->get_signs().at(2));
}

TEST(TxMultisig, TestExternalMultisig) {
    const char* expectedTx = "f901130102018001a0df8094d82558ea00eb81d35f2654953598f5d51737d31d880de0b6b3a7640000808002b8e8f8e694db4f4b6942cb927e8d7e3a1f602d0f1fb43b5bd2f8cff8431ba0d6e0e254e778d7561a8b04e08aafce2e7386df43f0f8ae018ee0364ba1690dfda037ce1cea1d2a41c1d6825fa15c71669a43142bb5eb7ba52ac6d2322dd1de2971f8431ba012b389e3dd031e3c7627c9ab8b808a0a657b03f14e7f18a65f49ba8f9a81c001a077d24311c974caf7a1fdf2c0c8c3a397734169dfd791074ffda220fbbd2b93aff8431ca0b6c8aedf7dfb6dfbd2808624a4c2f92e5895a60a93efc9806c2396c786de0daaa00a69ef06f735eb7e29c4bfc788be3ecb4f4f94d749756f692faa2c24fd303544";
    minter::address_t sender("Mxdb4f4b6942cb927e8d7e3a1f602d0f1fb43b5bd2");
    minter::privkey_t pk1("b354c3d1d456d5a1ddd65ca05fd710117701ec69d82dac1858986049a0385af9");
    minter::privkey_t pk2("38b7dfb77426247aed6081f769ed8f62aaec2ee2b38336110ac4f7484478dccb");
    minter::privkey_t pk3("94c0915734f92dd66acfdc48f82b1d0b208efd544fe763386160ec30c968b4af");

    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("1");
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to("Mxd82558ea00eb81d35f2654953598f5d51737d31d");
    data->set_value("1");
    data->set_coin_id("0");
    auto tx = data->build();

    minter::signature s1 = tx->sign_only_multiple(pk1);
    minter::signature s2 = tx->sign_only_multiple(pk2);
    minter::signature s3 = tx->sign_only_multiple(pk3);

    dev::bytes_data sign = tx->sign_multiple_external(sender, {s1, s2, s3});
    ASSERT_STREQ(expectedTx, sign.to_hex().c_str());
}