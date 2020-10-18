/*!
 * minter_tx.
 * utils.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */
#include <algorithm>
#include <bip3x/PCGRand.hpp>
#include <bip3x/crypto/sha2.hpp>
#include <bip3x/crypto/sha3.h>
#include <minter/tx/utils.h>
#include <random>
#include <sstream>
#include <toolbox/data/base64.h>
#include <toolbox/strings.hpp>
#include <toolbox/strings/decimal_formatter.h>
#include <vector>

dev::bytes minter::utils::to_bytes(std::string&& input) {
    if (!input.size()) {
        return dev::bytes(0);
    }

    dev::bytes output;
    output.resize(input.size());
    std::move(input.begin(), input.end(), output.begin());

    return output;
}
dev::bytes minter::utils::to_bytes(const std::string& input) {
    if (!input.size()) {
        return dev::bytes(0);
    }

    dev::bytes output;
    output.resize(input.length());
    for (std::string::size_type i = 0; i < input.size(); i++) {
        output[i] = (uint8_t) input[i];
    }

    return output;
}

dev::bytes minter::utils::to_bytes_fixed(const std::string& input, size_t fixed_size) {
    dev::bytes output;
    output.resize(fixed_size);
    size_t left = fixed_size;
    size_t fill_from = 0;
    for (std::string::size_type i = 0; i < input.size() && i < fixed_size; i++, left--, fill_from++) {
        output[i] = (uint8_t) input[i];
    }

    for (auto i = fill_from; i < fixed_size; i++) {
        output[i] = (uint8_t) 0x00;
    }

    return output;
}

dev::bytes minter::utils::to_bytes(const dev::bigint& num) {
    return num.export_bytes();
}

dev::bytes minter::utils::to_bytes(const dev::bigdec18& num) {
    auto out = num * dev::bigdec18("1000000000000000000");
    return out.to_bigint().export_bytes();
}

dev::bytes minter::utils::sha3k(const dev::bytes_data& message) {
    return sha3k(message.get());
}

dev::bytes minter::utils::sha3k(const dev::bytes& message) {
    SHA3_CTX hash_ctx;
    dev::bytes output(32);
    keccak_256_Init(&hash_ctx);
    keccak_Update(&hash_ctx, message.data(), message.size());
    keccak_Final(&hash_ctx, output.data());

    return output;
}

dev::bytes minter::utils::to_sha3k(dev::bytes message) {
    return sha3k(message);
}

dev::bytes minter::utils::sha256(const dev::bytes& message) {
    trezor::SHA256_CTX hash_ctx;
    dev::bytes output(SHA256_DIGEST_LENGTH);
    sha256_Init(&hash_ctx);
    sha256_Update(&hash_ctx, message.data(), message.size());
    sha256_Final(&hash_ctx, output.data());

    return output;
}

dev::bytes minter::utils::sha256(const dev::bytes_data& message) {
    return sha256(message.get());
}

dev::bytes minter::utils::to_sha256(const dev::bytes message) {
    return sha256(message);
}

dev::bytes minter::utils::from_base64_web(dev::bytes data) {
    dev::bytes out;
    for (size_t i = 0; i < data.size(); i++) {
        switch (data[i]) {
        case '-':
            out.push_back('+');
            break;
        case '_':
            out.push_back('/');
            break;
        default:
            out.push_back(data[i]);
        }
    }
    if (out.size() % 4 != 0) {
        const char padding = '=';
        size_t sz = out.size();
        size_t its = (4 - sz % 4);

        for (size_t i = 0; i < its; i++) {
            out.push_back(padding);
        }
    }

    //if (enc.length() % 4 != 0) {
    //            enc += strRepeat(PADDING, 4 - enc.length() % 4);
    //        }

    return toolbox::data::base64_decode_bytes(out);
}

dev::bytes minter::utils::to_base64_web(dev::bytes data) {
    dev::bytes b64 = toolbox::data::base64_encode_bytes(data);
    dev::bytes out;

    for (size_t i = 0; i < b64.size(); i++) {
        switch (b64[i]) {
        case '+':
            out.push_back('-');
            break;
        case '/':
            out.push_back('_');
            break;
        case '=':
            break;
        default:
            out.push_back(b64[i]);
        }
    }

    return out;
}

