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

minter::data::address::address(const char *hex) {
    std::string tmp(hex);
    if(tmp.length() != 40 && tmp.length() != 42) {
        throw std::runtime_error("address length is not valid");
    }

    std::string address = toolboxpp::strings::substringReplaceAll(
        std::vector<std::string>{"Mx", "mx"},
        std::vector<std::string>{"", ""},
        hex
        );

    m_data = address_data(address.c_str());
}

minter::data::address::address(const std::string &hex): address(hex.c_str()) {

}

minter::data::address::address(const std::vector<uint8_t> &data) {
    m_data = data;
}

minter::data::address::address(std::vector<uint8_t> &&data) {
    m_data = std::move(data);
}

minter::data::address::address(const minter::pubkey_t &pub_key) {
    minter::Data d = pub_key.get();
    dev::bytes dropped_first(pub_key.get().size()-1);
    std::copy(pub_key.get().begin()+1, pub_key.get().end(), dropped_first.begin());
    dev::bytes hashed = minter::utils::sha3k(dropped_first);
    dev::bytes last20(20);
    std::copy(hashed.end()-20, hashed.end(), last20.begin());

    m_data = std::move(last20);
}

minter::data::address::address(const minter::privkey_t &priv_key): address(priv_key.get_public_key()) {

}

minter::data::address::address(const toolboxpp::data::bytes_data &data) {
    if(data.size() == 20) {
        m_data.write(0, data);
    }
}

const uint8_t *minter::data::address::data() const {
    return m_data.cdata();
}

uint8_t *minter::data::address::data() {

    return m_data.data();
}

const std::vector<uint8_t> &minter::data::address::get() const {
    return m_data.get();
}
std::vector<uint8_t> &minter::data::address::get() {
    return m_data.get();
}

const std::string minter::data::address::to_string() const {
    return "Mx" + m_data.to_hex();
}

const std::string minter::data::address::to_string_no_prefix() const {
    return m_data.to_hex();
}

bool minter::data::address::operator==(const minter::data::address &other) const noexcept {
    return m_data.get() == other.m_data.get();
}
bool minter::data::address::operator==(const minter::Data &other) const noexcept {
    return m_data.get() == other.get();
}
bool minter::data::address::operator!=(const minter::data::address &other) const noexcept {
    return !(operator==(other));
}
bool minter::data::address::operator!=(const minter::Data &other) const noexcept {
    return !(operator==(other));
}

minter::data::address::operator std::string() const noexcept {
    return to_string();
}

std::ostream &operator<<(std::ostream &out, const minter::address_t &address) {
    out << address.to_string();
    return out;
}
