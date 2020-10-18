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
    minter::check_t valid_check("Mcf89a8334383001830f423f80888ac7230489e8000080b84191ea56636b6667bb9da14bd412d492b90b9ae29799a90d0d69a637f3894c8ba246aae2b466fe76acab0a65cc6791ab2ae29d155b56efe84a929e089a22e15615001ba0d88c6543ac5d791428d46f8625c0af8e908fde3ec339e3d77ecb585e7c507ea8a021debf60dd96497d430b3cd92dac7bf22a00b4518f39d084c1dc50ba4c8b0d3b");
    minter::privkey_t priv_key("4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e");
    minter::address_t address("Mx67691076548b20234461ff6fd2bc9c64393eb8fc");
    std::string pass = "pass";

    minter::check_tx check("480", pass);
    check
        .set_chain_id(minter::chain_id::mainnet)
        .set_gas_coin_id("0")
        .set_coin_id("0")
        .set_due_block("999999")
        .set_value("10");

    minter::check_t check_result = check.sign(priv_key);

    minter::check_tx decoded = minter::check_tx::decode(check_result);
    ASSERT_STREQ("480", decoded.get_nonce().to_string().c_str());
    ASSERT_EQ(minter::chain_id::mainnet, decoded.get_chain_id());
    ASSERT_EQ(dev::bigint("0"), decoded.get_gas_coin());
    ASSERT_EQ(dev::bigint("0"), decoded.get_coin_id());
    ASSERT_EQ(dev::bigint("999999"), decoded.get_due_block());
    ASSERT_EQ(dev::bigdec18("10"), decoded.get_value());

    minter::check_tx valid_dec = minter::check_tx::decode(valid_check);
    ASSERT_EQ(valid_dec.get_nonce(), decoded.get_nonce());
    ASSERT_EQ(valid_dec.get_chain_id(), decoded.get_chain_id());
    ASSERT_EQ(valid_dec.get_gas_coin(), decoded.get_gas_coin());
    ASSERT_EQ(valid_dec.get_coin_id(), decoded.get_coin_id());
    ASSERT_EQ(valid_dec.get_due_block(), decoded.get_due_block());
    ASSERT_EQ(valid_dec.get_value(), decoded.get_value());

    ASSERT_EQ(valid_check.size(), check_result.size());
    ASSERT_EQ(valid_check, check_result);
}