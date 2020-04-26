/*!
 * minter_tx.
 * tx_sell_all_coins.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_SELL_ALL_COINS_H
#define MINTER_TX_SELL_ALL_COINS_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_sell_all_coins : public virtual minter::tx_data {
public:
    explicit tx_sell_all_coins(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_sell_all_coins& set_coin_to_sell(const std::string& coin);
    tx_sell_all_coins& set_coin_to_buy(const std::string& coin);
    tx_sell_all_coins& set_min_value_to_buy(const std::string& amount);
    tx_sell_all_coins& set_min_value_to_buy(const dev::bigint& amount);
    tx_sell_all_coins& set_min_value_to_buy(const dev::bigdec18& amount);

    std::string get_coin_to_sell() const;
    std::string get_coin_to_buy() const;
    dev::bigdec18 get_min_value_to_buy() const;

private:
    std::string m_coin_to_sell;
    std::string m_coin_to_buy;
    dev::bigint m_min_value_to_buy;
};

} // namespace minter

#endif //MINTER_TX_SELL_ALL_COINS_H
