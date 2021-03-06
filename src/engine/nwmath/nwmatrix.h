/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2016 NEWorld Team
*
* This file is part of NEWorld.
* NEWorld is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* NEWorld is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with NEWorld.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef M_PI
#define M_PI 3.141592653589793
#endif // !M_PI


template <typename T>
class Mat4
{
public:
    T data[16];

    Mat4()
    {
        memset(data, 0, sizeof(data));
    }

    Mat4(const Mat4& rhs)
    {
        memcpy(data, rhs.data, sizeof(data));
    }

    explicit Mat4(T x)
    {
        memset(data, 0, sizeof(data));
        data[0] = data[5] = data[10] = data[15] = x; // Identity matrix
    }

    explicit Mat4(T* src)
    {
        memcpy(data, src, sizeof(data));
    }

    T* operator[](size_t index)
    {
        return data + index * 4;
    }

    Mat4 operator*(const Mat4& rhs) const
    {
        Mat4 res;
        res.data[0] = data[0] * rhs.data[0] + data[1] * rhs.data[4] + data[2] * rhs.data[8] + data[3] * rhs.data[12];
        res.data[1] = data[0] * rhs.data[1] + data[1] * rhs.data[5] + data[2] * rhs.data[9] + data[3] * rhs.data[13];
        res.data[2] = data[0] * rhs.data[2] + data[1] * rhs.data[6] + data[2] * rhs.data[10] + data[3] * rhs.data[14];
        res.data[3] = data[0] * rhs.data[3] + data[1] * rhs.data[7] + data[2] * rhs.data[11] + data[3] * rhs.data[15];
        res.data[4] = data[4] * rhs.data[0] + data[5] * rhs.data[4] + data[6] * rhs.data[8] + data[7] * rhs.data[12];
        res.data[5] = data[4] * rhs.data[1] + data[5] * rhs.data[5] + data[6] * rhs.data[9] + data[7] * rhs.data[13];
        res.data[6] = data[4] * rhs.data[2] + data[5] * rhs.data[6] + data[6] * rhs.data[10] + data[7] * rhs.data[14];
        res.data[7] = data[4] * rhs.data[3] + data[5] * rhs.data[7] + data[6] * rhs.data[11] + data[7] * rhs.data[15];
        res.data[8] = data[8] * rhs.data[0] + data[9] * rhs.data[4] + data[10] * rhs.data[8] + data[11] * rhs.data[12];
        res.data[9] = data[8] * rhs.data[1] + data[9] * rhs.data[5] + data[10] * rhs.data[9] + data[11] * rhs.data[13];
        res.data[10] = data[8] * rhs.data[2] + data[9] * rhs.data[6] + data[10] * rhs.data[10] + data[11] * rhs.data[14];
        res.data[11] = data[8] * rhs.data[3] + data[9] * rhs.data[7] + data[10] * rhs.data[11] + data[11] * rhs.data[15];
        res.data[12] = data[12] * rhs.data[0] + data[13] * rhs.data[4] + data[14] * rhs.data[8] + data[15] * rhs.data[12];
        res.data[13] = data[12] * rhs.data[1] + data[13] * rhs.data[5] + data[14] * rhs.data[9] + data[15] * rhs.data[13];
        res.data[14] = data[12] * rhs.data[2] + data[13] * rhs.data[6] + data[14] * rhs.data[10] + data[15] * rhs.data[14];
        res.data[15] = data[12] * rhs.data[3] + data[13] * rhs.data[7] + data[14] * rhs.data[11] + data[15] * rhs.data[15];
        return res;
    }

    Mat4& operator*=(const Mat4& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    // Transpose matrix
    void transpose()
    {
        std::swap(data[1], data[4]);
        std::swap(data[2], data[8]);
        std::swap(data[3], data[12]);
        std::swap(data[6], data[9]);
        std::swap(data[7], data[13]);
        std::swap(data[11], data[14]);
    }

    // Get transposed matrix
    Mat4 getTranspose() const
    {
        Mat4 res;
        res.data[0] = data[0], res.data[1] = data[4], res.data[2] = data[8], res.data[3] = data[12];
        res.data[4] = data[1], res.data[5] = data[5], res.data[6] = data[9], res.data[7] = data[13];
        res.data[8] = data[2], res.data[9] = data[6], res.data[10] = data[10], res.data[11] = data[14];
        res.data[12] = data[3], res.data[13] = data[7], res.data[14] = data[11], res.data[15] = data[15];
        return res;
    }

    // Construct a translation matrix
    static Mat4 translation(const Vec3<T>& delta)
    {
        Mat4 res(T(1.0));
        res.data[3] = delta.x;
        res.data[7] = delta.y;
        res.data[11] = delta.z;
        return res;
    }

    // Construct a rotation matrix
    static Mat4 rotation(T degrees, Vec3<T> vec)
    {
        Mat4 res;
        vec.normalize();
        T alpha = degrees * T(M_PI) / T(180.0), s = sin(alpha), c = cos(alpha), t = 1.0f - c;
        res.data[0] = t * vec.x * vec.x + c;
        res.data[1] = t * vec.x * vec.y + s * vec.z;
        res.data[2] = t * vec.x * vec.z - s * vec.y;
        res.data[4] = t * vec.x * vec.y - s * vec.z;
        res.data[5] = t * vec.y * vec.y + c;
        res.data[6] = t * vec.y * vec.z + s * vec.x;
        res.data[8] = t * vec.x * vec.z + s * vec.y;
        res.data[9] = t * vec.y * vec.z - s * vec.x;
        res.data[10] = t * vec.z * vec.z + c;
        res.data[15] = T(1.0);
        return res;
    }

    // Construct a perspective projection matrix
    static Mat4 perspective(T fov, T aspect, T zNear, T zFar)
    {
        Mat4 res;
        T f = T(1.0) / tan(fov * T(M_PI) / T(180.0) / T(2.0));
        T a = zNear - zFar;
        res.data[0] = f / aspect;
        res.data[5] = f;
        res.data[10] = (zFar + zNear) / a;
        res.data[11] = T(2.0) * zFar * zNear / a;
        res.data[14] = T(-1.0);
        return res;
    }

    // Construct an orthogonal projection matrix
    static Mat4 ortho(T left, T right, T top, T bottom, T zNear, T zFar)
    {
        T a = right - left;
        T b = top - bottom;
        T c = zFar - zNear;
        Mat4 res;
        res.data[0] = T(2.0) / a;
        res.data[3] = -(right + left) / a;
        res.data[5] = T(2.0) / b;
        res.data[7] = -(top + bottom) / b;
        res.data[10] = T(-2.0) / c;
        res.data[11] = -(zFar + zNear) / c;
        res.data[15] = T(1.0);
        return res;
    }

    // Multiply with Vec3 (with homogeneous coords normalized)
    Vec3<T> transformVec3(const Vec3<T>& vec) const
    {
        Vec3<T> res(data[0] * vec.x + data[4] * vec.y + data[8] * vec.z + data[12],
                    data[1] * vec.x + data[5] * vec.y + data[9] * vec.z + data[13],
                    data[2] * vec.x + data[6] * vec.y + data[10] * vec.z + data[14]);
        T homoCoord = data[3] * vec.x + data[7] * vec.y + data[11] * vec.z + data[15];
        return res / homoCoord;
    }
};

using Mat4f = Mat4<float>;
// If you are doing rendering, it's recommended to use Mat4f instead of Mat4d
using Mat4d = Mat4<double>;
