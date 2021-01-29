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
#ifndef MK_VECTOR19D_H
#define MK_VECTOR19D_H

#include "MaterKit.h"
#include "mkGlobalDefs.h"

class mkVector3d;
class mkVector19d   //19Œ¨œÚ¡ø
{
public:

	/* Number of vector components. */
	enum { num_components = 19 };

	mkReal _v[19];

	mkVector19d()
	{
		_v[ 0]=0.0f;
		_v[ 1]=0.0f; _v[ 2]=0.0f; _v[ 3]=0.0f; _v[ 4]=0.0f; _v[ 5]=0.0f; _v[ 6]=0.0f;
		_v[ 7]=0.0f; _v[ 8]=0.0f; _v[ 9]=0.0f; _v[10]=0.0f; _v[11]=0.0f; _v[12]=0.0f;
		_v[13]=0.0f; _v[14]=0.0f; _v[15]=0.0f; _v[16]=0.0f; _v[17]=0.0f; _v[18]=0.0f;
	}
	mkVector19d(
		mkReal v0,
		mkReal v1, mkReal v2, mkReal v3, mkReal v4, mkReal v5, mkReal v6, \
		mkReal v7, mkReal v8, mkReal v9, mkReal v10,mkReal v11,mkReal v12,\
		mkReal v13,mkReal v14,mkReal v15,mkReal v16,mkReal v17,mkReal v18)
	{
		_v[ 0]=v0;
		_v[ 1]=v1;  _v[ 2]=v2;  _v[ 3]=v3;  _v[ 4]=v4;  _v[ 5]=v5;  _v[ 6]=v6;
		_v[ 7]=v7;  _v[ 8]=v8;  _v[ 9]=v9;  _v[10]=v10; _v[11]=v11; _v[12]=v12;
		_v[13]=v13; _v[14]=v14; _v[15]=v15; _v[16]=v16; _v[17]=v17; _v[18]=v18;
	}

	inline mkReal* ptr() { return _v; }
	inline const mkReal* ptr() const { return _v; }

	inline void set(
		mkReal f0,
		mkReal f1, mkReal f2, mkReal f3, mkReal f4, mkReal f5, mkReal f6, \
		mkReal f7, mkReal f8, mkReal f9, mkReal f10,mkReal f11,mkReal f12,\
		mkReal f13,mkReal f14,mkReal f15,mkReal f16,mkReal f17,mkReal f18)
	{
		_v[ 0]=f0;
		_v[ 1]=f1;  _v[ 2]=f2;  _v[ 3]=f3;  _v[ 4]=f4;  _v[ 5]=f5;  _v[ 6]=f6;
		_v[ 7]=f7;  _v[ 8]=f8;  _v[ 9]=f9;  _v[10]=f10; _v[11]=f11; _v[12]=f12;
		_v[13]=f13; _v[14]=f14; _v[15]=f15; _v[16]=f16; _v[17]=f17; _v[18]=f18;
	}

	inline void set(const mkVector19d& rhs)
	{
		_v[ 0]=rhs._v[ 0];
		_v[ 1]=rhs._v[ 1]; _v[ 2]=rhs._v[ 2]; _v[ 3]=rhs._v[ 3]; _v[ 4]=rhs._v[ 4]; _v[ 5]=rhs._v[ 5] ;_v[ 6]=rhs._v[ 6];
		_v[ 7]=rhs._v[ 7]; _v[ 8]=rhs._v[ 8]; _v[ 9]=rhs._v[ 9]; _v[10]=rhs._v[10]; _v[11]=rhs._v[11]; _v[12]=rhs._v[12];
		_v[13]=rhs._v[13]; _v[14]=rhs._v[14]; _v[15]=rhs._v[15]; _v[16]=rhs._v[16]; _v[17]=rhs._v[17]; _v[18]=rhs._v[18];
	}

	inline mkReal& operator [] (int i) { return _v[i]; }
	inline mkReal operator [] (int i) const { return _v[i]; }


