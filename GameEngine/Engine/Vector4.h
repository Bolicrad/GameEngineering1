#pragma once
#include <cmath>
class Vector4 {
private:
    float m_data[4];

public:
    Vector4() {
        for (int i = 0; i < 4; i++) {
            m_data[i] = 0.0f;
        }
    }

    Vector4(float x, float y, float z, float w) {
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
        m_data[3] = w;
    }

    // Get component
    inline float operator[](int index) const {
        return m_data[index];
    }

    // Set Component
    inline float& operator[](int index) {
        return m_data[index];
    }

    //equality
    inline bool operator==(const Vector4& other) const {
        for (int i = 0; i < 4; i++) {
            if (m_data[i] != other[i])return false;
        };
        return true;
    };

    //inequality
    inline bool operator!=(const Vector4& other) const {
        for (int i = 0; i < 4; i++) {
            if (m_data[i] == other[i])return false;
        };
        return true;
    };

    // addition
    inline Vector4 operator+(const Vector4& other) const {
        Vector4 result;
        for (int i = 0; i < 4; i++) {
            result.m_data[i] = m_data[i] + other.m_data[i];
        }
        return result;
    }

    // subtraction
    inline Vector4 operator-(const Vector4& other) const {
        Vector4 result;
        for (int i = 0; i < 4; i++) {
            result.m_data[i] = m_data[i] - other.m_data[i];
        }
        return result;
    }

    // negation
    inline Vector4 operator-() const {
        Vector4 result;
        for (int i = 0; i < 4; i++) {
            result.m_data[i] = -m_data[i];
        }
        return result;
    }

    // scalar multiplication
    inline Vector4 operator*(float scalar) const {
        Vector4 result;
        for (int i = 0; i < 4; i++) {
            result.m_data[i] = m_data[i] * scalar;
        }
        return result;
    }

    // scalar division
    inline Vector4 operator/(float scalar) const {
        Vector4 result;
        for (int i = 0; i < 4; i++) {
            result.m_data[i] = m_data[i] / scalar;
        }
        return result;
    }

    // dot product
    inline float operator*(const Vector4& other) const {
        float result = 0.0f;
        for (int i = 0; i < 4; i++) {
            result += m_data[i] * other.m_data[i];
        }
        return result;
    }

    // length
    inline float length() const {
        return sqrtf(m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2] + m_data[3] * m_data[3]);
    }

    // normalization
    inline void normalize() {
        float len = length();
        if (len != 0.0f) {
            m_data[0] /= len;
            m_data[1] /= len;
            m_data[2] /= len;
            m_data[3] /= len;
        }
    }

    static bool UnitTest() {
        Vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 v2(2.0f, 3.0f, 4.0f, 5.0f);

        bool bReturn = true;

        // Test constructor
        bReturn &= v1[0] == 1.0f;
        bReturn &= v1[1] == 2.0f;
        bReturn &= v1[2] == 3.0f;
        bReturn &= v1[3] == 4.0f;

        // Test equality
        bReturn &= v1 == Vector4(1.0f, 2.0f, 3.0f, 4.0f);

        // Test inequality
        bReturn &= v1 != v2;

        // Test addition
        Vector4 result = v1 + v2;
        bReturn &= result[0] == 3.0f;
        bReturn &= result[1] == 5.0f;
        bReturn &= result[2] == 7.0f;
        bReturn &= result[3] == 9.0f;

        // Test subtraction
        result = v1 - v2;
        bReturn &= result[0] == -1.0f;
        bReturn &= result[1] == -1.0f;
        bReturn &= result[2] == -1.0f;
        bReturn &= result[3] == -1.0f;

        // Test negation
        result = -v1;
        bReturn &= result[0] == -1.0f;
        bReturn &= result[1] == -2.0f;
        bReturn &= result[2] == -3.0f;
        bReturn &= result[3] == -4.0f;

        // Test scalar multiplication
        result = v1 * 2.0f;
        bReturn &= result[0] == 2.0f;
        bReturn &= result[1] == 4.0f;
        bReturn &= result[2] == 6.0f;
        bReturn &= result[3] == 8.0f;

        // Test scalar division
        result = v1 / 2.0f;
        bReturn &= result[0] == 0.5f;
        bReturn &= result[1] == 1.0f;
        bReturn &= result[2] == 1.5f;
        bReturn &= result[3] == 2.0f;

        // Test dot product
        float dot = v1 * v2;
        bReturn &= dot == 40.0f;

        // Test length calculation
        bReturn &= abs(v1.length() - 5.4772f) < 0.0001f;
        bReturn &= abs(v2.length() - 7.3485f) < 0.0001f;

        // Test vector normalization
        v1.normalize();
        v2.normalize();

        bReturn &= abs(v1[0] - 0.1826f) < 0.0001f;
        bReturn &= abs(v1[1] - 0.3651f) < 0.0001f;
        bReturn &= abs(v1[2] - 0.5477f) < 0.0001f;
        bReturn &= abs(v1[3] - 0.7303f) < 0.0001f;

        bReturn &= abs(v2[0] - 0.2722f) < 0.0001f;
        bReturn &= abs(v2[1] - 0.4083f) < 0.0001f;
        bReturn &= abs(v2[2] - 0.5444f) < 0.0001f;
        bReturn &= abs(v2[3] - 0.6805f) < 0.0001f;

        return bReturn;
    }
};