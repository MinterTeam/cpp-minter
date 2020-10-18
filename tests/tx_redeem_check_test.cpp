/*!
 * minter_tx.
 * tx_check_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/check.h>
#include <minter/tx/tx_builder.h>
#include <minter/tx/tx_redeem_check.h>

TEST(TxRedeemCheck, TestEncode) {
    minter::privkey_t pk = "4daf02f92bf760b53d3c725d6bcc0da8e55d27ba5350c78d3a88f873e502bd6e";
    const char* expected_tx = "f901350101018009b8e4f8e2b89df89b843130303201830f423f80880de0b6b3a764000080b8412b326337a6f1fc5617a3f9b32b0949cdf6761db0129d6507de155c21513b6a0334deb6d0bb4662426d4472716cde0b8258f47c99a12f93a05b2e732c4caaa9fa011ba0bdbd9d7d63b157fc232d5d859d13916e85e076632614013902b838c02e294428a06c031b2115e2c7c68c8808f84bba0cd8be5d882104b5a5c8355aa36008354e39b8413d02668333291917face5bbdc6c5bb6c2020479b720b3ee345b095a79a913409136a09c192b9483f0ae973cf6c86a71a9b440e7bdcb9437489463b93e15382a300808001b845f8431ba07020bc3b709ca547d0eeffb4baf0bd897dcfb4adabfed6113f1f1e9048335271a02af056405d1fe8feff5004cf693de523645c6001bd9ba4a5d41a838ed3fd040e";
    minter::check_t valid_check("Mcf89b843130303201830f423f80880de0b6b3a764000080b8412b326337a6f1fc5617a3f9b32b0949cdf6761db0129d6507de155c21513b6a0334deb6d0bb4662426d4472716cde0b8258f47c99a12f93a05b2e732c4caaa9fa011ba0bdbd9d7d63b157fc232d5d859d13916e85e076632614013902b838c02e294428a06c031b2115e2c7c68c8808f84bba0cd8be5d882104b5a5c8355aa36008354e39");
    dev::bytes_data proof("3d02668333291917face5bbdc6c5bb6c2020479b720b3ee345b095a79a913409136a09c192b9483f0ae973cf6c86a71a9b440e7bdcb9437489463b93e15382a300");

    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("1");
    tx_builder->set_chain_id(minter::mainnet);
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin_id("0");
    std::shared_ptr<minter::tx_redeem_check> data = tx_builder->tx_redeem_check();
    data->set_check(valid_check);
    data->set_proof(proof);
    auto tx = data->build();

    dev::bytes_data sign = tx->sign_single(pk);
    ASSERT_STREQ(expected_tx, sign.to_hex().c_str());
}

TEST(TxRedeemCheck, TestDecode) {
    const char* valid_tx = "f901350101018009b8e4f8e2b89df89b843130303201830f423f80880de0b6b3a764000080b8412b326337a6f1fc5617a3f9b32b0949cdf6761db0129d6507de155c21513b6a0334deb6d0bb4662426d4472716cde0b8258f47c99a12f93a05b2e732c4caaa9fa011ba0bdbd9d7d63b157fc232d5d859d13916e85e076632614013902b838c02e294428a06c031b2115e2c7c68c8808f84bba0cd8be5d882104b5a5c8355aa36008354e39b8413d02668333291917face5bbdc6c5bb6c2020479b720b3ee345b095a79a913409136a09c192b9483f0ae973cf6c86a71a9b440e7bdcb9437489463b93e15382a300808001b845f8431ba07020bc3b709ca547d0eeffb4baf0bd897dcfb4adabfed6113f1f1e9048335271a02af056405d1fe8feff5004cf693de523645c6001bd9ba4a5d41a838ed3fd040e";
    minter::check_t valid_check("Mcf89b843130303201830f423f80880de0b6b3a764000080b8412b326337a6f1fc5617a3f9b32b0949cdf6761db0129d6507de155c21513b6a0334deb6d0bb4662426d4472716cde0b8258f47c99a12f93a05b2e732c4caaa9fa011ba0bdbd9d7d63b157fc232d5d859d13916e85e076632614013902b838c02e294428a06c031b2115e2c7c68c8808f84bba0cd8be5d882104b5a5c8355aa36008354e39");
    dev::bytes_data proof("3d02668333291917face5bbdc6c5bb6c2020479b720b3ee345b095a79a913409136a09c192b9483f0ae973cf6c86a71a9b440e7bdcb9437489463b93e15382a300");

    auto tx = minter::tx::decode(valid_tx);

    ASSERT_EQ(dev::bigint("1"), tx->get_nonce());
    ASSERT_EQ(dev::bigint("0"), tx->get_gas_coin_id());
    ASSERT_EQ(dev::bigint("1"), tx->get_gas_price());
    ASSERT_EQ(minter::mainnet, tx->get_chain_id());

    auto data = tx->get_data<minter::tx_redeem_check>();
    ASSERT_EQ(valid_check, data->get_check());
    ASSERT_EQ(proof.get(), data->get_proof());
}