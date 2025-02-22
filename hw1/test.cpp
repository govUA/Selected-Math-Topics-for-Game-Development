#include <gtest/gtest.h>
#include <cmath>
#include <cfloat>
#include "compare.h"

TEST(FloatConversionTest, Float32ToBits) {
    EXPECT_EQ(float32ToBits(3.14f), 1078523331);
    EXPECT_EQ(float32ToBits(0.0f), 0);
    EXPECT_EQ(float32ToBits(-0.0f), 0x80000000);
    EXPECT_EQ(float32ToBits(INFINITY), 0x7F800000);
    EXPECT_EQ(float32ToBits(-INFINITY), 0xFF800000);
    EXPECT_NE(float32ToBits(NAN) & 0x7F800000, 0);
    EXPECT_NE(float32ToBits(NAN) & 0x007FFFFF, 0);
}

TEST(FloatConversionTest, Float64ToBits) {
    EXPECT_EQ(float64ToBits(3.141592), 4614256655080292474);
    EXPECT_EQ(float64ToBits(0.0), 0);
    EXPECT_EQ(float64ToBits(-0.0), 0x8000000000000000);
    EXPECT_EQ(float64ToBits(INFINITY), 0x7FF0000000000000);
    EXPECT_EQ(float64ToBits(-INFINITY), 0xFFF0000000000000);
    EXPECT_NE(float64ToBits(NAN) & 0x7FF0000000000000, 0);
    EXPECT_NE(float64ToBits(NAN) & 0x000FFFFFFFFFFFFF, 0);
}

TEST(FloatConversionTest, BitsToFloat32) {
    EXPECT_FLOAT_EQ(bitsToFloat32(1078523331), 3.14f);
    EXPECT_FLOAT_EQ(bitsToFloat32(0), 0.0f);
    EXPECT_TRUE(std::signbit(bitsToFloat32(0x80000000)));
    EXPECT_EQ(bitsToFloat32(0x7F800000), INFINITY);
    EXPECT_EQ(bitsToFloat32(0xFF800000), -INFINITY);
    EXPECT_TRUE(std::isnan(bitsToFloat32(0x7F800001)));
}

TEST(FloatConversionTest, BitsToFloat64) {
    EXPECT_DOUBLE_EQ(bitsToFloat64(4614256655080292474), 3.141592);
    EXPECT_DOUBLE_EQ(bitsToFloat64(0), 0.0);
    EXPECT_TRUE(std::signbit(bitsToFloat64(0x8000000000000000)));
    EXPECT_EQ(bitsToFloat64(0x7FF0000000000000), INFINITY);
    EXPECT_EQ(bitsToFloat64(0xFFF0000000000000), -INFINITY);
    EXPECT_TRUE(std::isnan(bitsToFloat64(0x7FF0000000000001)));
}

TEST(FloatClassificationTest, IsFinite) {
    EXPECT_TRUE(isFinite32(3.14f));
    EXPECT_TRUE(isFinite32(0.0f));
    EXPECT_TRUE(isFinite32(-1000000.0f));
    EXPECT_FALSE(isFinite32(INFINITY));
    EXPECT_FALSE(isFinite32(-INFINITY));
    EXPECT_FALSE(isFinite32(NAN));

    EXPECT_TRUE(isFinite64(9.11));
    EXPECT_TRUE(isFinite64(0.0));
    EXPECT_TRUE(isFinite64(-DBL_MAX));
    EXPECT_FALSE(isFinite64(INFINITY));
    EXPECT_FALSE(isFinite64(-INFINITY));
    EXPECT_FALSE(isFinite64(NAN));
}

TEST(FloatClassificationTest, IsInf) {
    EXPECT_FALSE(isInf32(3.14f));
    EXPECT_FALSE(isInf32(0.0f));
    EXPECT_TRUE(isInf32(INFINITY));
    EXPECT_TRUE(isInf32(-INFINITY));
    EXPECT_FALSE(isInf32(NAN));

    EXPECT_FALSE(isInf64(9.11));
    EXPECT_FALSE(isInf64(0.0));
    EXPECT_TRUE(isInf64(INFINITY));
    EXPECT_TRUE(isInf64(-INFINITY));
    EXPECT_FALSE(isInf64(NAN));
}

