/*!
 * minter_tx.
 * signature.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_SIGNATURE_H
#define MINTER_SIGNATURE_H

#include "minter/minter_tx_config.h"

#include <bip3x/utils.h>

namespace minter {

enum signature_type : uint8_t {
    single = 0x01,
    multi = 0x02
};

struct signature {
    dev::bytes r, s, v;
    bool success = false;
};

inline minter::signature signature_from_data(dev::bytes_data&& input65) {
    if (input65.size() != 65) {
        throw std::out_of_range("Signature data must contains exact 65 bytes, and 65th byte is a recovery id");
    }
    return minter::signature{input65.take_range(0, 32), input65.take_range(32, 64), input65.take_last(1)};
}

} // namespace minter

#endif // MINTER_SIGNATURE_H
