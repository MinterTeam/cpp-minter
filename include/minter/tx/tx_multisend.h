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

#include <vector>
#include "tx_send_coin.h"
#include "tx_data.h"
#include "minter/tx/utils.h"
namespace minter {

    struct send_target {
        std::string coin;
        minter::data::address to;
        dev::bigint amount;

        dev::bigdec18 get_amount() const {
            return minter::utils::humanize_value(amount);
        }
    };

class MINTER_TX_API tx_multisend: public virtual minter::tx_data {
public:
    explicit tx_multisend(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;

    tx_multisend& add_item(const char* coin, const minter::data::address &to, const char* amount);
    tx_multisend& add_item(const char* coin, const minter::data::address &to, const dev::bigdec18 &amount);

    const std::vector<minter::send_target>& get_items() const;

protected:
    void decode_internal(dev::RLP rlp) override;

private:
    std::vector<send_target> m_items;
};

}

#endif //MINTER_TX_MULTISEND_H
