/*!
 * minter_tx.
 * tx_buy_coin.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_BUY_COIN_H
#define MINTER_TX_BUY_COIN_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_buy_coin : public virtual minter::tx_data {
public:
    explicit tx_buy_coin(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    dev::bigint get_coin_id_to_buy() const;
    dev::bigint get_coin_id_to_sell() const;
    dev::bigdec18 get_value_to_buy() const;
    dev::bigdec18 get_max_value_to_sell() const;

    tx_buy_coin& set_coin_id_to_buy(dev::bigint coin_id);
    tx_buy_coin& set_coin_id_to_buy(const std::string& coin_id_num);
    tx_buy_coin& set_coin_id_to_sell(dev::bigint coin_id);
    tx_buy_coin& set_coin_id_to_sell(const std::string& coin_id_num);

    tx_buy_coin& set_value_to_buy(const std::string& value);
    tx_buy_coin& set_value_to_buy(const dev::bigdec18& value);
    tx_buy_coin& set_value_to_buy(dev::bigint value);

    tx_buy_coin& set_max_value_to_sell(const std::string& value);
    tx_buy_coin& set_max_value_to_sell(const dev::bigdec18& value);
    tx_buy_coin& set_max_value_to_sell(dev::bigint value);

private:
    dev::bigint m_coin_id_to_buy;
    dev::bigint m_value_to_buy;
    dev::bigint m_coin_id_to_sell;
    dev::bigint m_max_value_to_sell;
};

} // namespace minter

#endif //MINTER_TX_BUY_COIN_H