TEST(FloatClassificationTest, IsPosInf) {
    EXPECT_FALSE(isPosInf32(3.14f));
    EXPECT_FALSE(isPosInf32(0.0f));
    EXPECT_TRUE(isPosInf32(INFINITY));
    EXPECT_FALSE(isPosInf32(-INFINITY));
    EXPECT_FALSE(isPosInf32(NAN));

    EXPECT_FALSE(isPosInf64(9.11));
    EXPECT_FALSE(isPosInf64(0.0));
    EXPECT_TRUE(isPosInf64(INFINITY));
    EXPECT_FALSE(isPosInf64(-INFINITY));
    EXPECT_FALSE(isPosInf64(NAN));
}

TEST(FloatClassificationTest, IsNegInf) {
    EXPECT_FALSE(isNegInf32(3.14f));
    EXPECT_FALSE(isNegInf32(0.0f));
    EXPECT_FALSE(isNegInf32(INFINITY));
    EXPECT_TRUE(isNegInf32(-INFINITY));
    EXPECT_FALSE(isNegInf32(NAN));

    EXPECT_FALSE(isNegInf64(9.11));
    EXPECT_FALSE(isNegInf64(0.0));
    EXPECT_FALSE(isNegInf64(INFINITY));
    EXPECT_TRUE(isNegInf64(-INFINITY));
    EXPECT_FALSE(isNegInf64(NAN));
}

TEST(FloatClassificationTest, IsZero) {
    EXPECT_FALSE(isZero32(3.14f));
    EXPECT_TRUE(isZero32(0.0f));
    EXPECT_TRUE(isZero32(-0.0f));
    EXPECT_FALSE(isZero32(INFINITY));
    EXPECT_FALSE(isZero32(NAN));

    EXPECT_FALSE(isZero64(9.11));
    EXPECT_TRUE(isZero64(0.0));
    EXPECT_TRUE(isZero64(-0.0));
    EXPECT_FALSE(isZero64(INFINITY));
    EXPECT_FALSE(isZero64(NAN));
}

TEST(FloatClassificationTest, IsPosZero) {
    EXPECT_FALSE(isPosZero32(3.14f));
    EXPECT_TRUE(isPosZero32(0.0f));
    EXPECT_FALSE(isPosZero32(-0.0f));
    EXPECT_FALSE(isPosZero32(INFINITY));
    EXPECT_FALSE(isPosZero32(NAN));

    EXPECT_FALSE(isPosZero64(9.11));
    EXPECT_TRUE(isPosZero64(0.0));
    EXPECT_FALSE(isPosZero64(-0.0));
    EXPECT_FALSE(isPosZero64(INFINITY));
    EXPECT_FALSE(isPosZero64(NAN));
}

TEST(FloatClassificationTest, IsNegZero) {
    EXPECT_FALSE(isNegZero32(3.14f));
    EXPECT_FALSE(isNegZero32(0.0f));
    EXPECT_TRUE(isNegZero32(-0.0f));
    EXPECT_FALSE(isNegZero32(INFINITY));
    EXPECT_FALSE(isNegZero32(NAN));

    EXPECT_FALSE(isNegZero64(9.11));
    EXPECT_FALSE(isNegZero64(0.0));
    EXPECT_TRUE(isNegZero64(-0.0));
    EXPECT_FALSE(isNegZero64(INFINITY));
    EXPECT_FALSE(isNegZero64(NAN));
}

TEST(FloatClassificationTest, IsNaN) {
    EXPECT_FALSE(isNaN32(3.14f));
    EXPECT_FALSE(isNaN32(0.0f));
    EXPECT_FALSE(isNaN32(INFINITY));
    EXPECT_FALSE(isNaN32(-INFINITY));
    EXPECT_TRUE(isNaN32(NAN));
    EXPECT_TRUE(isNaN32(0.0f / 0.0f));

    EXPECT_FALSE(isNaN64(9.11));
    EXPECT_FALSE(isNaN64(0.0));
    EXPECT_FALSE(isNaN64(INFINITY));
    EXPECT_FALSE(isNaN64(-INFINITY));
    EXPECT_TRUE(isNaN64(NAN));
    EXPECT_TRUE(isNaN64(0.0 / 0.0));
}

TEST(FloatClassificationTest, IsNormal) {
    EXPECT_TRUE(isNormal32(3.14f));
    EXPECT_FALSE(isNormal32(0.0f));
    EXPECT_FALSE(isNormal32(FLT_MIN / 2));
    EXPECT_FALSE(isNormal32(INFINITY));
    EXPECT_FALSE(isNormal32(NAN));

    EXPECT_TRUE(isNormal64(1.05));
    EXPECT_FALSE(isNormal64(0.0));
    EXPECT_FALSE(isNormal64(DBL_MIN / 2));
    EXPECT_FALSE(isNormal64(INFINITY));
    EXPECT_FALSE(isNormal64(NAN));
}

