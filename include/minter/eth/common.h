/*
    This file is part of cpp-ethereum.

    cpp-ethereum is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cpp-ethereum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file Common.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 *
 * Very common stuff (i.e. that every other header needs except vector_ref.h).
 */

#pragma once

// way too many unsigned to size_t warnings in 32 bit build
#ifdef _M_IX86
#pragma warning(disable:4244)
#endif

#if _MSC_VER && _MSC_VER < 1900
#define _ALLOW_KEYWORD_MACROS
#define noexcept throw()
#endif

#ifdef __INTEL_COMPILER
#pragma warning(disable:3682) //call through incomplete class
#endif

#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <functional>
#include <string>
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "minter/minter_tx_core.h"

// CryptoPP defines byte in the global namespace, so must we.
using byte = uint8_t;

namespace dev {

namespace mp = boost::multiprecision;

// Binary data types.
using bytes = std::vector<byte>;


// Numeric types.
using bigint = mp::number<mp::cpp_int_backend<>>;
using bigdec18 = mp::number<mp::cpp_dec_float<18>>;
using u256 =  mp::number<mp::cpp_int_backend<256,256,mp::unsigned_magnitude,mp::unchecked,void>>;
using u160 =  mp::number<mp::cpp_int_backend<160,160,mp::unsigned_magnitude,mp::unchecked,void>>;


// Algorithms for string and string-like collections.

/// Determine bytes required to encode the given integer value. @returns 0 if @a _i is zero.
template<class T>
inline unsigned bytesRequired(T _i) {
    static_assert(std::is_same<bigint, T>::value || !std::numeric_limits<T>::is_signed,
                  "only unsigned types or bigint supported"); //bigint does not carry sign bit on shift
    unsigned i = 0;
    for (; _i != 0; ++i, _i >>= 8) { }
    return i;
}

/// Concatenate the contents of a container onto a vector.
template<class T, class U>
inline std::vector<T> &operator+=(std::vector<T> &output, U const &input) {
    output.insert(output.end(), std::begin(input), std::end(input));
    return output;
}

/// Insert the contents of a container into a set
template<class T, class U>
std::set<T> &operator+=(std::set<T> &input, U const &output) {
    input.insert(std::begin(output), std::end(output));
    return input;
}

/// Insert the contents of a container into an unordered_set
template<class T, class U>
std::unordered_set<T> &operator+=(std::unordered_set<T> &input, U const &output) {
    input.insert(std::begin(output), std::end(output));
    return input;
}

/// Insert the contents of a container into a set
template<class T, class U>
std::set<T> operator+(std::set<T> input, U const &value) {
    return input += value;
}

/// Insert the contents of a container into an unordered_set
template<class T, class U>
std::unordered_set<T> operator+(std::unordered_set<T> input, U const &value) {
    return input += value;
}

/// Concatenate the contents of a container onto a vector
template<class T, class U>
std::vector<T> operator+(std::vector<T> input, U const &value) {
    return input += value;
}


/// Converts a big-endian byte-stream represented on a templated collection to a templated integer value.
/// @a _In will typically be either std::string or bytes.
/// @a T will typically by unsigned, u160, u256 or bigint.
template <class T, class _In>
inline T fromBigEndian(_In const& _bytes)
{
    T ret = (T)0;
    for (auto i: _bytes)
        ret = (T)((ret << 8) | (byte)(typename std::make_unsigned<decltype(i)>::type)i);
    return ret;
}


/// Escapes a string into the C-string representation.
/// @p _all if true will escape all characters, not just the unprintable ones.
std::string escaped(std::string const& _s, bool _all = true);

}  // namespace dev
