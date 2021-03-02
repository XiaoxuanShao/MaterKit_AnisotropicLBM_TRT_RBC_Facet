//============================================================================
//              Anisotropic LBM 3D code
//============================================================================
// Author      : DongKe SUN
// Copyright   : All rights reserved.
// Description : C++, Ansi-style
// Last updated: 2018.11.11 by DongKe SUN
//============================================================================
// SUN DongKe, Ph.D
// Website     : http://www.Magic-Lab.cn
// E-Mail      : dongke.sun@foxmail.com
//============================================================================
#ifndef MK_PDFS_H
#define MK_PDFS_H

#include "MaterKit.h"
#include "mkVectors.h"


class MK_API mkPDFs;

class mkPDFs : public mkVector19d //19-dimensional double vector
{
public:

	/* Number of vector components. */
	enum {
		num_components = 19
	};

	mkReal _v[19];

	mkPDFs();
	mkPDFs(mkReal v0, mkReal v1, mkReal v2, mkReal v3, mkReal v4, mkReal v5, mkReal v6,
		mkReal v7, mkReal v8, mkReal v9, mkReal v10, mkReal v11, mkReal v12,
		mkReal v13, mkReal v14, mkReal v15, mkReal v16, mkReal v17, mkReal v18);

	mkReal* ptr();

	const mkReal* ptr() const;

	void set(mkReal f0, mkReal f1, mkReal f2, mkReal f3, mkReal f4, mkReal f5,
		mkReal f6, mkReal f7, mkReal f8, mkReal f9, mkReal f10, mkReal f11,
		mkReal f12, mkReal f13, mkReal f14, mkReal f15, mkReal f16, mkReal f17,
		mkReal f18);

	void set(const mkVector19d& rhs);

	mkReal& operator [](int i);

	mkReal operator [](int i) const;

	/* Dot product. */
	mkReal operator *(const mkPDFs& rhs) const;

	/* Multiply by scalar. */
	const mkPDFs operator *(mkReal rhs) const;

	/* Unary multiply by scalar. */
	mkPDFs& operator *=(mkReal rhs);

	/** Divide by scalar. */
	const mkPDFs operator /(mkReal rhs) const;

	/** Unary divide by scalar. */
	mkPDFs& operator /=(mkReal rhs);

	/** Binary vector add. */
	const mkPDFs operator +(const mkPDFs& rhs) const;

	/* Unary vector add. Slightly more efficient because no temporary */
	/* intermediate object.*/
	mkPDFs& operator +=(const mkPDFs& rhs);

	/* Binary vector subtract. */
	const mkPDFs operator -(const mkPDFs& rhs) const;

	/* Unary vector subtract. */
	mkPDFs& operator -=(const mkPDFs& rhs);

	/* Negation operator. Returns the negative of the Vec3f. */
	const mkPDFs operator -() const;

	/* return sum of all components*/
	mkReal sum() const;

	/* return density */
	mkReal density() const;

	/* return scalar */
	mkReal scalar() const;

	/* return velocity in x-direction*/
	mkReal U() const;

	mkReal U(mkReal rho) const;

	mkReal U(mkReal rho, mkReal c) const;

	/* return velocity in y-direction*/
	mkReal V() const;

	mkReal V(mkReal rho) const;

	mkReal V(mkReal rho, mkReal c) const;

	/* return velocity in z-direction */
	mkReal W() const ;

	mkReal W(mkReal rho) const;

	mkReal W(mkReal rho, mkReal c) const;

	mkVector3d velocity() const;

	mkVector3d velocity(mkReal rho) const;

	mkVector3d velocity(mkReal rho, mkReal c) const;

	/*  bounceback D3Q19 lattice */
	const mkPDFs bounce() const;
};
// end of class mkPDFs

#endif