TEST(FloatClassificationTest, IsSubnormal) {
    EXPECT_FALSE(isSubnormal32(3.14f));
    EXPECT_FALSE(isSubnormal32(0.0f));
    EXPECT_TRUE(isSubnormal32(FLT_MIN / 2));
    EXPECT_FALSE(isSubnormal32(FLT_MIN));
    EXPECT_FALSE(isSubnormal32(INFINITY));
    EXPECT_FALSE(isSubnormal32(NAN));

    EXPECT_FALSE(isSubnormal64(1.05));
    EXPECT_FALSE(isSubnormal64(0.0));
    EXPECT_TRUE(isSubnormal64(DBL_MIN / 2));
    EXPECT_FALSE(isSubnormal64(DBL_MIN));
    EXPECT_FALSE(isSubnormal64(INFINITY));
    EXPECT_FALSE(isSubnormal64(NAN));
}

TEST(FloatClassificationTest, IsSignBitSet) {
    EXPECT_FALSE(isSignBitSet32(3.14f));
    EXPECT_FALSE(isSignBitSet32(0.0f));
    EXPECT_TRUE(isSignBitSet32(-0.0f));
    EXPECT_TRUE(isSignBitSet32(-3.14f));
    EXPECT_TRUE(isSignBitSet32(-INFINITY));
    EXPECT_FALSE(isSignBitSet32(INFINITY));

    EXPECT_FALSE(isSignBitSet64(9.11));
    EXPECT_FALSE(isSignBitSet64(0.0));
    EXPECT_TRUE(isSignBitSet64(-0.0));
    EXPECT_TRUE(isSignBitSet64(-9.11));
    EXPECT_TRUE(isSignBitSet64(-INFINITY));
    EXPECT_FALSE(isSignBitSet64(INFINITY));
}

TEST(FloatOperationsTest, Abs) {
    EXPECT_FLOAT_EQ(abs32(3.14f), 3.14f);
    EXPECT_FLOAT_EQ(abs32(-3.14f), 3.14f);
    EXPECT_FLOAT_EQ(abs32(0.0f), 0.0f);
    EXPECT_FALSE(std::signbit(abs32(-0.0f)));
    EXPECT_EQ(abs32(INFINITY), INFINITY);
    EXPECT_EQ(abs32(-INFINITY), INFINITY);
    EXPECT_TRUE(std::isnan(abs32(NAN)));

    EXPECT_DOUBLE_EQ(abs64(9.1142031415926966688), 9.1142031415926966688);
    EXPECT_DOUBLE_EQ(abs64(-9.1142031415926966688), 9.1142031415926966688);
    EXPECT_DOUBLE_EQ(abs64(0.0), 0.0);
    EXPECT_FALSE(std::signbit(abs64(-0.0)));
    EXPECT_EQ(abs64(INFINITY), INFINITY);
    EXPECT_EQ(abs64(-INFINITY), INFINITY);
    EXPECT_TRUE(std::isnan(abs64(NAN)));
}

TEST(FloatOperationsTest, Min) {
    EXPECT_FLOAT_EQ(min32(3.14f, 2.71f), 2.71f);
    EXPECT_FLOAT_EQ(min32(-3.14f, 2.71f), -3.14f);
    EXPECT_FLOAT_EQ(min32(-3.14f, -5.0f), -5.0f);
    EXPECT_EQ(min32(INFINITY, 0.0f), 0.0f);
    EXPECT_EQ(min32(-INFINITY, 0.0f), -INFINITY);
    EXPECT_FALSE(std::isnan(min32(NAN, 0.0f)));

    EXPECT_DOUBLE_EQ(min64(9.11, 3.14), 3.14);
    EXPECT_DOUBLE_EQ(min64(-9.11, 3.14), -9.11);
    EXPECT_DOUBLE_EQ(min64(-9.11, -10.0), -10.0);
    EXPECT_EQ(min64(INFINITY, 0.0), 0.0);
    EXPECT_EQ(min64(-INFINITY, 0.0), -INFINITY);
    EXPECT_FALSE(std::isnan(min64(NAN, 0.0)));
}

