/*!
 * minter_tx.
 * tx_builder.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_BUILDER_H
#define MINTER_TX_BUILDER_H

#include "minter/tx/tx.h"
#include "minter/tx/tx_fwd.h"

#include <memory>
#include <string>

namespace minter {

class MINTER_TX_API tx_builder {
public:
    tx_builder(std::shared_ptr<minter::tx> tx)
        : m_tx(std::move(tx)) {
    }
    ~tx_builder() = default;

    /// Base transaction data

    tx_builder& set_nonce(const std::string& nonce_num);
    tx_builder& set_nonce(const dev::bigint& num);

    /// \brief Network identifier. Declared in autogenerated header minter/minter_tx_config.h
    /// \see minter::testnet - for testnet
    /// \see minter::mainnet - for mainnet
    /// \param id
    /// \return
    tx_builder& set_chain_id(uint8_t id);

    tx_builder& set_gas_price(const std::string& amount_human);
    tx_builder& set_gas_price(const dev::bigdec18& amount_human);
    tx_builder& set_gas_price(const dev::bigint& amount);

    tx_builder& set_gas_coin_id(const dev::bigint& coin_id);
    tx_builder& set_gas_coin_id(const std::string& coin_id_num);

    tx_builder& set_payload(const std::string& payload);
    tx_builder& set_payload(std::string&& payload);
    tx_builder& set_payload(const dev::bytes& payload);
    tx_builder& set_payload(dev::bytes&& payload);

    tx_builder& set_service_data(const std::string& payload);
    tx_builder& set_service_data(std::string&& payload);
    tx_builder& set_service_data(const dev::bytes& payload);
    tx_builder& set_service_data(dev::bytes&& payload);

    /// \brief Type of signature.
    /// \param type can be single or multi. Can be casted to uint8_t
    /// \see minter::signature_type::single
    /// \see minter::signature_type::multi
    /// \return
    tx_builder& set_signature_type(minter::signature_type type);

    /// Typed transaction data
    std::shared_ptr<minter::tx_send_coin> tx_send_coin();
    std::shared_ptr<minter::tx_sell_coin> tx_sell_coin();
    std::shared_ptr<minter::tx_sell_all_coins> tx_sell_all_coins();
    std::shared_ptr<minter::tx_buy_coin> tx_buy_coin();
    std::shared_ptr<minter::tx_create_coin> tx_create_coin();
    std::shared_ptr<minter::tx_recreate_coin> tx_recreate_coin();
    std::shared_ptr<minter::tx_declare_candidacy> tx_declare_candidacy();
    std::shared_ptr<minter::tx_delegate> tx_delegate();
    std::shared_ptr<minter::tx_unbond> tx_unbond();
    std::shared_ptr<minter::tx_redeem_check> tx_redeem_check();
    std::shared_ptr<minter::tx_set_candidate_on> tx_set_candidate_on();
    std::shared_ptr<minter::tx_set_candidate_off> tx_set_candidate_off();
    std::shared_ptr<minter::tx_create_multisig_address> tx_create_multisig_address();
    std::shared_ptr<minter::tx_multisend> tx_multisend();
    std::shared_ptr<minter::tx_edit_candidate> tx_edit_candidate();
    std::shared_ptr<minter::tx_set_halt_block> tx_set_halt_block();
    std::shared_ptr<minter::tx_edit_coin_owner> tx_edit_coin_owner();
    std::shared_ptr<minter::tx_edit_multisig> tx_edit_multisig();
    std::shared_ptr<minter::tx_price_vote> tx_price_vote();
    std::shared_ptr<minter::tx_edit_candidate_public_key> tx_edit_candidate_public_key();
    /// \since minter 2.0
    std::shared_ptr<minter::tx_add_liquidity> tx_add_liquidity();
    std::shared_ptr<minter::tx_remove_liquidity> tx_remove_liquidity();
    std::shared_ptr<minter::tx_sell_swap_pool> tx_sell_swap_pool();
    std::shared_ptr<minter::tx_sell_all_swap_pool> tx_sell_all_swap_pool();
    std::shared_ptr<minter::tx_buy_swap_pool> tx_buy_swap_pool();
    std::shared_ptr<minter::tx_create_swap_pool> tx_create_swap_pool();
    std::shared_ptr<minter::tx_mint_token> tx_mint_token();
    std::shared_ptr<minter::tx_burn_token> tx_burn_token();
    std::shared_ptr<minter::tx_create_token> tx_create_token();
    std::shared_ptr<minter::tx_recreate_token> tx_recreate_token();
    std::shared_ptr<minter::tx_edit_candidate_commission> tx_edit_candidate_commission();
    std::shared_ptr<minter::tx_vote_update> tx_vote_update();
    std::shared_ptr<minter::tx_vote_commission> tx_vote_commission();

private:
    std::shared_ptr<minter::tx> m_tx;
};

MINTER_TX_API std::shared_ptr<minter::tx_builder> new_tx();

} // namespace minter

#endif //MINTER_TX_BUILDER_H
