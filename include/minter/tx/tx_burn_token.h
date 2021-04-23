/*!
 * minter_tx.
 * tx_burn_token.h
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_BURN_TOKEN_H
#define MINTER_TX_TX_BURN_TOKEN_H

#include "tx_data.h"
#include "tx_mint_token.h"

namespace minter {

class MINTER_TX_API tx_burn_token : public minter::tx_mint_token {
public:
    explicit tx_burn_token(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_burn_token& set_coin_id(dev::bigint coin);
    tx_burn_token& set_coin_id(const std::string& coin_id_num);
    tx_burn_token& set_value(const std::string& value);
    tx_burn_token& set_value(const dev::bigdec18& value);
    tx_burn_token& set_value(dev::bigint value);
};

} // namespace minter

#endif //MINTER_TX_TX_BURN_TOKEN_H
