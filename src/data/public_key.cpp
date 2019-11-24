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

minter::data::public_key::public_key() : bytes_data() {
}
minter::data::public_key::public_key(std::size_t size) : bytes_data(size) {
}
minter::data::public_key::public_key(const std::vector<uint8_t> &data) : bytes_data(data) {
}
minter::data::public_key::public_key(std::vector<uint8_t> &&data) : bytes_data(data) {
}
minter::data::public_key::public_key(const uint8_t *data, size_t len) : bytes_data(data, len) {
}

minter::data::public_key::public_key(const char *hexString) {
    std::string pk = toolboxpp::strings::substringReplaceAll(
        std::vector<std::string>{"Mp", "mp"},
        std::vector<std::string>{"", ""},
        std::string(hexString)
    );

    m_data = toolboxpp::data::hexToBytes(pk);
}

minter::data::public_key::public_key(const std::string &hexString) {
    std::string pk = toolboxpp::strings::substringReplaceAll(
        std::vector<std::string>{"Mp", "mp"},
        std::vector<std::string>{"", ""},
        hexString
    );

    m_data = toolboxpp::data::hexToBytes(pk);
}

bool minter::data::public_key::operator==(const minter::data::public_key &other) const noexcept {
    return m_data == other.m_data;
}

bool minter::data::public_key::operator!=(const minter::data::public_key &other) const noexcept {
    return m_data != other.m_data;
}

minter::data::public_key::operator std::string() const {
    return to_string();
}

std::string minter::data::public_key::to_string() const {
    return "Mp" + to_hex();
}

std::string minter::data::public_key::to_string_no_prefix() const {
    return to_hex();
}




