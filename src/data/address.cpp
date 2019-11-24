/*!
 * minter_tx.
 * minter_address.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <string>
#include <toolboxpp.hpp>
#include <regex>
#include "minter/address.h"
#include "minter/tx/utils.h"

minter::data::address::address() : FixedData() {
}
minter::data::address::address(const std::vector<uint8_t> &data) : FixedData(data) {
}
minter::data::address::address(std::vector<uint8_t> &&data) : FixedData(data) {
}
minter::data::address::address(const uint8_t *data, size_t len) : FixedData(data, len) {
}

minter::data::address::address(const char *hexString) {
    size_t l = strlen(hexString);
    if (l != 40 && l != 42) {
        throw std::runtime_error("address length is not valid");
    }

    std::string address = toolboxpp::strings::substringReplaceAll(
        std::vector<std::string>{"Mx", "mx"},
        std::vector<std::string>{"", ""},
        std::string(hexString)
    );

    m_data = toolboxpp::data::hexToBytes(address);
}
minter::data::address::address(const std::string &hexString) {
    if (hexString.length() != 40 && hexString.length() != 42) {
        throw std::runtime_error("address length is not valid");
    }

    std::string address = toolboxpp::strings::substringReplaceAll(
        std::vector<std::string>{"Mx", "mx"},
        std::vector<std::string>{"", ""},
        hexString
    );

    m_data = toolboxpp::data::hexToBytes(address);
}

minter::data::address::address(const minter::pubkey_t &pub_key) {
    dev::bytes dropped_first = pub_key.take_last(pub_key.size() - 1);
    dev::bytes hashed = minter::utils::sha3k(dropped_first);
    dev::bytes last20(20);
    std::copy(hashed.end()-20, hashed.end(), last20.begin());

    m_data = std::move(last20);
}

minter::data::address::address(const minter::privkey_t &priv_key): address(priv_key.get_public_key()) {
}

std::string minter::data::address::to_string() const {
    return "Mx" + to_hex();
}

std::string minter::data::address::to_string_no_prefix() const {
    return to_hex();
}

bool minter::data::address::operator==(const minter::data::address &other) const noexcept {
    return get() == other.get();
}

bool minter::data::address::operator!=(const minter::data::address &other) const noexcept {
    return !(operator==(other));
}

minter::data::address::operator std::string() const noexcept {
    return to_string();
}

std::ostream &operator<<(std::ostream &out, const minter::address_t &address) {
    out << address.to_string();
    return out;
}
