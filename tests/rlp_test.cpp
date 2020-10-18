/*!
 * minter_tx.
 * rlp_test
 *
 * \date 23.05.19
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <bip3x/utils.h>
#include <gtest/gtest.h>
#include <minter/eth/RLP.h>
#include <minter/tx/utils.h>

TEST(RLP, NullZeroEncoding) {

    eth::RLPStream out;
    {
        eth::RLPStream lst;
        dev::bigint zero("0");
        dev::bytes res = zero.export_bytes();
        ASSERT_EQ(1, res.size());
        ASSERT_EQ((uint8_t) 0x00, res.at(0));
        lst.append(zero);

        out.appendList(lst);
    }

    dev::bytes_data tmp = out.out();
    ASSERT_STREQ("c180", tmp.to_hex().c_str());

    eth::RLP s(tmp.get());
    ASSERT_EQ(dev::bigint("0"), (dev::bigint) s[0]);
}

TEST(RLP, EmptyListEncoding) {

    eth::RLPStream out;

    eth::RLPStream lst;
    out.appendList(lst);

    dev::bytes_data res = out.out();

    eth::RLP decoded(res.get());

    //    // convert ot RLP list
    //    eth::RLP sub_list = (eth::RLP) decoded[0];
    //    ASSERT_EQ(0, sub_list.size());

    // decode to bytes directly will throw badrlp exception
    //    dev::bytes empty_bytes = (dev::bytes) decoded[0];

    // Alternative
    dev::bigint val;
    if (decoded[0].isNull()) {
        val = dev::bigint("0");
    } else {
        val = (dev::bigint) decoded[0];
    }
}

TEST(RLP, StringEncoding) {

    eth::RLPStream out;
    std::string s = "                                                                                                                                                                                                                                                                                                                                                                                                                                ";
    out.append(s);
}

TEST(RLP, EncodeBigInt128) {

    dev::bigint nonce = dev::bigint("128");

    eth::RLPStream out;
    {
        eth::RLPStream lst;
        lst.append(nonce);
        out.appendList(lst);
    }
    auto _i = nonce;
    dev::bytes num;
    {
        num.resize(2);
        dev::byte* b = &num.back();
        for (; _i; _i >>= 8)
            *(b--) = (uint8_t)(_i & 0xff);
    }

    auto data = out.out();

    dev::bytes_data d = data;
    dev::bytes_data numd = num;
}
