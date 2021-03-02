//============================================================================
//              Anisotropic LBM 3D code
//============================================================================
// Author      : DongKe SUN
// Version     : 2010.09.30 MoonLight
// Copyright   : All rights reserved.
// Description : C++, Ansi-style
// Last updated: 2021.01.28 by DongKe SUN
//============================================================================
// SUN DongKe, Ph.D
// Website     : http://www.materkit.com
// E-Mail      : dksun@seu.edu.cn 
//============================================================================
#ifndef MK_TRIANGLE_SET_H
#define MK_TRIANGLE_SET_H
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <limits>
#include <algorithm>

#include "mkGlobalDefsMkt.h"

namespace mkt 
{
/// Test equality of two floating point numbers, with an accuracy
///   that is relative to the value of the arguments.
template<typename T>
bool fpequal(T x, T y, T eps)
{
    bool val;

    if (fabs(x) <= 2.0 * eps)
        x = 0.0;

    if (fabs(y) <= 2.0 * eps)
        y = 0.0;

    if (x == 0.0 || y == 0.0) {
        if (fabs(x - y) <= 2.0 * eps)
            val = true;
        else
            val = false;
    } else {
        if (fabs(x - y) <= eps * fabs(x) &&
            fabs(x - y) <= eps * fabs(y))
            val = true;
        else
            val = false;
    }
    return val;
}

/// Test equality of two floating point numbers, with absolute accuracy,
///   independent of the value of the arguments. This is useful in relation
///   with calculations in which all important quantities are of the order 1.
template<typename T>
bool fpequal_abs(T x, T y, T eps)
{
    return fabs(x-y) <= eps;
}
//#ifndef GLOBAL_DEFS_H
///// Enumeration type that sets the precision for further use.
///// Single precision (float): FLT
///// Double precision (double): DBL
///// Extended precision (long double): LDBL
//enum Precision { FLT, DBL, LDBL };
//
///// Enumeration type that sets the file format for the triangular surface meshes.
///// Stereolithography format: STL
//enum SurfaceGeometryFileFormat { STL };
//
//template<typename T>
//inline T getEpsilon(Precision precision)
//{
//    T epsilon;
//
//    switch (precision) {
//    case FLT:
//        epsilon = std::numeric_limits<float>::epsilon();
//        break;
//    case DBL:
//        epsilon = std::numeric_limits<double>::epsilon();
//        break;
//    case LDBL: default:
//        epsilon = std::numeric_limits<long double>::epsilon();
//        break;
//    }
//
//    T coef = 10.0; // hack for better results
//
//    return (coef * epsilon);
//}
//#endif

/** A simple array class, which is slightly more convenient
 *  to use than the pure C-array. It initializes the data to
 *  zero in the default constructor, can be assigned from an
 *  Array of different type, contains bound verifications for
 *  debugging, and is specialized for the 2D and 3D case.
 *
 *  ATTENTION: Values are not reset to zero in the constructor,
 *  for efficiency reason. If you need them to default to
 *  zero, you need to invoke method resetToZero() explicitly.
 */
template<typename T, int size>
class Array {
public:
    Array() { }
    /// Copy-construction is only allowed with same-size Arrays,
    /// to prevent bugs due to cutting off one of the arrays.
    template<typename U>
    Array(Array<U,size> const& rhs) {
        std::copy(&rhs[0], &rhs[0]+size, data);
    }
    /// Assignment is only allowed with same-size Arrays,
    /// to prevent bugs due to cutting off one of the arrays.
    template<typename U>
    Array<T,size>& operator=(Array<U,size> const& rhs) {
        std::copy(&rhs[0], &rhs[0]+size, data);
    }
    T& operator[](int index) {
//        PLB_PRECONDITION(index<size);
        return data[index];
    }
    T const& operator[](int index) const {
//        PLB_PRECONDITION(index<size);
        return data[index];
    }
    void from_cArray(T const* cArray) {
        std::copy(cArray, cArray+size, data);
    }
    void to_cArray(T* cArray) const {
        std::copy(data, data+size, cArray);
    }
    void resetToZero() {
        std::fill_n(data, size, T());
    }
    Array<T,size>& operator += (Array<T,size> const& b) {
        for (int i=0; i<size; ++i) {
            data[i] += b[i];
        }
        return *this;
    }
    Array<T,size>& operator += (T alpha) {
        for (int i=0; i<size; ++i) {
            data[i] += alpha;
        }
        return *this;
    }
    Array<T,size>& operator -= (Array<T,size> const& b) {
        for (int i=0; i<size; ++i) {
            data[i] -= b[i];
        }
        return *this;
    }
    Array<T,size>& operator -= (T alpha) {
        for (int i=0; i<size; ++i) {
            data[i] -= alpha;
        }
        return *this;
    }
    Array<T,size>& operator *= (Array<T,size> const& b) {
        for (int i=0; i<size; ++i) {
            data[i] *= b[i];
        }
        return *this;
    }
    Array<T,size>& operator *= (T alpha) {
        for (int i=0; i<size; ++i) {
            data[i] *= alpha;
        }
        return *this;
    }
    Array<T,size>& operator /= (Array<T,size> const& b) {
        for (int i=0; i<size; ++i) {
            data[i] /= b[i];
        }
        return *this;
    }
    Array<T,size>& operator /= (T alpha) {
        for (int i=0; i<size; ++i) {
            data[i] /= alpha;
        }
        return *this;
    }
private:
    T data[size];
};

template <typename T, int size>
Array<T,size> operator+(Array<T,size> const& a, Array<T,size> const& b) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator+(Array<T,size> const& a, T alpha) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = a[i] + alpha;
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator+(T alpha, Array<T,size> const& a) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = alpha + a[i];
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator-(Array<T,size> const& a, Array<T,size> const& b) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = a[i] - b[i];
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator-(Array<T,size> const& a) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = -a[i];
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator-(Array<T,size> const& a, T alpha) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = a[i] - alpha;
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator-(T alpha, Array<T,size> const& a) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = alpha - a[i];
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator*(Array<T,size> const& a, Array<T,size> const& b) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = a[i] * b[i];
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator*(Array<T,size> const& a, T alpha) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = a[i] * alpha;
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator*(T alpha, Array<T,size> const& a) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = alpha * a[i];
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator/(Array<T,size> const& a, Array<T,size> const& b) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = a[i] / b[i];
    }
    return result;
}

template<typename T, int size>
Array<T,size> operator/(Array<T,size> const& a, T alpha) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = a[i] / alpha;
    }
    return result;
}

template<typename T, int size>
inline bool operator==(Array<T,size> const& A, Array<T,size> const& B) {
    for (int iA = 0; iA < size; ++iA) {
        if (A[iA] != B[iA]) return false;
    }
    return true;
}

template<typename T, int size>
inline bool operator!=(Array<T,size> const& A, Array<T,size> const& B) {
    for (int iA = 0; iA < size; ++iA) {
        if (A[iA] != B[iA]) return true;
    }
    return false;
}

