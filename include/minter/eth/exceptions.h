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

#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/info_tuple.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tuple/tuple.hpp>
#include <exception>
#include <string>

namespace eth {
/// Base class for all exceptions.
struct Exception : virtual std::exception, virtual boost::exception {
    const char* what() const noexcept override {
        return boost::diagnostic_information_what(*this);
    }
};

/// Base class for all RLP exceptions.
struct RLPException : virtual Exception {};
#define DEV_SIMPLE_EXCEPTION_RLP(X) \
    struct X : virtual RLPException {}

DEV_SIMPLE_EXCEPTION_RLP(BadCast);
DEV_SIMPLE_EXCEPTION_RLP(BadRLP);
DEV_SIMPLE_EXCEPTION_RLP(OversizeRLP);
DEV_SIMPLE_EXCEPTION_RLP(UndersizeRLP);

// error information to be added to exceptions
using errinfo_comment = boost::error_info<struct tag_comment, std::string>;
using errinfo_required = boost::error_info<struct tag_required, eth::bigint>;
using errinfo_got = boost::error_info<struct tag_got, eth::bigint>;
using errinfo_min = boost::error_info<struct tag_min, eth::bigint>;
using errinfo_max = boost::error_info<struct tag_max, eth::bigint>;
using RequirementError = boost::tuple<errinfo_required, errinfo_got>;
using RequirementErrorComment = boost::tuple<errinfo_required, errinfo_got, errinfo_comment>;
} // namespace eth
