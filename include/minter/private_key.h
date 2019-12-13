/*!
 * minter_tx.
 * minter_private_key.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter_tx_config.h"
#include "public_key.h"

#ifndef MINTER_MINTER_PRIVATE_KEY_H
#define MINTER_MINTER_PRIVATE_KEY_H

namespace minter {
namespace data {

class MINTER_TX_API private_key : public dev::bytes_array<32> {
public:
    static private_key from_mnemonic(const std::string& mnem, uint32_t derive_index = 0);
    static private_key from_mnemonic(const char* mnemonic, uint32_t derive_index = 0);

    private_key();
    private_key(const char* hexString);
    private_key(const std::string& hexString);
    private_key(const uint8_t* data);
    private_key(std::vector<uint8_t>&& data);
    private_key(const std::vector<uint8_t>& data);
    private_key(const uint8_t* data, size_t len);
    minter::pubkey_t get_public_key(bool compressed = false) const;

    std::string to_string() const override;

    bool operator==(const private_key& other) const noexcept;
    bool operator!=(const private_key& other) const noexcept;
    explicit operator std::string() const;
};

} // namespace data

using privkey_t = minter::data::private_key;
} // namespace minter

MINTER_TX_API std::ostream& operator<<(std::ostream& os, const minter::privkey_t& privkey);

#endif //MINTER_MINTER_PRIVATE_KEY_H
