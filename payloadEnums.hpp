#ifndef PAYLOADENUMS_HPP
#define PAYLOADENUMS_HPP

#include <cstdint>

/**
 * @brief Bit flags for PayloadData
 *
 */
enum class PayloadDataFlag : int64_t {
    coincidenceCounts = INT64_C(1) << 0,
    siftedKeyBits = INT64_C(1) << 1,
    qber = INT64_C(1) << 2,
    numberOfBitsRevealed = INT64_C(1) << 3,
    fValue = INT64_C(1) << 4,
    secretKeyBits = INT64_C(1) << 5,
};

/**
 * @brief Bitwise OR operator for `enum class PayloadDataFlag`.
 *
 * @param PayloadDataFlag
 * @param PayloadDataFlag
 * @return PayloadDataFlag
 */
inline PayloadDataFlag operator|(PayloadDataFlag a, PayloadDataFlag b) {
    return static_cast<PayloadDataFlag>(static_cast<int64_t>(a) | static_cast<int64_t>(b));
}

/**
 * @brief Bitwise AND operator for `enum class PayloadDataFlag`.
 *
 * @param PayloadDataFlag
 * @param PayloadDataFlag
 * @return PayloadDataFlag
 */
inline PayloadDataFlag operator&(PayloadDataFlag a, PayloadDataFlag b) {
    return static_cast<PayloadDataFlag>(static_cast<int64_t>(a) & static_cast<int64_t>(b));
}

inline bool areFlagsSet(const PayloadDataFlag flags, const PayloadDataFlag flagsToCheck) {
    return (flags & flagsToCheck) == flagsToCheck;
}

#endif