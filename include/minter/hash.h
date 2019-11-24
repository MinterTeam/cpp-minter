/*!
 * minter_tx.
 * minter_hash.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_MINTER_HASH_H
#define MINTER_MINTER_HASH_H

#include <minter/bip39/utils.h>
#include "minter_tx_core.h"
#include "minter/eth/common.h"

namespace minter {
namespace data {

class MINTER_TX_API minter_hash : public toolboxpp::data::bytes_data {
 public:
    minter_hash();
    ~minter_hash() override = default;
    minter_hash(const bytes_data &other);
    minter_hash(bytes_data &&other);
    explicit minter_hash(std::size_t size);
    minter_hash(const char *hexString);
    minter_hash(const std::string &hexString);
    minter_hash(std::vector<uint8_t> data);
    minter_hash(const uint8_t *data, size_t len);

    explicit operator std::string() const noexcept;
    std::string to_string() const;
    std::string to_string_no_prefix() const;
};

}

using hash_t = minter::data::minter_hash;

}

MINTER_TX_API std::ostream &operator<<(std::ostream &os, const minter::hash_t &hash);

#endif //MINTER_MINTER_HASH_H
