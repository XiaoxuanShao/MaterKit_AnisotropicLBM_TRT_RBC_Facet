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
#ifndef MK_VECTOR3I_H
#define MK_VECTOR3I_H

#include "MaterKit.h"
#include "mkGlobalDefs.h" 
#include "mkVector03d.h"

class mkVector3d;
class mkVector3i   //
{
public:

	/** Number of vector components. */
	enum { num_components = 3 };

	int _v[3];

	mkVector3i() { _v[0]=0; _v[1]=0; _v[2]=0;}

	mkVector3i(int x, int y, int z) { _v[0]=x; _v[1]=y; _v[2]=z; }

	inline bool operator == (const mkVector3i& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2]; }

	inline bool operator != (const mkVector3i& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2]; }

	inline bool operator <  (const mkVector3i& v) const
	{
		if (_v[0]<v._v[0]) return true;
		else if (_v[0]>v._v[0]) return false;
		else if (_v[1]<v._v[1]) return true;
		else if (_v[1]>v._v[1]) return false;
		else return (_v[2]<v._v[2]);
	}

	inline int* ptr() { return _v; }
	inline const int* ptr() const { return _v; }

	inline void set( int x, int y, int z)
	{
		_v[0]=x; _v[1]=y; _v[2]=z;
	}

	inline void set( const mkVector3i& rhs)
	{
		_v[0]=rhs._v[0]; _v[1]=rhs._v[1]; _v[2]=rhs._v[2];
	}

	inline int& operator [] (int i) { return _v[i]; }
	inline int operator [] (int i) const { return _v[i]; }

	inline int& x() { return _v[0]; }
	inline int& y() { return _v[1]; }
	inline int& z() { return _v[2]; }

	inline int x() const { return _v[0]; }
	inline int y() const { return _v[1]; }
	inline int z() const { return _v[2]; }

	/* Dot product. */
	inline int operator * (const mkVector3i& rhs) const
	{
		return _v[0]*rhs._v[0]+_v[1]*rhs._v[1]+_v[2]*rhs._v[2];
	}

	/* Cross product. */
	inline const mkVector3i operator ^ (const mkVector3i& rhs) const
	{
		return mkVector3i(_v[1]*rhs._v[2]-_v[2]*rhs._v[1],
			_v[2]*rhs._v[0]-_v[0]*rhs._v[2] ,
			_v[0]*rhs._v[1]-_v[1]*rhs._v[0]);
	}

	/** Multiply by scalar. */
	inline const mkVector3i operator * (int rhs) const
	{
		return mkVector3i(_v[0]*rhs, _v[1]*rhs, _v[2]*rhs);
	}

	inline const mkVector3d operator * (mkReal rhs) const
	{
		return mkVector3d(_v[0]*rhs, _v[1]*rhs, _v[2]*rhs);
	}

	/** Unary multiply by scalar. */
	inline mkVector3i& operator *= (int rhs)
	{
		_v[0]*=rhs;
		_v[1]*=rhs;
		_v[2]*=rhs;
		return *this;
	}
	//inline mkVector3i& operator *= (mkReal rhs)
	//{
	//	_v[0]*=rhs;
	//	_v[1]*=rhs;
	//	_v[2]*=rhs;
	//	return *this;
	//}

	/** Divide by scalar. */
	inline const mkVector3i operator / (int rhs) const
	{
		return mkVector3i(_v[0]/rhs, _v[1]/rhs, _v[2]/rhs);
	}
	inline const mkVector3d operator / (mkReal rhs) const
	{
		return mkVector3d(_v[0]/rhs, _v[1]/rhs, _v[2]/rhs);
	}

	/** Unary divide by scalar. */
	inline mkVector3i& operator /= (int rhs)
	{
		_v[0]/=rhs;
		_v[1]/=rhs;
		_v[2]/=rhs;
		return *this;
	}
	//inline mkVector3i& operator /= (mkReal rhs)
	//{
	//	_v[0]/=rhs;
	//	_v[1]/=rhs;
	//	_v[2]/=rhs;
	//	return *this;
	//}

	/* Binary vector add. */
	inline const mkVector3i operator + (const mkVector3i& rhs) const
	{
		return mkVector3i(_v[0]+rhs._v[0], _v[1]+rhs._v[1], _v[2]+rhs._v[2]);
	}

	/* Unary vector add. Slightly more efficient because no temporary intermediate object. */
	inline mkVector3i& operator += (const mkVector3i& rhs)
	{
		_v[0] += rhs._v[0];
		_v[1] += rhs._v[1];
		_v[2] += rhs._v[2];
		return *this;
	}

	/* Binary vector subtract. */
	inline const mkVector3i operator - (const mkVector3i& rhs) const
	{
		return mkVector3i(_v[0]-rhs._v[0], _v[1]-rhs._v[1], _v[2]-rhs._v[2]);
	}

	/** Unary vector subtract. */
	inline mkVector3i& operator -= (const mkVector3i& rhs)
	{
		_v[0]-=rhs._v[0];
		_v[1]-=rhs._v[1];
		_v[2]-=rhs._v[2];
		return *this;
	}

	/** Negation operator. Returns the negative of the Vec3f. */
	inline const mkVector3i operator - () const
	{
		return mkVector3i (-_v[0], -_v[1], -_v[2]);
	}

	/** Length of the vector = sqrt( vec . vec ) */
	inline double length() const
	{
		return mkSqrt(1.0*( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] ));
	}

	/** Length squared of the vector = vec . vec */
	inline int length2() const
	{
		return _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2];
	}

	/** Normalize the vector so that it has length unity.
	* Returns the previous length of the vector.
	*/
	inline mkVector3d normalize()
	{
		mkVector3d tmp(_v[0],_v[1],_v[2]);
		tmp.normalize();
		return tmp;//mkVector3d();
	}
};    // end of class mkVector3i

#endif
