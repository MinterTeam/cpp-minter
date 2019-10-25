/*!
 * minter_tx.
 * tx_sell_coin.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_SELL_COIN_H
#define MINTER_TX_SELL_COIN_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_sell_coin: public virtual minter::tx_data {
public:
    explicit tx_sell_coin(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;

    tx_sell_coin& set_coin_to_sell(const char* coin);
    tx_sell_coin& set_coin_to_sell(const std::string &coin);
    tx_sell_coin& set_value_to_sell(const char* amount);
    tx_sell_coin& set_value_to_sell(const dev::bigdec18 &amount);
    tx_sell_coin& set_coin_to_buy(const char* coin);
    tx_sell_coin& set_coin_to_buy(const std::string &coin);
    tx_sell_coin& set_min_value_to_buy(const char* amount);
    tx_sell_coin& set_min_value_to_buy(const std::string &amount);
    tx_sell_coin& set_min_value_to_buy(const dev::bigdec18 &amount);

    std::string get_coin_to_sell() const;
    std::string get_coin_to_buy() const;
    dev::bigdec18 get_value_to_sell() const;
    dev::bigdec18 get_min_value_to_buy() const;

protected:
    void decode_internal(dev::RLP rlp) override;

private:
    std::string m_coin_to_sell;
    dev::bigint m_value_to_sell;
    std::string m_coin_to_buy;
    dev::bigint m_min_value_to_buy;
};

}

#endif //MINTER_TX_SELL_COIN_H
