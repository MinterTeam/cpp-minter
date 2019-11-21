/*!
 * minter_tx.
 * rlp_test
 *
 * \date 23.05.19
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <minter/eth/RLP.h>
#include <minter/eth/common.h>
#include <minter/bip39/utils.h>

TEST(RLP, EncodeBigInt128) {

    dev::bigint nonce = dev::bigint("128");

    dev::RLPStream out;
    {
        dev::RLPStream lst;
        lst.append(nonce);
        out.appendList(lst);

    }
    auto _i = nonce;
    dev::bytes num;
    {
        num.resize(2);
        byte* b = &num.back();
        for (; _i; _i >>= 8)
            *(b--) = (uint8_t)(_i & 0xff);
    }

    auto data = out.out();

    minter::Data d = data;
    minter::Data numd = num;

    std::cout << d.to_hex() << std::endl;
    std::cout << numd.to_hex() << std::endl;

}

