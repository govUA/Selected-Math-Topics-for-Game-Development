#include "infinity.h"
#include "zero.h"
#include "normals.h"

enum class ExpressionClass {
    _NAN,
    _INFINITE,
    _ZERO,
    _SUBNORMAL,
    _NORMAL
};

ExpressionClass fpClassify32(float value) {
    if (isNaN32(value)) return ExpressionClass::_NAN;
    if (isInf32(value)) return ExpressionClass::_INFINITE;
    if (isZero32(value)) return ExpressionClass::_ZERO;
    if (isSubnormal32(value)) return ExpressionClass::_SUBNORMAL;
    return ExpressionClass::_NORMAL;
}

ExpressionClass fpClassify64(double value) {
    if (isNaN64(value)) return ExpressionClass::_NAN;
    if (isInf64(value)) return ExpressionClass::_INFINITE;
    if (isZero64(value)) return ExpressionClass::_ZERO;
    if (isSubnormal64(value)) return ExpressionClass::_SUBNORMAL;
    return ExpressionClass::_NORMAL;
}