template<typename T, int size>
inline bool operator<(Array<T,size> const& A, Array<T,size> const& B) {
    for (int iA=0; iA<size; ++iA) {
        if (A[iA] < B[iA]) return true;
        if (A[iA] > B[iA]) return false;
    }
    return false;
}

template<typename T, int size>
Array<T,size> operator/(T alpha, Array<T,size> const& a) {
    Array<T,size> result;
    for (int i=0; i<size; ++i) {
        result[i] = alpha / a[i];
    }
    return result;
}


template<typename T>
class Array<T,2> {
public:
    Array() { }
    Array(T x, T y) {
        data[0] = x;
        data[1] = y;
    }
    template<typename U>
    Array(Array<U,2> const& rhs) {
        data[0] = (T) rhs[0];
        data[1] = (T) rhs[1];
    }
    template<typename U>
    Array<T,2>& operator=(Array<U,2> const& rhs) {
        data[0] = (T) rhs[0];
        data[1] = (T) rhs[1];
    }
    T& operator[](int index) {
        //PLB_PRECONDITION(index<2);
        return data[index];
    }
    T const& operator[](int index) const {
        //PLB_PRECONDITION(index<2);
        return data[index];
    }
    void from_cArray(T const* cArray) {
        data[0] = cArray[0];
        data[1] = cArray[1];
    }
    void to_cArray(T* cArray) const {
        cArray[0] = data[0];
        cArray[1] = data[1];
    }
    void resetToZero() {
        data[0] = T();
        data[1] = T();
    }
    Array<T,2>& operator+=(Array<T,2> const& b) {
        data[0] += b[0];
        data[1] += b[1];
        return *this;
    }
    Array<T,2>& operator+=(T alpha) {
        data[0] += alpha;
        data[1] += alpha;
        return *this;
    }
    Array<T,2>& operator-=(Array<T,2> const& b) {
        data[0] -= b[0];
        data[1] -= b[1];
        return *this;
    }
    Array<T,2>& operator-=(T alpha) {
        data[0] -= alpha;
        data[1] -= alpha;
        return *this;
    }
    Array<T,2>& operator*=(Array<T,2> const& b) {
        data[0] *= b[0];
        data[1] *= b[1];
        return *this;
    }
    Array<T,2>& operator*=(T alpha) {
        data[0] *= alpha;
        data[1] *= alpha;
        return *this;
    }
    Array<T,2>& operator/=(Array<T,2> const& b) {
        data[0] /= b[0];
        data[1] /= b[1];
        return *this;
    }
    Array<T,2>& operator/=(T alpha) {
        data[0] /= alpha;
        data[1] /= alpha;
        return *this;
    }
private:
    T data[2];
};

template<typename T>
Array<T,2> operator+(Array<T,2> const& a, Array<T,2> const& b) {
    return Array<T,2>(a[0]+b[0], a[1]+b[1]);
}

template<typename T>
Array<T,2> operator+(Array<T,2> const& a, T alpha) {
    return Array<T,2>(a[0]+alpha, a[1]+alpha);
}

template<typename T>
Array<T,2> operator+(T alpha, Array<T,2> const& a) {
    return Array<T,2>(alpha+a[0], alpha+a[1]);
}

template<typename T>
Array<T,2> operator-(Array<T,2> const& a, Array<T,2> const& b) {
    return Array<T,2>(a[0]-b[0], a[1]-b[1]);
}

template<typename T>
Array<T,2> operator-(Array<T,2> const& a) {
    return Array<T,2>(-a[0],-a[1]);
}

template<typename T>
Array<T,2> operator-(Array<T,2> const& a, T alpha) {
    return Array<T,2>(a[0]-alpha, a[1]-alpha);
}

template<typename T>
Array<T,2> operator-(T alpha, Array<T,2> const& a) {
    return Array<T,2>(alpha-a[0], alpha-a[1]);
}

template<typename T>
Array<T,2> operator*(Array<T,2> const& a, Array<T,2> const& b) {
    return Array<T,2>(a[0]*b[0], a[1]*b[1]);
}

template<typename T>
Array<T,2> operator*(Array<T,2> const& a, T alpha) {
    return Array<T,2>(a[0]*alpha, a[1]*alpha);
}

template<typename T>
Array<T,2> operator*(T alpha, Array<T,2> const& a) {
    return Array<T,2>(alpha*a[0], alpha*a[1]);
}

template<typename T>
Array<T,2> operator/(Array<T,2> const& a, Array<T,2> const& b) {
    return Array<T,2>(a[0]/b[0], a[1]/b[1]);
}

template<typename T>
Array<T,2> operator/(Array<T,2> const& a, T alpha) {
    return Array<T,2>(a[0]/alpha, a[1]/alpha);
}

template<typename T>
Array<T,2> operator/(T alpha, Array<T,2> const& a) {
    return Array<T,2>(alpha/a[0], alpha/a[1]);
}

template<typename T>
class Array<T,3> {
public:
    Array() { }
    Array(T x, T y, T z) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
    template<typename U>
    Array(Array<U,3> const& rhs) {
        data[0] = (T) rhs[0];
        data[1] = (T) rhs[1];
        data[2] = (T) rhs[2];
    }
    template<typename U>
    Array<T,3>& operator=(Array<U,3> const& rhs) {
        data[0] = (T) rhs[0];
        data[1] = (T) rhs[1];
        data[2] = (T) rhs[2];
    }
    T& operator[](int index) {
        //PLB_PRECONDITION(index<3);
        return data[index];
    }
    T const& operator[](int index) const {
        //PLB_PRECONDITION(index<3);
        return data[index];
    }
    void from_cArray(T const* cArray) {
        data[0] = cArray[0];
        data[1] = cArray[1];
        data[2] = cArray[2];
    }
    void to_cArray(T* cArray) const {
        cArray[0] = data[0];
        cArray[1] = data[1];
        cArray[2] = data[2];
    }
    void resetToZero() {
        data[0] = T();
        data[1] = T();
        data[2] = T();
    }
    Array<T,3>& operator += (Array<T,3> const& b) {
        data[0] += b[0];
        data[1] += b[1];
        data[2] += b[2];
        return *this;
    }
    Array<T,3>& operator += (T alpha) {
        data[0] += alpha;
        data[1] += alpha;
        data[2] += alpha;
        return *this;
    }
    Array<T,3>& operator -= (Array<T,3> const& b) {
        data[0] -= b[0];
        data[1] -= b[1];
        data[2] -= b[2];
        return *this;
    }
    Array<T,3>& operator -= (T alpha) {
        data[0] -= alpha;
        data[1] -= alpha;
        data[2] -= alpha;
        return *this;
    }
    Array<T,3>& operator *= (Array<T,3> const& b) {
        data[0] *= b[0];
        data[1] *= b[1];
        data[2] *= b[2];
        return *this;
    }
    Array<T,3>& operator *= (T alpha) {
        data[0] *= alpha;
        data[1] *= alpha;
        data[2] *= alpha;
        return *this;
    }
    Array<T,3>& operator /= (Array<T,3> const& b) {
        data[0] /= b[0];
        data[1] /= b[1];
        data[2] /= b[2];
        return *this;
    }
    Array<T,3>& operator /= (T alpha) {
        data[0] /= alpha;
        data[1] /= alpha;
        data[2] /= alpha;
        return *this;
    }
private:
    T data[3];
};

