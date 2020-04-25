/*!
 * minter_tx.
 * tx_deeplink.h
 *
 * \date 03/12/2020
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#ifndef MINTER_TX_TX_DEEPLINK_H
#define MINTER_TX_TX_DEEPLINK_H

#include <memory>
#include <minter/minter_tx_config.h>
#include <minter/tx/tx_fwd.h>

namespace minter {

class tx_deeplink {
public:
    static std::shared_ptr<minter::tx_deeplink> decode(const char* encoded_hex);
    static std::shared_ptr<minter::tx_deeplink> decode(const dev::bytes& tx);
    static std::shared_ptr<minter::tx_deeplink> decode(const dev::bytes_data& tx);

    tx_deeplink(std::shared_ptr<minter::tx>&& tx);
    virtual ~tx_deeplink() = default;
    dev::bytes_data encode() const;
    const std::shared_ptr<minter::tx>& get_tx() const;
    std::string to_url(const std::string& base_domain = "https://bip.to", const std::string& check_pass = "") const;

private:
    std::shared_ptr<minter::tx> m_tx;
};

} // namespace minter

#endif //MINTER_TX_TX_DEEPLINK_H
