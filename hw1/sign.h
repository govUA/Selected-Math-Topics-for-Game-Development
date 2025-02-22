#include "convert.h"

bool isSignBitSet32(float value) {
    uint32_t bits = float32ToBits(value);
    return (bits >> 31) != 0;
}

bool isSignBitSet64(double value) {
    uint64_t bits = float64ToBits(value);
    return (bits >> 63) != 0;
}