dev::bigint minter::utils::to_bigint(const dev::bytes& bytes) {
    if (bytes.empty()) {
        return dev::bigint("0");
    }
    //
    //    dev::bigint val;
    //    boost::multiprecision::import_bits(val, bytes.begin(), bytes.end());
    //    return val;

    return dev::bigint(bytes);
}

dev::bigint minter::utils::to_bigint(const uint8_t* bytes, size_t len) {
    if (len == 0) {
        return dev::bigint("0");
    }
    return to_bigint(dev::bytes(bytes, bytes + len));
}

std::string minter::utils::to_string(const dev::bytes& src) {
    std::stringstream ss;
    for (const auto& item : src) {
        ss << item;
    }

    return ss.str();
}

std::string minter::utils::to_string(const dev::bigdec18& src) {
    //    std::stringstream ss;
    //    ss << std::setprecision(std::numeric_limits<boost::multiprecision::cpp_dec_float<18>>::max_digits10);
    //    ss << src;
    //
    //    return toolbox::strings::decimal_formatter()(ss.str());

    return src.format(".18f");
}

std::string minter::utils::to_string_lp(const dev::bigdec18& src) {
    //    std::stringstream ss;
    //    ss << std::setprecision(std::numeric_limits<boost::multiprecision::cpp_dec_float<4>>::max_digits10);
    //    ss << src;
    const auto res = to_string(src);
    return toolbox::strings::decimal_formatter(res).set_min_fractions(4).set_max_fractions(4).format();
}

std::string minter::utils::to_string(const dev::bigint& src) {
    std::stringstream ss;
    ss << src;

    return ss.str();
}

std::string minter::utils::to_string(uint64_t src) {
    std::stringstream ss;
    ss << src;
    return ss.str();
}

std::string minter::utils::to_string(const std::vector<char>& data) {
    return std::string(data.begin(), data.end());
}

std::string minter::utils::to_string_clear(const dev::bytes& src) {
    const std::string tmp(to_string(src));
    const char* tmp2 = tmp.c_str();
    return strip_null_bytes(tmp2, tmp.size());
}

std::string minter::utils::strip_null_bytes(const char* input, size_t len) {
    if (input == nullptr || len == 0) {
        return std::string();
    }

    std::stringstream ss;
    for (size_t i = 0; i < len; i++) {
        if (input[i] == 0x00) {
            continue;
        }

        ss << input[i];
    }

    return ss.str();
}

dev::bytes minter::utils::gen_random_bytes(size_t n) {
    std::random_device dev;
    PCGRand rand(dev);
    std::uniform_int_distribution<> udist(0x00, 0xFF);

    std::vector<uint8_t> out;
    out.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        out.push_back((uint8_t) udist(rand));
    }

    return out;
}

dev::bigint minter::utils::normalize_value(const char* input) {
    return dev::bigint(dev::bigdec18(input) * minter::utils::normalized_value_dec);
}

dev::bigint minter::utils::normalize_value(const std::string& input) {
    return minter::utils::normalize_value(input.c_str());
}

dev::bigint minter::utils::normalize_value(const dev::bigdec18& value) {
    return dev::bigint(value * minter::utils::normalized_value_dec);
}

dev::bigdec18 minter::utils::humanize_value(const dev::bigint& value) {
    return dev::bigdec18(value) / minter::utils::normalized_value_dec;
}

std::ostream& operator<<(std::ostream& out, const dev::bytes& d) {
    dev::bytes_data tmp(d);
    out << tmp.to_hex();
    return out;
}

std::ostream& operator<<(std::ostream& out, const eth::RLPStream& rlp) {
    dev::bytes_data tmp(rlp.out());
    out << tmp.to_hex();
    return out;
}

void minter::utils::memset_s(uint8_t* dst, uint8_t val, size_t n) {
    if (dst == NULL)
        return;
    volatile unsigned char* p = dst;
    while (n--) {
        *p++ = val;
    }
}