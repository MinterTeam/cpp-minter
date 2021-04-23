/*!
 * minter_tx.
 * tx_fwd.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_FWD_H
#define MINTER_TX_FWD_H

namespace minter {

class tx_deeplink;
class tx_data;
class tx_send_coin;
class tx_sell_coin;
class tx_sell_all_coins;
class tx_buy_coin;
class tx_create_coin;
class tx_declare_candidacy;
class tx_delegate;
class tx_unbond;
class tx_redeem_check;
class tx_set_candidate_on;
class tx_set_candidate_off;
class tx_create_multisig_address;
class tx_multisend;
class tx_edit_candidate;

/// \since minter 1.2
class tx_set_halt_block;
class tx_recreate_coin;
class tx_edit_coin_owner;
class tx_edit_multisig;
class tx_price_vote;
class tx_edit_candidate_public_key;

/// \since minter 2.0
class tx_add_liquidity;
class tx_remove_liquidity;
class tx_sell_swap_pool;
class tx_buy_swap_pool;
class tx_sell_all_swap_pool;
class tx_edit_candidate_commission;
class tx_move_stake;
class tx_mint_token;
class tx_burn_token;
class tx_create_token;
class tx_recreate_token;
class tx_vote_commission;
class tx_vote_update;
class tx_create_swap_pool;

} // namespace minter

#endif //MINTER_TX_FWD_H
