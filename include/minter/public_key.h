/*!
 * minter_tx.
 * minter_public_key.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_MINTER_PUBLIC_KEY_H
#define MINTER_MINTER_PUBLIC_KEY_H

#include <minter/bip39/utils.h>
#include <vector>
#include "minter/eth/common.h"
#include "minter/hash.h"
#include "minter_tx_core.h"

namespace minter {
namespace data {

class MINTER_TX_API public_key {
private:
    using data_t = minter::Data;
public:
    public_key() = default;
    public_key(const char* hex);
    public_key(const std::string& hex);
    public_key(const std::vector<uint8_t> &data);
    public_key(std::vector<uint8_t> &&data);

    bool operator==(const minter::data::public_key& other) const noexcept ;
    bool operator==(const minter::Data& other) const noexcept ;
    bool operator!=(const minter::data::public_key& other) const noexcept ;
    bool operator!=(const minter::Data& other) const noexcept ;
    uint8_t operator[](size_t element) const noexcept;

    uint8_t at(size_t idx) const;

    const dev::bytes& get() const;
    dev::bytes& get();

    explicit operator std::string() const;

    std::string to_string() const;
    std::string to_string_no_prefix() const;

private:
    data_t m_data;
};

}

using pubkey_t = minter::data::public_key;
}



#endif //MINTER_MINTER_PUBLIC_KEY_H
