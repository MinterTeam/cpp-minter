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

class MINTER_TX_API public_key : public toolboxpp::data::bytes_data {
 public:
    public_key();
    public_key(std::size_t size);
    public_key(const std::vector<uint8_t> &data);
    public_key(std::vector<uint8_t> &&data);
    public_key(const uint8_t *data, size_t len);
    public_key(const char *hexString);
    public_key(const std::string &hexString);

    bool operator==(const minter::data::public_key &other) const noexcept;
    bool operator!=(const minter::data::public_key &other) const noexcept;

    explicit operator std::string() const;

    std::string to_string() const;
    std::string to_string_no_prefix() const;
};

}

using pubkey_t = minter::data::public_key;
}

MINTER_TX_API std::ostream &operator<<(std::ostream &os, const minter::pubkey_t &pubkey);

#endif //MINTER_MINTER_PUBLIC_KEY_H
