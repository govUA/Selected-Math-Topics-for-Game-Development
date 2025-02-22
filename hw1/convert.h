#include <cstdint>
#include <cstring>

uint32_t float32ToBits(float value);

uint64_t float64ToBits(double value);

float bitsToFloat32(uint32_t bits);

double bitsToFloat64(uint64_t bits);