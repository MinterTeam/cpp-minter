/*!
 * minter_tx.
 * tx_type.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_type.h"

#include "minter/tx/tx_add_liquidity.h"
#include "minter/tx/tx_burn_token.h"
#include "minter/tx/tx_buy_coin.h"
#include "minter/tx/tx_buy_swap_pool.h"
#include "minter/tx/tx_create_coin.h"
#include "minter/tx/tx_create_multisig_address.h"
#include "minter/tx/tx_create_swap_pool.h"
#include "minter/tx/tx_create_token.h"
#include "minter/tx/tx_data.h"
#include "minter/tx/tx_declare_candidacy.h"
#include "minter/tx/tx_delegate.h"
#include "minter/tx/tx_edit_candidate.h"
#include "minter/tx/tx_edit_candidate_commission.h"
#include "minter/tx/tx_mint_token.h"
#include "minter/tx/tx_multisend.h"
#include "minter/tx/tx_recreate_token.h"
#include "minter/tx/tx_redeem_check.h"
#include "minter/tx/tx_remove_liquidity.h"
#include "minter/tx/tx_sell_all_coins.h"
#include "minter/tx/tx_sell_all_swap_pool.h"
#include "minter/tx/tx_sell_coin.h"
#include "minter/tx/tx_sell_swap_pool.h"
#include "minter/tx/tx_send_coin.h"
#include "minter/tx/tx_set_candidate_on_off.h"
#include "minter/tx/tx_unbond.h"
#include "minter/tx/tx_vote_commission.h"
#include "minter/tx/tx_vote_update.h"

const std::unordered_map<minter::tx_type_val, std::string> minter::tx_type_names = {
    {minter::tx_type_val::send_coin, "send"},
    {minter::tx_type_val::sell_coin, "sell"},
    {minter::tx_type_val::sell_all_coins, "sell all"},
    {minter::tx_type_val::buy_coin, "buy"},
    {minter::tx_type_val::create_coin, "create coin_id"},
    {minter::tx_type_val::declare_candidacy, "declare candidacy"},
    {minter::tx_type_val::delegate, "delegate"},
    {minter::tx_type_val::unbond, "unbond"},
    {minter::tx_type_val::redeem_check, "redeem check"},
    {minter::tx_type_val::set_candidate_on, "set candidate on"},
    {minter::tx_type_val::set_candidate_off, "set candidate off"},
    {minter::tx_type_val::create_multisig, "create multisig address"},
    {minter::tx_type_val::multisend, "multisend"},
    {minter::tx_type_val::edit_candidate, "edit candidate"},
    {minter::tx_type_val::add_liquidity, "add liquidity"},
    {minter::tx_type_val::remove_liquidity, "remove liquidity"},
    {minter::tx_type_val::sell_swap_pool, "sell swap pool"},
    {minter::tx_type_val::buy_swap_pool, "buy swap pool"},
    {minter::tx_type_val::sell_all_swap_pool, "sell all swap pool"},
    {minter::tx_type_val::create_swap_pool, "create swap pool"},
    {minter::tx_type_val::burn_token, "burn token"},
    {minter::tx_type_val::mint_token, "mint token"},
    {minter::tx_type_val::create_token, "create token"},
    {minter::tx_type_val::recreate_token, "recreate token"},
    {minter::tx_type_val::edit_candidate_commission, "edit candidate commission"},
    {minter::tx_type_val::vote_commission, "vote commission"},
    {minter::tx_type_val::vote_update, "vote update"},
};
