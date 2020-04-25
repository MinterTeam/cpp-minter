/*!
 * minter_tx.
 * utils.hpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_UTILS_H
#define MINTER_UTILS_H

#include "minter/minter_tx_config.h"

#include <iostream>
#include <minter/eth/RLP.h>
#include <string>

namespace minter {
namespace utils {

static const dev::bigint normalized_value_int = dev::bigint("1000000000000000000");
static const dev::bigdec18 normalized_value_dec = dev::bigdec18("1000000000000000000");

MINTER_TX_API dev::bytes to_bytes_fixed(const std::string& input, size_t fixed_size = 10);
MINTER_TX_API dev::bytes to_bytes(std::string&& input);
MINTER_TX_API dev::bytes to_bytes(const std::string& input);
MINTER_TX_API dev::bytes to_bytes(const dev::bigint& num);
MINTER_TX_API dev::bytes to_bytes(const dev::u256& num);
MINTER_TX_API dev::bytes to_bytes(const dev::bigdec18& num);
MINTER_TX_API dev::bigint to_bigint(const dev::bytes& bytes);
MINTER_TX_API dev::bigint to_bigint(const uint8_t* bytes, size_t len);
MINTER_TX_API dev::bytes sha3k(const dev::bytes& message);
MINTER_TX_API dev::bytes sha3k(const dev::bytes_data& message);
MINTER_TX_API dev::bytes to_sha3k(dev::bytes message);
MINTER_TX_API dev::bytes sha256(const dev::bytes& message);
MINTER_TX_API dev::bytes sha256(const dev::bytes_data& message);
MINTER_TX_API dev::bytes to_sha256(dev::bytes message);
MINTER_TX_API dev::bytes from_base64_web(const dev::bytes data);
MINTER_TX_API dev::bytes to_base64_web(const dev::bytes data);
MINTER_TX_API std::string strip_null_bytes(const char* input, size_t len);
MINTER_TX_API std::string to_string(const dev::bytes& src);
MINTER_TX_API std::string to_string(const std::vector<char>& src);
MINTER_TX_API std::string to_string(const dev::bigdec18& src);
MINTER_TX_API std::string to_string_lp(const dev::bigdec18& src);
MINTER_TX_API std::string to_string(const dev::bigint& src);
MINTER_TX_API std::string to_string_clear(const dev::bytes& src);
MINTER_TX_API std::string to_string(uint64_t src);

MINTER_TX_API dev::bytes gen_random_bytes(size_t n);

MINTER_TX_API void memset_s(uint8_t* dst, uint8_t val, size_t n);

MINTER_TX_API dev::bigint normalize_value(const char* input);
MINTER_TX_API dev::bigint normalize_value(const std::string& input);
MINTER_TX_API dev::bigint normalize_value(const dev::bigdec18& value);
MINTER_TX_API dev::bigdec18 humanize_value(const dev::bigint& value);
} // namespace utils
} // namespace minter

std::ostream& operator<<(std::ostream& out, const dev::bytes& d);
std::ostream& operator<<(std::ostream& out, const eth::RLPStream& rlp);

#endif //MINTER_UTILS_H
