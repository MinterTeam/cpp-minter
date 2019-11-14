/*!
 * minter_tx.
 * tx_set_candidate_on_off
 *
 * \date 27.04.19
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include <minter/tx.hpp>
#include <gtest/gtest.h>

TEST(SetCandidateOn, TestEncode) {
    const char* expected = "f87c0102018a4d4e54000000000000000aa2e1a00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43808001b845f8431ba0095aed433171fe5ac385ccd299507bdcad3dd2269794fd0d14d4f58327ddc87ea046ec7e4f8f9b477a1255485f36e0567e62283723ecc5a0bd1e5d201e53e85245";
    minter::pubkey_t pubkey = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";
    minter::privkey_t privkey = "05ddcd4e6f7d248ed1388f0091fe345bf9bf4fc2390384e26005e7675c98b3c1";

    auto tx = minter::new_tx()
            ->set_nonce("1")
            .tx_set_candidate_on()
            ->set_pub_key(pubkey)
            .build();

    auto signature = tx->sign_single(privkey);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(SetCandidateOn, TestDecode) {
    const char* encoded = "f87c0102018a4d4e54000000000000000aa2e1a00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43808001b845f8431ba0095aed433171fe5ac385ccd299507bdcad3dd2269794fd0d14d4f58327ddc87ea046ec7e4f8f9b477a1255485f36e0567e62283723ecc5a0bd1e5d201e53e85245";
    minter::pubkey_t pubkey = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";

    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_set_candidate_on>();
    ASSERT_EQ(pubkey, data->get_pub_key());
}

TEST(SetCandidateOff, TestEncode) {
    const char *expected = "f87c0102018a4d4e54000000000000000ba2e1a00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43808001b845f8431ca02ac45817f167c34b55b8afa0b6d9692be28e2aa41dd28a134663d1f5bebb5ad8a06d5f161a625701d506db20c497d24e9939c2e342a6ff7d724cb1962267bd4ba5";
    minter::privkey_t privkey = "05ddcd4e6f7d248ed1388f0091fe345bf9bf4fc2390384e26005e7675c98b3c1";
    minter::pubkey_t pubkey = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";

    auto tx = minter::new_tx()
            ->set_nonce("1")
            .tx_set_candidate_off()
            ->set_pub_key(pubkey)
            .build();

    auto signature = tx->sign_single(privkey);

    ASSERT_STREQ(expected, signature.to_hex().c_str());
}

TEST(SetCandidateOff, TestDecode) {
    const char* encoded = "f87c0102018a4d4e54000000000000000ba2e1a00eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43808001b845f8431ca02ac45817f167c34b55b8afa0b6d9692be28e2aa41dd28a134663d1f5bebb5ad8a06d5f161a625701d506db20c497d24e9939c2e342a6ff7d724cb1962267bd4ba5";
    minter::pubkey_t pubkey = "Mp0eb98ea04ae466d8d38f490db3c99b3996a90e24243952ce9822c6dc1e2c1a43";

    auto decoded = minter::tx::decode(encoded);
    auto data = decoded->get_data<minter::tx_set_candidate_off>();
    ASSERT_EQ(pubkey, data->get_pub_key());
}