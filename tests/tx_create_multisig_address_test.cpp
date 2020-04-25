/*!
 * minter_tx.
 * tx_create_multisig_address_test.cpp
 *
 * \date 03/06/2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/check.h>
#include <minter/tx/tx_builder.h>
#include <minter/tx/tx_create_multisig_address.h>

TEST(TxCreateMultisigAddress, TestEncode) {
    minter::privkey_t priv_key("bc3503cae8c8561df5eadc4a9eda21d32c252a6c94cfae55b5310bf6085c8582");
    const char* valid_tx = "f8a30102018a4d4e54000000000000000cb848f84607c3010305f83f94ee81347211c72524338f9680072af9074433314394ee81347211c72524338f9680072af9074433314594ee81347211c72524338f9680072af90744333144808001b845f8431ca094eb41d39e6782f5539615cc66da7073d4283893f0b3ee2b2f36aee1eaeb7c57a037f90ffdb45eb9b6f4cf301b48e73a6a81df8182e605b656a52057537d264ab4";
    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce(dev::bigint("1"));
    tx_builder->set_gas_price(dev::bigint("1"));
    tx_builder->set_gas_coin("MNT");
    tx_builder->set_chain_id(minter::testnet);
    auto tx_data = tx_builder->tx_create_multisig_address();
    tx_data->set_threshold(7);
    tx_data->add_address("Mxee81347211c72524338f9680072af90744333143", 1);
    tx_data->add_address("Mxee81347211c72524338f9680072af90744333145", 3);
    tx_data->add_address("Mxee81347211c72524338f9680072af90744333144", 5);
    auto tx = tx_data->build();

    auto sign = tx->sign_single(priv_key);

    ASSERT_STREQ(valid_tx, sign.to_hex().c_str());
}

TEST(TxCreateMultisigAddress, TestDecode) {
    const char* valid_tx = "f8a30102018a4d4e54000000000000000cb848f84607c3010305f83f94ee81347211c72524338f9680072af9074433314394ee81347211c72524338f9680072af9074433314594ee81347211c72524338f9680072af90744333144808001b845f8431ca094eb41d39e6782f5539615cc66da7073d4283893f0b3ee2b2f36aee1eaeb7c57a037f90ffdb45eb9b6f4cf301b48e73a6a81df8182e605b656a52057537d264ab4";
    auto tx = minter::tx::decode(valid_tx);
    ASSERT_EQ(dev::bigint("1"), tx->get_nonce());
    ASSERT_EQ(dev::bigint("1"), tx->get_gas_price());
    ASSERT_STREQ("MNT", tx->get_gas_coin().c_str());
    ASSERT_EQ(minter::testnet, tx->get_chain_id());

    auto data = tx->get_data<minter::tx_create_multisig_address>();
    ASSERT_EQ(7, data->get_threshold());
    ASSERT_EQ(3, data->get_addresses().size());
    ASSERT_EQ(minter::address_t("Mxee81347211c72524338f9680072af90744333143"), data->get_addresses().at(0));
    ASSERT_EQ(minter::address_t("Mxee81347211c72524338f9680072af90744333145"), data->get_addresses().at(1));
    ASSERT_EQ(minter::address_t("Mxee81347211c72524338f9680072af90744333144"), data->get_addresses().at(2));
    ASSERT_EQ(1, data->get_weights().at(0));
    ASSERT_EQ(3, data->get_weights().at(1));
    ASSERT_EQ(5, data->get_weights().at(2));
}