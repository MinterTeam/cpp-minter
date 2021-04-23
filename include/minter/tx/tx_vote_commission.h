/*!
 * minter_tx.
 * tx_vote_commission.h
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TX_VOTE_COMMISSION_H
#define MINTER_TX_TX_VOTE_COMMISSION_H

#include "minter/public_key.h"
#include "tx_data.h"

namespace minter {

class MINTER_TX_API tx_vote_commission : public virtual minter::tx_data {
public:
    explicit tx_vote_commission(std::shared_ptr<minter::tx> tx);
    uint16_t type() const override;
    dev::bytes encode() override;
    void decode(const dev::bytes& data) override;

    tx_vote_commission& set_pub_key(const std::string& pubkey);
    tx_vote_commission& set_pub_key(const minter::pubkey_t& pubkey);
    tx_vote_commission& set_height(const dev::bigint& height);
    tx_vote_commission& set_height(const std::string& height_num);
    tx_vote_commission& set_coin_id(dev::bigint coin);
    tx_vote_commission& set_coin_id(const std::string& coin_id_num);

    tx_vote_commission& set_fee_payload_byte(dev::bigint fee);
    tx_vote_commission& set_fee_send(dev::bigint fee);
    tx_vote_commission& set_fee_buy_bancor(dev::bigint fee);
    tx_vote_commission& set_fee_sell_bancor(dev::bigint fee);
    tx_vote_commission& set_fee_sell_all_bancor(dev::bigint fee);
    tx_vote_commission& set_fee_buy_pool_base(dev::bigint fee);
    tx_vote_commission& set_fee_buy_pool_delta(dev::bigint fee);
    tx_vote_commission& set_fee_sell_pool_base(dev::bigint fee);
    tx_vote_commission& set_fee_sell_pool_delta(dev::bigint fee);
    tx_vote_commission& set_fee_sell_all_pool_base(dev::bigint fee);
    tx_vote_commission& set_fee_sell_all_pool_delta(dev::bigint fee);
    tx_vote_commission& set_fee_create_ticker_3(dev::bigint fee);
    tx_vote_commission& set_fee_create_ticker_4(dev::bigint fee);
    tx_vote_commission& set_fee_create_ticker_5(dev::bigint fee);
    tx_vote_commission& set_fee_create_ticker_6(dev::bigint fee);
    tx_vote_commission& set_fee_create_ticker_7_to_10(dev::bigint fee);
    tx_vote_commission& set_fee_create_coin(dev::bigint fee);
    tx_vote_commission& set_fee_create_token(dev::bigint fee);
    tx_vote_commission& set_fee_recreate_coin(dev::bigint fee);
    tx_vote_commission& set_fee_recreate_token(dev::bigint fee);
    tx_vote_commission& set_fee_declare_candidacy(dev::bigint fee);
    tx_vote_commission& set_fee_delegate(dev::bigint fee);
    tx_vote_commission& set_fee_unbond(dev::bigint fee);
    tx_vote_commission& set_fee_redeem_check(dev::bigint fee);
    tx_vote_commission& set_fee_set_candidate_on(dev::bigint fee);
    tx_vote_commission& set_fee_set_candidate_off(dev::bigint fee);
    tx_vote_commission& set_fee_create_multisig(dev::bigint fee);
    tx_vote_commission& set_fee_multisend_base(dev::bigint fee);
    tx_vote_commission& set_fee_multisend_delta(dev::bigint fee);
    tx_vote_commission& set_fee_edit_candidate(dev::bigint fee);
    tx_vote_commission& set_fee_set_halt_block(dev::bigint fee);
    tx_vote_commission& set_fee_edit_ticker_owner(dev::bigint fee);
    tx_vote_commission& set_fee_edit_multisig(dev::bigint fee);
    tx_vote_commission& set_fee_edit_candidate_pub_key(dev::bigint fee);
    tx_vote_commission& set_fee_create_swap_pool(dev::bigint fee);
    tx_vote_commission& set_fee_add_liquidity(dev::bigint fee);
    tx_vote_commission& set_fee_remove_liquidity(dev::bigint fee);
    tx_vote_commission& set_fee_edit_candidate_commission(dev::bigint fee);
    tx_vote_commission& set_fee_mint_token(dev::bigint fee);
    tx_vote_commission& set_fee_burn_token(dev::bigint fee);
    tx_vote_commission& set_fee_vote_commission(dev::bigint fee);
    tx_vote_commission& set_fee_vote_update(dev::bigint fee);

    const minter::pubkey_t& get_pub_key() const;
    const dev::bigint& get_height() const;
    const dev::bigint& get_coin_id() const;

    dev::bigint get_fee_payload_byte() const;
    dev::bigint get_fee_send() const;
    dev::bigint get_fee_buy_bancor() const;
    dev::bigint get_fee_sell_bancor() const;
    dev::bigint get_fee_sell_all_bancor() const;
    dev::bigint get_fee_buy_pool_base() const;
    dev::bigint get_fee_buy_pool_delta() const;
    dev::bigint get_fee_sell_pool_base() const;
    dev::bigint get_fee_sell_pool_delta() const;
    dev::bigint get_fee_sell_all_pool_base() const;
    dev::bigint get_fee_sell_all_pool_delta() const;
    dev::bigint get_fee_create_ticker_3() const;
    dev::bigint get_fee_create_ticker_4() const;
    dev::bigint get_fee_create_ticker_5() const;
    dev::bigint get_fee_create_ticker_6() const;
    dev::bigint get_fee_create_ticker_7_to_10() const;
    dev::bigint get_fee_create_coin() const;
    dev::bigint get_fee_create_token() const;
    dev::bigint get_fee_recreate_coin() const;
    dev::bigint get_fee_recreate_token() const;
    dev::bigint get_fee_declare_candidacy() const;
    dev::bigint get_fee_delegate() const;
    dev::bigint get_fee_unbond() const;
    dev::bigint get_fee_redeem_check() const;
    dev::bigint get_fee_set_candidate_on() const;
    dev::bigint get_fee_set_candidate_off() const;
    dev::bigint get_fee_create_multisig() const;
    dev::bigint get_fee_multisend_base() const;
    dev::bigint get_fee_multisend_delta() const;
    dev::bigint get_fee_edit_candidate() const;
    dev::bigint get_fee_set_halt_block() const;
    dev::bigint get_fee_edit_ticker_owner() const;
    dev::bigint get_fee_edit_multisig() const;
    dev::bigint get_fee_edit_candidate_pub_key() const;
    dev::bigint get_fee_create_swap_pool() const;
    dev::bigint get_fee_add_liquidity() const;
    dev::bigint get_fee_remove_liquidity() const;
    dev::bigint get_fee_edit_candidate_commission() const;
    dev::bigint get_fee_mint_token() const;
    dev::bigint get_fee_burn_token() const;
    dev::bigint get_fee_vote_commission() const;
    dev::bigint get_fee_vote_update() const;

private:
    minter::pubkey_t m_pub_key;
    dev::bigint m_height;
    dev::bigint m_coin_id;

    // all these values counts in PIPs, so if you want to get absolute BIP value, you could multiple value to OperationType.BASE_FEE
    dev::bigint m_payload_byte;
    dev::bigint m_send;
    dev::bigint m_buy_bancor;
    dev::bigint m_sell_bancor;
    dev::bigint m_sell_all_bancor;
    dev::bigint m_buy_pool_base;
    dev::bigint m_buy_pool_delta;
    dev::bigint m_sell_pool_base;
    dev::bigint m_sell_pool_delta;
    dev::bigint m_sell_all_pool_base;
    dev::bigint m_sell_all_pool_delta;
    dev::bigint m_create_ticker_3;
    dev::bigint m_create_ticker_4;
    dev::bigint m_create_ticker_5;
    dev::bigint m_create_ticker_6;
    dev::bigint m_create_ticker_7_to_10;
    dev::bigint m_create_coin;
    dev::bigint m_create_token;
    dev::bigint m_recreate_coin;
    dev::bigint m_recreate_token;
    dev::bigint m_declare_candidacy;
    dev::bigint m_delegate;
    dev::bigint m_unbond;
    dev::bigint m_redeem_check;
    dev::bigint m_set_candidate_on;
    dev::bigint m_set_candidate_off;
    dev::bigint m_create_multisig;
    dev::bigint m_multisend_base;
    dev::bigint m_multisend_delta;
    dev::bigint m_edit_candidate;
    dev::bigint m_set_halt_block;
    dev::bigint m_edit_ticker_owner;
    dev::bigint m_edit_multisig;
    dev::bigint m_edit_candidate_pub_key;
    dev::bigint m_create_swap_pool;
    dev::bigint m_add_liquidity;
    dev::bigint m_remove_liquidity;
    dev::bigint m_edit_candidate_commission;
    dev::bigint m_mint_token;
    dev::bigint m_burn_token;
    dev::bigint m_vote_commission;
    dev::bigint m_vote_update;
};

} // namespace minter

#endif //MINTER_TX_TX_VOTE_COMMISSION_H
