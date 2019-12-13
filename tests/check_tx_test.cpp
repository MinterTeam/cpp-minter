/*!
 * minter_tx.
 * check_tx_test.cpp
 *
 * \date 12/10/2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/tx/check_tx.h>

using namespace minter;

TEST(CheckTx, MakeProof) {
    dev::bytes_data valid_proof("133824027bddf75120c93cf183f5ff18beea9c350203eb7af02bcbbbca5e282201efe7e4eac2494de85b762296dd4b7ea7879b238a6dd8b012838ee6fc04d51501");
    dev::bytes_data pass = dev::bytes_data::from_string_raw("hello");
    address_t address("Mx5f0b55330e289490efa54c92e2120d6ebb6514ca");

    dev::bytes_data res_proof = check_tx::make_proof(address, pass.get());

    ASSERT_STREQ(valid_proof.to_hex().c_str(), res_proof.to_hex().c_str());
    ASSERT_EQ(valid_proof, res_proof);
}

TEST(CheckTx, SignEncodeDecode) {
    minter::check_t valid_check("Mcf8b08331323802843b9ac9ff8a4d4e54000000000000008906f05b59d3b20000008a4d4e5400000000000000b841b59c9a11ee79a5dbe6e40383a5db5a90960b452e5fddc63cc8f3d092ebf7e39303340d8f42bda3b55a681b9ece3229f9cf718d717ef0c2cb818c52a9b93f27d9001ca0afe5f4c59f1a1f64bd2d7bb97f0fc0cbb9cf1b40d12dc59f948dc419bbad51f8a05033b98e743a9d2af329e890933ea585785573d3a40f52aaa76858083d68654e");
    minter::privkey_t priv_key = minter::privkey_t::from_mnemonic("december wedding engage learn plate lion phone lemon hill grocery effort dismiss");
    minter::address_t address("Mx5f0b55330e289490efa54c92e2120d6ebb6514ca");
    std::string pass = "hello";

    minter::check_tx check("128", pass);
    check.set_chain_id(minter::chain_id::testnet)
        .set_gas_coin("MNT")
        .set_coin("MNT")
        .set_due_block("999999999")
        .set_value("128");

    minter::check_t check_result = check.sign(priv_key);

    minter::check_tx decoded = minter::check_tx::decode(check_result);
    ASSERT_STREQ("128", decoded.get_nonce().to_string().c_str());
    ASSERT_NE(128ULL, decoded.get_nonce().to_num_any());
    ASSERT_EQ(0x313238ULL, decoded.get_nonce().to_num_any());
    ASSERT_EQ(dev::bytes_data("313238"), decoded.get_nonce());
    ASSERT_EQ(minter::chain_id::testnet, decoded.get_chain_id());
    ASSERT_STREQ("MNT", decoded.get_gas_coin().c_str());
    ASSERT_STREQ("MNT", decoded.get_coin().c_str());
    ASSERT_EQ(dev::bigint("999999999"), decoded.get_due_block());
    ASSERT_EQ(dev::bigdec18("128"), decoded.get_value());

    minter::check_tx valid_dec = minter::check_tx::decode(valid_check);
    ASSERT_EQ(valid_dec.get_nonce(), decoded.get_nonce());
    ASSERT_EQ(valid_dec.get_chain_id(), decoded.get_chain_id());
    ASSERT_STREQ(valid_dec.get_gas_coin().c_str(), decoded.get_gas_coin().c_str());
    ASSERT_STREQ(valid_dec.get_coin().c_str(), decoded.get_coin().c_str());
    ASSERT_EQ(valid_dec.get_due_block(), decoded.get_due_block());
    ASSERT_EQ(valid_dec.get_value(), decoded.get_value());

    ASSERT_EQ(valid_check.size(), check_result.size());
    ASSERT_EQ(valid_check, check_result);
}