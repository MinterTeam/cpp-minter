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

#include <minter/eth/Common.h>

namespace minter {

typedef enum {
  single = (uint8_t) 0x01,
  multi = (uint8_t) 0x02
} signature_type;

typedef struct {
  dev::bytes r, s, v;
  bool success = false;
} signature;

}

#endif //MINTER_SIGNATURE_H
