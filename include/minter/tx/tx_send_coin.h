/*!
 * minter_tx.
 * tx_send_coin.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_SEND_COIN_H
#define MINTER_TX_SEND_COIN_H

#include "minter/address.h"
#include "minter/minter_tx_config.h"
#include "tx_data.h"

#include <minter/eth/RLP.h>

namespace minter {

class MINTER_TX_API tx_send_coin : public virtual minter::tx_data {
public:
    explicit tx_send_coin(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_send_coin& set_coin(const std::string& coin);
    tx_send_coin& set_coin(std::string&& coin);
    tx_send_coin& set_coin(const char* coin);
    tx_send_coin& set_to(const minter::data::address& address);
    tx_send_coin& set_to(const std::string& address);
    tx_send_coin& set_to(const char* address);
    tx_send_coin& set_value(const dev::bigdec18& normalized);
    tx_send_coin& set_value(const std::string& normalized);
    tx_send_coin& set_value(const dev::bigint& raw);
    std::string get_coin() const;

    const minter::data::address& get_to() const;
    dev::bigdec18 get_value() const;

private:
    std::string m_coin;
    minter::data::address m_to;
    dev::bigint m_value;
};

} // namespace minter

#endif //MINTER_TX_SEND_COIN_H
