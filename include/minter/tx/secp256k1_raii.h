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

#include <memory>
#include <secp256k1/include/secp256k1.h>
#include <secp256k1/include/secp256k1_ecdh.h>
#include <secp256k1/include/secp256k1_recovery.h>

namespace minter {

class secp256k1_raii {
public:
    struct secp256k1_deleter {
      void operator()(secp256k1_context *ctx) {
          secp256k1_context_destroy(ctx);
      }
    };
    using ptr_t = std::unique_ptr<secp256k1_context, secp256k1_deleter>;

    secp256k1_raii(uint32_t flags = SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY) {
        auto *ctx = secp256k1_context_create(flags);
        m_ctx = ptr_t(ctx);
    }

    virtual ~secp256k1_raii() = default;

    const secp256k1_context * get() const {
        return m_ctx.get();
    }
private:
    ptr_t m_ctx;
};

}

#endif //MINTER_SECP256K1_RAII_H
