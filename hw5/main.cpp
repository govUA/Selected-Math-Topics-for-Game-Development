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
    std::cout << "Passed.\n\n";
    resetConsoleColor();
}

int main() {
    std::cout << "Tests:\n\n";

    {
        std::cout << "1. 3-parameter constructor\n";
        vector4 v(1.0f, 2.0f, 3.0f);
        assert(areEqual(v.x(), 1.0f));
        assert(areEqual(v.y(), 2.0f));
        assert(areEqual(v.z(), 3.0f));
        assert(areEqual(v.w(), 0.0f));
        testPassed();
    }

    {
        std::cout << "2. 4-parameter constructor\n";
        vector4 v(4.0f, 5.0f, 6.0f, 7.0f);
        assert(areEqual(v.x(), 4.0f));
        assert(areEqual(v.y(), 5.0f));
        assert(areEqual(v.z(), 6.0f));
        assert(areEqual(v.w(), 7.0f));
        testPassed();
    }

    {
        std::cout << "3. Edge case values\n";
        vector4 v(-1.5f, 0.0f, 1e10f, -1e10f);
        assert(areEqual(v.x(), -1.5f));
        assert(areEqual(v.y(), 0.0f));
        assert(areEqual(v.z(), 1e10f));
        assert(areEqual(v.w(), -1e10f));
        testPassed();
    }

    std::cout << "All tests passed.\n";
    return 0;
}