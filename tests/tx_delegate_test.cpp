/*!
 * minter_tx.
 * tx_delegate_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <minter/tx.hpp>
#include <gtest/gtest.h>
#include <minter/public_key.h>
#include <minter/tx/signature_data.h>
#include <minter/tx/utils.h>

TEST(TxDelegate, TestEncode) {
    const char* expected = "f8900102018a4d4e540000000000000007b6f5a00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a438a4d4e5400000000000000888ac7230489e80000808001b845f8431ba01c2c8f702d80cf64da1e9bf1f07a52e2fee8721aebe419aa9f62260a98983f89a07ed297d71d9dc37a57ffe9bb16915dccc703d8c09f30da8aadb9d5dbab8c7da9";
    minter::privkey_t pk = "6e1df6ec69638d152f563c5eca6c13cdb5db4055861efc11ec1cdd578afd96bf";
    minter::pubkey_t pub = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";

    auto tx = minter::new_tx()
        ->set_gas_coin("MNT")
        .set_nonce("1")
        .set_gas_price("1")
        .set_chain_id(minter::testnet)
        .tx_delegate()
        ->set_pub_key(pub)
        .set_coin("MNT")
        .set_stake("10")
        .build();

    auto signature = tx->sign_single(pk);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxDelegate, TestDecode) {
    const char* encoded = "f8900102018a4d4e540000000000000007b6f5a00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a438a4d4e5400000000000000888ac7230489e80000808001b845f8431ba01c2c8f702d80cf64da1e9bf1f07a52e2fee8721aebe419aa9f62260a98983f89a07ed297d71d9dc37a57ffe9bb16915dccc703d8c09f30da8aadb9d5dbab8c7da9";
    minter::pubkey_t pub = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_delegate>();

    ASSERT_STREQ("MNT", data->get_coin().c_str());
    ASSERT_EQ(dev::bigdec18("10"), data->get_stake());
    ASSERT_EQ(pub, data->get_pub_key());
}

TEST(TxUnbond, TestEncode) {
    const char *expected = "f8900102018a4d4e540000000000000008b6f5a00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a438a4d4e5400000000000000888ac7230489e80000808001b845f8431ca0ff5766c85847b37a276f3f9d027fb7c99745920fa395c7bd399cedd8265c5e1da000791bcdfe4d1bc1e73ada7bf833103c828f22d83189dad2b22ad28a54aacf2a";
    minter::pubkey_t pub = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";
    minter::privkey_t pk = "6e1df6ec69638d152f563c5eca6c13cdb5db4055861efc11ec1cdd578afd96bf";

    ASSERT_EQ(0x0e, pub[0]);
    ASSERT_EQ(0x43, pub[31]);

    ASSERT_EQ(0x6e, pk[0]);
    ASSERT_EQ(0xbf, pk[31]);

    auto tx = minter::new_tx()
            ->set_nonce("1")
            .set_gas_price("1")
            .set_gas_coin("MNT")
            .set_chain_id(minter::testnet)
            .tx_unbond()
            ->set_pub_key(pub)
            .set_coin("MNT")
            .set_value("10")
            .build();

    auto signature = tx->sign_single(pk);

    {
        auto decoded = minter::tx::decode(signature.get());
        auto data = decoded->get_data<minter::tx_unbond>();

        const char* R = "ff5766c85847b37a276f3f9d027fb7c99745920fa395c7bd399cedd8265c5e1d";
        const char* S = "00791bcdfe4d1bc1e73ada7bf833103c828f22d83189dad2b22ad28a54aacf2a";
        const char* V = "1c";

        auto sign_data = decoded->get_signature_data<minter::signature_single_data>();
        minter::Data r = sign_data->get_r();
        minter::Data s = sign_data->get_s();
        minter::Data v = sign_data->get_v();
        ASSERT_STREQ(R, r.to_hex().c_str());
        ASSERT_STREQ(S, s.to_hex().c_str());
        ASSERT_STREQ(V, v.to_hex().c_str());
    }

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(TxUnbond, TestDecode) {
    const char* encoded = "f8900102018a4d4e540000000000000008b6f5a00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a438a4d4e5400000000000000888ac7230489e80000808001b845f8431ca0ff5766c85847b37a276f3f9d027fb7c99745920fa395c7bd399cedd8265c5e1da000791bcdfe4d1bc1e73ada7bf833103c828f22d83189dad2b22ad28a54aacf2a";
    minter::pubkey_t pub = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";
    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_unbond>();

    ASSERT_STREQ("MNT", decoded->get_gas_coin().c_str());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_EQ(minter::testnet, decoded->get_chain_id());
    ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
    ASSERT_EQ((uint8_t)0x08, decoded->get_type());
    ASSERT_EQ(dev::bytes(0), decoded->get_service_data());
    ASSERT_EQ(dev::bytes(0), decoded->get_payload());
    ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());

    ASSERT_STREQ("MNT", data->get_coin().c_str());
    ASSERT_EQ(dev::bigdec18("10"), data->get_value());
    ASSERT_EQ(pub, data->get_pub_key());

    const char* R = "ff5766c85847b37a276f3f9d027fb7c99745920fa395c7bd399cedd8265c5e1d";
    const char* S = "00791bcdfe4d1bc1e73ada7bf833103c828f22d83189dad2b22ad28a54aacf2a";
    const char* V = "1c";

    auto sign_data = decoded->get_signature_data<minter::signature_single_data>();
    minter::Data r = sign_data->get_r();
    minter::Data s = sign_data->get_s();
    minter::Data v = sign_data->get_v();
    ASSERT_STREQ(R, r.to_hex().c_str());
    ASSERT_STREQ(S, s.to_hex().c_str());
    ASSERT_STREQ(V, v.to_hex().c_str());
}