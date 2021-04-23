/*!
 * minter_tx.
 * tx_create_coin.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_CREATE_COIN_H
#define MINTER_TX_CREATE_COIN_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_create_coin : public virtual minter::tx_data {
public:
    explicit tx_create_coin(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    /// \brief common coin name, example Bitcoin BTC
    /// \param coin_name
    /// \return
    tx_create_coin& set_name(const std::string& coin_name);
    /// \brief ticker name, example BTC
    /// \param coin_symbol
    /// \return
    tx_create_coin& set_ticker(const std::string& coin_symbol);
    /// \brief Initial coin amount in decimal string representation
    /// \param amount decimal string
    /// \return
    tx_create_coin& set_initial_amount(const std::string& amount);
    /// \brief Initial coin amount in bigdecimal
    /// \param amount bigdecimal representation
    /// \return
    tx_create_coin& set_initial_amount(const dev::bigdec18& amount);
    /// \brief Initial coin amount in bigint representation (PIPs)
    /// \param amount bigint
    /// \return
    tx_create_coin& set_initial_amount(dev::bigint amount);
    /// \brief Initial reserve in decimal string
    /// \param amount decimal string
    /// \return
    tx_create_coin& set_initial_reserve(const std::string& amount);
    /// \brief Initial reserve in big decimal
    /// \param amount bigdecimal
    /// \return
    tx_create_coin& set_initial_reserve(const dev::bigdec18& amount);
    /// \brief Initial reserve in PIPs
    /// \param amount
    /// \return
    tx_create_coin& set_initial_reserve(dev::bigint amount);
    /// \brief
    /// \param crr Min value: 10, max = 100
    /// \return
    tx_create_coin& set_crr(unsigned crr);
    /// \brief Coin purchase will not be possible if the limit is exceeded.
    /// \param max_supply decimal string
    /// \return self
    tx_create_coin& set_max_supply(const std::string& max_supply);
    tx_create_coin& set_max_supply(dev::bigint max_supply);
    tx_create_coin& set_max_supply(const dev::bigdec18& max_supply);

    std::string get_name() const;
    std::string get_ticker() const;
    dev::bigdec18 get_initial_amount() const;
    dev::bigdec18 get_initial_reserve() const;
    unsigned get_crr() const;
    dev::bigdec18 get_max_supply() const;

protected:
    std::string m_name;
    std::string m_ticker;
    dev::bigint m_initial_amount;
    dev::bigint m_initial_reserve;
    dev::bigint m_crr;
    dev::bigint m_max_supply;
};

} // namespace minter

#endif //MINTER_TX_CREATE_COIN_H
