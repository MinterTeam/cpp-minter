/*!
 * minter_tx.
 * tx_recreate_token.h
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_RECREATE_TOKEN_H
#define MINTER_TX_TX_RECREATE_TOKEN_H

#include "tx_create_token.h"

namespace minter {

class MINTER_TX_API tx_recreate_token : public minter::tx_create_token {
public:
    explicit tx_recreate_token(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    /// \brief common token name, example Bitcoin BTC
    /// \param coin_name
    /// \return
    tx_recreate_token& set_name(const std::string& coin_name);
    /// \brief ticker name, example BTC
    /// \param coin_symbol
    /// \return
    tx_recreate_token& set_ticker(const std::string& coin_symbol);
    /// \brief Initial token amount in decimal string representation
    /// \param amount decimal string
    /// \return
    tx_recreate_token& set_initial_amount(const std::string& amount);
    /// \brief Initial token amount in bigdecimal
    /// \param amount bigdecimal representation
    /// \return
    tx_recreate_token& set_initial_amount(const dev::bigdec18& amount);
    /// \brief Initial token amount in bigint representation (PIPs)
    /// \param amount bigint
    /// \return
    tx_recreate_token& set_initial_amount(dev::bigint amount);

    /// \brief Coin purchase will not be possible if the limit is exceeded.
    /// \param max_supply decimal string
    /// \return self
    tx_recreate_token& set_max_supply(const std::string& max_supply);
    tx_recreate_token& set_max_supply(dev::bigint max_supply);
    tx_recreate_token& set_max_supply(const dev::bigdec18& max_supply);

    tx_recreate_token& set_mintable(bool mintable);
    tx_recreate_token& set_burnable(bool burnable);
};

} // namespace minter

#endif //MINTER_TX_TX_RECREATE_TOKEN_H
