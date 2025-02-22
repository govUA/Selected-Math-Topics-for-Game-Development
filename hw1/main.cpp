#include <iostream>
#include <cmath>
#include <cfloat>

#include "minmax.h"
#include "sign.h"

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
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << isNaN32(1.0 / 0.0) << std::endl;
    std::cout << isNaN64(0.0 / 0.0) << std::endl;
    std::cout << isNormal32(DBL_MIN / 2) << std::endl;
    std::cout << isNormal64(1.05) << std::endl;
    std::cout << isSubnormal32(DBL_MAX / 4) << std::endl;
    std::cout << isSubnormal64(DBL_MIN / 3) << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << isSignBitSet32(-1.23456789) << std::endl;
    std::cout << isSignBitSet64(9.11) << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << abs32(-1.23456789) << std::endl;
    std::cout << abs64(9.1142031415926966688) << std::endl;
    std::cout << min32(-1.23456789, 4.0) << std::endl;
    std::cout << min64(3.221, 9.1142031415926966688) << std::endl;
    std::cout << max32(-4444444.0901, -1.23456789) << std::endl;
    std::cout << max64(0.0 / 0.0, 9.1142031415926966688) << std::endl;
    std::cout << clamp32(-1.23456789, -INFINITY, INFINITY) << std::endl;
    std::cout << clamp64(9.1142031415926966688, INFINITY, -INFINITY) << std::endl;
    return 0;
}