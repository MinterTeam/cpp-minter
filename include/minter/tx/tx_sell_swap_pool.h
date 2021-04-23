/*!
 * minter_tx.
 * tx_sell_swap_pool.h
 *
 * \date 03/23/2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#ifndef MINTER_TX_TX_SELL_SWAP_POOL_H
#define MINTER_TX_TX_SELL_SWAP_POOL_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_sell_swap_pool : public virtual minter::tx_data {
public:
    static const uint32_t MAX_EXCHANGE_CHAIN = 5;

    explicit tx_sell_swap_pool(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    std::vector<dev::bigint> get_coins() const;
    dev::bigdec18 get_value_to_sell() const;
    dev::bigdec18 get_min_value_to_buy() const;

    tx_sell_swap_pool& add_coin(dev::bigint coin);
    tx_sell_swap_pool& add_coin(const std::string& coin_id_num);
    tx_sell_swap_pool& clear_coins();

    tx_sell_swap_pool& set_value_to_sell(const std::string& value);
    tx_sell_swap_pool& set_value_to_sell(const dev::bigdec18& value);
    tx_sell_swap_pool& set_value_to_sell(dev::bigint value);

    tx_sell_swap_pool& set_min_value_to_buy(const std::string& value);
    tx_sell_swap_pool& set_min_value_to_buy(const dev::bigdec18& value);
    tx_sell_swap_pool& set_min_value_to_buy(dev::bigint value);

private:
    std::vector<dev::bigint> m_coins;
    dev::bigint m_value_to_sell;
    dev::bigint m_min_value_to_buy;
};

} // namespace minter

#endif //MINTER_TX_TX_SELL_SWAP_POOL_H
