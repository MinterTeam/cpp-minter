/*!
 * minter_tx.
 * tx_price_vote.h
 *
 * \date 2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_PRICE_VOTE_H
#define MINTER_TX_TX_PRICE_VOTE_H

#include "tx_data.h"

namespace minter {

class tx_price_vote : virtual public minter::tx_data {
public:
    explicit tx_price_vote(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_price_vote& set_price(dev::bigint price);

    dev::bigint get_price() const;

private:
    dev::bigint m_price;
};

} // namespace minter

#endif //MINTER_TX_TX_PRICE_VOTE_H
