#include <iostream>
#include <cmath>

#include "infinity.h"
#include "zero.h"

int main() {
    std::cout << float32ToBits(3.14) << std::endl;
    std::cout << float64ToBits(3.141592) << std::endl;
    std::cout << bitsToFloat32(1078523331) << std::endl;
    std::cout << bitsToFloat64(4614256655080292474) << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << isFinite32(INFINITY) << std::endl;
    std::cout << isFinite64(9.11) << std::endl;
    std::cout << isInf32(INFINITY) << std::endl;
    std::cout << isInf64(NAN) << std::endl;
    std::cout << isPosInf32(INFINITY) << std::endl;
    std::cout << isPosInf64(-INFINITY) << std::endl;
    std::cout << isNegInf32(INFINITY) << std::endl;
    std::cout << isNegInf64(-INFINITY) << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << isZero32(0) << std::endl;
    std::cout << isZero64(INFINITY) << std::endl;
    std::cout << isPosZero32(0.0f) << std::endl;
    std::cout << isPosZero64(-0.0f) << std::endl;
    std::cout << isNegZero32(-0.0f) << std::endl;
    std::cout << isNegZero64(-INFINITY) << std::endl;
    return 0;
}