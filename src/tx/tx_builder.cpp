/*!
 * minter_tx.
 * tx_builder.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_builder.h"

#include "minter/tx/tx_buy_coin.h"
#include "minter/tx/tx_create_coin.h"
#include "minter/tx/tx_create_multisig_address.h"
#include "minter/tx/tx_declare_candidacy.h"
#include "minter/tx/tx_delegate.h"
#include "minter/tx/tx_edit_candidate.h"
#include "minter/tx/tx_edit_candidate_public_key.h"
#include "minter/tx/tx_edit_coin_owner.h"
#include "minter/tx/tx_edit_multisig.h"
#include "minter/tx/tx_multisend.h"
#include "minter/tx/tx_price_vote.h"
#include "minter/tx/tx_recreate_coin.h"
#include "minter/tx/tx_redeem_check.h"
#include "minter/tx/tx_sell_all_coins.h"
#include "minter/tx/tx_sell_coin.h"
#include "minter/tx/tx_send_coin.h"
#include "minter/tx/tx_set_candidate_on_off.h"
#include "minter/tx/tx_set_halt_block.h"
#include "minter/tx/tx_unbond.h"
#include "minter/tx/utils.h"

#include <memory>

// Out of line
std::shared_ptr<minter::tx_builder> minter::new_tx() {
    auto out = std::make_shared<minter::tx_builder>(std::make_shared<minter::tx>());
    return out;
}

// setters
minter::tx_builder& minter::tx_builder::set_nonce(const dev::bigint& nonce) {
    m_tx->m_nonce = nonce;
    return *this;
}

minter::tx_builder& minter::tx_builder::set_nonce(const std::string& num) {
    return set_nonce(dev::bigint(num));
}

minter::tx_builder& minter::tx_builder::set_chain_id(uint8_t id) {
    m_tx->m_chain_id = id;
    return *this;
}

minter::tx_builder& minter::tx_builder::set_gas_price(const std::string& amount_human) {
    m_tx->m_gas_price = dev::bigint(amount_human);
    return *this;
}

minter::tx_builder& minter::tx_builder::set_gas_price(const dev::bigdec18& amount) {
    m_tx->m_gas_price = amount.to_bigint();
    return *this;
}

minter::tx_builder& minter::tx_builder::set_gas_price(const dev::bigint& amount) {
    m_tx->m_gas_price = amount;
    return *this;
}

minter::tx_builder& minter::tx_builder::set_gas_coin_id(const dev::bigint& coin_id) {
    m_tx->m_gas_coin_id = coin_id;
    return *this;
}

minter::tx_builder& minter::tx_builder::set_gas_coin_id(const std::string& coin_id_num) {
    m_tx->m_gas_coin_id = dev::bigint(coin_id_num);
    return *this;
}

minter::tx_builder& minter::tx_builder::set_payload(const dev::bytes& payload) {
    std::copy(payload.begin(), payload.end(), m_tx->m_payload.begin());
    return *this;
}

minter::tx_builder& minter::tx_builder::set_payload(dev::bytes&& payload) {
    m_tx->m_payload = std::move(payload);
    return *this;
}

minter::tx_builder& minter::tx_builder::set_payload(const std::string& payload) {
    m_tx->m_payload = minter::utils::to_bytes(payload);
    return *this;
}

minter::tx_builder& minter::tx_builder::set_payload(std::string&& payload) {
    m_tx->m_payload = minter::utils::to_bytes(std::move(payload));
    return *this;
}

minter::tx_builder& minter::tx_builder::set_service_data(const dev::bytes& payload) {
    std::copy(payload.begin(), payload.end(), m_tx->m_service_data.begin());
    return *this;
}

minter::tx_builder& minter::tx_builder::set_service_data(dev::bytes&& payload) {
    m_tx->m_service_data = std::move(payload);
    return *this;
}

minter::tx_builder& minter::tx_builder::set_service_data(const std::string& payload) {
    m_tx->m_service_data = minter::utils::to_bytes(payload);
    return *this;
}

minter::tx_builder& minter::tx_builder::set_service_data(std::string&& payload) {
    m_tx->m_service_data = minter::utils::to_bytes(std::move(payload));
    return *this;
}

minter::tx_builder& minter::tx_builder::set_signature_type(minter::signature_type type) {
    m_tx->m_signature_type = type;
    return *this;
}

// Detailed data builders
std::shared_ptr<minter::tx_send_coin> minter::tx_builder::tx_send_coin() {
    return std::make_shared<minter::tx_send_coin>(m_tx);
}

std::shared_ptr<minter::tx_sell_coin> minter::tx_builder::tx_sell_coin() {
    return std::make_shared<minter::tx_sell_coin>(m_tx);
}

std::shared_ptr<minter::tx_sell_all_coins> minter::tx_builder::tx_sell_all_coins() {
    return std::make_shared<minter::tx_sell_all_coins>(m_tx);
}

std::shared_ptr<minter::tx_buy_coin> minter::tx_builder::tx_buy_coin() {
    return std::make_shared<minter::tx_buy_coin>(m_tx);
}

std::shared_ptr<minter::tx_create_coin> minter::tx_builder::tx_create_coin() {
    return std::make_shared<minter::tx_create_coin>(m_tx);
}

std::shared_ptr<minter::tx_recreate_coin> minter::tx_builder::tx_recreate_coin() {
    return std::make_shared<minter::tx_recreate_coin>(m_tx);
}

std::shared_ptr<minter::tx_declare_candidacy> minter::tx_builder::tx_declare_candidacy() {
    return std::make_shared<minter::tx_declare_candidacy>(m_tx);
}

std::shared_ptr<minter::tx_delegate> minter::tx_builder::tx_delegate() {
    return std::make_shared<minter::tx_delegate>(m_tx);
}

std::shared_ptr<minter::tx_unbond> minter::tx_builder::tx_unbond() {
    return std::make_shared<minter::tx_unbond>(m_tx);
}

std::shared_ptr<minter::tx_redeem_check> minter::tx_builder::tx_redeem_check() {
    return std::make_shared<minter::tx_redeem_check>(m_tx);
}

std::shared_ptr<minter::tx_set_candidate_on> minter::tx_builder::tx_set_candidate_on() {
    return std::make_shared<minter::tx_set_candidate_on>(m_tx);
}

std::shared_ptr<minter::tx_set_candidate_off> minter::tx_builder::tx_set_candidate_off() {
    return std::make_shared<minter::tx_set_candidate_off>(m_tx);
}

std::shared_ptr<minter::tx_create_multisig_address> minter::tx_builder::tx_create_multisig_address() {
    return std::make_shared<minter::tx_create_multisig_address>(m_tx);
}

std::shared_ptr<minter::tx_multisend> minter::tx_builder::tx_multisend() {
    return std::make_shared<minter::tx_multisend>(m_tx);
}

std::shared_ptr<minter::tx_edit_candidate> minter::tx_builder::tx_edit_candidate() {
    return std::make_shared<minter::tx_edit_candidate>(m_tx);
}

std::shared_ptr<minter::tx_set_halt_block> minter::tx_builder::tx_set_halt_block() {
    return std::make_shared<minter::tx_set_halt_block>(m_tx);
}

std::shared_ptr<minter::tx_edit_coin_owner> minter::tx_builder::tx_edit_coin_owner() {
    return std::make_shared<minter::tx_edit_coin_owner>(m_tx);
}

std::shared_ptr<minter::tx_edit_multisig> minter::tx_builder::tx_edit_multisig() {
    return std::make_shared<minter::tx_edit_multisig>(m_tx);
}

std::shared_ptr<minter::tx_price_vote> minter::tx_builder::tx_price_vote() {
    return std::make_shared<minter::tx_price_vote>(m_tx);
}

std::shared_ptr<minter::tx_edit_candidate_public_key> minter::tx_builder::tx_edit_candidate_public_key() {
    return std::make_shared<minter::tx_edit_candidate_public_key>(m_tx);
}
