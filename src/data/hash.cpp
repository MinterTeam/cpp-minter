/*!
 * minter_tx.
 * minter_hash.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <toolboxpp.hpp>
#include "minter/hash.h"

minter::data::minter_hash::minter_hash(const char *hex) {
    std::string pk = toolboxpp::strings::substringReplaceAll(
        std::vector<std::string>{"Mt", "mt"},
        std::vector<std::string>{"", ""},
        hex
    );

    m_data = data_t(pk.c_str());
}
minter::data::minter_hash::minter_hash(const std::string &hex): minter_hash(hex.c_str()) {

}
minter::data::minter_hash::minter_hash(const std::vector<uint8_t> &data) {
    m_data = data;
}
minter::data::minter_hash::minter_hash(std::vector<uint8_t> &&data) {
    m_data = std::move(data);
}
bool minter::data::minter_hash::operator==(const minter::data::minter_hash &other) const noexcept {
    return m_data == other.m_data;
}
bool minter::data::minter_hash::operator==(const minter::Data &other) const noexcept {
    return m_data == other.get();
}
bool minter::data::minter_hash::operator!=(const minter::data::minter_hash &other) const noexcept {
    return m_data == other.m_data;
}
bool minter::data::minter_hash::operator!=(const minter::Data &other) const noexcept {
    return m_data == other.get();
}
uint8_t minter::data::minter_hash::operator[](size_t element) const noexcept {
    return at(element);
}
uint8_t minter::data::minter_hash::at(size_t idx) const {
    return m_data.get().at(idx);
}
const dev::bytes &minter::data::minter_hash::get() const {
    return m_data.get();
}
dev::bytes &minter::data::minter_hash::get() {
    return m_data.get();
}
minter::data::minter_hash::operator std::string() const {
    return to_string();
}
std::string minter::data::minter_hash::to_string() const {
    return "Mt" + m_data.to_hex();
}
std::string minter::data::minter_hash::to_string_no_prefix() const {
    return m_data.to_hex();
}

std::ostream& operator << (std::ostream &os, const minter::hash_t &hash) {
    os << hash.to_string();
    return os;
}
 
 