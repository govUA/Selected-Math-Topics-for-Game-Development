#include "convert.h"

bool isNaN32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t fraction = bits & 0x7FFFFF;
    return exponent == 0xFF && fraction != 0;
}

bool isNaN64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t exponent = (bits >> 52) & 0x7FF;
    uint64_t fraction = bits & 0xFFFFFFFFFFFFF;
    return exponent == 0x7FF && fraction != 0;
}

bool isNormal32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t exponent = (bits >> 23) & 0xFF;
    return exponent > 0 && exponent < 0xFF;
}

bool isNormal64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t exponent = (bits >> 52) & 0x7FF;
    return exponent > 0 && exponent < 0x7FF;
}

bool isSubnormal32(float value) {
    uint32_t bits = float32ToBits(value);
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t fraction = bits & 0x7FFFFF;
    return exponent == 0 && fraction != 0;
}

bool isSubnormal64(double value) {
    uint64_t bits = float64ToBits(value);
    uint64_t exponent = (bits >> 52) & 0x7FF;
    uint64_t fraction = bits & 0xFFFFFFFFFFFFF;
    return exponent == 0 && fraction != 0;
}