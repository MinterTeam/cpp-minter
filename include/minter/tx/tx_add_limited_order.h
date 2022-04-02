/*!
 * minter_tx.
 * tx_add_limited_order.h
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_ADD_LIMITED_ORDER_H
#define MINTER_TX_TX_ADD_LIMITED_ORDER_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_add_limited_order : public virtual minter::tx_data {
public:
    explicit tx_add_limited_order(std::shared_ptr<minter::tx> tx);
    ~tx_add_limited_order() override = default;
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    dev::bigint get_coin_id_to_sell() const;
    dev::bigint get_coin_id_to_buy() const;
    dev::bigdec18 get_value_to_sell() const;
    dev::bigdec18 get_value_to_buy() const;

    tx_add_limited_order& set_coin_id_to_sell(dev::bigint coin_id);
    tx_add_limited_order& set_coin_id_to_sell(const std::string& coin_id_num);
    tx_add_limited_order& set_coin_id_to_buy(dev::bigint coin_id);
    tx_add_limited_order& set_coin_id_to_buy(const std::string& coin_id_num);

    tx_add_limited_order& set_value_to_buy(const std::string& value);
    tx_add_limited_order& set_value_to_buy(const dev::bigdec18& value);
    tx_add_limited_order& set_value_to_buy(dev::bigint value);

    tx_add_limited_order& set_value_to_sell(const std::string& value);
    tx_add_limited_order& set_value_to_sell(const dev::bigdec18& value);
    tx_add_limited_order& set_value_to_sell(dev::bigint value);

private:
    dev::bigint m_coin_id_to_sell;
    dev::bigint m_value_to_sell;
    dev::bigint m_coin_id_to_buy;
    dev::bigint m_value_to_buy;
};

} // namespace minter

#endif // MINTER_TX_TX_ADD_LIMITED_ORDER_H