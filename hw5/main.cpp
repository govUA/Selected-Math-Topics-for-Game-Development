#include <cassert>
#include <cmath>
#include <iostream>
#include <immintrin.h>
#include <windows.h>

struct vector4 {
private:
    __m128 data;

public:
    vector4(float x, float y, float z) {
        data = _mm_set_ps(0.0f, z, y, x);
    }

    vector4(float x, float y, float z, float w) {
        data = _mm_set_ps(w, z, y, x);
    }

    float x() const {
        return _mm_cvtss_f32(data);
    }

    float y() const {
        return _mm_cvtss_f32(_mm_shuffle_ps(data, data, _MM_SHUFFLE(1, 1, 1, 1)));
    }

    float z() const {
        return _mm_cvtss_f32(_mm_shuffle_ps(data, data, _MM_SHUFFLE(2, 2, 2, 2)));
    }

    float w() const {
        return _mm_cvtss_f32(_mm_shuffle_ps(data, data, _MM_SHUFFLE(3, 3, 3, 3)));
    }

    vector4 &add(const vector4 &other) {
        data = _mm_add_ps(data, other.data);
        return *this;
    }

    vector4 &add(float x, float y, float z) {
        __m128 temp = _mm_set_ps(0.0f, z, y, x);
        data = _mm_add_ps(data, temp);
        return *this;
    }

    vector4 &sub(const vector4 &other) {
        data = _mm_sub_ps(data, other.data);
        return *this;
    }

    vector4 &sub(float x, float y, float z) {
        __m128 temp = _mm_set_ps(0.0f, z, y, x);
        data = _mm_sub_ps(data, temp);
        return *this;
    }

    vector4 &mul(float scale) {
        __m128 scale_vec = _mm_set1_ps(scale);
        data = _mm_mul_ps(data, scale_vec);
        return *this;
    }

    vector4 &mul(float scale, float w_scale) {
        __m128 scale_vec = _mm_set_ps(w_scale, scale, scale, scale);
        data = _mm_mul_ps(data, scale_vec);
        return *this;
    }

    vector4 &div(float scale) {
        __m128 scale_vec = _mm_set1_ps(scale);
        data = _mm_div_ps(data, scale_vec);
        return *this;
    }

    vector4 &div(float scale, float w_scale) {
        __m128 scale_vec = _mm_set_ps(w_scale, scale, scale, scale);
        data = _mm_div_ps(data, scale_vec);
        return *this;
    }

    float dot(const vector4 &other) const {
        __m128 mul = _mm_mul_ps(data, other.data);
        __m128 shuf = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1));
        __m128 sums = _mm_add_ps(mul, shuf);
        shuf = _mm_movehl_ps(shuf, sums);
        sums = _mm_add_ss(sums, shuf);
        return _mm_cvtss_f32(sums);
    }

    float dot(float x, float y, float z) const {
        __m128 temp = _mm_set_ps(0.0f, z, y, x);
        __m128 mul = _mm_mul_ps(data, temp);
        __m128 shuf = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1));
        __m128 sums = _mm_add_ps(mul, shuf);
        shuf = _mm_movehl_ps(shuf, sums);
        sums = _mm_add_ss(sums, shuf);
        return _mm_cvtss_f32(sums);
    }

    float magnitude_square() const {
        return dot(*this);
    }

    float magnitude() const {
        return std::sqrt(magnitude_square());
    }
};

bool areEqual(float a, float b, float epsilon = 1e-6f) {
    return std::fabs(a - b) < epsilon;
}

void setConsoleColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetConsoleColor() {
    setConsoleColor(7);
}

void testPassed() {
    setConsoleColor(10);
    std::cout << "\tPassed.\n\n";
    resetConsoleColor();
}

void allTestsPassed(const std::string &group) {
    setConsoleColor(10);
    std::cout << "\tAll " << group << "tests passed.\n\n";
    resetConsoleColor();
}

