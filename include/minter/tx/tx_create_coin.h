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

class MINTER_TX_API tx_create_coin: public virtual minter::tx_data {
public:
    explicit tx_create_coin(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;

    tx_create_coin& set_name(const char* coin_name);
    tx_create_coin& set_name(const std::string &coin_name);
    tx_create_coin& set_ticker(const char* coin_symbol);
    tx_create_coin& set_ticker(const std::string& coin_symbol);
    tx_create_coin& set_initial_amount(const char* amount);
    tx_create_coin& set_initial_amount(const dev::bigdec18 &amount);
    tx_create_coin& set_initial_amount(const dev::bigint &amount);
    tx_create_coin& set_initial_reserve(const char* amount);
    tx_create_coin& set_initial_reserve(const dev::bigdec18 &amount);
    tx_create_coin& set_initial_reserve(const dev::bigint &amount);
    /// \brief
    /// \param crr Min value: 10, max = 100
    /// \return
    tx_create_coin& set_crr(unsigned crr);

    std::string get_name() const;
    std::string get_ticker() const;
    dev::bigdec18 get_initial_amount() const;
    dev::bigdec18 get_initial_reserve() const;
    unsigned get_crr() const;

protected:
    void decode_internal(dev::RLP rlp) override;

private:
    std::string m_name;
    std::string m_ticker;
    dev::bigint m_initial_amount;
    dev::bigint m_initial_reserve;
    dev::bigint m_crr;
};

}

#endif //MINTER_TX_CREATE_COIN_H
