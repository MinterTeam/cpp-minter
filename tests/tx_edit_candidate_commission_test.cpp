/*!
 * minter_tx.
 * tx_edit_candidate_commission_test.cpp.c
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
#include <minter/tx/tx_edit_candidate_commission.h>

TEST(TxEditCandidateCommission, Encode) {
    const char* expected = "f873010201801aa3e2a0fffffffff1000fffffffffffffffffffffffffffffffffffffffffffffffffff32808001b845f8431ca00f7c12972d0694f2eaa0b18f866ded2ab3b17060636c2e4a2046a6d2d01456e9a03b8035b65c787f1f3f7c5582f8a3cb6c96d06b6a146ab64fb3966fc4584f8937";
    minter::privkey_t pk = "474ad4c6517502f3f939e276ae619f494d586a9b6cae81d63f8287dda0aabd4f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_gas_coin_id("0");
    tx_builder->set_gas_price("1");
    tx_builder->set_nonce("1");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_edit_candidate_commission();
    data->set_commission(50);
    data->set_pub_key("Mpfffffffff1000fffffffffffffffffffffffffffffffffffffffffffffffffff");
    auto tx_result = data->build();
    auto signature = tx_result->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxEditCandidateCommission, Decode) {
    const char* encoded = "f873010201801aa3e2a0fffffffff1000fffffffffffffffffffffffffffffffffffffffffffffffffff32808001b845f8431ca00f7c12972d0694f2eaa0b18f866ded2ab3b17060636c2e4a2046a6d2d01456e9a03b8035b65c787f1f3f7c5582f8a3cb6c96d06b6a146ab64fb3966fc4584f8937";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_edit_candidate_commission>();

    ASSERT_EQ(minter::tx_edit_candidate_commission_type.type(), decoded->get_type());

    ASSERT_EQ(minter::pubkey_t("Mpfffffffff1000fffffffffffffffffffffffffffffffffffffffffffffffffff"), data->get_pub_key());
    ASSERT_EQ(50, data->get_commission());
}