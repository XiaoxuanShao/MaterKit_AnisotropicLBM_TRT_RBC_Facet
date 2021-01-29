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
#ifndef MK_VECTORS_H
#define MK_VECTORS_H
#include "MaterKit.h"
#include "mkGlobalDefs.h"

#ifdef MK_INLINE
#include "mkVector03i.h"
#include "mkVector03d.h"
#include "mkVector19i.h"
#include "mkVector19d.h"
#else

class MK_API mkVector3i;
class MK_API mkVector3d;
class MK_API mkVector19i;
class MK_API mkVector19d;

class mkVector3i   //
{
public:

	/** Number of vector components. */
	enum { num_components = 3 };

	int _v[3];

	mkVector3i();

	mkVector3i(int x, int y, int z);

	bool operator == (const mkVector3i& v) const;

	bool operator != (const mkVector3i& v) const;

	bool operator <  (const mkVector3i& v) const;

	int* ptr();

	const int* ptr() const;

	void set(int x, int y, int z);

	void set(const mkVector3i& rhs);

	int& operator [] (int i);

	int  operator [] (int i) const;

	int& x();
	int& y();
	int& z();

	int x() const;
	int y() const;
	int z() const;

	/* Dot product. */
	int operator * (const mkVector3i& rhs) const;

	/* Cross product. */
	const mkVector3i operator ^ (const mkVector3i& rhs) const;

	/** Multiply by scalar. */
	const mkVector3i operator * (int rhs) const;

	const mkVector3d operator * (mkReal rhs) const;

	/** Unary multiply by scalar. */
	mkVector3i& operator *= (int rhs);

	//inline mkVector3i& operator *= (mkReal rhs);

	/** Divide by scalar. */
	const mkVector3i operator / (int rhs) const;

	const mkVector3d operator / (mkReal rhs) const;

	/** Unary divide by scalar. */
	mkVector3i& operator /= (int rhs);

	//inline mkVector3i& operator /= (mkReal rhs);

	/* Binary vector add. */
	const mkVector3i operator + (const mkVector3i& rhs) const;

	/* Unary vector add. Slightly more efficient because no temporary intermediate object. */
	mkVector3i& operator += (const mkVector3i& rhs);

	/* Binary vector subtract. */
	const mkVector3i operator - (const mkVector3i& rhs) const;

	/** Unary vector subtract. */
	mkVector3i& operator -= (const mkVector3i& rhs);

	/** Negation operator. Returns the negative of the Vec3f. */
	const mkVector3i operator - () const;

	/** Length of the vector = sqrt( vec . vec ) */
	double length() const;

	/** Length squared of the vector = vec . vec */
	int length2() const;

	/** Normalize the vector so that it has length unity.
	* Returns the previous length of the vector.
	*/
	mkVector3d normalize();
};    // end of class mkVector3i

class mkVector3d
{
public:

	/** Type of Vec class.*/
//	typedef mkReal mkReal;

	/** Number of vector components. */
	enum { num_components = 3 };

	mkReal _v[3];

	mkVector3d();

	mkVector3d(mkReal x, mkReal y, mkReal z);

	bool operator == (const mkVector3d& v) const;

	bool operator != (const mkVector3d& v) const;

	bool operator <  (const mkVector3d& v) const;

	mkReal* ptr();

	const mkReal* ptr() const;

	void set(mkReal x, mkReal y, mkReal z);

	void set(const mkVector3d& rhs);

	void add(mkReal x, mkReal y, mkReal z);

	void sub(mkReal x, mkReal y, mkReal z);

	mkReal& operator [] (int i);
	mkReal  operator [] (int i) const;

	mkReal& x();
	mkReal& y();
	mkReal& z();

	mkReal x() const;
	mkReal y() const;
	mkReal z() const;

	/** Dot product. */
	mkReal operator * (const mkVector3d& rhs) const;

	/** Cross product. */
	const mkVector3d operator ^ (const mkVector3d& rhs) const;

	/** Multiply by scalar. */
	const mkVector3d operator * (mkReal rhs) const;

	/** Unary multiply by scalar. */
	mkVector3d& operator *= (mkReal rhs);

	/** Divide by scalar. */
	const mkVector3d operator / (mkReal rhs) const;

	/** Unary divide by scalar. */
	mkVector3d& operator /= (mkReal rhs);

	/** Binary vector add. */
	const mkVector3d operator + (const mkVector3d& rhs) const;

	/** Unary vector add. Slightly more efficient because no temporary
	* intermediate object.
	*/
	mkVector3d& operator += (const mkVector3d& rhs);

	/** Binary vector subtract. */
	const mkVector3d operator - (const mkVector3d& rhs) const;

	/** Unary vector subtract. */
	mkVector3d& operator -= (const mkVector3d& rhs);

	/** Negation operator. Returns the negative of the Vec3f. */
	const mkVector3d operator - () const;