int main() {
    std::cout << "TESTS:\n\n";

    {
        std::cout << "1. Struct base tests:\n\n";
        {
            std::cout << "\t1. 3-parameter constructor:\n";
            vector4 v(1.0f, 2.0f, 3.0f);
            assert(areEqual(v.x(), 1.0f));
            assert(areEqual(v.y(), 2.0f));
            assert(areEqual(v.z(), 3.0f));
            assert(areEqual(v.w(), 0.0f));
            testPassed();
        }

        {
            std::cout << "\t2. 4-parameter constructor:\n";
            vector4 v(4.0f, 5.0f, 6.0f, 7.0f);
            assert(areEqual(v.x(), 4.0f));
            assert(areEqual(v.y(), 5.0f));
            assert(areEqual(v.z(), 6.0f));
            assert(areEqual(v.w(), 7.0f));
            testPassed();
        }

        {
            std::cout << "\t3. Edge case values:\n";
            vector4 v(-1.5f, 0.0f, 1e10f, -1e10f);
            assert(areEqual(v.x(), -1.5f));
            assert(areEqual(v.y(), 0.0f));
            assert(areEqual(v.z(), 1e10f));
            assert(areEqual(v.w(), -1e10f));
            testPassed();
        }

        allTestsPassed("struct base ");
    }

    {
        std::cout << "2. Addition/subtraction tests:\n\n";
        {
            std::cout << "\t1. Vector addition:\n";
            vector4 a(1.0f, 2.0f, 3.0f);
            vector4 b(4.0f, 5.0f, 6.0f);
            a.add(b);
            assert(areEqual(a.x(), 5.0f));
            assert(areEqual(a.y(), 7.0f));
            assert(areEqual(a.z(), 9.0f));
            assert(areEqual(a.w(), 0.0f));
            testPassed();
        }

        {
            std::cout << "\t2. Vector-value addition:\n";
            vector4 v(1.0f, 2.0f, 3.0f);
            v.add(10.0f, 20.0f, 30.0f);
            assert(areEqual(v.x(), 11.0f));
            assert(areEqual(v.y(), 22.0f));
            assert(areEqual(v.z(), 33.0f));
            assert(areEqual(v.w(), 0.0f));
            testPassed();
        }

        {
            std::cout << "\t3. Vector subtraction:\n";
            vector4 a(10.0f, 20.0f, 30.0f);
            vector4 b(1.0f, 2.0f, 3.0f);
            a.sub(b);
            assert(areEqual(a.x(), 9.0f));
            assert(areEqual(a.y(), 18.0f));
            assert(areEqual(a.z(), 27.0f));
            assert(areEqual(a.w(), 0.0f));
            testPassed();
        }

        {
            std::cout << "\t4. Vector-value subtraction:\n";
            vector4 v(5.0f, 10.0f, 15.0f);
            v.sub(1.0f, 2.0f, 3.0f);
            assert(areEqual(v.x(), 4.0f));
            assert(areEqual(v.y(), 8.0f));
            assert(areEqual(v.z(), 12.0f));
            assert(areEqual(v.w(), 0.0f));
            testPassed();
        }
        allTestsPassed("addition/subtraction ");
    }

    {
        std::cout << "3. Multiplication/division tests:\n\n";
        {
            std::cout << "\t1. Multiply by scalar:\n";
            vector4 v(2.0f, 3.0f, 4.0f, 5.0f);
            v.mul(2.0f);
            assert(areEqual(v.x(), 4.0f));
            assert(areEqual(v.y(), 6.0f));
            assert(areEqual(v.z(), 8.0f));
            assert(areEqual(v.w(), 10.0f));
            testPassed();
        }

        {
            std::cout << "\t2. Multiply by scalar with scale:\n";
            vector4 v(2.0f, 3.0f, 4.0f, 5.0f);
            v.mul(3.0f, 2.0f);
            assert(areEqual(v.x(), 6.0f));
            assert(areEqual(v.y(), 9.0f));
            assert(areEqual(v.z(), 12.0f));
            assert(areEqual(v.w(), 10.0f));
            testPassed();
        }

        {
            std::cout << "\t3. Divide by scalar:\n";
            vector4 v(4.0f, 6.0f, 8.0f, 10.0f);
            v.div(2.0f);
            assert(areEqual(v.x(), 2.0f));
            assert(areEqual(v.y(), 3.0f));
            assert(areEqual(v.z(), 4.0f));
            assert(areEqual(v.w(), 5.0f));
            testPassed();
        }

        {
            std::cout << "\t4. Divide by scalar with scale:\n";
            vector4 v(6.0f, 9.0f, 12.0f, 10.0f);
            v.div(3.0f, 2.0f);
            assert(areEqual(v.x(), 2.0f));
            assert(areEqual(v.y(), 3.0f));
            assert(areEqual(v.z(), 4.0f));
            assert(areEqual(v.w(), 5.0f));
            testPassed();
        }
        allTestsPassed("multiplication/division ");
    }

    {
        std::cout << "4. Dot tests:\n\n";
        {
            std::cout << "\t1. Dot vector:\n";
            vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
            vector4 b(4.0f, 5.0f, 6.0f, 7.0f);
            float result = a.dot(b);
            assert(areEqual(result, 60.0f));
            testPassed();
        }

        {
            std::cout << "\t2. Dot value:\n";
            vector4 a(1.0f, 2.0f, 3.0f, 10.0f);
            float result = a.dot(4.0f, 5.0f, 6.0f);
            assert(areEqual(result, 32.0f));
            testPassed();
        }

        {
            std::cout << "\t3. Dot zero:\n";
            vector4 a(0.0f, 0.0f, 0.0f, 0.0f);
            vector4 b(1.0f, 2.0f, 3.0f, 4.0f);
            float result = a.dot(b);
            assert(areEqual(result, 0.0f));
            testPassed();
        }
        allTestsPassed("dot ");
    }

    {
        std::cout << "5. Magnitude tests:\n\n";
        {
            std::cout << "\t1. Magnitude and magnitude squared:\n";
            vector4 v(3.0f, 4.0f, 0.0f, 0.0f);
            float expectedMagSq = 25.0f;
            float expectedMag = 5.0f;

            assert(areEqual(v.magnitude_square(), expectedMagSq));
            assert(areEqual(v.magnitude(), expectedMag));
            testPassed();
        }

        {
            std::cout << "\t2. Magnitude with non-zero w:\n";
            vector4 v(1.0f, 2.0f, 2.0f, 3.0f);
            assert(areEqual(v.magnitude_square(), 18.0f));
            assert(areEqual(v.magnitude(), std::sqrt(18.0f)));
            testPassed();
        }

        {
            std::cout << "\t3. Zero-vector magnitude:\n";
            vector4 v(0.0f, 0.0f, 0.0f, 0.0f);
            assert(areEqual(v.magnitude_square(), 0.0f));
            assert(areEqual(v.magnitude(), 0.0f));
            testPassed();
        }

        {
            std::cout << "\t4. Negative-value vector magnitude:\n";
            vector4 v(-5.0f, 0.0f, 1.0f, 0.0f);
            assert(areEqual(v.magnitude_square(), 26.0f));
            assert(areEqual(v.magnitude(), std::sqrt(26.0f)));
            testPassed();
        }
        allTestsPassed("magnitude ");
    }

    std::cout << "ALL TESTS PASSED.\n";
    return 0;
}