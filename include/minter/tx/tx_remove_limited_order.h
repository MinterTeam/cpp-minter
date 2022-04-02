/*!
 * minter_tx.
 * tx_remove_limited_order.h
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_REMOVE_LIMITED_ORDER_H
#define MINTER_TX_TX_REMOVE_LIMITED_ORDER_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_remove_limited_order : public virtual minter::tx_data {
public:
    explicit tx_remove_limited_order(std::shared_ptr<minter::tx> tx);
    ~tx_remove_limited_order() override = default;
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    dev::bigint get_id() const;

    tx_remove_limited_order& set_id(dev::bigint id);
    tx_remove_limited_order& set_id(const std::string& id_num);

private:
    dev::bigint m_id;
};

} // namespace minter

#endif // MINTER_TX_TX_REMOVE_LIMITED_ORDER_H