	/** Length of the vector = sqrt( vec . vec ) */
	mkReal length() const;

	/** Length squared of the vector = vec . vec */
	mkReal length_sq() const;

	/** Normalize the vector so that it has length unity.
	* Returns the previous length of the vector.
	*/
	mkVector3d normalize();

	// angle between the current vector and
	// the direction along with the x-axis.
	mkReal angle();

	// angle between the current vector and
	// the direction along with the x-axis.
	mkReal angle(const mkVector3d & rhs);
};    // end of class mkVector3d


class mkVector19i   //19维向量
{
public:

	/* Number of vector components. */
	enum { num_components = 19 };

	int _v[19];

	mkVector19i();
	mkVector19i(
		mkReal v0,
		mkReal v1, mkReal v2, mkReal v3, mkReal v4, mkReal v5, mkReal v6, \
		mkReal v7, mkReal v8, mkReal v9, mkReal v10, mkReal v11, mkReal v12, \
		mkReal v13, mkReal v14, mkReal v15, mkReal v16, mkReal v17, mkReal v18);

	int* ptr();
	const int* ptr() const;

	void set(
		mkReal f0,
		mkReal f1, mkReal f2, mkReal f3, mkReal f4, mkReal f5, mkReal f6, \
		mkReal f7, mkReal f8, mkReal f9, mkReal f10, mkReal f11, mkReal f12, \
		mkReal f13, mkReal f14, mkReal f15, mkReal f16, mkReal f17, mkReal f18);

	void set(const mkVector19i& rhs);

	int& operator [] (int i);

	int operator [] (int i) const;

	/* Dot product. */
	int operator * (const mkVector19i& rhs) const;

	/* Multiply by scalar. */
	const mkVector19i operator * (mkReal rhs) const;

	/* Unary multiply by scalar. */
	mkVector19i& operator *= (mkReal rhs);

	/** Divide by scalar. */
	const mkVector19i operator / (mkReal rhs) const;

	/** Unary divide by scalar. */
	mkVector19i& operator /= (mkReal rhs);

	/** Binary vector add. */
	const mkVector19i operator + (const mkVector19i& rhs) const;

	/* Unary vector add. Slightly more efficient because no temporary */
	/* intermediate object.*/
	mkVector19i& operator += (const mkVector19i& rhs);

	/* Binary vector subtract. */
	const mkVector19i operator - (const mkVector19i& rhs) const;

	/* Unary vector subtract. */
	mkVector19i& operator -= (const mkVector19i& rhs);

	/* Negation operator. Returns the negative of the Vec3f. */
	const mkVector19i operator - () const;
	/* return sum of all components*/
	mkReal sum() const;

};  // end of class mkVector19i


class mkVector19d   //19维向量
{
public:

	/* Number of vector components. */
	enum { num_components = 19 };

	mkReal _v[19];

	mkVector19d();

	mkVector19d(
		mkReal v0,
		mkReal v1, mkReal v2, mkReal v3, mkReal v4, mkReal v5, mkReal v6, \
		mkReal v7, mkReal v8, mkReal v9, mkReal v10, mkReal v11, mkReal v12, \
		mkReal v13, mkReal v14, mkReal v15, mkReal v16, mkReal v17, mkReal v18);

	mkReal* ptr();
	const mkReal* ptr() const;

	void set(
		mkReal f0,
		mkReal f1, mkReal f2, mkReal f3, mkReal f4, mkReal f5, mkReal f6, \
		mkReal f7, mkReal f8, mkReal f9, mkReal f10, mkReal f11, mkReal f12, \
		mkReal f13, mkReal f14, mkReal f15, mkReal f16, mkReal f17, mkReal f18);

	void set(const mkVector19d& rhs);

	mkReal& operator [] (int i);
	mkReal operator [] (int i) const;

	/* Dot product. */
	mkReal operator * (const mkVector19d& rhs) const;

	/* Multiply by scalar. */
	const mkVector19d operator * (mkReal rhs) const;

	/* Unary multiply by scalar. */
	mkVector19d& operator *= (mkReal rhs);

	/** Divide by scalar. */
	const mkVector19d operator / (mkReal rhs) const;

	/** Unary divide by scalar. */
	mkVector19d& operator /= (mkReal rhs);

	/** Binary vector add. */
	const mkVector19d operator + (const mkVector19d& rhs) const;

	/* Unary vector add. Slightly more efficient because no temporary */
	/* intermediate object.*/
	mkVector19d& operator += (const mkVector19d& rhs);

	/* Binary vector subtract. */
	const mkVector19d operator - (const mkVector19d& rhs) const;

	/* Unary vector subtract. */
	mkVector19d& operator -= (const mkVector19d& rhs);

	/* Negation operator. Returns the negative of the Vec3f. */
	const mkVector19d operator - () const;
	/* return sum of all components*/
	mkReal sum() const;

};  // end of class mkVector19d


#endif
#endif
