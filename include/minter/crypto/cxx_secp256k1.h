/*!
 * minter_tx.
 * secp256k1_raii.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_SECP256K1_RAII_H
#define MINTER_SECP256K1_RAII_H

#include "minter/minter_tx_config.h"
#include "minter/tx/signature.h"
#include "minter/tx/utils.h"

#include <algorithm>
#include <memory>
#include <secp256k1.h>
#include <secp256k1_ecdh.h>
#include <secp256k1_recovery.h>

namespace minter {

class MINTER_TX_API cxx_secp256k1 {
public:
    struct secp256k1_deleter {
        void operator()(secp256k1_context* ctx) {
            secp256k1_context_destroy(ctx);
        }
    };
    using ptr_t = std::unique_ptr<secp256k1_context, secp256k1_deleter>;

    explicit cxx_secp256k1(uint32_t flags = SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY) {
        auto* ctx = secp256k1_context_create(flags);
        m_ctx = ptr_t(ctx);
    }

    signature sign_message(const dev::bytes_data& message, const dev::bytes_data& key) const {
        secp256k1_ecdsa_recoverable_signature sig;

        int ret = secp256k1_ecdsa_sign_recoverable(get(), &sig, message.data(), key.data(), NULL, NULL);

        dev::bytes_data tmp_sign(65);
        minter::signature out;
        out.success = false;

        int recoveryId = 0;

        if (ret) {
            secp256k1_ecdsa_recoverable_signature_serialize_compact(
                get(),
                tmp_sign.data(),
                &recoveryId,
                &sig);

            tmp_sign.at(64) = ((uint8_t) recoveryId) + (uint8_t) 27;
        } else {
            return out;
        }

        out.r = tmp_sign.take_range(0, 32);
        out.s = tmp_sign.take_range(32, 64);
        out.v = tmp_sign.take_last(1);

        tmp_sign.clear();

        out.success = true;

        return out;
    }

    virtual ~cxx_secp256k1() = default;

    const secp256k1_context* get() const {
        return m_ctx.get();
    }

private:
    ptr_t m_ctx;
};

} // namespace minter

#endif // MINTER_SECP256K1_RAII_H
