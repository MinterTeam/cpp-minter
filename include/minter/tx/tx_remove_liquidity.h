/*!
 * minter_tx.
 * tx_remove_liquidity.h
 *
 * \date 03/23/2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#ifndef MINTER_TX_TX_REMOVE_LIQUIDITY_H
#define MINTER_TX_TX_REMOVE_LIQUIDITY_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_remove_liquidity : public virtual minter::tx_data {
public:
    explicit tx_remove_liquidity(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    dev::bigint get_coin_0() const;
    dev::bigint get_coin_1() const;
    dev::bigdec18 get_liquidity() const;
    dev::bigdec18 get_min_volume_0() const;
    dev::bigdec18 get_min_volume_1() const;

    tx_remove_liquidity& set_coin_0(dev::bigint coin);
    tx_remove_liquidity& set_coin_0(const std::string& coin_id_num);
    tx_remove_liquidity& set_coin_1(dev::bigint coin);
    tx_remove_liquidity& set_coin_1(const std::string& coin_id_num);

    tx_remove_liquidity& set_liquidity(const std::string& value);
    tx_remove_liquidity& set_liquidity(const dev::bigdec18& value);
    tx_remove_liquidity& set_liquidity(dev::bigint value);

    tx_remove_liquidity& set_min_volume_0(const std::string& value);
    tx_remove_liquidity& set_min_volume_0(const dev::bigdec18& value);
    tx_remove_liquidity& set_min_volume_0(dev::bigint value);

    tx_remove_liquidity& set_min_volume_1(const std::string& value);
    tx_remove_liquidity& set_min_volume_1(const dev::bigdec18& value);
    tx_remove_liquidity& set_min_volume_1(dev::bigint value);

private:
    dev::bigint m_coin_0;
    dev::bigint m_coin_1;
    dev::bigint m_liquidity;
    dev::bigint m_min_volume_0;
    dev::bigint m_min_volume_1;
};

} // namespace minter

#endif //MINTER_TX_TX_REMOVE_LIQUIDITY_H
