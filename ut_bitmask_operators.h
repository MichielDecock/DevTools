// Utility class enabling to use enums as flags

// Property of Bricsys NV. All rights reserved.
// This file is part of the source code of Bricsys NV. The source code is subject to copyright,
// is a trade secret of Bricsys NV, and contains embodiments of inventions
// disclosed in patent applications and patents of Bricsys NV.

// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
#pragma once

#include "ut_utils.h"

#include <type_traits>

/**
    Example:

    enum class A: unsigned long {
        x=0x80000000,y=0x40000000
    };

    COMBINABLE_ENUM(A)

    int main(){
        A a1 = A::x | A::y;
        A a2 = a1&A::y;
        a2^ = A::x;
        A a3 = ~a1;
    }

    Pay special attention to enum classes declared in another class. They should be registered
    outside the container class: COMBINABLE_ENUM(ContainerClass::EnumClass)

    All functionality here should be put at global namespace
*/

#define COMBINABLE_ENUM(E)                                                                         \
    template <>                                                                                    \
    struct enable_bitmask_operators<E>                                                             \
    {                                                                                              \
        static const bool enable = true;                                                           \
    };

template <typename E>
struct UTILS_API enable_bitmask_operators
{
    static const bool enable = false;
};

template <typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator|(E lhs, E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

template <typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator&(E lhs, E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

template <typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator^(E lhs, E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

template <typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator~(E lhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(~static_cast<underlying>(lhs));
}

template <typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator|=(E& lhs, E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    lhs = static_cast<E>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
    return lhs;
}

template <typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator&=(E& lhs, E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    lhs = static_cast<E>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
    return lhs;
}

template <typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator^=(E& lhs, E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    lhs = static_cast<E>(static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
    return lhs;
}

#define OPTION_TRUE(var, option) (static_cast<unsigned long long>((var) & (option)) != 0)
#define OPTION_FALSE(var, option) (static_cast<unsigned long long>((var) & (option)) == 0)
#define OPTION_CHECK_ALL(var, option) (static_cast<unsigned long long>((var) & (option)) == option)
#define OPTION_ADD(var, option) ((var) | (option))
#define OPTION_REMOVE(var, option) ((var) & ~(option))
