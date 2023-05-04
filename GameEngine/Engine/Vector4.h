#pragma once
#include <cmath>
#define M_PI acos(-1.0f)

class Matrix4x4;
class Vector4 {
private:
    float m_data[4];

public:

    // default constructor
    Vector4() {
        memset(m_data, 0.0f, sizeof(m_data));
    }

    // copy constructor
    Vector4(const Vector4& other) {
        memcpy(m_data, other.m_data, sizeof(m_data));
    }

    // data constructor
    Vector4(float data[4]) {
        memcpy(m_data, data, sizeof(m_data));
    }

    // value constructor
    Vector4(float x, float y, float z, float w) {
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
        m_data[3] = w;
    }

    // get component
    inline float operator[](int index) const {
        return m_data[index];
    }

    // set Component
    inline float& operator[](int index) {
        return m_data[index];
    }

    // direct assignment
    Vector4& operator=(const Vector4& other) {
        memcpy(m_data, other.m_data, sizeof(m_data));
        return *this;
    }

    // equality
    inline bool operator==(const Vector4& other) const {
        for (int i = 0; i < 4; i++) {
            if (m_data[i] != other[i])return false;
        };
        return true;
    };

    // inequality
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

    // Matrix multiplication
    inline Vector4 operator*(const Matrix4x4& other) const;

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

class Matrix4x4 {
private:
    float m_data[4][4];

public:
    // default constructor
    Matrix4x4() {
        memset(m_data, 0.0f, sizeof(m_data));
    }

    // copy constructor
    Matrix4x4(const Matrix4x4& other) {
        memcpy(m_data, other.m_data, sizeof(m_data));
    }

    // data constructor
    Matrix4x4(float data[4][4]) {
        memcpy(m_data, data, sizeof(m_data));
    }

    // get matrix elements
    inline float get(int row, int col) const {
        return m_data[row][col];
    }

    // set matrix elements
    inline void set(int row, int col, float value) {
        m_data[row][col] = value;
    }

    // direct assignment
    Matrix4x4& operator=(const Matrix4x4& other) {
        memcpy(m_data, other.m_data, sizeof(m_data));
        return *this;
    }

