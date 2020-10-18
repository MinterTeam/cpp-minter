/*!
 * minter_tx.
 * tx_edit_multisig_owners_data_test.cpp
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx/tx.h>
#include <minter/tx/tx_builder.h>
#include <minter/tx/tx_edit_multisig.h>

TEST(TxEditMultisigOwnersData, TestEncode) {
    const char* expected = "f8800801018012b0ef03c20102ea9467691076548b20234461ff6fd2bc9c64393eb8fc94c26dbd06984949a0efce1517925ca57a8d7a2c06808001b845f8431ca02da06551a97e23cefd1f0aecdbbb4ae5a40bf412a817a38c59d89ff18c33520ca06a758b304bb363e34746284db3df1809c6f17506726eab8378d59063ddd93764";
    minter::privkey_t pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";

    //addAddress("Mx67691076548b20234461ff6fd2bc9c64393eb8fc", 1)
    //                .addAddress("Mxc26dbd06984949a0efce1517925ca57a8d7a2c06", 2)
    //                .setThreshold(3)
    auto tx = minter::new_tx()
                  ->set_gas_coin_id(dev::bigint("0"))
                  .set_nonce(dev::bigint("8"))
                  .set_gas_price("1")
                  .set_chain_id(minter::mainnet)
                  .tx_edit_multisig()
                  ->add_address(minter::address_t("Mx67691076548b20234461ff6fd2bc9c64393eb8fc"), 1)
                  .add_address(minter::address_t("Mxc26dbd06984949a0efce1517925ca57a8d7a2c06"), 2)
                  .set_threshold(3)
                  .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxEditMultisigOwnersData, TestDecode) {
    const char* encoded = "f8800801018012b0ef03c20102ea9467691076548b20234461ff6fd2bc9c64393eb8fc94c26dbd06984949a0efce1517925ca57a8d7a2c06808001b845f8431ca02da06551a97e23cefd1f0aecdbbb4ae5a40bf412a817a38c59d89ff18c33520ca06a758b304bb363e34746284db3df1809c6f17506726eab8378d59063ddd93764";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_edit_multisig>();

    ASSERT_EQ(2, data->get_addresses().size());
    ASSERT_EQ(2, data->get_weights().size());
    ASSERT_EQ(3, data->get_threshold());

    minter::address_t a1 = data->get_addresses()[0];
    minter::address_t a2 = data->get_addresses()[1];

    ASSERT_EQ(minter::address_t("Mx67691076548b20234461ff6fd2bc9c64393eb8fc"), a1);
    ASSERT_EQ(minter::address_t("Mxc26dbd06984949a0efce1517925ca57a8d7a2c06"), a2);

    dev::bigint w1 = data->get_weights()[0];
    dev::bigint w2 = data->get_weights()[1];

    ASSERT_EQ(dev::bigint("1"), w1);
    ASSERT_EQ(dev::bigint("2"), w2);
}