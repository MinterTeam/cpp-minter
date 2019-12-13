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

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>
#include <toolbox/data/bytes_data.h>
#include <vector>

namespace eth {

namespace mp = boost::multiprecision;

using byte = uint8_t;

// Binary data types.
using bytes = std::vector<byte>;
using bytes_data = toolbox::data::bytes_data;

// Numeric types.
using bigint = mp::number<mp::cpp_int_backend<>>;
using bigdec18 = mp::number<mp::cpp_dec_float<18>>;
using u256 = mp::number<mp::cpp_int_backend<256, 256, mp::unsigned_magnitude, mp::unchecked, void>>;
using u160 = mp::number<mp::cpp_int_backend<160, 160, mp::unsigned_magnitude, mp::unchecked, void>>;

} // namespace eth

#endif //MINTER_TX_ETH_TYPES_H