template<typename T>
Array<T,3> operator+(Array<T,3> const& a, Array<T,3> const& b) {
    return Array<T,3>(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}

template<typename T>
Array<T,3> operator+(Array<T,3> const& a, T alpha) {
    return Array<T,3>(a[0]+alpha, a[1]+alpha, a[2]+alpha);
}

template<typename T>
Array<T,3> operator+(T alpha, Array<T,3> const& a) {
    return Array<T,3>(alpha+a[0], alpha+a[1], alpha+a[2]);
}

template<typename T>
Array<T,3> operator-(Array<T,3> const& a, Array<T,3> const& b) {
    return Array<T,3>(a[0]-b[0], a[1]-b[1], a[2]-b[2]);
}

template<typename T>
Array<T,3> operator-(Array<T,3> const& a) {
    return Array<T,3>(-a[0], -a[1], -a[2]);
}

template<typename T>
Array<T,3> operator-(Array<T,3> const& a, T alpha) {
    return Array<T,3>(a[0]-alpha, a[1]-alpha, a[2]-alpha);
}

template<typename T>
Array<T,3> operator-(T alpha, Array<T,3> const& a) {
    return Array<T,3>(alpha-a[0], alpha-a[1], alpha-a[2]);
}

template<typename T>
Array<T,3> operator*(Array<T,3> const& a, Array<T,3> const& b) {
    return Array<T,3>(a[0]*b[0], a[1]*b[1], a[2]*b[2]);
}

template<typename T>
Array<T,3> operator*(Array<T,3> const& a, T alpha) {
    return Array<T,3>(a[0]*alpha, a[1]*alpha, a[2]*alpha);
}

template<typename T>
Array<T,3> operator*(T alpha, Array<T,3> const& a) {
    return Array<T,3>(alpha*a[0], alpha*a[1], alpha*a[2]);
}

template<typename T>
Array<T,3> operator/(Array<T,3> const& a, Array<T,3> const& b) {
    return Array<T,3>(a[0]/b[0], a[1]/b[1], a[2]/b[2]);
}

template<typename T>
Array<T,3> operator/(Array<T,3> const& a, T alpha) {
    return Array<T,3>(a[0]/alpha, a[1]/alpha, a[2]/alpha);
}

template<typename T>
Array<T,3> operator/(T alpha, Array<T,3> const& a) {
    return Array<T,3>(alpha/a[0], alpha/a[1], alpha/a[2]);
}


template<typename T>
class Array<T,4> {
public:
    Array() { }
    Array(T a0, T a1, T a2, T a3) {
        data[0] = a0;
        data[1] = a1;
        data[2] = a2;
        data[3] = a3;
    }
    template<typename U>
    Array(Array<U,4> const& rhs) {
        data[0] = (T) rhs[0];
        data[1] = (T) rhs[1];
        data[2] = (T) rhs[2];
        data[3] = (T) rhs[3];
    }
    template<typename U>
    Array<T,4>& operator=(Array<U,4> const& rhs) {
        data[0] = (T) rhs[0];
        data[1] = (T) rhs[1];
        data[2] = (T) rhs[2];
        data[3] = (T) rhs[3];
    }
    T& operator[](int index) {
//        PLB_PRECONDITION(index<4);
        return data[index];
    }
    T const& operator[](int index) const {
//        PLB_PRECONDITION(index<4);
        return data[index];
    }
    void from_cArray(T const* cArray) {
        data[0] = cArray[0];
        data[1] = cArray[1];
        data[2] = cArray[2];
        data[3] = cArray[3];
    }
    void to_cArray(T* cArray) const {
        cArray[0] = data[0];
        cArray[1] = data[1];
        cArray[2] = data[2];
        cArray[3] = data[3];
    }
    void resetToZero() {
        data[0] = T();
        data[1] = T();
        data[2] = T();
        data[3] = T();
    }
    Array<T,4>& operator += (Array<T,4> const& b) {
        data[0] += b[0];
        data[1] += b[1];
        data[2] += b[2];
        data[3] += b[3];
        return *this;
    }
    Array<T,4>& operator += (T alpha) {
        data[0] += alpha;
        data[1] += alpha;
        data[2] += alpha;
        data[3] += alpha;
        return *this;
    }
    Array<T,4>& operator -= (Array<T,4> const& b) {
        data[0] -= b[0];
        data[1] -= b[1];
        data[2] -= b[2];
        data[3] -= b[3];
        return *this;
    }
    Array<T,4>& operator -= (T alpha) {
        data[0] -= alpha;
        data[1] -= alpha;
        data[2] -= alpha;
        data[3] -= alpha;
        return *this;
    }
    Array<T,4>& operator *= (Array<T,4> const& b) {
        data[0] *= b[0];
        data[1] *= b[1];
        data[2] *= b[2];
        data[3] *= b[3];
        return *this;
    }
    Array<T,4>& operator *= (T alpha) {
        data[0] *= alpha;
        data[1] *= alpha;
        data[2] *= alpha;
        data[3] *= alpha;
        return *this;
    }
    Array<T,4>& operator /= (Array<T,4> const& b) {
        data[0] /= b[0];
        data[1] /= b[1];
        data[2] /= b[2];
        data[3] /= b[3];
        return *this;
    }
    Array<T,4>& operator /= (T alpha) {
        data[0] /= alpha;
        data[1] /= alpha;
        data[2] /= alpha;
        data[3] /= alpha;
        return *this;
    }
private:
    T data[4];
};

template<typename T>
Array<T,4> operator+(Array<T,4> const& a, Array<T,4> const& b) {
    return Array<T,4>(a[0]+b[0], a[1]+b[1], a[2]+b[2], a[3]+b[3]);
}

template<typename T>
Array<T,4> operator+(Array<T,4> const& a, T alpha) {
    return Array<T,4>(a[0]+alpha, a[1]+alpha, a[2]+alpha, a[3]+alpha);
}

template<typename T>
Array<T,4> operator+(T alpha, Array<T,4> const& a) {
    return Array<T,4>(alpha+a[0], alpha+a[1], alpha+a[2], alpha+a[3]);
}

template<typename T>
Array<T,4> operator-(Array<T,4> const& a, Array<T,4> const& b) {
    return Array<T,4>(a[0]-b[0], a[1]-b[1], a[2]-b[2], a[3]-b[3]);
}

template<typename T>
Array<T,4> operator-(Array<T,4> const& a) {
    return Array<T,4>(-a[0], -a[1], -a[2], -a[3]);
}

template<typename T>
Array<T,4> operator-(Array<T,4> const& a, T alpha) {
    return Array<T,4>(a[0]-alpha, a[1]-alpha, a[2]-alpha, a[3]-alpha);
}

template<typename T>
Array<T,4> operator-(T alpha, Array<T,4> const& a) {
    return Array<T,4>(alpha-a[0], alpha-a[1], alpha-a[2], alpha-a[3]);
}

template<typename T>
Array<T,4> operator*(Array<T,4> const& a, Array<T,4> const& b) {
    return Array<T,4>(a[0]*b[0], a[1]*b[1], a[2]*b[2], a[3]*b[3]);
}

template<typename T>
Array<T,4> operator*(Array<T,4> const& a, T alpha) {
    return Array<T,4>(a[0]*alpha, a[1]*alpha, a[2]*alpha, a[3]*alpha);
}

template<typename T>
Array<T,4> operator*(T alpha, Array<T,4> const& a) {
    return Array<T,4>(alpha*a[0], alpha*a[1], alpha*a[2], alpha*a[3]);
}

template<typename T>
Array<T,4> operator/(Array<T,4> const& a, Array<T,4> const& b) {
    return Array<T,4>(a[0]/b[0], a[1]/b[1], a[2]/b[2], a[3]/b[3]);
}

template<typename T>
Array<T,4> operator/(Array<T,4> const& a, T alpha) {
    return Array<T,4>(a[0]/alpha, a[1]/alpha, a[2]/alpha, a[3]/alpha);
}

template<typename T>
Array<T,4> operator/(T alpha, Array<T,4> const& a) {
    return Array<T,4>(alpha/a[0], alpha/a[1], alpha/a[2], alpha/a[3]);
}

/// Definition of a 3D unbounded plane.
template<typename T>
struct Plane {
    Array<T,3> point;
    Array<T,3> normal;
};

/// Definition of a cuboid (rectangular parallelepiped).
template<typename T>
struct Cuboid {
    Array<T,3> lowerLeftCorner;
    Array<T,3> upperRightCorner;
};


template <typename T, int d> struct VectorTemplateImpl;
template <typename T, template<typename U> class Descriptor> struct SymmetricTensor;
template <typename T, template<typename U> class Descriptor> struct SymmetricRankThreeTensor;
template <typename T, int d> struct SymmetricTensorImpl;
template <typename T, int d> struct SymmetricRankThreeTensorImpl;

template <typename T, template<typename U> class Descriptor>
struct VectorTemplate {
    /// Number of dimensions for current lattice
    static const int d = Descriptor<T>::d;
    /// Compute scalar product between two vectors
    static T scalarProduct(Array<T,d> const& u1, Array<T,d> const& u2) {
        return VectorTemplateImpl<T,d>::scalarProduct(u1,u2);
    }
    /// Compute scalar product between two a c-array and a plb-array
    static T scalarProduct(const T u1[d], Array<T,d> const& u2) {
        return VectorTemplateImpl<T,d>::scalarProduct(u1,u2);
    }
    /// Compute norm-square of a vector
    static T normSqr(Array<T,d> const& u) {
        return VectorTemplateImpl<T,d>::normSqr(u);
    }
    /// Multiply vector elements component-wise by a scalar
    static void multiplyByScalar(Array<T,d>& u, T scalar) {
        VectorTemplateImpl<T,d>::multiplyByScalar(u,scalar);
    }
    /// Multiply vector elements component-wise by a scalar and store in second vector
    static void multiplyByScalar(Array<T,d> const& u, T scalar, Array<T,d>& result) {
        VectorTemplateImpl<T,d>::multiplyByScalar(u,scalar,result);
    }
    /// Symmetric tensor product of two vectors
    static void symTensorProduct( Array<T,d> const &u, Array<T,d> const &v,
                                  Array<T,SymmetricTensor<T,Descriptor>::n> &result)
    {
        VectorTemplateImpl<T,d>::symTensorProduct(u,v,result);
    }
    /// Symmetric tensor product of three vectors
    static void symTensorProduct(Array<T,d> const &u, Array<T,d> const &v, Array<T,d> const &w,
                                 Array<T,SymmetricRankThreeTensor<T,Descriptor>::n> &result)
    {
        VectorTemplateImpl<T,d>::symTensorProduct(u,v,w,result);
    }
};

template <typename T, int d>
struct VectorTemplateImpl {
    static T scalarProduct(Array<T,d> const& u1, Array<T,d> const& u2) {
        T result = T();
        for (int iD=0; iD<d; ++iD) {
            result += u1[iD]*u2[iD];
        }
        return result;
    }
    static T scalarProduct(const T u1[d], Array<T,d> const& u2) {
        T result = T();
        for (int iD=0; iD<d; ++iD) {
            result += u1[iD]*u2[iD];
        }
        return result;
    }
    static T normSqr(Array<T,d> const& u) {
        return scalarProduct(u,u);
    }
    static void multiplyByScalar(Array<T,d>& u, T scalar) {
        for (int iD=0; iD<d; ++iD) {
            u[iD] *= scalar;
        }
    }

    static void multiplyByScalar(Array<T,d> const& u, T scalar, Array<T,d>& result) {
        for (int iD=0; iD<d; ++iD) {
            result[iD] = u[iD]*scalar;
        }
    }

    static void symTensorProduct(Array<T,d> const &u, Array<T,d> const &v, Array<T,SymmetricTensorImpl<T,d>::n> &result) {
        int iPi = 0;
        for (int iA = 0; iA < d; ++iA) {
            for (int iB = iA; iB < d; ++iB) {
                result[iPi] = u[iA]*v[iB];
                ++iPi;
            }
        }
    }

    static void symTensorProduct(Array<T,d> const &u, Array<T,d> const &v, Array<T,d> const &w,
                                 Array<T,SymmetricRankThreeTensorImpl<T,d>::n> &result) {
        int iPi = 0;
        for (int iA = 0; iA < d; ++iA) {
            for (int iB = iA; iB < d; ++iB) {
                for (int iC = iB; iC < d; ++iC) {
                    result[iPi] = u[iA]*v[iB]*w[iC];
                    ++iPi;
                }
            }
        }
    }
};


template <typename T>
struct VectorTemplateImpl<T,2> {
    static T scalarProduct(Array<T,2> const& u1, Array<T,2> const& u2) {
        return u1[0]*u2[0] + u1[1]*u2[1];
    }
    static T scalarProduct(const T u1[2], Array<T,2> const& u2) {
        return u1[0]*u2[0] + u1[1]*u2[1];
    }
    static T normSqr(Array<T,2> const& u) {
        return u[0]*u[0] + u[1]*u[1];
    }
    static void multiplyByScalar(Array<T,2>& u, T scalar) {
        u[0] *= scalar;
        u[1] *= scalar;
    }
    static void multiplyByScalar(Array<T,2> const& u, T scalar, Array<T,2>& result) {
        result[0] = u[0]*scalar;
        result[1] = u[1]*scalar;
    }
    static void symTensorProduct(Array<T,2> const &u, Array<T,2> const &v, Array<T,3> &result) {
        result[0] = u[0]*v[0];
        result[1] = u[0]*v[1];
        result[2] = u[1]*v[1];
    }
    static void symTensorProduct(Array<T,2> const &u, Array<T,2> const &v, Array<T,2> const &w,
                                 Array<T,4> &result) {
        result[0] = u[0]*v[0]*w[0];
        result[1] = u[0]*v[0]*w[1];
        result[2] = u[0]*v[1]*w[1];
        result[3] = u[1]*v[1]*w[1];
    }
};


template <typename T>
struct VectorTemplateImpl<T,3> {
    static T scalarProduct(Array<T,3> const& u1, Array<T,3> const& u2) {
        return u1[0]*u2[0] + u1[1]*u2[1] + u1[2]*u2[2];
    }
    static T scalarProduct(const T u1[3], Array<T,3> const& u2) {
        return u1[0]*u2[0] + u1[1]*u2[1] + u1[2]*u2[2];
    }
    static T normSqr(Array<T,3> const& u) {
        return u[0]*u[0] + u[1]*u[1] + u[2]*u[2];
    }
    static void multiplyByScalar(Array<T,3>& u, T scalar) {
        u[0] *= scalar;
        u[1] *= scalar;
        u[2] *= scalar;
    }
    static void multiplyByScalar(Array<T,3> const& u, T scalar, Array<T,3>& result) {
        result[0] = u[0]*scalar;
        result[1] = u[1]*scalar;
        result[2] = u[2]*scalar;
    }
    static void symTensorProduct(Array<T,3> const &u, Array<T,3> const &v, Array<T,6> &result) {
        result[0] = u[0]*v[0];
        result[1] = u[0]*v[1];
        result[2] = u[0]*v[2];
        result[3] = u[1]*v[1];
        result[4] = u[1]*v[2];
        result[5] = u[2]*v[2];
    }
    static void symTensorProduct(Array<T,3> const &u, Array<T,3> const &v, Array<T,3> const &w,
                                 Array<T,10> &result) {
        result[0] = u[0]*v[0]*w[0];
        result[1] = u[0]*v[0]*w[1];
        result[2] = u[0]*v[0]*w[2];
        result[3] = u[0]*v[1]*w[1];
        result[4] = u[0]*v[1]*w[2];
        result[5] = u[0]*v[2]*w[2];
        result[6] = u[1]*v[1]*w[1];
        result[7] = u[1]*v[1]*w[2];
        result[8] = u[1]*v[2]*w[2];
        result[9] = u[2]*v[2]*w[2];
    }
};


template <typename T, int d> struct SymmetricTensorImpl { };

template<typename T> struct SymmetricTensorImpl<T,2> {
    static const int n = 3;
    enum Indices { xx=0, xy=1, yy=2 };
    static void matVectMult(Array<T,n> const& mat, Array<T,2> const& vect, Array<T,2>& result) {
        result[0] = mat[xx]*vect[0] + mat[xy]*vect[1];
        result[1] = mat[xy]*vect[0] + mat[yy]*vect[1];
    }
    static T tensorNormSqr(Array<T,n> const& mat) {
        return mat[xx]*mat[xx]+mat[yy]*mat[yy] + (T)2*mat[xy]*mat[xy];
    }
    static T contractIndexes(Array<T,n> const& A, Array<T,n> const& B) {
        return A[xx]*B[xx]+A[yy]*B[yy]+ (T)2*A[xy]*B[xy];
    }
    static T trace(Array<T,n> const &A) {
        return A[xx] + A[yy];
    }
    static Array<T,n> id() {
        return Array<T,n>((T)1,T(),(T)1);
    }
};

template<typename T> struct SymmetricTensorImpl<T,3> {
    static const int n = 6;
    enum Indices { xx=0, xy=1, xz=2, yy=3, yz=4, zz=5 };
    static void matVectMult(Array<T,n> const& mat, Array<T,3> const& vect, Array<T,3>& result) {
        result[0] = mat[xx]*vect[0] + mat[xy]*vect[1] + mat[xz]*vect[2];
        result[1] = mat[xy]*vect[0] + mat[yy]*vect[1] + mat[yz]*vect[2];
        result[2] = mat[xz]*vect[0] + mat[yz]*vect[1] + mat[zz]*vect[2];
    }
    static T tensorNormSqr(Array<T,n> const& mat) {
        return mat[xx]*mat[xx]+mat[yy]*mat[yy]+mat[zz]*mat[zz]
               + (T)2*mat[xy]*mat[xy] + (T)2*mat[xz]*mat[xz] + (T)2*mat[yz]*mat[yz];
    }
    static T contractIndexes(Array<T,n> const& A, Array<T,n> const& B) {
        return A[xx]*B[xx]+A[yy]*B[yy]+A[zz]*B[zz]
            + (T)2*(A[xy]*B[xy] + A[xz]*B[xz] + A[yz]*B[yz]);
    }
    static T trace(Array<T,n> const &A) {
        return A[xx] + A[yy] + A[zz];
    }
    static Array<T,n> id() {
        Array<T,n> I;

        I[0] = (T)1;
        I[1] = T();
        I[2] = T();
        I[3] = (T)1;
        I[4] = T();
        I[5] = (T)1;

        return I;
    }
};

/// Operations on a symmetric tensor which stores only above-or-on-diagonal values
template <typename T, template<typename U> class Descriptor>
struct SymmetricTensor {
    /// Number of dimensions for current lattice
    static const int d = Descriptor<T>::d;
    /// Number of elements (reduced by symmetry)
    static const int n = SymmetricTensorImpl<T,d>::n;
    static void matVectMult(Array<T,n> const& mat, Array<T,d> const& vect, Array<T,d>& result) {
        SymmetricTensorImpl<T,d>::matVectMult(mat, vect, result);
    }
    static T tensorNormSqr(Array<T,n> const& mat) {
        return SymmetricTensorImpl<T,d>::tensorNormSqr(mat);
    }
    static T contractIndexes(Array<T,n> const& A, Array<T,n> const& B) {
        return SymmetricTensorImpl<T,d>::contractIndexes(A,B);
    }
    static T trace(Array<T,n> const &A) {
        return SymmetricTensorImpl<T,d>::trace(A);
    }
    static Array<T,n> id() {
        return SymmetricTensorImpl<T,d>::id();
    }
};

template <typename T, int d> struct SymmetricRankThreeTensorImpl { };

template<typename T> struct SymmetricRankThreeTensorImpl<T,2> {
    static const int n = 4;
    enum Indices { xxx=0, xxy=1, xyy=2, yyy = 3 };
    static void contractLastTwoIndexes(Array<T,n> const& tens, Array<T,2> & res) {
        res[0] = tens[xxx] + tens[xyy];
        res[1] = tens[xxy] + tens[yyy];
    }

    static T contractIndexes(Array<T,n> const& A, Array<T,n> const& B) {
        return A[xxx]*B[xxx] + A[yyy]*B[yyy] + (T)3*(A[xxy]*B[xxy] + A[xyy]*B[xyy]);
    }

    static void multWithRankTwoSymTensor(Array<T,n> const&A, Array<T,SymmetricTensorImpl<T,2>::n> const &B,
                                         Array<T,2> &x) {
        x[0] = A[xxx]*B[SymmetricTensorImpl<T,2>::xx] + (T)2*A[xxy]*B[SymmetricTensorImpl<T,2>::xy] + A[xyy]*B[SymmetricTensorImpl<T,2>::yy];
        x[1] = A[xxy]*B[SymmetricTensorImpl<T,2>::xx] + (T)2*A[xyy]*B[SymmetricTensorImpl<T,2>::xy] + A[yyy]*B[SymmetricTensorImpl<T,2>::yy];
    }
};

template<typename T> struct SymmetricRankThreeTensorImpl<T,3> {
    static const int n = 10;
    enum Indices { xxx=0, xxy=1, xxz=2, xyy=3, xyz=4, xzz=5, yyy=6, yyz=7, yzz=8, zzz=9 };
    static void contractLastTwoIndexes(Array<T,n> const& tens, Array<T,3> & res) {
        res[0] = tens[xxx] + tens[xyy] + tens[xzz];
        res[1] = tens[xxy] + tens[yyy] + tens[yzz];
        res[2] = tens[xxz] + tens[yyz] + tens[zzz];
    }

    static T contractIndexes(Array<T,n> const& A, Array<T,n> const& B) {
        return A[xxx]*B[xxx] + A[yyy]*B[yyy] + A[zzz]*B[zzz]
            + (T)3*(A[xxy]*B[xxy] + A[xxz]*B[xxz] + A[xyy]*B[xyy] + A[xzz]*B[xzz] + A[yzz]*B[yzz] + A[yyz]*B[yyz])
            + (T)6*A[xyz]*B[xyz];
    }

    static void multWithRankTwoSymTensor(Array<T,n> const&A, Array<T,SymmetricTensorImpl<T,3>::n> const &B,
                                         Array<T,3> &x) {
        x[0] = A[xxx]*B[SymmetricTensorImpl<T,3>::xx] + A[xyy]*B[SymmetricTensorImpl<T,3>::yy] + A[xzz]*B[SymmetricTensorImpl<T,3>::zz]
            + (T)2*(A[xxy]*B[SymmetricTensorImpl<T,3>::xy] + A[xxz]*B[SymmetricTensorImpl<T,3>::xz] + A[xyz]*B[SymmetricTensorImpl<T,3>::yz]);
        x[1] = A[yyy]*B[SymmetricTensorImpl<T,3>::yy] + A[xxy]*B[SymmetricTensorImpl<T,3>::xx] + A[yzz]*B[SymmetricTensorImpl<T,3>::zz]
            + (T)2*(A[xyy]*B[SymmetricTensorImpl<T,3>::xy] + A[yyz]*B[SymmetricTensorImpl<T,3>::yz] + A[xyz]*B[SymmetricTensorImpl<T,3>::xz]);
        x[2] = A[zzz]*B[SymmetricTensorImpl<T,3>::zz] + A[xxz]*B[SymmetricTensorImpl<T,3>::xx] + A[yyz]*B[SymmetricTensorImpl<T,3>::yy]
            + (T)2*(A[xzz]*B[SymmetricTensorImpl<T,3>::xz] + A[yzz]*B[SymmetricTensorImpl<T,3>::yz] + A[xyz]*B[SymmetricTensorImpl<T,3>::xy]);
    }
};

/// Operations on a symmetric tensor which stores only above-or-on-diagonal values
template <typename T, template<typename U> class Descriptor>
struct SymmetricRankThreeTensor {
    /// Number of dimensions for current lattice
    static const int d = Descriptor<T>::d;
    /// Number of elements (reduced by symmetry)
    static const int n = SymmetricRankThreeTensorImpl<T,d>::n;
    /// computes the contraction of the last two indexes of the tensor
    static void contractLastTwoIndexes(Array<T,n> const& tens, Array<T,d> &res) {
        SymmetricRankThreeTensorImpl<T,d>::contractLastTwoIndexes(tens, res);
    }
    /// computes the contraction of the last two indexes of the tensor
    static T contractIndexes(Array<T,n> const& A, Array<T,n> const& B) {
        return SymmetricRankThreeTensorImpl<T,d>::contractIndexes(A, B);
    }
    static void multWithRankTwoSymTensor(Array<T,n> const&A, Array<T,SymmetricTensor<T,Descriptor>::n> const &B,
                                         Array<T,d> &x) {
        SymmetricRankThreeTensorImpl<T,d>::multWithRankTwoSymTensor(A, B, x);
    }
};

template <typename T, int d> struct SymmetricRankFourTensorImpl { };

template<typename T> struct SymmetricRankFourTensorImpl<T,2> {
    static const int n = 5;
    enum Indices { xxxx=0, xxxy=1, xxyy=2, xyyy = 3, yyyy = 4 };

    static T contractIndexes(Array<T,n> const& A, Array<T,n> const& B) {
        return A[xxxx]*B[xxxx] + A[yyyy]*B[yyyy] + (T)4*(A[xxxy]*B[xxxy] + A[xyyy]*B[xyyy]) + (T)6*A[xxyy]*B[xxyy];
    }
    /// computes the contraction of the last two indexes of the tensor
    static void contractLastTwoIndexes(Array<T,n> const& tens, Array<T,3> &res) {
        res[SymmetricTensorImpl<T,2>::xx] = tens[xxxx]+tens[xxyy];
        res[SymmetricTensorImpl<T,2>::xy] = tens[xxxy]+tens[xyyy];
        res[SymmetricTensorImpl<T,2>::yy] = tens[xxyy]+tens[yyyy];
    }
    /// computes the interior product of symmetric rank 4 with rank three tensor
    static void multWithRankThreeSymTensor(Array<T,n> const&A,
                                           Array<T,SymmetricRankThreeTensorImpl<T,2>::n> const &B,
                                           Array<T,2> &x) {
        typedef SymmetricRankThreeTensorImpl<T,2> SRT;

        x[0] = A[xxxx]*B[SRT::xxx]+(T)3*(A[xxxy]*B[SRT::xxy]+A[xxyy]*B[SRT::xyy])+A[xyyy]*B[SRT::yyy];
        x[1] = A[xxxy]*B[SRT::xxx]+(T)3*(A[xxyy]*B[SRT::xxy]+A[xyyy]*B[SRT::xyy])+A[yyyy]*B[SRT::yyy];
    }
};

template<typename T> struct SymmetricRankFourTensorImpl<T,3> {
    static const int n = 15;
    enum Indices { xxxx=0, xxxy=1, xxxz=2, xxyy=3, xxyz=4, xxzz=5, xyyy=6, xyyz=7, xyzz=8, xzzz=9,
                   yyyy=10, yyyz=11, yyzz=12, yzzz=13, zzzz=14 };

    static T contractIndexes(Array<T,n> const& A, Array<T,n> const& B) {
        return A[xxxx]*B[xxxx] + A[yyyy]*B[yyyy] + A[zzzz]*B[zzzz]
            + (T)4*(A[xxxy]*B[xxxy] + A[xxxz]*B[xxxz] + A[xyyy]*B[xyyy] + A[xzzz]*B[xzzz] + A[yyyz]*B[yyyz] + A[yzzz]*B[yzzz])
            + (T)6*(A[xxyy]*B[xxyy] + A[xxzz]*B[xxzz] + A[yyzz]*B[yyzz])
            + (T)12*(A[xxyz]*B[xxyz] + A[xyyz]*B[xyyz] + A[xyzz]*B[xyzz]);
    }
    /// computes the contraction of the last two indexes of the tensor
    static void contractLastTwoIndexes(Array<T,n> const& tens, Array<T,6> &res) {
        res[SymmetricTensorImpl<T,3>::xx] = tens[xxxx]+tens[xxyy]+tens[xxzz];
        res[SymmetricTensorImpl<T,3>::xy] = tens[xxxy]+tens[xyyy]+tens[xyzz];
        res[SymmetricTensorImpl<T,3>::xz] = tens[xxxz]+tens[xyyz]+tens[xzzz];
        res[SymmetricTensorImpl<T,3>::yy] = tens[xxyy]+tens[yyyy]+tens[yyzz];
        res[SymmetricTensorImpl<T,3>::yz] = tens[xxyz]+tens[yyyz]+tens[yzzz];
        res[SymmetricTensorImpl<T,3>::zz] = tens[xxzz]+tens[yyzz]+tens[zzzz];
    }
    static void multWithRankThreeSymTensor(Array<T,n> const&A,
                                           Array<T,SymmetricRankThreeTensorImpl<T,3>::n> const &B,
                                           Array<T,3> &x) {
        typedef SymmetricRankThreeTensorImpl<T,3> SRT;

        x[0] = A[xxxx]*B[SRT::xxx]+A[xyyy]*B[SRT::yyy]+A[xzzz]*B[SRT::zzz]
            +(T)3*(A[xxxy]*B[SRT::xxy]+A[xxyy]*B[SRT::xyy]+A[xxxz]*B[SRT::xxz]+A[xyyz]*B[SRT::yyz]+A[xxzz]*B[SRT::xzz]+A[xyzz]*B[SRT::yzz])
            +(T)6*A  [xxyz]*B[SRT::xyz];

        x[1] = A[yyyy]*B[SRT::yyy]+A[xxxy]*B[SRT::xxx]+A[yzzz]*B[SRT::zzz]
            +(T)3*(A[xxyy]*B[SRT::xxy]+A[xyyy]*B[SRT::xyy]+A[yyyz]*B[SRT::yyz]+A[yyzz]*B[SRT::yzz]+A[xyzz]*B[SRT::xzz]+A[xxyz]*B[SRT::xxz])
            +(T)6*A[xyyz]*B[SRT::xyz];

        x[2] = A[zzzz]*B[SRT::zzz]+A[xxxz]*B[SRT::xxx]+A[yyyz]*B[SRT::yyy]
            +(T)3*(A[xxyz]*B[SRT::xxy]+A[xyyz]*B[SRT::xyy]+A[xxzz]*B[SRT::xxz]+A[yyzz]*B[SRT::yyz]+A[xzzz]*B[SRT::xzz]+A[yzzz]*B[SRT::yzz])
            +(T)6*A[xyzz]*B[SRT::xyz];
    }
};

/// Operations on a symmetric tensor which stores only above-or-on-diagonal values
template <typename T, template<typename U> class Descriptor>
struct SymmetricRankFourTensor {
    /// Number of dimensions for current lattice
    static const int d = Descriptor<T>::d;
    /// Number of elements (reduced by symmetry)
    static const int n = SymmetricRankFourTensorImpl<T,d>::n;

    /// computes the contraction of the last two indexes of the tensor
    static T contractIndexes(Array<T,n> const& A, Array<T,n> const& B) {
        return SymmetricRankFourTensorImpl<T,d>::contractIndexes(A, B);
    }
    /// computes the contraction of the last two indexes of the tensor
    static void contractLastTwoIndexes(Array<T,n> const& tens, Array<T,SymmetricTensor<T,Descriptor>::n> &res) {
        SymmetricRankFourTensorImpl<T,d>::contractLastTwoIndexes(tens, res);
    }
    static void multWithRankThreeSymTensor(Array<T,n> const&A,
                                           Array<T,SymmetricRankThreeTensor<T,Descriptor>::n> const &B,
                                           Array<T,d> &x) {
        SymmetricRankFourTensorImpl<T,d>::multWithRankThreeSymTensor(A, B, x);
    }
};

template <typename T>
void crossProduct(Array<T,3> const& u1, Array<T,3> const& u2, Array<T,3>& result)
{
    result[0] = u1[1]*u2[2] - u1[2]*u2[1];
    result[1] = u1[2]*u2[0] - u1[0]*u2[2];
    result[2] = u1[0]*u2[1] - u1[1]*u2[0];
}


template <typename T>
Array<T,3> cross(Array<T,3> const& u1, Array<T,3> const& u2)
{
    T r0 = u1[1]*u2[2] - u1[2]*u2[1];
    T r1 = u1[2]*u2[0] - u1[0]*u2[2];
    T r2 = u1[0]*u2[1] - u1[1]*u2[0];

	return Array<T,3> (r0, r1, r2);
}

/// Scalar product between two vectors.
template<typename T, int n>
T dot(Array<T,n> const& v1, Array<T,n> const& v2) {
    return VectorTemplateImpl<T,n>::scalarProduct(v1,v2);
}

/// Scalar product between a c-array and a vector.
template<typename T, int n>
T dot(T v1[n], Array<T,n> const& v2) {
    return VectorTemplateImpl<T,n>::scalarProduct(v1,v2);
}

template<typename T, int n>
T normSqr(Array<T,n> const& v) {
    return VectorTemplateImpl<T,n>::normSqr(v);
}

template<typename T, int n>
T norm(Array<T,n> const& v) {
    return sqrt(normSqr<T,n>(v));
}

template<typename T>
T computeTriangleArea(Array<T,3> const& v0, Array<T,3> const& v1, Array<T,3> const& v2)
{
    Array<T,3> e01 = v1 - v0;
    Array<T,3> e02 = v2 - v0;
    Array<T,3> cross;
    crossProduct<T>(e01, e02, cross);

    return 0.5 * norm<T,3>(cross);
}

template<typename T>
T computeTriangleArea(T *v0, T *v1, T *v2)
{
    int i;
    T e01[3], e02[3], cross[3];

    //for (i = 0; i < 3; e01[i] = v1[i] - v0[i], i++)
    //    ;
    //for (i = 0; i < 3; e02[i] = v2[i] - v0[i], i++)
    //    ;

    cross[0] = e01[1]*e02[2] - e01[2]*e02[1];
    cross[1] = e01[2]*e02[0] - e01[0]*e02[2];
    cross[2] = e01[0]*e02[1] - e01[1]*e02[0];

    return 0.5 * sqrt(cross[0]*cross[0] + cross[1]*cross[1] + cross[2]*cross[2]);
}

/// Given two vectors this function computes the angle between them
///   assuming that they originate at the same point in space
template<typename T>
T angleBetweenVectors(Array<T,3> const& v1, Array<T,3> const& v2)
{
    Array<T,3> cross;
    crossProduct<T>(v1, v2, cross);
    return atan2(norm(cross), dot(v1,v2));
}

//template<typename T>
//Array<T,3> rotateAtOrigin(Array<T,3> const& p, Array<T,3> const& normedAxis, T theta)
//{
//    Array<T,3> const& u = normedAxis;
//    T d = sqrt(u[1]*u[1] + u[2]*u[2]);
//
//    Array<T,3> q1 = p;
//    Array<T,3> q2 = q1;
//
//    T eps = 1.e-2;
//    //T eps = (T)100.*std::numeric_limits<T>::epsilon();
//    // Rotate about the x-axis to be in xz-plane.
//    if (!util::fpequal(d, (T)0., eps))
//    {
//        q2[0] = q1[0];
//        q2[1] = q1[1] * u[2] / d - q1[2] * u[1] / d;
//        q2[2] = q1[1] * u[1] / d + q1[2] * u[2] / d;
//    }
//
//    // Rotate about the y-axis to fall on z-axis.
//    q1[0] = q2[0] * d - q2[2] * u[0];
//    q1[1] = q2[1];
//    q1[2] = q2[0] * u[0] + q2[2] * d;
//
//    // Perform desired rotation.
//    T ct = cos(theta);
//    T st = sin(theta);
//    q2[0] = q1[0] * ct - q1[1] * st;
//    q2[1] = q1[0] * st + q1[1] * ct;
//    q2[2] = q1[2];
//
//    // Rotate backward around y-axis.
//    q1[0] =   q2[0] * d + q2[2] * u[0];
//    q1[1] =   q2[1];
//    q1[2] = - q2[0] * u[0] + q2[2] * d;
//
//    q2 = q1;
//    // Rotate backward around x-axis.
//    if (!util::fpequal(d, (T)0., eps)) {
//        q2[0] =   q1[0];
//        q2[1] =   q1[1] * u[2] / d + q1[2] * u[1] / d;
//        q2[2] = - q1[1] * u[1] / d + q1[2] * u[2] / d;
//    }
//    return q2;
//}

template<typename T>
class TriangleSet
{
public:
    typedef Array<Array<T,3>,3> Triangle;
public:
    TriangleSet(Precision precision_ = FLT);
    TriangleSet(std::vector<Triangle> const& triangles_, Precision precision_ = FLT);
    TriangleSet(std::string fname, Precision precision_ = FLT, SurfaceGeometryFileFormat fformat = STL);
    std::vector<Triangle> const& getTriangles() const;
    Precision getPrecision() const { return precision; }
    void setPrecision(Precision precision_);

    /// Translate the triangle set surface mesh.
    void translate(Array<T,3> const& vector);
    /// Scale the triangle set surface mesh.
    void scale(T alpha);
    /// Rotate the triangle set surface mesh.
    ///   The arguments of this function are the Euler angles in radians.
    ///   The so-called "x-convention" is used, in which the rotation is
    ///   given by the three angles (phi, theta, psi), where:
    ///   1.] The first rotation is by an angle phi about the z-axis,
    ///   2.] The second rotation is by an angle theta in [0, pi] about
    ///       the new x-axis,
    ///   3.] The third rotation is by an angle psi about the new z-axis.
    void rotate(T phi, T theta, T psi);
    void rotateAtOrigin(Array<T,3> const& normedAxis, T theta);

    /// Erase the current triangle set surface mesh, and merge into it the new meshes.
    ///   This function currently does not check for duplicate
    ///   triangles in the new meshes, and does not handle
    ///   cases when the resulting merged surface mesh is
    ///   non-manifold. It is in the user's jurisdiction to
    ///   make sure that the resulting mesh is well defined.
    ///   Practically, this can be achieved if the new triangle set
    ///   meshes given as arguments are mutually disjoint.
    void merge(std::vector<TriangleSet<T> > meshes);

    /// A very simple orientation reversing function.
    void reverseOrientation();

    /// Export the mesh as an ASCII STL file.
    void writeAsciiSTL(std::string fname) const;
    /// Export the mesh as an binary STL file.
    void writeBinarySTL(std::string fname) const;


    /// Cut the current triangle set mesh by a plane "plane" which is
    ///   defined by a point and a normal. This cutting operation will
    ///   produce a new triangle set "newTriangleSet" which is
    ///   the one that belongs to the half-space that the normal of the
    ///   cutting plane points outside of. The function returns 1 if
    ///   the cut was successful, 0 if there was no intersection between
    ///   the original triangle set and the plane provided, and -1 if an
    ///   error occured.
    int cutWithPlane(Plane<T> const& plane, TriangleSet<T>& newTriangleSet) const;

    /// Cut the current triangle set mesh by a plane "plane" which is
    ///   defined by a point and a normal and a cuboid "cuboid" which is
    ///   defined by a lower left corner and a right upper corner. This
    ///   cutting operation will cut off all triangles, or parts of triangles
    ///   that are fully contained in the cuboid and are positioned in
    ///   the half-space that the normal of the cutting plane points into.
    ///   Caution is needed, because this function does not use the cuboid
    ///   to cut, but only to select parts of the original triangle set,
    ///   to be then cut by the plane. Obviously, at least a part of the
    ///   cutting plane must be contained in the cuboid, for the cutting
    ///   to make any sense. If not used wisely, this function can lead to
    ///   broken STL files. The function returns 1 if the cut was successful,
    ///   0 if there was no intersection between the original triangle set
    ///   the plane and the cuboid provided, and -1 if an error occured.
    int cutWithPlane(Plane<T> const& plane, Cuboid<T> const& cuboid,
            TriangleSet<T>& newTriangleSet) const;

    T getMinEdgeLength() const { return minEdgeLength; }
    T getMaxEdgeLength() const { return maxEdgeLength; }

    Cuboid<T> getBoundingCuboid() const { return boundingCuboid; }

private:
    void readSTL(std::string fname);
    void readAsciiSTL(FILE* fp);
    void readBinarySTL(FILE* fp);
    void check(Triangle& triangle, Array<T,3> const& n);
    void computeMinMaxEdge(int iTriangle, T& minEdge, T& maxEdge) const;
    void computeMinMaxEdges();
    void computeBoundingCuboid();
    /// Cut the current triangle by a plane "plane" which is
    ///   defined by a point and a normal. This cutting operation will
    ///   add or not one or more triangles to the triangle set "newTriangleSet".
    ///   The triangles added belong to the half-space that the normal of
    ///   the plane given points outside of. The function returns 1 if the
    ///   cut was successful, 0 if there was no intersection between the
    ///   original triangle set and the plane and -1 if an error occured.
    int cutTriangleWithPlane(Plane<T> const& plane, Triangle const& triangle,
            TriangleSet<T>& newTriangleSet) const;

private:
    std::vector<Triangle> triangles;
    T minEdgeLength, maxEdgeLength;
    Cuboid<T> boundingCuboid;
    /// Enumeration constant that sets the precision for triangle set checks.
    /// Single precision (float): FLT
    /// Double precision (double): DBL
    /// Extended precision (long double): LDBL
    Precision precision;

};
}

#endif
