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

#include <memory>
#include <string>
#include <minter/eth/Common.h>
#include "minter/tx/tx_fwd.h"
#include "minter/tx/tx.h"

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

namespace minter {

class MINTER_TX_API tx_builder {
public:
    tx_builder(std::shared_ptr<minter::tx> tx) : m_tx(std::move(tx)) { }
    ~tx_builder() = default;
    tx_builder &set_nonce(const dev::bigint &num);
    tx_builder &set_nonce(const char *num);
    tx_builder &set_chain_id(uint8_t id);
    tx_builder &set_gas_price(const std::string &amountNormalized);
    tx_builder &set_gas_price(const dev::bigdec18 &amountNormalized);
    tx_builder &set_gas_price(const dev::bigint &amount);
    tx_builder &set_gas_coin(const std::string &coin);
    tx_builder &set_gas_coin(const char *coin);
    tx_builder &set_payload(const dev::bytes &payload);
    tx_builder &set_payload(dev::bytes &&payload);
    tx_builder &set_payload(const std::string &payload);
    tx_builder &set_payload(std::string &&payload);
    tx_builder &set_payload(const char *payload);
    tx_builder &set_service_data(const dev::bytes &payload);
    tx_builder &set_service_data(dev::bytes &&payload);
    tx_builder &set_service_data(const std::string &payload);
    tx_builder &set_service_data(std::string &&payload);
    tx_builder &set_service_data(const char *payload);
    tx_builder &set_signature_type(uint8_t type);

    std::shared_ptr<minter::tx_send_coin> tx_send_coin();
    std::shared_ptr<minter::tx_sell_coin> tx_sell_coin();
    std::shared_ptr<minter::tx_sell_all_coins> tx_sell_all_coins();
    std::shared_ptr<minter::tx_buy_coin> tx_buy_coin();
    std::shared_ptr<minter::tx_create_coin> tx_create_coin();
    std::shared_ptr<minter::tx_declare_candidacy> tx_declare_candidacy();
    std::shared_ptr<minter::tx_delegate> tx_delegate();
    std::shared_ptr<minter::tx_unbond> tx_unbond();
    std::shared_ptr<minter::tx_redeem_check> tx_redeem_check();
    std::shared_ptr<minter::tx_set_candidate_on> tx_set_candidate_on();
    std::shared_ptr<minter::tx_set_candidate_off> tx_set_candidate_off();
    std::shared_ptr<minter::tx_create_multisig_address> tx_create_multisig_address();
    std::shared_ptr<minter::tx_multisend> tx_multisend();
    std::shared_ptr<minter::tx_edit_candidate> tx_edit_candidate();

private:
    std::shared_ptr<minter::tx> m_tx;
};


MINTER_TX_API std::shared_ptr<minter::tx_builder> new_tx();

}

#endif //MINTER_TX_BUILDER_H
