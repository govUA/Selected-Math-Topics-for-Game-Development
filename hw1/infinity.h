#include "convert.h"

bool isFinite32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t exponent = (bits >> 23) & 0xFF;
    return exponent != 0xFF;
}

bool isFinite64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t exponent = (bits >> 52) & 0x7FF;
    return exponent != 0x7FF;
}

bool isInf32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t fraction = bits & 0x7FFFFF;
    return exponent == 0xFF && fraction == 0;
}

bool isInf64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t exponent = (bits >> 52) & 0x7FF;
    uint64_t fraction = bits & 0xFFFFFFFFFFFFF;
    return exponent == 0x7FF && fraction == 0;
}

bool isPosInf32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t sign = bits >> 31;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t fraction = bits & 0x7FFFFF;
    return sign == 0 && exponent == 0xFF && fraction == 0;
}

bool isPosInf64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t sign = bits >> 63;
    uint64_t exponent = (bits >> 52) & 0x7FF;
    uint64_t fraction = bits & 0xFFFFFFFFFFFFF;
    return sign == 0 && exponent == 0x7FF && fraction == 0;
}

bool isNegInf32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t sign = bits >> 31;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t fraction = bits & 0x7FFFFF;
    return sign == 1 && exponent == 0xFF && fraction == 0;
}

bool isNegInf64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t sign = bits >> 63;
    uint64_t exponent = (bits >> 52) & 0x7FF;
    uint64_t fraction = bits & 0xFFFFFFFFFFFFF;
    return sign == 1 && exponent == 0x7FF && fraction == 0;
}