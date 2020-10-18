/*!
 * minter_tx.
 * types.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#ifndef MINTER_TX_ETH_TYPES_H
#define MINTER_TX_ETH_TYPES_H

#include "minter/minter_tx_config.h"

#include <toolbox/data/bytes_data.h>
#include <vector>

namespace eth {

using byte = uint8_t;

// Binary data types.
using bytes = std::vector<byte>;
using bytes_data = toolbox::data::bytes_data;

// Numeric types.
using bigint = dev::bigint;
using bigdec18 = dev::bigdec18;

} // namespace eth

#endif //MINTER_TX_ETH_TYPES_H
