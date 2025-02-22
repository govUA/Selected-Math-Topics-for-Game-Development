#include "minmax.h"
#include "sign.h"

bool equalPrecision32(float a, float b, float precision) {
    if (isNaN32(a) || isNaN32(b)) return false;
    if (isInf32(a) && isInf32(b)) return (isPosInf32(a) == isPosInf32(b));
    if (isZero32(a) && isZero32(b)) return true;

    return abs32(a - b) <= precision;
}

bool equalPrecision64(double a, double b, double precision) {
    if (isNaN64(a) || isNaN64(b)) return false;
    if (isInf64(a) && isInf64(b)) return (isPosInf64(a) == isPosInf64(b));
    if (isZero64(a) && isZero64(b)) return true;

    return abs64(a - b) <= precision;
}

bool equalAny32(float a, float b) {
    return float32ToBits(a) == float32ToBits(b);
}

bool equalAny64(double a, double b) {
    return float64ToBits(a) == float64ToBits(b);
}

bool lessPrecision32(float a, float b, float precision) {
    if (isNaN32(a) || isNaN32(b)) return false;
    if (isInf32(a)) return isNegInf32(a) && !isNegInf32(b);
    if (isInf32(b)) return !isPosInf32(a) && isPosInf32(b);

    return (a < b) && !equalPrecision32(a, b, precision);
}

bool lessPrecision64(double a, double b, double precision) {
    if (isNaN64(a) || isNaN64(b)) return false;
    if (isInf64(a)) return isNegInf64(a) && !isNegInf64(b);
    if (isInf64(b)) return !isPosInf64(a) && isPosInf64(b);

    return (a < b) && !equalPrecision64(a, b, precision);
}

bool lessAny32(float a, float b) {
    if (isNaN32(a) || isNaN32(b)) return false;

    if (isZero32(a) && isZero32(b)) {
        return isNegZero32(a) && isPosZero32(b);
    }

    bool aSign = isSignBitSet32(a);
    bool bSign = isSignBitSet32(b);
    if (aSign != bSign) {
        return aSign;
    }

    if (aSign) {
        return b < a;
    } else {
        return a < b;
    }
}

bool lessAny64(double a, double b) {
    if (isNaN64(a) || isNaN64(b)) return false;

    if (isZero64(a) && isZero64(b)) {
        return isNegZero64(a) && isPosZero64(b);
    }

    bool aSign = isSignBitSet64(a);
    bool bSign = isSignBitSet64(b);
    if (aSign != bSign) {
        return aSign;
    }

    if (aSign) {
        return b < a;
    } else {
        return a < b;
    }
}

bool greaterPrecision32(float a, float b, float precision) {
    if (isNaN32(a) || isNaN32(b)) return false;
    if (isInf32(a)) return isPosInf32(a) && !isPosInf32(b);
    if (isInf32(b)) return !isNegInf32(a) && isNegInf32(b);

    return (a > b) && !equalPrecision32(a, b, precision);
}

bool greaterPrecision64(double a, double b, double precision) {
    if (isNaN64(a) || isNaN64(b)) return false;
    if (isInf64(a)) return isPosInf64(a) && !isPosInf64(b);
    if (isInf64(b)) return !isNegInf64(a) && isNegInf64(b);

    return (a > b) && !equalPrecision64(a, b, precision);
}

bool greaterAny32(float a, float b) {
    if (isNaN32(a) || isNaN32(b)) return false;

    if (isZero32(a) && isZero32(b)) {
        return isPosZero32(a) && isNegZero32(b);
    }

    bool aSign = isSignBitSet32(a);
    bool bSign = isSignBitSet32(b);
    if (aSign != bSign) {
        return bSign;
    }

    if (aSign) {
        return a < b;
    } else {
        return a > b;
    }
}

bool greaterAny64(double a, double b) {
    if (isNaN64(a) || isNaN64(b)) return false;

    if (isZero64(a) && isZero64(b)) {
        return isPosZero64(a) && isNegZero64(b);
    }

    bool aSign = isSignBitSet64(a);
    bool bSign = isSignBitSet64(b);
    if (aSign != bSign) {
        return bSign;
    }

    if (aSign) {
        return a < b;
    } else {
        return a > b;
    }
}