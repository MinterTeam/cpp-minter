#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
/*!
 * minter_tx.
 * minter_address.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_MINTER_ADDRESS_H
#define MINTER_MINTER_ADDRESS_H

#include <minter/bip39/utils.h>
#include <vector>
#include <utility>
#include <cstdint>
#include <string>
#include "minter_tx_core.h"
#include "minter/public_key.h"
#include "minter/private_key.h"

namespace minter {
namespace data {

class MINTER_TX_API address : public minter::FixedData<20> {
 public:
    address();
    address(const char *hexString);
    address(const std::string &hexString);
    address(const minter::pubkey_t &pub_key);
    address(const minter::privkey_t &priv_key);
    address(const std::vector<uint8_t> &data);
    address(std::vector<uint8_t> &&data);
    address(const uint8_t *data, size_t len);

    std::string to_string() const;
    std::string to_string_no_prefix() const;

    bool operator==(const minter::data::address &other) const noexcept;
    bool operator!=(const minter::data::address &other) const noexcept;

    explicit operator std::string() const noexcept;
};

} // data

// Aliases
using address_t = minter::data::address;
} // minter

// hack
namespace std {
template<>
struct hash<minter::address_t> {
  std::size_t operator()(const minter::address_t &k) const {
      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      std::size_t out = 0;
      for (const auto &item: k.get()) {
          out ^= std::hash<uint8_t>()(item);
      }

      return out;
  }
};
}

MINTER_TX_API std::ostream &operator<<(std::ostream &out, const minter::address_t &address);

#endif //MINTER_MINTER_ADDRESS_H

#pragma clang diagnostic pop