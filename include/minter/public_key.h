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

#include "minter_tx_config.h"

#include <vector>

namespace minter {
namespace data {

class MINTER_TX_API public_key : public dev::bytes_data {
public:
    public_key();
    public_key(std::size_t size);
    public_key(const std::vector<uint8_t>& data);
    public_key(std::vector<uint8_t>&& data);
    public_key(const uint8_t* data, size_t len);
    public_key(const char* hexString);
    public_key(const std::string& hexString);

    bool operator==(const minter::data::public_key& other) const noexcept;
    bool operator!=(const minter::data::public_key& other) const noexcept;

    explicit operator std::string() const;

    std::string to_string() const override;
    std::string to_string_no_prefix() const;
};

} // namespace data

using pubkey_t = minter::data::public_key;
} // namespace minter

MINTER_TX_API std::ostream& operator<<(std::ostream& os, const minter::pubkey_t& pubkey);

#endif //MINTER_MINTER_PUBLIC_KEY_H
