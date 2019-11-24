/*!
 * minter_tx.
 * tx_send_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>

#include "minter/tx/tx.h"
#include "minter/tx/tx_builder.h"
#include "minter/private_key.h"
#include "minter/tx/tx_send_coin.h"
#include "minter/crypto/secp256k1_raii.h"

static minter::signature test_signer_func(minter::Data32 hash) {
    minter::privkey_t pk("33671c8f2363dffb45e166f1cadced9aa5f86ad32509e5c4f0b39257c30b4110");
    minter::secp256k1_raii ctx;
    secp256k1_ecdsa_recoverable_signature sig;

    int ret = secp256k1_ecdsa_sign_recoverable(ctx.get(), &sig, hash.cdata(), pk.cdata(), NULL, NULL);

    uint8_t outputSer[65];
    minter::signature outSig;
    int recoveryId = 0;

    if (ret) {
        int serializeRet = secp256k1_ecdsa_recoverable_signature_serialize_compact(
            ctx.get(),
            outputSer,
            &recoveryId,
            &sig);
        (void)serializeRet;
        outputSer[64] = ((uint8_t) recoveryId) + (uint8_t) 27;
    } else {
        return outSig;
    }

    uint8_t r[32], s[32], v[1];
    memcpy(r, outputSer + 0, 32);
    memcpy(s, outputSer + 32, 32);
    v[0] = outputSer[64];
    memset(outputSer, 0, 65);

    outSig.r = dev::bytes(r, r + 32);
    outSig.s = dev::bytes(s, s + 32);
    outSig.v = dev::bytes(v, v + 1);
    outSig.success = true;

    return outSig;
}

TEST(TxSend, SerializeSign) {
    minter::Data raw("");
}

TEST(TxSend, TestEncodeSignExternal) {
    const char* expectedTx = "f8840102018a4d4e540000000000000001aae98a4d4e540000000000000094bf5c2fec34cfe73e7178b3ab96deaf9ca6d9a592880de0b6b3a7640000808001b845f8431ca04090688ae6f0e989d99440a80dce1133deed569edb73c29e22611a9e614d2817a0215cb8614f410d4bb26927dd6d32efe9a7f1fe066f88603842d99b6ea37f57cb";

    auto signer_func = [](const minter::Data32 &hash){
      return test_signer_func(hash);
    };

    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("1");
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin("MNT");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to("Mxbf5c2fec34cfe73e7178b3ab96deaf9ca6d9a592");
    data->set_value("1");
    data->set_coin("MNT");
    auto tx = data->build();

    minter::privkey_t pk("33671c8f2363dffb45e166f1cadced9aa5f86ad32509e5c4f0b39257c30b4110");

    auto sign1 = signer_func(tx->get_unsigned_hash());
    std::cout << "Unsigned hash:\n";
    std::cout << tx->get_unsigned_hash().to_hex() << "\n";
    std::cout << "Signed hash:\n";
    std::cout << toolboxpp::data::bytesToHex(sign1.r.data(), 32);
    std::cout << toolboxpp::data::bytesToHex(sign1.s.data(), 32);
    std::cout << toolboxpp::data::bytesToHex(sign1.v.data(), 1);
    std::cout << std::endl;



    auto signedTx0 = tx->sign_single(pk);
    std::cout << "TX 0: " << tx->get_signature_data<minter::signature_single_data>()->to_hex() << std::endl;
    auto signedTx1 = tx->sign_external(sign1);
    std::cout << "TX 1: " << tx->get_signature_data<minter::signature_single_data>()->to_hex() << std::endl;
    auto signedTx2 = tx->sign_external(signer_func);
    std::cout << "TX 2: " << tx->get_signature_data<minter::signature_single_data>()->to_hex() << std::endl;
    auto signedTx3 = tx->sign_external(&test_signer_func);
    std::cout << "TX 3: " << tx->get_signature_data<minter::signature_single_data>()->to_hex() << std::endl;

    ASSERT_TRUE(signedTx1 == signedTx0);
    ASSERT_TRUE(signedTx2 == signedTx1);
    ASSERT_TRUE(signedTx3 == signedTx2);

    {
        auto decoded = minter::tx::decode(signedTx1.to_hex().c_str());

        ASSERT_STREQ("MNT", decoded->get_gas_coin().c_str());
        ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
        ASSERT_EQ(minter::testnet, decoded->get_chain_id());
        ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
        ASSERT_EQ((uint8_t)0x01, decoded->get_type());
        ASSERT_EQ(dev::bytes(0), decoded->get_service_data());
        ASSERT_EQ(dev::bytes(0), decoded->get_payload());
        ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
        std::shared_ptr<minter::tx_send_coin> data = decoded->get_data<minter::tx_send_coin>();
        ASSERT_EQ(minter::address_t("Mxbf5c2fec34cfe73e7178b3ab96deaf9ca6d9a592"), data->get_to());
        ASSERT_EQ(dev::bigdec18("1"), data->get_value());
        ASSERT_STREQ("MNT", data->get_coin().c_str());

        ASSERT_STREQ(expectedTx, signedTx1.to_hex().c_str());
        ASSERT_STREQ(expectedTx, signedTx2.to_hex().c_str());
        ASSERT_STREQ(expectedTx, signedTx3.to_hex().c_str());
    }
}

TEST(TxSend, TestSendEncode) {
    const char* expectedTx = "f8840102018a4d4e540000000000000001aae98a4d4e5400000000000000940000000000000000000000000000000000000000888ac7230489e80000808001b845f8431ba07a27eed01eae753c028d74e189f23b371fdd936dc0274d36ab27d8f0f4b2e9e1a03cd85dcf65e4204b393de0cd4db03d47479ba4321f074bedff2049b6e048fb6f";

    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("1");
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin("MNT");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to("Mx0000000000000000000000000000000000000000");
    data->set_value("10");
    data->set_coin("MNT");
    auto tx = data->build();

    minter::privkey_t pk("df1f236d0396cc43147e44206c341a65573326e907d033690e31a21323c03a9f");
    auto signedTx = tx->sign_single(pk);

    {
        auto decoded = minter::tx::decode(signedTx.to_hex().c_str());
        ASSERT_STREQ("MNT", decoded->get_gas_coin().c_str());
        ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
        ASSERT_EQ(minter::testnet, decoded->get_chain_id());
        ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
        ASSERT_EQ((uint8_t)0x01, decoded->get_type());
        ASSERT_EQ(dev::bytes(0), decoded->get_service_data());
        ASSERT_EQ(dev::bytes(0), decoded->get_payload());
        ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
        std::shared_ptr<minter::tx_send_coin> data = decoded->get_data<minter::tx_send_coin>();
        ASSERT_EQ(minter::address_t("Mx0000000000000000000000000000000000000000"), data->get_to());
        ASSERT_EQ(dev::bigdec18("10"), data->get_value());
        ASSERT_STREQ("MNT", data->get_coin().c_str());
    }

    ASSERT_STREQ(expectedTx, signedTx.to_hex().c_str());
}


TEST(TxSend, TestSendDecode) {
    const char* encoded = "f8840102018a4d4e540000000000000001aae98a4d4e5400000000000000940000000000000000000000000000000000000000888ac7230489e80000808001b845f8431ba07a27eed01eae753c028d74e189f23b371fdd936dc0274d36ab27d8f0f4b2e9e1a03cd85dcf65e4204b393de0cd4db03d47479ba4321f074bedff2049b6e048fb6f";

    std::shared_ptr<minter::tx> decoded = minter::tx::decode(encoded);
    minter::address_t exAddress = "Mx0000000000000000000000000000000000000000";

    ASSERT_EQ(dev::bigint("1"), decoded->get_nonce());
    ASSERT_STREQ("MNT", decoded->get_gas_coin().c_str());
    ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
    ASSERT_NE(dev::bigint("2"), decoded->get_gas_price());
    ASSERT_EQ(minter::testnet, decoded->get_chain_id());
    std::shared_ptr<minter::tx_send_coin> data = decoded->get_data<minter::tx_send_coin>();
    ASSERT_EQ(exAddress, data->get_to());
    ASSERT_EQ(dev::bigdec18("10"), data->get_value());
    ASSERT_STREQ("MNT", data->get_coin().c_str());
}

TEST(TxSend, TestEncodeForAndroidSDK) {
    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("128");
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin("MNT");
    tx_builder->set_chain_id(minter::testnet);
    auto data = tx_builder->tx_send_coin();
    data->set_to("Mxb445feaf3eb747ac52426b054aa42b0b3d913e1f");
    data->set_value("1");
    data->set_coin("MNT");
    auto tx = data->build();

    minter::privkey_t pk = minter::privkey_t::from_mnemonic("body attitude enable enjoy swift wise example hammer trap saddle bike lobster");
    auto signedTx = tx->sign_single(pk);

    {
        auto decoded = minter::tx::decode(signedTx.to_hex().c_str());
        ASSERT_STREQ("MNT", decoded->get_gas_coin().c_str());
        ASSERT_EQ(dev::bigint("1"), decoded->get_gas_price());
        ASSERT_EQ(minter::testnet, decoded->get_chain_id());
        ASSERT_EQ(dev::bigint("128"), decoded->get_nonce());
        ASSERT_EQ((uint8_t)0x01, decoded->get_type());
        ASSERT_EQ(dev::bytes(0), decoded->get_service_data());
        ASSERT_EQ(dev::bytes(0), decoded->get_payload());
        ASSERT_EQ(minter::signature_type::single, decoded->get_signature_type());
        auto data = decoded->get_data<minter::tx_send_coin>();
        ASSERT_EQ(minter::address_t("Mxb445feaf3eb747ac52426b054aa42b0b3d913e1f"), data->get_to());
        ASSERT_EQ(dev::bigdec18("1"), data->get_value());
        ASSERT_STREQ("MNT", data->get_coin().c_str());
    }

    std::cout << signedTx.to_hex() << '\n';
}