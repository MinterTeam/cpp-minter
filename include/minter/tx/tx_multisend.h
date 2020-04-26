/*!
 * minter_tx.
 * tx_multisend.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_MULTISEND_H
#define MINTER_TX_MULTISEND_H

#include "minter/tx/utils.h"
#include "tx_data.h"
#include "tx_send_coin.h"

#include <vector>
namespace minter {

struct send_target {
    std::string coin;
    minter::data::address to;
    dev::bigint amount;

    dev::bigdec18 get_amount() const {
        return minter::utils::humanize_value(amount);
    }
};

class MINTER_TX_API tx_multisend : public virtual minter::tx_data {
public:
    explicit tx_multisend(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_multisend& add_item(const std::string& coin, const minter::data::address& to, const std::string& amount);
    tx_multisend& add_item(const std::string& coin, const minter::data::address& to, const dev::bigdec18& amount);
    tx_multisend& add_item(const std::string& coin, const minter::data::address& to, const dev::bigint& amount);

    const std::vector<minter::send_target>& get_items() const;

private:
    std::vector<send_target> m_items;
};

} // namespace minter

#endif //MINTER_TX_MULTISEND_H
