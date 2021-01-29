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
#ifndef MK_LATTICE_H
#define MK_LATTICE_H

#include "MaterKit.h"
#include "mkGlobalDefs.h" 
#include "mkPDFs.h"
#include "mkVectors.h"


class MK_API mkLattice;

/// D3Q19/D2Q9 for flow field, and D3Q7/D2Q5 for scalar fields
class mkLattice
{
public:

	mkLattice();
	~mkLattice();

	mkVector3i    e[QF];
	mkVector3d    c[QF];
	mkVector19i   inv;

	mkReal        cl;      //格子速度
	mkReal        cs;      //格子声速
	mkReal        cs_squ;
	mkReal        cs_1;
	mkReal        cs_2;
	mkReal		  cs_3;
	mkPDFs        weight;

	mkReal        cs_scalar;
	mkReal        cs_squ_scalar;
	mkReal		  cs_1_scalar;
	mkReal        cs_2_scalar;
	mkReal        cs_3_scalar;
	mkPDFs        weight_scalar;

	//Phase-field modeling by the method of lattice Boltzmann equations, PHYSICAL REVIEW E 81, 036707 - 2010 
	//Phase-field-based multiple-relaxation-time lattice Boltzmann, PHYSICAL REVIEW E 89, 053320 (2014)
	mkReal        eta ; //an adjustable parameter that controls the mobility, used for the D2Q9 model

	//int inv[19];//inverse direction of i-th direction

public:

	//void mrtShowMatrix(const char * matrix_name, double *p, int m, int n);
	//void mrtSetSdiag(double omega = 1.0);
	//void mrtAssign(double *ap, int n);
	//void mrtInverse(void);
	//void mrtMultiplyVector(double *pC, double *pA, double *pB, int m, int n);
	//void mrtMultiply(double *pC, double *pA, double *pB, int m, int n, int k);

	void setSdiag(double omega); 
	void setSdiag2(double omega);//.for large omega

	void setMartrix(double *ap = NULL, int n = QF);
	//converse inverse matrix
	void setMinverse(void);

	void MultiplyVector(double *pC, double *pA, double *pB, int m = QF, int n = QF);
	void Multiply(double *pC, double *pA, double *pB, int m = QF, int n = QF, int k = QF);

	void setMiS(mkReal omega);

	void setLambda(mkReal omega);

	void showMatrix(const char * matrix_name, double *p, int m, int n);
	void initialize(mkReal omega);

	mkReal & omega();// { return Omega; }
	mkReal   omega() const;// { return Omega; }
	void     setOmega(const mkReal & omega);// { Omega = omega; }
	
	mkReal Sdiag[QF][QF];
	mkReal M[QF][QF];
	mkReal Mi[QF][QF]; //M inverse
	mkReal MiS[QF][QF]; // M_inverse * S
	mkReal MiImhalfS[QF][QF];// M_inverse * (I - S / 2)

	mkReal ImhalfS[QF][QF];// I - S/2
	mkReal Lambda[QF][QF];//mkReal S[QF][QF];
	mkReal Lambda2[QF][QF];//M_inverse * (I - S/2) * M

private:
	mkReal Omega;
};
#endif