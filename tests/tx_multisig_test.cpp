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
    const char* expectedTx = "f901270102018a4d4e540000000000000001aae98a4d4e540000000000000094d82558ea00eb81d35f2654953598f5d51737d31d880de0b6b3a7640000808002b8e8f8e694db4f4b6942cb927e8d7e3a1f602d0f1fb43b5bd2f8cff8431ca0a116e33d2fea86a213577fc9dae16a7e4cadb375499f378b33cddd1d4113b6c1a021ee1e9eb61bbd24233a0967e1c745ab23001cf8816bb217d01ed4595c6cb2cdf8431ca0f7f9c7a6734ab2db210356161f2d012aa9936ee506d88d8d0cba15ad6c84f8a7a04b71b87cbbe7905942de839211daa984325a15bdeca6eea75e5d0f28f9aaeef8f8431ba0d8c640d7605034eefc8870a6a3d1c22e2f589a9319288342632b1c4e6ce35128a055fe3f93f31044033fe7b07963d547ac50bccaac38a057ce61665374c72fb454";
    minter::address_t sender("Mxdb4f4b6942cb927e8d7e3a1f602d0f1fb43b5bd2");
    minter::privkey_t pk1("b354c3d1d456d5a1ddd65ca05fd710117701ec69d82dac1858986049a0385af9");
    minter::privkey_t pk2("38b7dfb77426247aed6081f769ed8f62aaec2ee2b38336110ac4f7484478dccb");
    minter::privkey_t pk3("94c0915734f92dd66acfdc48f82b1d0b208efd544fe763386160ec30c968b4af");

    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("1");
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin("MNT");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to("Mxd82558ea00eb81d35f2654953598f5d51737d31d");
    data->set_value("1");
    data->set_coin("MNT");
    auto tx = data->build();

    dev::bytes_data sign = tx->sign_multiple(sender, {pk1, pk2, pk3});
    ASSERT_STREQ(expectedTx, sign.to_hex().c_str());

    // Decode
    std::shared_ptr<minter::tx> decoded = minter::tx::decode(sign);
    ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
    ASSERT_STREQ("MNT", decoded->get_gas_coin().c_str());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_EQ(minter::testnet, decoded->get_chain_id());
    std::shared_ptr<minter::tx_send_coin> dec_data = decoded->get_data<minter::tx_send_coin>();
    ASSERT_EQ(minter::address_t("Mxd82558ea00eb81d35f2654953598f5d51737d31d"), dec_data->get_to());
    ASSERT_EQ(dev::bigdec18("1"), dec_data->get_value());
    ASSERT_STREQ("MNT", dec_data->get_coin().c_str());

    auto sig_data = decoded->get_signature_data<minter::signature_multi_data>();
    ASSERT_EQ(3, sig_data->get_signs().size());
    ASSERT_EQ(sender, sig_data->get_address());
    ASSERT_EQ(tx->get_signature_data<minter::signature_multi_data>()->get_signs().at(0), sig_data->get_signs().at(0));
    ASSERT_EQ(tx->get_signature_data<minter::signature_multi_data>()->get_signs().at(1), sig_data->get_signs().at(1));
    ASSERT_EQ(tx->get_signature_data<minter::signature_multi_data>()->get_signs().at(2), sig_data->get_signs().at(2));
}

TEST(TxMultisig, TestExternalMultisig) {
    const char* expectedTx = "f901270102018a4d4e540000000000000001aae98a4d4e540000000000000094d82558ea00eb81d35f2654953598f5d51737d31d880de0b6b3a7640000808002b8e8f8e694db4f4b6942cb927e8d7e3a1f602d0f1fb43b5bd2f8cff8431ca0a116e33d2fea86a213577fc9dae16a7e4cadb375499f378b33cddd1d4113b6c1a021ee1e9eb61bbd24233a0967e1c745ab23001cf8816bb217d01ed4595c6cb2cdf8431ca0f7f9c7a6734ab2db210356161f2d012aa9936ee506d88d8d0cba15ad6c84f8a7a04b71b87cbbe7905942de839211daa984325a15bdeca6eea75e5d0f28f9aaeef8f8431ba0d8c640d7605034eefc8870a6a3d1c22e2f589a9319288342632b1c4e6ce35128a055fe3f93f31044033fe7b07963d547ac50bccaac38a057ce61665374c72fb454";
    minter::address_t sender("Mxdb4f4b6942cb927e8d7e3a1f602d0f1fb43b5bd2");
    minter::privkey_t pk1("b354c3d1d456d5a1ddd65ca05fd710117701ec69d82dac1858986049a0385af9");
    minter::privkey_t pk2("38b7dfb77426247aed6081f769ed8f62aaec2ee2b38336110ac4f7484478dccb");
    minter::privkey_t pk3("94c0915734f92dd66acfdc48f82b1d0b208efd544fe763386160ec30c968b4af");

    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("1");
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin("MNT");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to("Mxd82558ea00eb81d35f2654953598f5d51737d31d");
    data->set_value("1");
    data->set_coin("MNT");
    auto tx = data->build();

    minter::signature s1 = tx->sign_only_multiple(pk1);
    minter::signature s2 = tx->sign_only_multiple(pk2);
    minter::signature s3 = tx->sign_only_multiple(pk3);

    dev::bytes_data sign = tx->sign_multiple_external(sender, {s1, s2, s3});
    ASSERT_STREQ(expectedTx, sign.to_hex().c_str());
}