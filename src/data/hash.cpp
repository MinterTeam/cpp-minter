/*!
 * minter_tx.
 * minter_hash.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/hash.h"

#include <toolbox/strings.hpp>
#include <utility>

minter::data::minter_hash::minter_hash()
    : bytes_data() {
}
minter::data::minter_hash::minter_hash(const toolbox::data::bytes_data& other)
    : bytes_data(other) {
}
minter::data::minter_hash::minter_hash(toolbox::data::bytes_data&& other)
    : bytes_data(other) {
}

minter::data::minter_hash::minter_hash(std::size_t size)
    : bytes_data(size) {
}
minter::data::minter_hash::minter_hash(const char* hexString) {
    std::string mh = toolbox::strings::substr_replace_all_ret(
        std::vector<std::string>{"Mt", "mt"},
        std::vector<std::string>{"", ""},
        hexString);

    m_data = toolbox::data::hex_to_bytes(mh);
}
minter::data::minter_hash::minter_hash(const std::string& hexString) {
    std::string mh = toolbox::strings::substr_replace_all_ret(
        std::vector<std::string>{"Mt", "mt"},
        std::vector<std::string>{"", ""},
        hexString);

    m_data = toolbox::data::hex_to_bytes(mh);
}
minter::data::minter_hash::minter_hash(std::vector<uint8_t> data)
    : bytes_data(std::move(data)) {
}
minter::data::minter_hash::minter_hash(const uint8_t* data, size_t len)
    : bytes_data(data, len) {
}

std::string minter::data::minter_hash::to_string() const {
    return "Mt" + to_hex();
}
std::string minter::data::minter_hash::to_string_no_prefix() const {
    return to_hex();
}

minter::data::minter_hash::operator std::string() const noexcept {
    return to_string();
}

std::ostream& operator<<(std::ostream& os, const minter::hash_t& hash) {
    os << hash.to_string();
    return os;
}
