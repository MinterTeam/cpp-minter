/*!
 * minter_tx.
 * tx_buy_swap_pool.h
 *
 * \date 03/23/2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#ifndef MINTER_TX_TX_BUY_SWAP_POOL_H
#define MINTER_TX_TX_BUY_SWAP_POOL_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_buy_swap_pool : public virtual tx_data {
public:
    static const uint32_t MAX_EXCHANGE_CHAIN = 5;

    explicit tx_buy_swap_pool(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    std::vector<dev::bigint> get_coins() const;
    dev::bigdec18 get_value_to_buy() const;
    dev::bigdec18 get_max_value_to_sell() const;

    tx_buy_swap_pool& add_coin(const dev::bigint& coin);
    tx_buy_swap_pool& clear_coins();

    tx_buy_swap_pool& set_value_to_buy(const std::string& value);
    tx_buy_swap_pool& set_value_to_buy(const dev::bigdec18& value);
    tx_buy_swap_pool& set_value_to_buy(dev::bigint value);

    tx_buy_swap_pool& set_max_value_to_sell(const std::string& value);
    tx_buy_swap_pool& set_max_value_to_sell(const dev::bigdec18& value);
    tx_buy_swap_pool& set_max_value_to_sell(dev::bigint value);

private:
    std::vector<dev::bigint> m_coins;
    dev::bigint m_value_to_buy;
    dev::bigint m_max_value_to_sell;
};

} // namespace minter

#endif //MINTER_TX_TX_BUY_SWAP_POOL_H