TEST(FloatOperationsTest, Max) {
    EXPECT_FLOAT_EQ(max32(3.14f, 2.71f), 3.14f);
    EXPECT_FLOAT_EQ(max32(-3.14f, 2.71f), 2.71f);
    EXPECT_FLOAT_EQ(max32(-3.14f, -5.0f), -3.14f);
    EXPECT_EQ(max32(INFINITY, 0.0f), INFINITY);
    EXPECT_EQ(max32(-INFINITY, 0.0f), 0.0f);
    EXPECT_FALSE(std::isnan(max32(NAN, 0.0f)));

    EXPECT_DOUBLE_EQ(max64(9.11, 3.14), 9.11);
    EXPECT_DOUBLE_EQ(max64(-9.11, 3.14), 3.14);
    EXPECT_DOUBLE_EQ(max64(-9.11, -10.0), -9.11);
    EXPECT_EQ(max64(INFINITY, 0.0), INFINITY);
    EXPECT_EQ(max64(-INFINITY, 0.0), 0.0);
    EXPECT_FALSE(std::isnan(max64(NAN, 0.0)));
}

TEST(FloatOperationsTest, Clamp) {
    EXPECT_FLOAT_EQ(clamp32(3.14f, 0.0f, 10.0f), 3.14f);
    EXPECT_FLOAT_EQ(clamp32(12.0f, 0.0f, 10.0f), 10.0f);
    EXPECT_FLOAT_EQ(clamp32(-5.0f, 0.0f, 10.0f), 0.0f);
    EXPECT_EQ(clamp32(INFINITY, 0.0f, 10.0f), 10.0f);
    EXPECT_EQ(clamp32(-INFINITY, 0.0f, 10.0f), 0.0f);
    EXPECT_FALSE(std::isnan(clamp32(NAN, 0.0f, 10.0f)));

    EXPECT_DOUBLE_EQ(clamp64(5.5, 0.0, 10.0), 5.5);
    EXPECT_DOUBLE_EQ(clamp64(15.0, 0.0, 10.0), 10.0);
    EXPECT_DOUBLE_EQ(clamp64(-5.0, 0.0, 10.0), 0.0);
    EXPECT_EQ(clamp64(INFINITY, 0.0, 10.0), 10.0);
    EXPECT_EQ(clamp64(-INFINITY, 0.0, 10.0), 0.0);
    EXPECT_FALSE(std::isnan(clamp64(NAN, 0.0, 10.0)));
}

TEST(FloatComparisonTest, EqualPrecision) {
    EXPECT_TRUE(equalPrecision32(3.14f, 3.14f, 0.001f));
    EXPECT_TRUE(equalPrecision32(3.14f, 3.141f, 0.002f));
    EXPECT_FALSE(equalPrecision32(3.14f, 3.15f, 0.001f));
    EXPECT_TRUE(equalPrecision32(INFINITY, INFINITY, 0.1f));
    EXPECT_FALSE(equalPrecision32(INFINITY, -INFINITY, 0.1f));
    EXPECT_FALSE(equalPrecision32(NAN, 0.0f, 0.1f));

    EXPECT_TRUE(equalPrecision64(3.14, 3.14, 0.001));
    EXPECT_TRUE(equalPrecision64(3.14, 3.141, 0.002));
    EXPECT_FALSE(equalPrecision64(3.14, 3.15, 0.001));
    EXPECT_TRUE(equalPrecision64(INFINITY, INFINITY, 0.1));
    EXPECT_FALSE(equalPrecision64(INFINITY, -INFINITY, 0.1));
    EXPECT_FALSE(equalPrecision64(NAN, 0.0, 0.1));
}

TEST(FloatComparisonTest, LessPrecision) {
    EXPECT_TRUE(lessPrecision32(3.0f, 3.14f, 0.1f));
    EXPECT_FALSE(lessPrecision32(3.0f, 3.05f, 0.1f));
    EXPECT_FALSE(lessPrecision32(3.2f, 3.14f, 0.1f));
    EXPECT_TRUE(lessPrecision32(-INFINITY, 0.0f, 0.1f));
    EXPECT_FALSE(lessPrecision32(INFINITY, 0.0f, 0.1f));
    EXPECT_FALSE(lessPrecision32(NAN, 0.0f, 0.1f));

    EXPECT_TRUE(lessPrecision64(3.0, 3.14, 0.1));
    EXPECT_FALSE(lessPrecision64(3.0, 3.05, 0.1));
    EXPECT_FALSE(lessPrecision64(3.2, 3.14, 0.1));
    EXPECT_TRUE(lessPrecision64(-INFINITY, 0.0, 0.1));
    EXPECT_FALSE(lessPrecision64(INFINITY, 0.0, 0.1));
    EXPECT_FALSE(lessPrecision64(NAN, 0.0, 0.1));
}

