/*!
 * minter_tx.
 * tx_edit_coin_owner.h
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_EDIT_COIN_OWNER_H
#define MINTER_TX_TX_EDIT_COIN_OWNER_H

#include <minter/address.h>
#include <minter/tx/tx_data.h>
#include <minter/tx/tx_type.h>
#include <string>

namespace minter {

class MINTER_TX_API tx_edit_coin_owner : virtual public minter::tx_data {
public:
    tx_edit_coin_owner(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_edit_coin_owner& set_symbol(const std::string& symbol);
    tx_edit_coin_owner& set_symbol(const char* symbol);
    tx_edit_coin_owner& set_new_owner(const minter::address_t& new_owner);

    std::string get_symbol() const;
    const minter::address_t& get_new_owner() const;

private:
    std::string m_symbol;
    minter::address_t m_new_owner;
};

} // namespace minter

#endif //MINTER_TX_TX_EDIT_COIN_OWNER_H
