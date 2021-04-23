/*!
 * minter_tx.
 * tx_create_swap_pool.h
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_CREATE_SWAP_POOL_H
#define MINTER_TX_TX_CREATE_SWAP_POOL_H

#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_create_swap_pool : public virtual minter::tx_data {
public:
    explicit tx_create_swap_pool(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    dev::bigint get_coin_0() const;
    dev::bigint get_coin_1() const;
    dev::bigdec18 get_volume_0() const;
    dev::bigdec18 get_volume_1() const;

    tx_create_swap_pool& set_coin_0(dev::bigint coin);
    tx_create_swap_pool& set_coin_0(const std::string& coin_id_num);
    tx_create_swap_pool& set_coin_1(dev::bigint coin);
    tx_create_swap_pool& set_coin_1(const std::string& coin_id_num);

    tx_create_swap_pool& set_volume_0(const std::string& volume);
    tx_create_swap_pool& set_volume_0(dev::bigint volume);
    tx_create_swap_pool& set_volume_0(const dev::bigdec18& volume);
    tx_create_swap_pool& set_volume_1(const std::string& volume);
    tx_create_swap_pool& set_volume_1(dev::bigint volume);
    tx_create_swap_pool& set_volume_1(const dev::bigdec18& volume);

private:
    dev::bigint m_coin_0;
    dev::bigint m_coin_1;
    dev::bigint m_volume_0;
    dev::bigint m_volume_1;
};

} // namespace minter

#endif //MINTER_TX_TX_CREATE_SWAP_POOL_H
