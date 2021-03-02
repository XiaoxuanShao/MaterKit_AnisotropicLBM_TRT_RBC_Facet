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
#ifndef MK_VECTOR3D_H
#define MK_VECTOR3D_H

#include "MaterKit.h"
#include "mkGlobalDefs.h"

#include "mkVector03i.h"
class mkVector3i;
class mkVector3d
{
public:

	/** Type of Vec class.*/
//	typedef mkReal mkReal;

	/** Number of vector components. */
	enum { num_components = 3 };

	mkReal _v[3];

	mkVector3d() { _v[0]=0.0f; _v[1]=0.0f; _v[2]=0.0f;}

	mkVector3d(mkReal x, mkReal y, mkReal z) { _v[0]=x; _v[1]=y; _v[2]=z; }

	inline bool operator == (const mkVector3d& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2]; }

	inline bool operator != (const mkVector3d& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2]; }

	inline bool operator <  (const mkVector3d& v) const
	{
		if (_v[0]<v._v[0]) return true;
		else if (_v[0]>v._v[0]) return false;
		else if (_v[1]<v._v[1]) return true;
		else if (_v[1]>v._v[1]) return false;
		else return (_v[2]<v._v[2]);
	}

	inline mkReal* ptr() { return _v; }
	inline const mkReal* ptr() const { return _v; }

	inline void set( mkReal x, mkReal y, mkReal z)
	{
		_v[0]=x; _v[1]=y; _v[2]=z;
	}

	inline void set( const mkVector3d& rhs)
	{
		_v[0]=rhs._v[0]; _v[1]=rhs._v[1]; _v[2]=rhs._v[2];
	}

	inline void add( mkReal x, mkReal y, mkReal z)
	{
		_v[0]+=x; _v[1]+=y; _v[2]+=z;
	}

	inline void sub( mkReal x, mkReal y, mkReal z)
	{
		_v[0]-=x; _v[1]-=y; _v[2]-=z;
	}

	inline mkReal& operator [] (int i)       { return _v[i]; }
	inline mkReal  operator [] (int i) const { return _v[i]; }

	inline mkReal& x() { return _v[0]; }
	inline mkReal& y() { return _v[1]; }
	inline mkReal& z() { return _v[2]; }

	inline mkReal x() const { return _v[0]; }
	inline mkReal y() const { return _v[1]; }
	inline mkReal z() const { return _v[2]; }

	/** Dot product. */
	inline mkReal operator * (const mkVector3d& rhs) const
	{
		return _v[0]*rhs._v[0]+_v[1]*rhs._v[1]+_v[2]*rhs._v[2];
	}

	/** Cross product. */
	inline const mkVector3d operator ^ (const mkVector3d& rhs) const
	{
		return mkVector3d(_v[1]*rhs._v[2]-_v[2]*rhs._v[1],
			_v[2]*rhs._v[0]-_v[0]*rhs._v[2] ,
			_v[0]*rhs._v[1]-_v[1]*rhs._v[0]);
	}

	/** Multiply by scalar. */
	inline const mkVector3d operator * (mkReal rhs) const
	{
		return mkVector3d(_v[0]*rhs, _v[1]*rhs, _v[2]*rhs);
	}

	/** Unary multiply by scalar. */
	inline mkVector3d& operator *= (mkReal rhs)
	{
		_v[0]*=rhs;
		_v[1]*=rhs;
		_v[2]*=rhs;
		return *this;
	}

	/** Divide by scalar. */
	inline const mkVector3d operator / (mkReal rhs) const
	{
		return mkVector3d(_v[0]/rhs, _v[1]/rhs, _v[2]/rhs);
	}

	/** Unary divide by scalar. */
	inline mkVector3d& operator /= (mkReal rhs)
	{
		_v[0]/=rhs;
		_v[1]/=rhs;
		_v[2]/=rhs;
		return *this;
	}

	/** Binary vector add. */
	inline const mkVector3d operator + (const mkVector3d& rhs) const
	{
		return mkVector3d(_v[0]+rhs._v[0], _v[1]+rhs._v[1], _v[2]+rhs._v[2]);
	}

	/** Unary vector add. Slightly more efficient because no temporary
	* intermediate object.
	*/
	inline mkVector3d& operator += (const mkVector3d& rhs)
	{
		_v[0] += rhs._v[0];
		_v[1] += rhs._v[1];
		_v[2] += rhs._v[2];
		return *this;
	}

	/** Binary vector subtract. */
	inline const mkVector3d operator - (const mkVector3d& rhs) const
	{
		return mkVector3d(_v[0]-rhs._v[0], _v[1]-rhs._v[1], _v[2]-rhs._v[2]);
	}

	/** Unary vector subtract. */
	inline mkVector3d& operator -= (const mkVector3d& rhs)
	{
		_v[0]-=rhs._v[0];
		_v[1]-=rhs._v[1];
		_v[2]-=rhs._v[2];
		return *this;
	}

	/** Negation operator. Returns the negative of the Vec3f. */
	inline const mkVector3d operator - () const
	{
		return mkVector3d (-_v[0], -_v[1], -_v[2]);
	}

	/** Length of the vector = sqrt( vec . vec ) */
	inline mkReal length() const
	{
		return mkSqrt( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] );
	}

	/** Length squared of the vector = vec . vec */
	inline mkReal length_sq() const
	{
		return _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2];
	}

	/** Normalize the vector so that it has length unity.
	* Returns the previous length of the vector.
	*/
	inline mkVector3d normalize()
	{
		mkReal inv = 0;
		mkReal norm = mkVector3d::length();
		if (norm>0.0)
		{
			inv = 1.0f/norm;
		}
		_v[0] *= inv;
		_v[1] *= inv;
		_v[2] *= inv;
		return mkVector3d( _v[0],_v[1],_v[2] );
	}

	// angle between the current vector and
	// the direction along with the x-axis.
	inline mkReal angle()
	{
		//mkReal x = _v[0];
		//mkReal y = mcSqrt( _v[1]*_v[1] + _v[2]*_v[2] );
		return atan2(mkSqrt( _v[1]*_v[1] + _v[2]*_v[2] ), _v[0]);
	}

	// angle between the current vector and
	// the direction along with the x-axis.
	inline mkReal angle(const mkVector3d & rhs)
	{
		mkReal x = _v[0]*rhs._v[0]+_v[1]*rhs._v[1]+_v[2]*rhs._v[2];

		mkVector3d tmp(_v[1]*rhs._v[2]-_v[2]*rhs._v[1],
			_v[2]*rhs._v[0]-_v[0]*rhs._v[2] ,
			_v[0]*rhs._v[1]-_v[1]*rhs._v[0]);

		mkReal y = tmp.length();
		return atan2(y, x);
	}
};    // end of class mkVector3d

#endif
