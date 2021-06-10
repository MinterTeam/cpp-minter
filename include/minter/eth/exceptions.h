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
/** @file Exceptions.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 */

#pragma once

#include "types.h"

#include <exception>
#include <sstream>
#include <string>
#include <tuple>

namespace eth {

#ifndef BOOST_THROW_EXCEPTION
#define ETH_THROW_EXCEPTION(e) throw e
#else
#define ETH_THROW_EXCEPTION(e) BOOST_THROW_EXCEPTION(e)
#endif

#ifndef _NOEXCEPT
#define _NOEXCEPT noexcept
#endif

/// Base class for all exceptions.
class Exception : virtual public std::exception {
public:
    ~Exception() _NOEXCEPT override {
    }
    const char* what() const _NOEXCEPT override {
        return std::exception::what();
        //        return boost::diagnostic_information_what(*this);
    }
};

template<class T>
class RLPErrorInfo {
public:
    typedef T value_type;

    RLPErrorInfo() {
    }
    RLPErrorInfo(const value_type& value)
        : m_value(value) {
    }
    RLPErrorInfo(value_type&& value)
        : m_value(std::move(value)) {
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << m_value;
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const RLPErrorInfo<value_type>& val) {
        os << val.m_value;
        return os;
    }

private:
    value_type m_value;
};

/// Base class for all RLP exceptions.
class RLPException : virtual public Exception {
public:
    RLPException() {
    }

    RLPException(const char* msg) {
        ss << msg;
    }
    RLPException(const std::string& msg) {
        ss << msg;
    }

    RLPException(const RLPException& other) {
        ss << other.ss.str();
    }

    RLPException(RLPException&& other) {
        ss << other.ss.str();
        other.ss.str();
        other.ss.clear();
    }

    virtual ~RLPException() _NOEXCEPT override {
        ss.str("");
        ss.clear();
    }

    template<class T>
    RLPException(RLPErrorInfo<T> info) {
        ss << info.to_string();
    }

    template<class T>
    RLPException& operator<<(RLPErrorInfo<T> info) {
        ss << info.to_string();
        return *this;
    }

    template<class A, class B>
    RLPException& operator<<(std::tuple<RLPErrorInfo<A>, RLPErrorInfo<B>> info) {
        ss << std::get<0>(info) << "\n";
        ss << std::get<1>(info);
        return *this;
    }

private:
    std::stringstream ss;
};

#define DEV_SIMPLE_EXCEPTION_RLP(X) \
    class X : virtual public RLPException {}

DEV_SIMPLE_EXCEPTION_RLP(BadCast);
DEV_SIMPLE_EXCEPTION_RLP(BadRLP);
DEV_SIMPLE_EXCEPTION_RLP(OversizeRLP);
DEV_SIMPLE_EXCEPTION_RLP(UndersizeRLP);

// error information to be added to exceptions
using errinfo_comment = RLPErrorInfo<std::string>;
using errinfo_required = RLPErrorInfo<eth::bigint>;
using errinfo_got = RLPErrorInfo<eth::bigint>;
using errinfo_min = RLPErrorInfo<eth::bigint>;
using errinfo_max = RLPErrorInfo<eth::bigint>;
using RequirementError = std::tuple<errinfo_required, errinfo_got>;
using RequirementErrorComment = std::tuple<errinfo_required, errinfo_got, errinfo_comment>;
} // namespace eth