    // equality
    inline bool operator==(const Matrix4x4& other) const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (m_data[i][j] != other.get(i, j))return false;
            }
        };
        return true;
    };

    // inequality
    inline bool operator!=(const Matrix4x4& other) const {
        return !(*this == other);
    };

    // matrix addition 
    inline Matrix4x4 operator+(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m_data[i][j] = m_data[i][j] + other.m_data[i][j];
            }
        }
        return result;
    }

    // matrix subtraction
    inline Matrix4x4 operator-(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m_data[i][j] = m_data[i][j] - other.m_data[i][j];
            }
        }
        return result;
    }

    // scalar multiplication
    inline Matrix4x4 operator*(float scalar) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m_data[i][j] = m_data[i][j] * scalar;
            }
        }
        return result;
    }

    // matrix multiplication
    inline Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m_data[i][j] = 0.0f;
                for (int k = 0; k < 4; k++) {
                    result.m_data[i][j] += m_data[i][k] * other.m_data[k][j];
                }
            }
        }
        return result;
    }

    // vector multiplication
    inline Vector4 operator*(const Vector4& vec) const {
        Vector4 result;
        for (int i = 0; i < 4; i++) {
            result[i] = 0.0f;
            for (int j = 0; j < 4; j++) {
                result[i] += m_data[i][j] * vec[j];
            }
        }
        return result;
    }

    // matrix transpose
    inline Matrix4x4 Transpose() const {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m_data[i][j] = m_data[j][i];
            }
        }
        return result;
    }

    inline Matrix4x4 Inverse() const {
        float temp[8][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[i][j] = get(i, j);
                temp[i + 4][j] = (i == j) ? 1.0f : 0.0f;
            }
        }

        for (int i = 0; i < 4; i++) {
            float diag = temp[i][i];
            if (diag == 0.0f) {
                //The Matrix cannot be inversed, return a zero matrix
                return Matrix4x4();
            }

            for (int j = 0; j < 8; j++) {
                temp[j][i] /= diag;
            }

            for (int j = 0; j < 4; j++) {
                if (i != j) {
                    float ratio = temp[i][j];
                    for (int k = 0; k < 8; k++) {
                        temp[k][j] -= temp[k][i] * ratio;
                    }
                }
            }
        }

        Matrix4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.set(i, j, temp[i + 4][j]);
            }
        }

        return result;
    }

    inline static Matrix4x4 Identity() {
        float data[4][4] = {
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        return Matrix4x4(data);
    }

    inline static Matrix4x4 Translation(float tx, float ty, float tz) {
        float data[4][4] = {
            { 1.0f, 0.0f, 0.0f, tx },
            { 0.0f, 1.0f, 0.0f, ty },
            { 0.0f, 0.0f, 1.0f, tz },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        return Matrix4x4(data);
    }

    inline static Matrix4x4 Rotation(float angle, float x, float y, float z) {
        float rad = angle * M_PI / 180.0f;
        float c = cos(rad);
        float s = sin(rad);
        float mag = sqrt(x * x + y * y + z * z);
        x /= mag;
        y /= mag;
        z /= mag;

        float data[4][4] = {
            { x * x * (1 - c) + c,     x * y * (1 - c) - z * s, x * z * (1 - c) + y * s, 0.0f },
            { x * y * (1 - c) + z * s, y * y * (1 - c) + c,     y * z * (1 - c) - x * s, 0.0f },
            { x * z * (1 - c) - y * s, y * z * (1 - c) + x * s, z * z * (1 - c) + c,     0.0f },
            { 0.0f,                    0.0f,                    0.0f,                    1.0f }
        };
        return Matrix4x4(data);
    }

    inline static Matrix4x4 RotationX(float angle) {
        return Rotation(angle, 1.0f, 0.0f, 0.0f);
    }

    inline static Matrix4x4 RotationY(float angle) {
        return Rotation(angle, 0.0f, 1.0f, 0.0f);
    }

    inline static Matrix4x4 RotationZ(float angle) {
        return Rotation(angle, 0.0f, 0.0f, 1.0f);
    }

    inline static Matrix4x4 Scaling(float sx, float sy, float sz) {
        float data[4][4] = {
            { sx,   0.0f, 0.0f, 0.0f },
            { 0.0f, sy,   0.0f, 0.0f },
            { 0.0f, 0.0f, sz,   0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        return Matrix4x4(data);
    }

    inline static bool UnitTest() {
        float data[4][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };
        Matrix4x4 mat1(data);

        bool bReturn = true;
       
        // test get and set functions
        bReturn &= (mat1.get(0, 0) == 1);
        bReturn &= (mat1.get(3, 3) == 16);
        mat1.set(0, 0, 100);
        bReturn &= (mat1.get(0, 0) == 100);

        // test copy constructor
        Matrix4x4 mat2(mat1);
        bReturn &= (mat2 == mat1);
        mat2.set(0, 0, 200);
        bReturn &= (mat2 != mat1);

        // test assignment operator
        Matrix4x4 mat3;
        mat3 = mat2;
        bReturn &= (mat3 == mat2);
        mat3.set(0, 0, 300);
        bReturn &= (mat3 != mat2);

        // test matrix addition
        Matrix4x4 mat4 = mat1 + mat2;
        bReturn &= (mat4.get(0, 0) == 300);
        bReturn &= (mat4.get(1, 1) == 12);

        // test matrix subtraction
        Matrix4x4 mat5 = mat4 - mat2;
        bReturn &= (mat5 == mat1);

        // test scalar multiplication
        Matrix4x4 mat6 = mat5 * 2.0f;
        bReturn &= (mat6.get(0, 0) == 200);
        bReturn &= (mat6.get(3, 3) == 32);

        // test matrix multiplication
        float data2[4][4] = { {2,0,0,0},{0,2,0,0},{0,0,2,0},{0,0,0,2} };
        Matrix4x4 mat7(data2);
        Matrix4x4 mat8 = mat6 * mat7;
        bReturn &= (mat8.get(0, 0) == 400);
        bReturn &= (mat8.get(3, 3) == 64);

        // test vector multiplication (col)
        float data3[4] = { 1,2,3,4 };
        Vector4 vec(data3);
        Vector4 result = mat8 * vec;
        bReturn &= (result[0] == 516);
        bReturn &= (result[1] == 280);
        bReturn &= (result[2] == 440);
        bReturn &= (result[3] == 600);

        // test vector multiplication (row)
        float data4[4] = { 1, 2, 3, 4 };
        Vector4 vec2(data4);
        Vector4 result2 = vec2 * mat8;
        bReturn &= (result2[0] == 756);
        bReturn &= (result2[1] == 400);
        bReturn &= (result2[2] == 440);
        bReturn &= (result2[3] == 480);
      
        // test matrix transpose
        Matrix4x4 mat9 = mat8.Transpose();
        bReturn &= (mat9.get(1, 0) == 8);
        bReturn &= (mat9.get(3, 2) == 48);

        // test matrix inverse
        float data5[4][4] = { {1,0,0,0},{0,1,-1,0},{0,1,1,0},{0,0,0,1} };
        Matrix4x4 mat10(data5);
        Matrix4x4 mat11 = mat10.Inverse();
        bReturn &= (mat11.get(1, 1) == 0.5f);
        bReturn &= (mat11.get(2, 1) == -0.5f);

        return bReturn;
    }
};

inline Vector4 Vector4::operator*(const Matrix4x4& other) const {
    Vector4 result;
    for (int i = 0; i < 4; i++) {
        result[i] = 0.0f;
        for (int j = 0; j < 4; j++) {
            result[i] += other.get(j, i) * m_data[j];
        }
    }
    return result;
}