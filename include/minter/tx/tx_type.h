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

#include "minter/tx/tx.h"
#include "minter/tx/tx_fwd.h"

#include <cstdint>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace minter {

constexpr const static double FEE_BASE = 0.001;

enum tx_type_val : uint8_t {
    send_coin = 0x01,
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

MINTER_TX_API extern const std::unordered_map<tx_type_val, std::string> tx_type_names;

template<typename T>
class tx_type {
public:
    using ref_type = T;

    constexpr tx_type(double tx_fee, tx_type_val type)
        : m_tx_fee(tx_fee),
          m_type(type) {
    }

    std::shared_ptr<T> create(std::shared_ptr<tx> ptr, const std::vector<uint8_t>& encodedData) const {
        std::shared_ptr<T> data = std::make_shared<T>(ptr);
        data->decode(encodedData);
        return data;
    }

    dev::bigdec18 get_fee() const {
        return dev::bigdec18(m_tx_fee) * dev::bigdec18(FEE_BASE);
    }

    dev::bigdec18 get_fee(const dev::bigint& gas) const {
        return dev::bigdec18(gas) * get_fee();
    }
    constexpr tx_type_val type() const {
        return m_type;
    }

private:
    double m_tx_fee;
    tx_type_val m_type;
};

constexpr const static auto tx_send_coin_type = tx_type<tx_send_coin>(10.0, tx_type_val::send_coin);
constexpr const static auto tx_sell_coin_type = tx_type<tx_sell_coin>(100.0, tx_type_val::sell_coin);
constexpr const static auto tx_sell_all_coins_type = tx_type<tx_sell_all_coins>(100.0, tx_type_val::sell_all_coins);
constexpr const static auto tx_buy_coin_type = tx_type<tx_buy_coin>(100.0, tx_type_val::buy_coin);
constexpr const static auto tx_create_coin_type = tx_type<tx_create_coin>(1000.0, tx_type_val::create_coin);
constexpr const static auto tx_declare_candidacy_type = tx_type<tx_declare_candidacy>(10000.0, tx_type_val::declare_candidacy);
constexpr const static auto tx_delegate_type = tx_type<tx_delegate>(200.0, tx_type_val::delegate);
constexpr const static auto tx_unbond_type = tx_type<tx_unbond>(200.0, tx_type_val::unbond);
constexpr const static auto tx_redeem_check_type = tx_type<tx_redeem_check>(30.0, tx_type_val::redeem_check);
constexpr const static auto tx_set_candidate_on_type = tx_type<tx_set_candidate_on>(100.0, tx_type_val::set_candidate_on);
constexpr const static auto tx_set_candidate_off_type = tx_type<tx_set_candidate_off>(100.0, tx_type_val::set_candidate_off);
constexpr const static auto tx_create_multisig_address_type = tx_type<tx_create_multisig_address>(100.0, tx_type_val::create_multisig);
constexpr const static auto tx_multisend_type = tx_type<tx_multisend>(10.0, tx_type_val::multisend);
constexpr const static auto tx_edit_candidate_type = tx_type<tx_edit_candidate>(10000.0, tx_type_val::edit_candidate);

} // namespace minter

namespace std {
template<>
struct hash<minter::tx_type_val> {
    std::size_t operator()(const minter::tx_type_val& k) const {
        return std::hash<uint8_t>()(k);
    }
};
} // namespace std

#endif //MINTER_TX_TYPE_H
