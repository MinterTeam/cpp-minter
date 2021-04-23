/*!
 * minter_tx.
 * tx_vote_commission.cpp.c
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include "minter/tx/tx_vote_commission.h"

#include "minter/tx/tx_type.h"
#include "minter/tx/utils.h"

#include <utility>

minter::tx_vote_commission::tx_vote_commission(std::shared_ptr<minter::tx> tx)
    : tx_data(std::move(tx)) {
}

uint16_t minter::tx_vote_commission::type() const {
    return minter::tx_vote_commission_type.type();
}
dev::bytes minter::tx_vote_commission::encode() {
    eth::RLPStream out;
    eth::RLPStream lst;
    {
        lst.append(m_pub_key);
        lst.append(m_height);
        lst.append(m_coin_id);

        lst.append(m_payload_byte);
        lst.append(m_send);
        lst.append(m_buy_bancor);
        lst.append(m_sell_bancor);
        lst.append(m_sell_all_bancor);
        lst.append(m_buy_pool_base);
        lst.append(m_buy_pool_delta);
        lst.append(m_sell_pool_base);
        lst.append(m_sell_pool_delta);
        lst.append(m_sell_all_pool_base);
        lst.append(m_sell_all_pool_delta);
        lst.append(m_create_ticker_3);
        lst.append(m_create_ticker_4);
        lst.append(m_create_ticker_5);
        lst.append(m_create_ticker_6);
        lst.append(m_create_ticker_7_to_10);
        lst.append(m_create_coin);
        lst.append(m_create_token);
        lst.append(m_recreate_coin);
        lst.append(m_recreate_token);
        lst.append(m_declare_candidacy);
        lst.append(m_delegate);
        lst.append(m_unbond);
        lst.append(m_redeem_check);
        lst.append(m_set_candidate_on);
        lst.append(m_set_candidate_off);
        lst.append(m_create_multisig);
        lst.append(m_multisend_base);
        lst.append(m_multisend_delta);
        lst.append(m_edit_candidate);
        lst.append(m_set_halt_block);
        lst.append(m_edit_ticker_owner);
        lst.append(m_edit_multisig);
        lst.append(m_edit_candidate_pub_key);
        lst.append(m_create_swap_pool);
        lst.append(m_add_liquidity);
        lst.append(m_remove_liquidity);
        lst.append(m_edit_candidate_commission);
        lst.append(m_mint_token);
        lst.append(m_burn_token);
        lst.append(m_vote_commission);
        lst.append(m_vote_update);

        out.appendList(lst);
    }

    return out.out();
}
void minter::tx_vote_commission::decode(const dev::bytes& data) {
    eth::RLP rlp(data);
    size_t i = 0;
    m_pub_key = (dev::bytes) rlp[i++];
    m_height = (dev::bigint) rlp[i++];
    m_coin_id = (dev::bigint) rlp[i++];

    m_payload_byte = (dev::bigint) rlp[i++];
    m_send = (dev::bigint) rlp[i++];
    m_buy_bancor = (dev::bigint) rlp[i++];
    m_sell_bancor = (dev::bigint) rlp[i++];
    m_sell_all_bancor = (dev::bigint) rlp[i++];
    m_buy_pool_base = (dev::bigint) rlp[i++];
    m_buy_pool_delta = (dev::bigint) rlp[i++];
    m_sell_pool_base = (dev::bigint) rlp[i++];
    m_sell_pool_delta = (dev::bigint) rlp[i++];
    m_sell_all_pool_base = (dev::bigint) rlp[i++];
    m_sell_all_pool_delta = (dev::bigint) rlp[i++];
    m_create_ticker_3 = (dev::bigint) rlp[i++];
    m_create_ticker_4 = (dev::bigint) rlp[i++];
    m_create_ticker_5 = (dev::bigint) rlp[i++];
    m_create_ticker_6 = (dev::bigint) rlp[i++];
    m_create_ticker_7_to_10 = (dev::bigint) rlp[i++];
    m_create_coin = (dev::bigint) rlp[i++];
    m_create_token = (dev::bigint) rlp[i++];
    m_recreate_coin = (dev::bigint) rlp[i++];
    m_recreate_token = (dev::bigint) rlp[i++];
    m_declare_candidacy = (dev::bigint) rlp[i++];
    m_delegate = (dev::bigint) rlp[i++];
    m_unbond = (dev::bigint) rlp[i++];
    m_redeem_check = (dev::bigint) rlp[i++];
    m_set_candidate_on = (dev::bigint) rlp[i++];
    m_set_candidate_off = (dev::bigint) rlp[i++];
    m_create_multisig = (dev::bigint) rlp[i++];
    m_multisend_base = (dev::bigint) rlp[i++];
    m_multisend_delta = (dev::bigint) rlp[i++];
    m_edit_candidate = (dev::bigint) rlp[i++];
    m_set_halt_block = (dev::bigint) rlp[i++];
    m_edit_ticker_owner = (dev::bigint) rlp[i++];
    m_edit_multisig = (dev::bigint) rlp[i++];
    m_edit_candidate_pub_key = (dev::bigint) rlp[i++];
    m_create_swap_pool = (dev::bigint) rlp[i++];
    m_add_liquidity = (dev::bigint) rlp[i++];
    m_remove_liquidity = (dev::bigint) rlp[i++];
    m_edit_candidate_commission = (dev::bigint) rlp[i++];
    m_mint_token = (dev::bigint) rlp[i++];
    m_burn_token = (dev::bigint) rlp[i++];
    m_vote_commission = (dev::bigint) rlp[i++];
    m_vote_update = (dev::bigint) rlp[i++];
}

minter::tx_vote_commission& minter::tx_vote_commission::set_pub_key(const std::string& pubkey) {
    m_pub_key = minter::pubkey_t(pubkey);
    return *this;
}
minter::tx_vote_commission& minter::tx_vote_commission::set_pub_key(const minter::pubkey_t& pubkey) {
    m_pub_key = pubkey;
    return *this;
}
minter::tx_vote_commission& minter::tx_vote_commission::set_height(const dev::bigint& height) {
    m_height = height;
    return *this;
}
minter::tx_vote_commission& minter::tx_vote_commission::set_height(const std::string& height_num) {
    m_height = dev::bigint(height_num);
    return *this;
}
minter::tx_vote_commission& minter::tx_vote_commission::set_coin_id(dev::bigint coin) {
    m_coin_id = std::move(coin);
    return *this;
}
minter::tx_vote_commission& minter::tx_vote_commission::set_coin_id(const std::string& coin_id_num) {
    m_coin_id = dev::bigint(coin_id_num);
    return *this;
}
const minter::pubkey_t& minter::tx_vote_commission::get_pub_key() const {
    return m_pub_key;
}
const dev::bigint& minter::tx_vote_commission::get_height() const {
    return m_height;
}
const dev::bigint& minter::tx_vote_commission::get_coin_id() const {
    return m_coin_id;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_payload_byte(dev::bigint fee) {
    m_payload_byte = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_send(dev::bigint fee) {
    m_send = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_buy_bancor(dev::bigint fee) {
    m_buy_bancor = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_sell_bancor(dev::bigint fee) {
    m_sell_bancor = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_sell_all_bancor(dev::bigint fee) {
    m_sell_all_bancor = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_buy_pool_base(dev::bigint fee) {
    m_buy_pool_base = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_buy_pool_delta(dev::bigint fee) {
    m_buy_pool_delta = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_sell_pool_base(dev::bigint fee) {
    m_sell_pool_base = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_sell_pool_delta(dev::bigint fee) {
    m_sell_pool_delta = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_sell_all_pool_base(dev::bigint fee) {
    m_sell_all_pool_base = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_sell_all_pool_delta(dev::bigint fee) {
    m_sell_all_pool_delta = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_create_ticker_3(dev::bigint fee) {
    m_create_ticker_3 = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_create_ticker_4(dev::bigint fee) {
    m_create_ticker_4 = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_create_ticker_5(dev::bigint fee) {
    m_create_ticker_5 = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_create_ticker_6(dev::bigint fee) {
    m_create_ticker_6 = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_create_ticker_7_to_10(dev::bigint fee) {
    m_create_ticker_7_to_10 = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_create_coin(dev::bigint fee) {
    m_create_coin = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_create_token(dev::bigint fee) {
    m_create_token = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_recreate_coin(dev::bigint fee) {
    m_recreate_coin = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_recreate_token(dev::bigint fee) {
    m_recreate_token = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_declare_candidacy(dev::bigint fee) {
    m_declare_candidacy = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_delegate(dev::bigint fee) {
    m_delegate = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_unbond(dev::bigint fee) {
    m_unbond = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_redeem_check(dev::bigint fee) {
    m_redeem_check = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_set_candidate_on(dev::bigint fee) {
    m_set_candidate_on = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_set_candidate_off(dev::bigint fee) {
    m_set_candidate_off = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_create_multisig(dev::bigint fee) {
    m_create_multisig = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_multisend_base(dev::bigint fee) {
    m_multisend_base = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_multisend_delta(dev::bigint fee) {
    m_multisend_delta = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_edit_candidate(dev::bigint fee) {
    m_edit_candidate = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_set_halt_block(dev::bigint fee) {
    m_set_halt_block = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_edit_ticker_owner(dev::bigint fee) {
    m_edit_ticker_owner = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_edit_multisig(dev::bigint fee) {
    m_edit_multisig = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_edit_candidate_pub_key(dev::bigint fee) {
    m_edit_candidate_pub_key = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_create_swap_pool(dev::bigint fee) {
    m_create_swap_pool = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_add_liquidity(dev::bigint fee) {
    m_add_liquidity = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_remove_liquidity(dev::bigint fee) {
    m_remove_liquidity = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_edit_candidate_commission(dev::bigint fee) {
    m_edit_candidate_commission = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_mint_token(dev::bigint fee) {
    m_mint_token = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_burn_token(dev::bigint fee) {
    m_burn_token = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_vote_commission(dev::bigint fee) {
    m_vote_commission = std::move(fee);
    return *this;
}

minter::tx_vote_commission& minter::tx_vote_commission::set_fee_vote_update(dev::bigint fee) {
    m_vote_update = std::move(fee);
    return *this;
}

dev::bigint minter::tx_vote_commission::get_fee_payload_byte() const {
    return m_payload_byte;
}

dev::bigint minter::tx_vote_commission::get_fee_send() const {
    return m_send;
}

dev::bigint minter::tx_vote_commission::get_fee_buy_bancor() const {
    return m_buy_bancor;
}

dev::bigint minter::tx_vote_commission::get_fee_sell_bancor() const {
    return m_sell_bancor;
}

dev::bigint minter::tx_vote_commission::get_fee_sell_all_bancor() const {
    return m_sell_all_bancor;
}

dev::bigint minter::tx_vote_commission::get_fee_buy_pool_base() const {
    return m_buy_pool_base;
}

dev::bigint minter::tx_vote_commission::get_fee_buy_pool_delta() const {
    return m_buy_pool_delta;
}

dev::bigint minter::tx_vote_commission::get_fee_sell_pool_base() const {
    return m_sell_pool_base;
}

dev::bigint minter::tx_vote_commission::get_fee_sell_pool_delta() const {
    return m_sell_pool_delta;
}

dev::bigint minter::tx_vote_commission::get_fee_sell_all_pool_base() const {
    return m_sell_all_pool_base;
}

dev::bigint minter::tx_vote_commission::get_fee_sell_all_pool_delta() const {
    return m_sell_all_pool_delta;
}

dev::bigint minter::tx_vote_commission::get_fee_create_ticker_3() const {
    return m_create_ticker_3;
}

dev::bigint minter::tx_vote_commission::get_fee_create_ticker_4() const {
    return m_create_ticker_4;
}

dev::bigint minter::tx_vote_commission::get_fee_create_ticker_5() const {
    return m_create_ticker_5;
}

dev::bigint minter::tx_vote_commission::get_fee_create_ticker_6() const {
    return m_create_ticker_6;
}

dev::bigint minter::tx_vote_commission::get_fee_create_ticker_7_to_10() const {
    return m_create_ticker_7_to_10;
}

dev::bigint minter::tx_vote_commission::get_fee_create_coin() const {
    return m_create_coin;
}

dev::bigint minter::tx_vote_commission::get_fee_create_token() const {
    return m_create_token;
}

dev::bigint minter::tx_vote_commission::get_fee_recreate_coin() const {
    return m_recreate_coin;
}

dev::bigint minter::tx_vote_commission::get_fee_recreate_token() const {
    return m_recreate_token;
}

dev::bigint minter::tx_vote_commission::get_fee_declare_candidacy() const {
    return m_declare_candidacy;
}

dev::bigint minter::tx_vote_commission::get_fee_delegate() const {
    return m_delegate;
}

dev::bigint minter::tx_vote_commission::get_fee_unbond() const {
    return m_unbond;
}

dev::bigint minter::tx_vote_commission::get_fee_redeem_check() const {
    return m_redeem_check;
}

dev::bigint minter::tx_vote_commission::get_fee_set_candidate_on() const {
    return m_set_candidate_on;
}

dev::bigint minter::tx_vote_commission::get_fee_set_candidate_off() const {
    return m_set_candidate_off;
}

dev::bigint minter::tx_vote_commission::get_fee_create_multisig() const {
    return m_create_multisig;
}

dev::bigint minter::tx_vote_commission::get_fee_multisend_base() const {
    return m_multisend_base;
}

dev::bigint minter::tx_vote_commission::get_fee_multisend_delta() const {
    return m_multisend_delta;
}

dev::bigint minter::tx_vote_commission::get_fee_edit_candidate() const {
    return m_edit_candidate;
}

dev::bigint minter::tx_vote_commission::get_fee_set_halt_block() const {
    return m_set_halt_block;
}

dev::bigint minter::tx_vote_commission::get_fee_edit_ticker_owner() const {
    return m_edit_ticker_owner;
}

dev::bigint minter::tx_vote_commission::get_fee_edit_multisig() const {
    return m_edit_multisig;
}

dev::bigint minter::tx_vote_commission::get_fee_edit_candidate_pub_key() const {
    return m_edit_candidate_pub_key;
}

dev::bigint minter::tx_vote_commission::get_fee_create_swap_pool() const {
    return m_create_swap_pool;
}

dev::bigint minter::tx_vote_commission::get_fee_add_liquidity() const {
    return m_add_liquidity;
}

dev::bigint minter::tx_vote_commission::get_fee_remove_liquidity() const {
    return m_remove_liquidity;
}

dev::bigint minter::tx_vote_commission::get_fee_edit_candidate_commission() const {
    return m_edit_candidate_commission;
}

dev::bigint minter::tx_vote_commission::get_fee_mint_token() const {
    return m_mint_token;
}

dev::bigint minter::tx_vote_commission::get_fee_burn_token() const {
    return m_burn_token;
}

dev::bigint minter::tx_vote_commission::get_fee_vote_commission() const {
    return m_vote_commission;
}

dev::bigint minter::tx_vote_commission::get_fee_vote_update() const {
    return m_vote_update;
}
