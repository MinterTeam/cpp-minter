/*!
 * minter_tx.
 * tx_remove_limited_order.cpp
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_remove_limited_order.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

minter::tx_remove_limited_order::tx_remove_limited_order(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}
dev::bigint minter::tx_remove_limited_order::get_id() const {
    return m_id;
}

minter::tx_remove_limited_order& minter::tx_remove_limited_order::set_id(dev::bigint id) {
    m_id = std::move(id);
    return *this;
}

minter::tx_remove_limited_order& minter::tx_remove_limited_order::set_id(const std::string& id_num) {
    m_id = dev::bigint(id_num);
    return *this;
}

uint16_t minter::tx_remove_limited_order::type() const {
    return minter::tx_remove_limited_order_type.type();
}

dev::bytes minter::tx_remove_limited_order::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_id);
        out.appendList(lst);
    }
    return out.out();
}

void minter::tx_remove_limited_order::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    m_id = minter::utils::to_bigint((dev::bytes) rlp[0]);
}
