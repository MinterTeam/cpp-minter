/*!
 * minter_tx.
 * rlp_encodable.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_RLP_ENCODABLE_H
#define MINTER_RLP_ENCODABLE_H

#include <minter/eth/RLP.h>

namespace minter {

class rlp_encodable {
public:
    virtual dev::bytes encode() = 0;
};

}

#endif //MINTER_RLP_ENCODABLE_H
