#include "convert.h"

uint32_t float32ToBits(float value) {
    uint32_t result;
    std::memcpy(&result, &value, sizeof(float));
    return result;
}

uint64_t float64ToBits(double value) {
    uint64_t result;
    std::memcpy(&result, &value, sizeof(double));
    return result;
}

float bitsToFloat32(uint32_t bits) {
    float result;
    std::memcpy(&result, &bits, sizeof(float));
    return result;
}

double bitsToFloat64(uint64_t bits) {
    double result;
    std::memcpy(&result, &bits, sizeof(double));
    return result;
}