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

#include <minter/eth/common.h>

namespace minter {

typedef enum {
  single = (uint8_t) 0x01,
  multi = (uint8_t) 0x02
} signature_type;

typedef struct {
  dev::bytes r, s, v;
  bool success = false;
} signature;

inline minter::signature signature_from_data(minter::Data &&input65) {
    if(input65.size() != 65) {
        throw std::out_of_range("Signature data must contains exact 65 bytes, where 65th byte is an recovery id");
    }
    return minter::signature{
        input65.take_range(0, 32),
        input65.take_range(32, 64),
        input65.take_last(1)
    };
}

}

#endif //MINTER_SIGNATURE_H
