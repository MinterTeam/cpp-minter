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
    minter::privkey_t priv_key("4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e");
    const char* valid_tx = "f880080101800cb0ef03c20102ea9467691076548b20234461ff6fd2bc9c64393eb8fc94c26dbd06984949a0efce1517925ca57a8d7a2c06808001b845f8431ba077b3ac0b0605279239bdcec12a698f7beb2c5d9d213c2cdc90638b3da020bbeaa021f4a509eaa7e93bc77901de3061d98e092c9ce1c414ad779a92804aedf4eb97";
    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce(dev::bigint("8"));
    tx_builder->set_gas_price(dev::bigint("1"));
    tx_builder->set_gas_coin_id(minter::def_coin_id);
    tx_builder->set_chain_id(minter::mainnet);
    auto tx_data = tx_builder->tx_create_multisig_address();
    tx_data->set_threshold(3);
    tx_data->add_address("Mx67691076548b20234461ff6fd2bc9c64393eb8fc", 1);
    tx_data->add_address("Mxc26dbd06984949a0efce1517925ca57a8d7a2c06", 2);
    auto tx = tx_data->build();

    auto sign = tx->sign_single(priv_key);

    ASSERT_STREQ(valid_tx, sign.to_hex().c_str());
}

TEST(TxCreateMultisigAddress, TestDecode) {
    const char* valid_tx = "f880080101800cb0ef03c20102ea9467691076548b20234461ff6fd2bc9c64393eb8fc94c26dbd06984949a0efce1517925ca57a8d7a2c06808001b845f8431ba077b3ac0b0605279239bdcec12a698f7beb2c5d9d213c2cdc90638b3da020bbeaa021f4a509eaa7e93bc77901de3061d98e092c9ce1c414ad779a92804aedf4eb97";
    auto tx = minter::tx::decode(valid_tx);
    ASSERT_EQ(dev::bigint("8"), tx->get_nonce());
    ASSERT_EQ(dev::bigint("1"), tx->get_gas_price());
    ASSERT_EQ(minter::def_coin_id, tx->get_gas_coin_id());
    ASSERT_EQ(minter::mainnet, tx->get_chain_id());

    auto data = tx->get_data<minter::tx_create_multisig_address>();
    ASSERT_EQ(3, data->get_threshold());
    ASSERT_EQ(2, data->get_addresses().size());
    ASSERT_EQ(minter::address_t("Mx67691076548b20234461ff6fd2bc9c64393eb8fc"), data->get_addresses().at(0));
    ASSERT_EQ(minter::address_t("Mxc26dbd06984949a0efce1517925ca57a8d7a2c06"), data->get_addresses().at(1));
    ASSERT_EQ(1, data->get_weights().at(0));
    ASSERT_EQ(2, data->get_weights().at(1));
}