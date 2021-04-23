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

    /// \brief Set coin_id to send
    /// \param coin_id network coin ID
    /// \return
    tx_send_coin& set_coin_id(dev::bigint coin_id);
    tx_send_coin& set_coin_id(const std::string& coin_id_num);

    /// \brief Set recipient address
    /// \param address may be minter::address_t and std::string (implicitly converts to address_t)
    /// \return
    tx_send_coin& set_to(const minter::address_t& address);

    tx_send_coin& set_value(const std::string& value);
    tx_send_coin& set_value(const dev::bigdec18& value);
    tx_send_coin& set_value(dev::bigint value);

    dev::bigint get_coin_id() const;
    const minter::address_t& get_to() const;
    dev::bigdec18 get_value() const;

private:
    dev::bigint m_coin_id;
    minter::data::address m_to;
    dev::bigint m_value;
};

} // namespace minter

#endif //MINTER_TX_SEND_COIN_H