TEST(FloatComparisonTest, GreaterPrecision) {
    EXPECT_TRUE(greaterPrecision32(3.14f, 3.0f, 0.1f));
    EXPECT_FALSE(greaterPrecision32(3.05f, 3.0f, 0.1f));
    EXPECT_FALSE(greaterPrecision32(3.14f, 3.2f, 0.1f));
    EXPECT_TRUE(greaterPrecision32(0.0f, -INFINITY, 0.1f));
    EXPECT_FALSE(greaterPrecision32(0.0f, INFINITY, 0.1f));
    EXPECT_FALSE(greaterPrecision32(NAN, 0.0f, 0.1f));

    EXPECT_TRUE(greaterPrecision64(3.14, 3.0, 0.1));
    EXPECT_FALSE(greaterPrecision64(3.05, 3.0, 0.1));
    EXPECT_FALSE(greaterPrecision64(3.14, 3.2, 0.1));
    EXPECT_TRUE(greaterPrecision64(0.0, -INFINITY, 0.1));
    EXPECT_FALSE(greaterPrecision64(0.0, INFINITY, 0.1));
    EXPECT_FALSE(greaterPrecision64(NAN, 0.0, 0.1));
}

TEST(FloatComparisonTest, EqualAny) {
    EXPECT_TRUE(equalAny32(3.14f, 3.14f));
    EXPECT_FALSE(equalAny32(3.14f, 3.141f));
    EXPECT_TRUE(equalAny32(INFINITY, INFINITY));
    EXPECT_FALSE(equalAny32(INFINITY, -INFINITY));
    EXPECT_TRUE(equalAny32(NAN, NAN));

    EXPECT_TRUE(equalAny64(8.8, 8.8));
    EXPECT_TRUE(equalAny64(8.8, 8.80));
    EXPECT_FALSE(equalAny64(8.8, 8.801));
    EXPECT_TRUE(equalAny64(INFINITY, INFINITY));
    EXPECT_FALSE(equalAny64(INFINITY, -INFINITY));
    EXPECT_TRUE(equalAny64(NAN, NAN));
}

TEST(FloatComparisonTest, LessAny) {
    EXPECT_TRUE(lessAny32(3.0f, 3.14f));
    EXPECT_FALSE(lessAny32(3.14f, 3.14f));
    EXPECT_FALSE(lessAny32(3.15f, 3.14f));
    EXPECT_TRUE(lessAny32(-INFINITY, 0.0f));
    EXPECT_FALSE(lessAny32(INFINITY, 0.0f));
    EXPECT_FALSE(lessAny32(NAN, 0.0f));
    EXPECT_FALSE(lessAny32(0.0f, NAN));

    EXPECT_TRUE(lessAny64(3.0, 3.14));
    EXPECT_FALSE(lessAny64(3.14, 3.14));
    EXPECT_FALSE(lessAny64(3.15, 3.14));
    EXPECT_TRUE(lessAny64(-INFINITY, 0.0));
    EXPECT_FALSE(lessAny64(INFINITY, 0.0));
    EXPECT_FALSE(lessAny64(NAN, 0.0));
    EXPECT_FALSE(lessAny64(0.0, NAN));
}

TEST(FloatComparisonTest, GreaterAny) {
    EXPECT_TRUE(greaterAny32(3.14f, 3.0f));
    EXPECT_FALSE(greaterAny32(3.14f, 3.14f));
    EXPECT_FALSE(greaterAny32(3.14f, 3.15f));
    EXPECT_TRUE(greaterAny32(0.0f, -INFINITY));
    EXPECT_FALSE(greaterAny32(0.0f, INFINITY));
    EXPECT_FALSE(greaterAny32(NAN, 0.0f));
    EXPECT_FALSE(greaterAny32(0.0f, NAN));

    EXPECT_TRUE(greaterAny64(3.14, 3.0));
    EXPECT_FALSE(greaterAny64(3.14, 3.14));
    EXPECT_FALSE(greaterAny64(3.14, 3.15));
    EXPECT_TRUE(greaterAny64(0.0, -INFINITY));
    EXPECT_FALSE(greaterAny64(0.0, INFINITY));
    EXPECT_FALSE(greaterAny64(NAN, 0.0));
    EXPECT_FALSE(greaterAny64(0.0, NAN));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}