	/* Dot product. */
	inline mkReal operator * (const mkVector19d& rhs) const
	{
		return _v[0]*rhs._v[0] \
		+ _v[ 1]*rhs._v[ 1] + _v[ 2]*rhs._v[ 2] + _v[ 3]*rhs._v[ 3] + _v[ 4]*rhs._v[ 4] + _v[ 5]*rhs._v[ 5] + _v[ 6]*rhs._v[ 6] \
		+ _v[ 7]*rhs._v[ 7] + _v[ 8]*rhs._v[ 8] + _v[ 9]*rhs._v[ 9] + _v[10]*rhs._v[10] + _v[11]*rhs._v[11] + _v[12]*rhs._v[12] \
		+ _v[13]*rhs._v[13] + _v[14]*rhs._v[14] + _v[15]*rhs._v[15] + _v[16]*rhs._v[16] + _v[17]*rhs._v[17] + _v[18]*rhs._v[18];
	}

	/* Multiply by scalar. */
	inline const mkVector19d operator * (mkReal rhs) const
	{
		return mkVector19d(_v[ 0]*rhs, \
			_v[ 1]*rhs,_v[ 2]*rhs,_v[ 3]*rhs,_v[ 4]*rhs,_v[ 5]*rhs,_v[ 6]*rhs, \
			_v[ 7]*rhs,_v[ 8]*rhs,_v[ 9]*rhs,_v[10]*rhs,_v[11]*rhs,_v[12]*rhs, \
			_v[13]*rhs,_v[14]*rhs,_v[15]*rhs,_v[16]*rhs,_v[17]*rhs,_v[18]*rhs);
	}

	/* Unary multiply by scalar. */
	inline mkVector19d& operator *= (mkReal rhs)
	{
		_v[ 0]*=rhs;
		_v[ 1]*=rhs; _v[ 2]*=rhs; _v[ 3]*=rhs; _v[ 4]*=rhs; _v[ 5]*=rhs; _v[ 6]*=rhs;
		_v[ 7]*=rhs; _v[ 8]*=rhs; _v[ 9]*=rhs; _v[10]*=rhs; _v[11]*=rhs; _v[12]*=rhs;
		_v[13]*=rhs; _v[14]*=rhs; _v[15]*=rhs; _v[16]*=rhs; _v[17]*=rhs; _v[18]*=rhs;
		return *this;
	}

	/** Divide by scalar. */
	inline const mkVector19d operator / (mkReal rhs) const
	{
		return mkVector19d(_v[ 0]/rhs,
			_v[ 1]/rhs, _v[ 2]/rhs, _v[ 3]/rhs, _v[ 4]/rhs, _v[ 5]/rhs, _v[ 6]/rhs,
			_v[ 7]/rhs, _v[ 8]/rhs, _v[ 9]/rhs, _v[10]/rhs, _v[11]/rhs, _v[12]/rhs,
			_v[13]/rhs, _v[14]/rhs, _v[15]/rhs, _v[16]/rhs, _v[17]/rhs, _v[18]/rhs);
	}

	/** Unary divide by scalar. */
	inline mkVector19d& operator /= (mkReal rhs)
	{
		_v[ 0]/=rhs;
		_v[ 1]/=rhs; _v[ 2]/=rhs; _v[ 3]/=rhs; _v[ 4]/=rhs; _v[ 5]/=rhs; _v[ 6]/=rhs;
		_v[ 7]/=rhs; _v[ 8]/=rhs; _v[ 9]/=rhs; _v[10]/=rhs; _v[11]/=rhs; _v[12]/=rhs;
		_v[13]/=rhs; _v[14]/=rhs; _v[15]/=rhs; _v[16]/=rhs; _v[17]/=rhs; _v[18]/=rhs;
		return *this;
	}

	/** Binary vector add. */
	inline const mkVector19d operator + (const mkVector19d& rhs) const
	{
		return mkVector19d(_v[ 0]+rhs._v[ 0],
			_v[ 1]+rhs._v[ 1], _v[ 2]+rhs._v[ 2], _v[ 3]+rhs._v[ 3], _v[ 4]+rhs._v[ 4], _v[ 5]+rhs._v[ 5], _v[ 6]+rhs._v[ 6],
			_v[ 7]+rhs._v[ 7], _v[ 8]+rhs._v[ 8], _v[ 9]+rhs._v[ 9], _v[10]+rhs._v[10], _v[11]+rhs._v[11], _v[12]+rhs._v[12],
			_v[13]+rhs._v[13], _v[14]+rhs._v[14], _v[15]+rhs._v[15], _v[16]+rhs._v[16], _v[17]+rhs._v[17], _v[18]+rhs._v[18]);
	}

