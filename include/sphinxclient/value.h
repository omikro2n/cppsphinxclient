/*
 *
 * C++ sphinx search client library
 * Copyright (C) 2007  Seznam.cz, a.s.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Seznam.cz, a.s.
 * Radlicka 2, Praha 5, 15000, Czech Republic
 * http://www.seznam.cz, mailto:sphinxclient@firma.seznam.cz
 *
 *
 * $Id$
 *
 * DESCRIPTION
 * SphinxClient header file - attribute value abstraction
 *
 * AUTHOR
 * Jan Kirschner <jan.kirschner@firma.seznam.cz>
 *
 * HISTORY
 * 2007-01-03 (jan.kirschner)
 *            First draft.
 */

//! @file value.h

#ifndef __SPHINXVALUE_H__
#define __SPHINXVALUE_H__

#include <vector>
#include <sphinxclient/error.h>
#include <stdint.h>

namespace Sphinx
{

/** @brief real attribute value types generated by searchd
  */

enum ValueType_t {
    VALUETYPE_UINT32 = 0, //!< @brief 32bit unsigned integer
    VALUETYPE_FLOAT = 1,  //!< @brief 32bit floating point value
    VALUETYPE_VECTOR = 2, //!< @brief vector of uint32_ts or floats
    VALUETYPE_UINT64 = 3, //!< @brief 64bit unsigned integer
    VALUETYPE_STRING = 4  //!< @brief string
};

class ValueBase_t;

/** @brief Generic value type of sphinx attribute
 *
 *  Value returned by Sphinx searchd in search result
 *  attributes. Supported types are uint32_t, float
 *  and std::vector<Value_t>
 */

class Value_t {
protected:
    ValueBase_t *value;
    void clear();
    void makeCopy(const Value_t&);

public:
    Value_t() : value(0) {}
    //! @brief initializes Value_t as uint32_t type
    Value_t(uint32_t v);
    //! @brief initializes Value_t as float type
    Value_t(float v);
    //! @brief initializes Value_t as vector type
    Value_t(const std::vector<Value_t> &v);
    //! @brief initializes Value_t as uint64_t type
    Value_t(uint64_t v);
    //! @brief initializes Value_t as string type
    Value_t(const std::string &v);

    ~Value_t(){ clear(); }

    //! @brief copy constructor, that performs deep copy of *value pointer
    Value_t(const Value_t &v){ makeCopy(v); }
    //! @brief assignment, that performs deep copy of *value pointer
    Value_t & operator = (const Value_t&);

    /** @brief check if contains a valid value.
     */
    inline bool isValid() const { return value; }

    /** @brief returns current type of Value_t
     *
     *  @return current value type. One of VALUETYPE_UINT32, VALUETYPE_FLOAT,
     *          VALUETYPE_VECTOR
     *  @see ValueType_t
     */
    ValueType_t getValueType() const;

    /** @brief overloaded implicit conversion operator to uint32_t
     *
     *  Returns value as uint32_t. If the current value type is other than
     *  uint32_t, throws ValueTypeError_t;
     */
    operator uint32_t () const throw (ValueTypeError_t);

    /** @brief overloaded implicit conversion operator to std::vector
     *
     *  Returns value as std::vector<Value_t>. If the current value type
     *  is other than std::vector, throws ValueTypeError_t;
     */
    operator const std::vector<Value_t>& () const throw (ValueTypeError_t);

    /** @brief overloaded implicit conversion operator to float
     *
     *  Returns value as float. If the current value type is other than
     *  float, throws ValueTypeError_t;
     */
    operator float () const throw (ValueTypeError_t);

    /** @brief overloaded implicit conversion operator to uint64_t
     *
     *  Returns value as uint64_t. If the current value type is other than
     *  uint64_t, throws ValueTypeError_t;
     */
    operator uint64_t () const throw (ValueTypeError_t);

    /** @brief overloaded implicit conversion operator to std::string
     *
     *  Returns value as std::string. If the current value type is other than
     *  string, throws ValueTypeError_t;
     */
    operator const std::string & () const throw (ValueTypeError_t);
};//class


}//namespace

#endif
