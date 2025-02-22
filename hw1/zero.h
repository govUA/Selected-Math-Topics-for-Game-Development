#include "convert.h"

bool isZero32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t fraction = bits & 0x7FFFFF;
    return exponent == 0 && fraction == 0;
}

bool isZero64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t exponent = (bits >> 52) & 0x7FF;
    uint64_t fraction = bits & 0xFFFFFFFFFFFFF;
    return exponent == 0 && fraction == 0;
}

bool isPosZero32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t sign = bits >> 31;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t fraction = bits & 0x7FFFFF;
    return sign == 0 && exponent == 0 && fraction == 0;
}

bool isPosZero64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t sign = bits >> 63;
    uint64_t exponent = (bits >> 52) & 0x7FF;
    uint64_t fraction = bits & 0xFFFFFFFFFFFFF;
    return sign == 0 && exponent == 0 && fraction == 0;
}

bool isNegZero32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t sign = bits >> 31;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t fraction = bits & 0x7FFFFF;
    return sign == 1 && exponent == 0 && fraction == 0;
}

bool isNegZero64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t sign = bits >> 63;
    uint64_t exponent = (bits >> 52) & 0x7FF;
    uint64_t fraction = bits & 0xFFFFFFFFFFFFF;
    return sign == 1 && exponent == 0 && fraction == 0;
}