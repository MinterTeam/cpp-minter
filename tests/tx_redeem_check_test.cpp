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
    minter::privkey_t pk = minter::privkey_t::from_mnemonic("december wedding engage learn plate lion phone lemon hill grocery effort dismiss");
    const char* expected_tx = "f901540102018a4d4e540000000000000009b8f9f8f7b8b2f8b08331323802843b9ac9ff8a4d4e54000000000000008906f05b59d3b20000008a4d4e5400000000000000b841b59c9a11ee79a5dbe6e40383a5db5a90960b452e5fddc63cc8f3d092ebf7e39303340d8f42bda3b55a681b9ece3229f9cf718d717ef0c2cb818c52a9b93f27d9001ca0afe5f4c59f1a1f64bd2d7bb97f0fc0cbb9cf1b40d12dc59f948dc419bbad51f8a05033b98e743a9d2af329e890933ea585785573d3a40f52aaa76858083d68654eb841133824027bddf75120c93cf183f5ff18beea9c350203eb7af02bcbbbca5e282201efe7e4eac2494de85b762296dd4b7ea7879b238a6dd8b012838ee6fc04d51501808001b845f8431ca0d00ee903c7859ec891a983ff70b4167843140a62a5d346df29baf344c9feedd6a0323f997418d719e3a4d5b1da8854e60cb9f70674d12763214c374f9bd53d47ec";
    minter::check_t valid_check("Mcf8b08331323802843b9ac9ff8a4d4e54000000000000008906f05b59d3b20000008a4d4e5400000000000000b841b59c9a11ee79a5dbe6e40383a5db5a90960b452e5fddc63cc8f3d092ebf7e39303340d8f42bda3b55a681b9ece3229f9cf718d717ef0c2cb818c52a9b93f27d9001ca0afe5f4c59f1a1f64bd2d7bb97f0fc0cbb9cf1b40d12dc59f948dc419bbad51f8a05033b98e743a9d2af329e890933ea585785573d3a40f52aaa76858083d68654e");
    dev::bytes_data proof("133824027bddf75120c93cf183f5ff18beea9c350203eb7af02bcbbbca5e282201efe7e4eac2494de85b762296dd4b7ea7879b238a6dd8b012838ee6fc04d51501");

    auto tx_builder = minter::new_tx();
    tx_builder->set_nonce("1");
    tx_builder->set_chain_id(minter::testnet);
    tx_builder->set_gas_price("1");
    tx_builder->set_gas_coin("MNT");
    std::shared_ptr<minter::tx_redeem_check> data = tx_builder->tx_redeem_check();
    data->set_check(valid_check);
    data->set_proof(proof);
    auto tx = data->build();

    dev::bytes_data sign = tx->sign_single(pk);
    ASSERT_STREQ(expected_tx, sign.to_hex().c_str());
}

TEST(TxRedeemCheck, TestDecode) {
    const char* valid_tx = "f901540102018a4d4e540000000000000009b8f9f8f7b8b2f8b08331323802843b9ac9ff8a4d4e54000000000000008906f05b59d3b20000008a4d4e5400000000000000b841b59c9a11ee79a5dbe6e40383a5db5a90960b452e5fddc63cc8f3d092ebf7e39303340d8f42bda3b55a681b9ece3229f9cf718d717ef0c2cb818c52a9b93f27d9001ca0afe5f4c59f1a1f64bd2d7bb97f0fc0cbb9cf1b40d12dc59f948dc419bbad51f8a05033b98e743a9d2af329e890933ea585785573d3a40f52aaa76858083d68654eb841133824027bddf75120c93cf183f5ff18beea9c350203eb7af02bcbbbca5e282201efe7e4eac2494de85b762296dd4b7ea7879b238a6dd8b012838ee6fc04d51501808001b845f8431ca0d00ee903c7859ec891a983ff70b4167843140a62a5d346df29baf344c9feedd6a0323f997418d719e3a4d5b1da8854e60cb9f70674d12763214c374f9bd53d47ec";
    minter::check_t valid_check("Mcf8b08331323802843b9ac9ff8a4d4e54000000000000008906f05b59d3b20000008a4d4e5400000000000000b841b59c9a11ee79a5dbe6e40383a5db5a90960b452e5fddc63cc8f3d092ebf7e39303340d8f42bda3b55a681b9ece3229f9cf718d717ef0c2cb818c52a9b93f27d9001ca0afe5f4c59f1a1f64bd2d7bb97f0fc0cbb9cf1b40d12dc59f948dc419bbad51f8a05033b98e743a9d2af329e890933ea585785573d3a40f52aaa76858083d68654e");
    dev::bytes_data proof("133824027bddf75120c93cf183f5ff18beea9c350203eb7af02bcbbbca5e282201efe7e4eac2494de85b762296dd4b7ea7879b238a6dd8b012838ee6fc04d51501");

    auto tx = minter::tx::decode(valid_tx);

    ASSERT_EQ(dev::bigint("1"), tx->get_nonce());
    ASSERT_STREQ("MNT", tx->get_gas_coin().c_str());
    ASSERT_EQ(dev::bigint("1"), tx->get_gas_price());
    ASSERT_EQ(minter::testnet, tx->get_chain_id());

    auto data = tx->get_data<minter::tx_redeem_check>();
    ASSERT_EQ(valid_check, data->get_check());
    ASSERT_EQ(proof.get(), data->get_proof());
}