#pragma once

#include <tuple>
#include <string>
#include <exception>

// --- 1. Utilitaires ---
#define ORM_EXPAND(x) x

// --- 2. Génération des pointeurs pour std::make_tuple ---
#define ORM_TUPLE_1(C, x) &C::x
#define ORM_TUPLE_2(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_1(C, __VA_ARGS__))
#define ORM_TUPLE_3(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_2(C, __VA_ARGS__))
#define ORM_TUPLE_4(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_3(C, __VA_ARGS__))
#define ORM_TUPLE_5(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_4(C, __VA_ARGS__))
#define ORM_TUPLE_6(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_5(C, __VA_ARGS__))
#define ORM_TUPLE_7(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_6(C, __VA_ARGS__))
#define ORM_TUPLE_8(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_7(C, __VA_ARGS__))
#define ORM_TUPLE_9(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_8(C, __VA_ARGS__))
#define ORM_TUPLE_10(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_9(C, __VA_ARGS__))
#define ORM_TUPLE_11(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_10(C, __VA_ARGS__))
#define ORM_TUPLE_12(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_11(C, __VA_ARGS__))
#define ORM_TUPLE_13(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_12(C, __VA_ARGS__))
#define ORM_TUPLE_14(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_13(C, __VA_ARGS__))
#define ORM_TUPLE_15(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_14(C, __VA_ARGS__))
#define ORM_TUPLE_16(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_15(C, __VA_ARGS__))
#define ORM_TUPLE_17(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_16(C, __VA_ARGS__))
#define ORM_TUPLE_18(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_17(C, __VA_ARGS__))
#define ORM_TUPLE_19(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_18(C, __VA_ARGS__))
#define ORM_TUPLE_20(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_19(C, __VA_ARGS__))
#define ORM_TUPLE_21(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_20(C, __VA_ARGS__))
#define ORM_TUPLE_22(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_21(C, __VA_ARGS__))
#define ORM_TUPLE_23(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_22(C, __VA_ARGS__))
#define ORM_TUPLE_24(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_23(C, __VA_ARGS__))
#define ORM_TUPLE_25(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_24(C, __VA_ARGS__))
#define ORM_TUPLE_26(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_25(C, __VA_ARGS__))
#define ORM_TUPLE_27(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_26(C, __VA_ARGS__))
#define ORM_TUPLE_28(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_27(C, __VA_ARGS__))
#define ORM_TUPLE_29(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_28(C, __VA_ARGS__))
#define ORM_TUPLE_30(C, x, ...) &C::x, ORM_EXPAND(ORM_TUPLE_29(C, __VA_ARGS__))

// --- 3. Génération des vérifications if() pour getColumnName ---
#define ORM_NAME_1(C, x) \
    if constexpr (std::is_same_v<std::decay_t<decltype(member)>, decltype(&C::x)>) { \
        if (member == &C::x) return #x; \
    }
#define ORM_NAME_2(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_1(C, __VA_ARGS__))
#define ORM_NAME_3(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_2(C, __VA_ARGS__))
#define ORM_NAME_4(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_3(C, __VA_ARGS__))
#define ORM_NAME_5(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_4(C, __VA_ARGS__))
#define ORM_NAME_6(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_5(C, __VA_ARGS__))
#define ORM_NAME_7(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_6(C, __VA_ARGS__))
#define ORM_NAME_8(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_7(C, __VA_ARGS__))
#define ORM_NAME_9(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_8(C, __VA_ARGS__))
#define ORM_NAME_10(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_9(C, __VA_ARGS__))
#define ORM_NAME_11(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_10(C, __VA_ARGS__))
#define ORM_NAME_12(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_11(C, __VA_ARGS__))
#define ORM_NAME_13(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_12(C, __VA_ARGS__))
#define ORM_NAME_14(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_13(C, __VA_ARGS__))
#define ORM_NAME_15(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_14(C, __VA_ARGS__))
#define ORM_NAME_16(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_15(C, __VA_ARGS__))
#define ORM_NAME_17(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_16(C, __VA_ARGS__))
#define ORM_NAME_18(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_17(C, __VA_ARGS__))
#define ORM_NAME_19(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_18(C, __VA_ARGS__))
#define ORM_NAME_20(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_19(C, __VA_ARGS__))
#define ORM_NAME_21(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_20(C, __VA_ARGS__))
#define ORM_NAME_22(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_21(C, __VA_ARGS__))
#define ORM_NAME_23(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_22(C, __VA_ARGS__))
#define ORM_NAME_24(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_23(C, __VA_ARGS__))
#define ORM_NAME_25(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_24(C, __VA_ARGS__))
#define ORM_NAME_26(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_25(C, __VA_ARGS__))
#define ORM_NAME_27(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_26(C, __VA_ARGS__))
#define ORM_NAME_28(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_27(C, __VA_ARGS__))
#define ORM_NAME_29(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_28(C, __VA_ARGS__))
#define ORM_NAME_30(C, x, ...) ORM_NAME_1(C, x) ORM_EXPAND(ORM_NAME_29(C, __VA_ARGS__))

// --- 4. Sélecteurs automatiques selon le nombre d'arguments ---
#define ORM_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, NAME, ...) NAME

#define ORM_TUPLE(C, ...) ORM_EXPAND(ORM_GET_MACRO(__VA_ARGS__, ORM_TUPLE_30, ORM_TUPLE_29, ORM_TUPLE_28, ORM_TUPLE_27, ORM_TUPLE_26, ORM_TUPLE_25, ORM_TUPLE_24, ORM_TUPLE_23, ORM_TUPLE_22, ORM_TUPLE_21, ORM_TUPLE_20, ORM_TUPLE_19, ORM_TUPLE_18, ORM_TUPLE_17, ORM_TUPLE_16, ORM_TUPLE_15, ORM_TUPLE_14, ORM_TUPLE_13, ORM_TUPLE_12, ORM_TUPLE_11, ORM_TUPLE_10, ORM_TUPLE_9, ORM_TUPLE_8, ORM_TUPLE_7, ORM_TUPLE_6, ORM_TUPLE_5, ORM_TUPLE_4, ORM_TUPLE_3, ORM_TUPLE_2, ORM_TUPLE_1)(C, __VA_ARGS__))
#define ORM_NAMES(C, ...) ORM_EXPAND(ORM_GET_MACRO(__VA_ARGS__, ORM_NAME_30, ORM_NAME_29, ORM_NAME_28, ORM_NAME_27, ORM_NAME_26, ORM_NAME_25, ORM_NAME_24, ORM_NAME_23, ORM_NAME_22, ORM_NAME_21, ORM_NAME_20, ORM_NAME_19, ORM_NAME_18, ORM_NAME_17, ORM_NAME_16, ORM_NAME_15, ORM_NAME_14, ORM_NAME_13, ORM_NAME_12, ORM_NAME_11, ORM_NAME_10, ORM_NAME_9, ORM_NAME_8, ORM_NAME_7, ORM_NAME_6, ORM_NAME_5, ORM_NAME_4, ORM_NAME_3, ORM_NAME_2, ORM_NAME_1)(C, __VA_ARGS__))

// --- 5. LA MACRO PRINCIPALE EXPOSÉE ---
#define DECLARE_ORM_METADATA(STRUCT_NAME, ...) \
    static constexpr auto members() { \
        return std::make_tuple(ORM_TUPLE(STRUCT_NAME, __VA_ARGS__)); \
    } \
    template<typename T, typename C> \
    static std::string getColumnName(T C::* member) { \
        ORM_NAMES(STRUCT_NAME, __VA_ARGS__) \
        std::terminate(); \
    }
