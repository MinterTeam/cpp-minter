/*!
 * minter_tx.
 * tx_type.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_TYPE_H
#define MINTER_TX_TYPE_H

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <minter/eth/Common.h>
#include <vector>
#include "minter/tx/tx_fwd.h"
#include "minter/tx/tx.h"

namespace minter {

static constexpr double FEE_BASE = 0.001;

enum tx_type_val {
  send_coin = (uint8_t) 0x01,
  sell_coin,
  sell_all_coins,
  buy_coin,
  create_coin,
  declare_candidacy,
  delegate,
  unbond,
  redeem_check,
  set_candidate_on,
  set_candidate_off,
  create_multisig,
  multisend,
  edit_candidate
};

extern const std::unordered_map<tx_type_val, std::string> tx_type_names;

template<class ref_type>
struct tx_type;

#define create_tx_type(_T) \
template<> struct tx_type<minter::_T> { \
  typedef minter::_T ref_type; \
\
  static const uint16_t type(); \
  static dev::bigdec18 get_fee(); \
  static dev::bigdec18 get_fee(const dev::bigint &gas); \
  static std::shared_ptr<minter::_T> create(std::shared_ptr<minter::tx> ptr, const std::vector<uint8_t>& encodedData); \
}; \
using _T##_type = tx_type<minter::_T>

#define define_tx_type_funcs(_T, type_byte, fee) \
    std::shared_ptr<minter::_T> minter::tx_type<minter::_T>::create(std::shared_ptr<minter::tx> ptr, const std::vector<uint8_t> &encodedData) { \
        auto data = std::make_shared<minter::_T>(ptr); \
        data->decode(encodedData); \
        return data; \
    } \
    dev::bigdec18 minter::tx_type<minter::_T>::get_fee() { \
        return dev::bigdec18(#fee) * dev::bigdec18(minter::FEE_BASE); \
    } \
    dev::bigdec18 minter::tx_type<minter::_T>::get_fee(const dev::bigint &gas) { \
        return dev::bigdec18(gas) * get_fee(); \
    } \
    const uint16_t minter::tx_type<minter::_T>::type() { \
        return static_cast<uint16_t>(type_byte); \
    }

create_tx_type(tx_send_coin);
create_tx_type(tx_sell_coin);
create_tx_type(tx_sell_all_coins);
create_tx_type(tx_buy_coin);
create_tx_type(tx_create_coin);
create_tx_type(tx_declare_candidacy);
create_tx_type(tx_delegate);
create_tx_type(tx_unbond);
create_tx_type(tx_redeem_check);
create_tx_type(tx_set_candidate_on);
create_tx_type(tx_set_candidate_off);
create_tx_type(tx_create_multisig_address);
create_tx_type(tx_multisend);
create_tx_type(tx_edit_candidate);

}

#endif //MINTER_TX_TYPE_H
