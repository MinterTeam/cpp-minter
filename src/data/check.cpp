//
// Created by edwar on 10-Dec-19.
//

#include "minter/check.h"

#include <toolbox/strings.hpp>

minter::data::minter_check::minter_check()
    : bytes_data() {
}
minter::data::minter_check::minter_check(const toolbox::data::bytes_data& other)
    : bytes_data(other) {
}
minter::data::minter_check::minter_check(toolbox::data::bytes_data&& other)
    : bytes_data(other) {
}

minter::data::minter_check::minter_check(std::size_t size)
    : bytes_data(size) {
}
minter::data::minter_check::minter_check(const char* hexString) {
    std::string mh = toolbox::strings::substr_replace_all_ret(
        std::vector<std::string>{"Mc", "mc"},
        std::vector<std::string>{"", ""},
        hexString);

    m_data = toolbox::data::hex_to_bytes(mh);
}
minter::data::minter_check::minter_check(const std::string& hexString) {
    std::string mh = toolbox::strings::substr_replace_all_ret(
        std::vector<std::string>{"Mc", "mc"},
        std::vector<std::string>{"", ""},
        hexString);

    m_data = toolbox::data::hex_to_bytes(mh);
}
minter::data::minter_check::minter_check(std::vector<uint8_t> data)
    : bytes_data(std::move(data)) {
}
minter::data::minter_check::minter_check(const uint8_t* data, size_t len)
    : bytes_data(data, len) {
}

std::string minter::data::minter_check::to_string() const {
    return "Mc" + to_hex();
}
std::string minter::data::minter_check::to_string_no_prefix() const {
    return to_hex();
}

minter::data::minter_check::operator std::string() const noexcept {
    return to_string();
}

std::ostream& operator<<(std::ostream& os, const minter::check_t& hash) {
    os << hash.to_string();
    return os;
}