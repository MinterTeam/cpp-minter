/*!
 * minter_tx.
 * tx_multisend.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_multisend.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"
minter::tx_multisend::tx_multisend(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}
uint16_t minter::tx_multisend::type() const {
    return minter::tx_multisend_type.type();
}

#include <iostream>
dev::bytes minter::tx_multisend::encode() {
    eth::RLPStream out;
    eth::RLPStream items_out;
    eth::RLPStream items;
    {
        for (const auto& item : m_items) {
            eth::RLPStream elements;
            elements.append(minter::utils::to_bytes_fixed(item.coin, 10));
            elements.append(item.to.get());
            elements.append(item.amount);
            items.appendList(elements);
        }

        items_out.appendList(items);
    }
    out.appendList(items_out);

    return out.out();
}

void minter::tx_multisend::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    if (rlp.itemCount() == 0) {
        return;
    }

    m_items.reserve(rlp[0].itemCount());

    for (size_t i = 0; i < rlp[0].itemCount(); i++) {
        eth::RLP els = rlp[0][i];
        send_target t{
            minter::utils::to_string_clear((dev::bytes) els[0]),
            (dev::bytes) els[1],
            (dev::bigint) els[2]};

        m_items.push_back(std::move(t));
    }
}

minter::tx_multisend&
minter::tx_multisend::add_item(const std::string& coin, const minter::data::address& to, const std::string& amount) {
    m_items.push_back(minter::send_target{coin, to, minter::utils::normalize_value(amount)});
    return *this;
}

minter::tx_multisend&
minter::tx_multisend::add_item(const std::string& coin, const minter::data::address& to, const dev::bigdec18& amount) {
    m_items.push_back(minter::send_target{std::string(coin), to, minter::utils::normalize_value(amount)});
    return *this;
}

minter::tx_multisend&
minter::tx_multisend::add_item(const std::string& coin, const minter::data::address& to, const dev::bigint& amount) {
    m_items.push_back(minter::send_target{std::string(coin), to, amount});
    return *this;
}

const std::vector<minter::send_target>& minter::tx_multisend::get_items() const {
    return m_items;
}
