//
// Created by edwar on 10-Dec-19.
//

#ifndef MINTER_TX_CHECK_H
#define MINTER_TX_CHECK_H

#include "minter_tx_config.h"

#include <string>

namespace minter {
namespace data {

class MINTER_TX_API minter_check : public dev::bytes_data {
public:
    minter_check();
    ~minter_check() override = default;
    minter_check(const toolbox::data::bytes_data& other);
    minter_check(toolbox::data::bytes_data&& other);
    explicit minter_check(std::size_t size);
    minter_check(const char* hexString);
    minter_check(const std::string& hexString);
    minter_check(std::vector<uint8_t> data);
    minter_check(const uint8_t* data, size_t len);

    explicit operator std::string() const noexcept;
    std::string to_string() const override;
    std::string to_string_no_prefix() const;
};

} // namespace data

using check_t = minter::data::minter_check;

} // namespace minter

MINTER_TX_API std::ostream& operator<<(std::ostream& os, const minter::check_t& hash);

#endif //MINTER_TX_CHECK_H