	/* Unary vector add. Slightly more efficient because no temporary */
	/* intermediate object.*/
	inline mkVector19d& operator += (const mkVector19d& rhs)
	{
		_v[ 0]+=rhs._v[ 0];
		_v[ 1]+=rhs._v[ 1]; _v[ 2]+=rhs._v[ 2]; _v[ 3]+=rhs._v[ 3]; _v[ 4]+=rhs._v[ 4]; _v[ 5]+=rhs._v[ 5]; _v[ 6]+=rhs._v[ 6];
		_v[ 7]+=rhs._v[ 7]; _v[ 8]+=rhs._v[ 8]; _v[ 9]+=rhs._v[ 9]; _v[10]+=rhs._v[10]; _v[11]+=rhs._v[11]; _v[12]+=rhs._v[12];
		_v[13]+=rhs._v[13]; _v[14]+=rhs._v[14]; _v[15]+=rhs._v[15]; _v[16]+=rhs._v[16]; _v[17]+=rhs._v[17]; _v[18]+=rhs._v[18];
		return *this;
	}

	/* Binary vector subtract. */
	inline const mkVector19d operator - (const mkVector19d& rhs) const
	{
		return mkVector19d(_v[ 0]-rhs._v[ 0],
			_v[ 1]-rhs._v[ 1], _v[ 2]-rhs._v[ 2], _v[ 3]-rhs._v[ 3], _v[ 4]-rhs._v[ 4], _v[ 5]-rhs._v[ 5], _v[ 6]-rhs._v[ 6],
			_v[ 7]-rhs._v[ 7], _v[ 8]-rhs._v[ 8], _v[ 9]-rhs._v[ 9], _v[10]-rhs._v[10], _v[11]-rhs._v[11], _v[12]-rhs._v[12],
			_v[13]-rhs._v[13], _v[14]-rhs._v[14], _v[15]-rhs._v[15], _v[16]-rhs._v[16], _v[17]-rhs._v[17], _v[18]-rhs._v[18]);
	}

	/* Unary vector subtract. */
	inline mkVector19d& operator -= (const mkVector19d& rhs)
	{
		_v[ 0]-=rhs._v[ 0];
		_v[ 1]-=rhs._v[ 1]; _v[ 2]-=rhs._v[ 2]; _v[ 3]-=rhs._v[ 3]; _v[ 4]-=rhs._v[ 4]; _v[ 5]-=rhs._v[ 5]; _v[ 6]-=rhs._v[ 6];
		_v[ 7]-=rhs._v[ 7]; _v[ 8]-=rhs._v[ 8]; _v[ 9]-=rhs._v[ 9]; _v[10]-=rhs._v[10]; _v[11]-=rhs._v[11]; _v[12]-=rhs._v[12];
		_v[13]-=rhs._v[13]; _v[14]-=rhs._v[14]; _v[15]-=rhs._v[15]; _v[16]-=rhs._v[16]; _v[17]-=rhs._v[17]; _v[18]-=rhs._v[18];
		return *this;
	}

	/* Negation operator. Returns the negative of the Vec3f. */
	inline const mkVector19d operator - () const
	{
		return mkVector19d (-_v[0], \
			-_v[ 1], -_v[ 2], -_v[ 3], -_v[ 4], -_v[ 5], -_v[ 6], \
			-_v[ 7], -_v[ 8], -_v[ 9], -_v[10], -_v[11], -_v[12], \
			-_v[13], -_v[14], -_v[15], -_v[16], -_v[17], -_v[18]);
	}
	/* return sum of all components*/
	inline mkReal sum() const
	{
		return ( _v[0]\
			+ _v[ 1] + _v[ 2] + _v[ 3] + _v[ 4] + _v[ 5] + _v[ 6] \
			+ _v[ 7] + _v[ 8] + _v[ 9] + _v[10] + _v[11] + _v[12] \
			+ _v[13] + _v[14] + _v[15] + _v[16] + _v[17] + _v[18]);
	}

};  // end of class mkVector19d

#endif
