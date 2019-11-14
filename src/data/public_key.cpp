/*!
 * minter_tx.
 * public_key.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <toolboxpp.hpp>
#include "minter/public_key.h"

minter::data::public_key::public_key(const char *hex) {
    std::string pk = toolboxpp::strings::substringReplaceAll(
        std::vector<std::string>{"Mp", "mp"},
        std::vector<std::string>{"", ""},
        hex
    );

    m_data = data_t(pk.c_str());
}

minter::data::public_key::public_key(const std::string &hex): public_key(hex.c_str()) {

}

minter::data::public_key::public_key(const std::vector<uint8_t> &data) :
    m_data(data) {
}
minter::data::public_key::public_key(std::vector<uint8_t> &&data) :
    m_data(std::move(data)) {
}

bool minter::data::public_key::operator==(const minter::data::public_key &other) const noexcept {
    return m_data == other.m_data;
}

bool minter::data::public_key::operator==(const minter::Data &other) const noexcept {
    return m_data == other.get();
}

bool minter::data::public_key::operator!=(const minter::data::public_key &other) const noexcept {
    return m_data == other.m_data;
}

bool minter::data::public_key::operator!=(const minter::Data &other) const noexcept {
    return m_data == other.get();
}

minter::data::public_key::operator std::string() const {
    return to_string();
}

minter::data::public_key::operator const std::vector<uint8_t> &() const {
    return m_data.get();
}

const dev::bytes &minter::data::public_key::get() const {
    return m_data.get();
}

dev::bytes &minter::data::public_key::get() {
    return m_data.get();
}

uint8_t minter::data::public_key::operator[](size_t element) const noexcept {
    return at(element);
}

uint8_t minter::data::public_key::at(size_t idx) const {
    return m_data.get().at(idx);
}

std::string minter::data::public_key::to_string() const {
    return "Mp" + m_data.to_hex();
}

std::string minter::data::public_key::to_string_no_prefix() const {
    return m_data.to_hex();
}
