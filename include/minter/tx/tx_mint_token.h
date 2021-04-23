/*!
 * minter_tx.
 * tx_mint_token.h
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_MINT_TOKEN_H
#define MINTER_TX_TX_MINT_TOKEN_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_mint_token : public virtual minter::tx_data {
public:
    explicit tx_mint_token(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    dev::bigint get_coin_id() const;
    dev::bigdec18 get_value() const;

    tx_mint_token& set_coin_id(dev::bigint coin);
    tx_mint_token& set_coin_id(const std::string& coin_id_num);
    tx_mint_token& set_value(const std::string& value);
    tx_mint_token& set_value(const dev::bigdec18& value);
    tx_mint_token& set_value(dev::bigint value);

protected:
    dev::bigint m_coin_id;
    dev::bigint m_value;
};

} // namespace minter

#endif //MINTER_TX_TX_MINT_TOKEN_H
