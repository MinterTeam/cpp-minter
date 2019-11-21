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

class MINTER_TX_API minter_hash {
private:
    using data_t = minter::Data;
public:
public:
    minter_hash() = default;
    minter_hash(const char* hex);
    minter_hash(const std::string& hex);
    minter_hash(const std::vector<uint8_t> &data);
    minter_hash(std::vector<uint8_t> &&data);

    bool operator==(const minter::data::minter_hash& other) const noexcept ;
    bool operator==(const minter::Data& other) const noexcept ;
    bool operator!=(const minter::data::minter_hash& other) const noexcept ;
    bool operator!=(const minter::Data& other) const noexcept ;
    uint8_t operator[](size_t element) const noexcept;
    explicit operator std::string() const;

    uint8_t at(size_t idx) const;

    const dev::bytes& get() const;
    dev::bytes& get();

    std::string to_string() const;
    std::string to_string_no_prefix() const;

private:
    data_t m_data;
};

}

using hash_t = minter::data::minter_hash;

}

MINTER_TX_API std::ostream& operator << (std::ostream &os, const minter::hash_t &hash);

#endif //MINTER_MINTER_HASH_H
