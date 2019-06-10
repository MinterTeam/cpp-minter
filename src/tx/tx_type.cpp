/*!
 * minter_tx.
 * tx_type.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/tx/tx_type.h"
#include "minter/tx/tx_send_coin.h"
#include "minter/tx/tx_sell_coin.h"
#include "minter/tx/tx_sell_all_coins.h"
#include "minter/tx/tx_buy_coin.h"
#include "minter/tx/tx_create_coin.h"
#include "minter/tx/tx_declare_candidacy.h"
#include "minter/tx/tx_delegate.h"
#include "minter/tx/tx_unbond.h"
#include "minter/tx/tx_redeem_check.h"
#include "minter/tx/tx_set_candidate_on_off.h"
#include "minter/tx/tx_create_multisig_address.h"
#include "minter/tx/tx_multisend.h"
#include "minter/tx/tx_edit_candidate.h"

const std::unordered_map<minter::tx_type_val, std::string> minter::tx_type_names = {
    {minter::tx_type_val::send_coin,         "send"},
    {minter::tx_type_val::sell_coin,         "sell"},
    {minter::tx_type_val::sell_all_coins,    "sell all"},
    {minter::tx_type_val::buy_coin,          "buy"},
    {minter::tx_type_val::create_coin,       "create coin"},
    {minter::tx_type_val::declare_candidacy, "declare candidacy"},
    {minter::tx_type_val::delegate,          "delegate"},
    {minter::tx_type_val::unbond,            "unbond"},
    {minter::tx_type_val::redeem_check,      "redeem check"},
    {minter::tx_type_val::set_candidate_on,  "set candidate on"},
    {minter::tx_type_val::set_candidate_off, "set candidate off"},
    {minter::tx_type_val::create_multisig,   "create multisig address"},
    {minter::tx_type_val::multisend,         "multisend"},
    {minter::tx_type_val::edit_candidate,    "edit candidate"},
};


define_tx_type_funcs(tx_send_coin, tx_type_val::send_coin, 10u)
define_tx_type_funcs(tx_sell_coin, tx_type_val::sell_coin, 100)
define_tx_type_funcs(tx_sell_all_coins, tx_type_val::sell_all_coins, 100)
define_tx_type_funcs(tx_buy_coin, tx_type_val::buy_coin, 100)
define_tx_type_funcs(tx_create_coin, tx_type_val::create_coin, 1000)
define_tx_type_funcs(tx_declare_candidacy, tx_type_val::declare_candidacy, 10000)
define_tx_type_funcs(tx_delegate, tx_type_val::delegate, 200)
define_tx_type_funcs(tx_unbond, tx_type_val::unbond, 200)
define_tx_type_funcs(tx_redeem_check, tx_type_val::redeem_check, 30)
define_tx_type_funcs(tx_set_candidate_on, tx_type_val::set_candidate_on, 100)
define_tx_type_funcs(tx_set_candidate_off, tx_type_val::set_candidate_off, 100)
define_tx_type_funcs(tx_create_multisig_address, tx_type_val::create_multisig, 100)
define_tx_type_funcs(tx_multisend, tx_type_val::multisend, 100)
define_tx_type_funcs(tx_edit_candidate, tx_type_val::edit_candidate, 10000)