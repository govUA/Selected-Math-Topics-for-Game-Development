#include "classify.h"

float abs32(float value) {
    uint32_t bits = float32ToBits(value);
    bits &= 0x7FFFFFFF;
    return bitsToFloat32(bits);
}

double abs64(double value) {
    uint64_t bits = float64ToBits(value);
    bits &= 0x7FFFFFFFFFFFFFFF;
    return bitsToFloat64(bits);
}

float min32(float a, float b) {
    if (isNaN32(a)) return b;
    if (isNaN32(b)) return a;

    if (isPosZero32(a) && isNegZero32(b)) return b;
    if (isNegZero32(a) && isPosZero32(b)) return a;

    return (a < b) ? a : b;
}

double min64(double a, double b) {
    if (isNaN64(a)) return b;
    if (isNaN64(b)) return a;

    if (isPosZero64(a) && isNegZero64(b)) return b;
    if (isNegZero64(a) && isPosZero64(b)) return a;

    return (a < b) ? a : b;
}

float max32(float a, float b) {
    if (isNaN32(a)) return b;
    if (isNaN32(b)) return a;

    if (isPosZero32(a) && isNegZero32(b)) return a;
    if (isNegZero32(a) && isPosZero32(b)) return b;

    return (a > b) ? a : b;
}

double max64(double a, double b) {
    if (isNaN64(a)) return b;
    if (isNaN64(b)) return a;

    if (isPosZero64(a) && isNegZero64(b)) return a;
    if (isNegZero64(a) && isPosZero64(b)) return b;

    return (a > b) ? a : b;
}

float clamp32(float value, float min_val, float max_val) {
    return min32(max32(value, min_val), max_val);
}

double clamp64(double value, double min_val, double max_val) {
    return min64(max64(value, min_val), max_val);
}