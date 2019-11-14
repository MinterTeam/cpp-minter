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
using address_data = minter::FixedData<20>;

class MINTER_TX_API address {
public:
    address() = default;
    address(const char *hex);
    address(const std::string &hex);
    address(const std::vector<uint8_t> &data);
    address(std::vector<uint8_t> &&data);
    address(const minter::pubkey_t &pub_key);
    address(const minter::privkey_t &priv_key);
    address(const toolboxpp::data::bytes_data &data);
    address(toolboxpp::data::bytes_data &&data);
    const std::string to_string() const;
    const std::string to_string_no_prefix() const;

    const uint8_t *data() const;
    uint8_t *data();
    const std::vector<uint8_t> &get() const;
    std::vector<uint8_t> &get();

    bool operator==(const minter::data::address& other) const noexcept ;
    bool operator==(const minter::Data& other) const noexcept ;
    bool operator!=(const minter::data::address& other) const noexcept ;
    bool operator!=(const minter::Data& other) const noexcept ;

    explicit operator std::string() const noexcept;
private:
    address_data m_data;
};


} // data

// Aliases
using address_t = minter::data::address;
} // minter

// hack
namespace std {
template <>
struct hash<minter::address_t>
{
  std::size_t operator()(const minter::address_t& k) const
  {
      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      std::size_t out = 0;
      for(const auto& item: k.get()) {
          out ^= std::hash<uint8_t>()(item);
      }

      return out;
  }
};
}

MINTER_TX_API std::ostream &operator << (std::ostream &out, const minter::address_t &address);

#endif //MINTER_MINTER_ADDRESS_H
