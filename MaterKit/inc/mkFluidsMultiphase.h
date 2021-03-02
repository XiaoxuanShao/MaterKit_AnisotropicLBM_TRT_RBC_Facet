//============================================================================
// Name        : LBM_FSI_MP.cpp
// Author      : DongKe SUN and Yuting CAO
// Version     : 2010.09.30 MoonLight
// Copyright   : All rights reserved.
// Description : C++, Ansi-style
// Last updated: 2021.01.28 by DongKe SUN and Yuting CAO
//============================================================================
// SUN DongKe, Ph.D
// Website     : http://www.materkit.com
// E-Mail      : dksun@seu.edu.cn and ytcao@seu.edu.cn
//============================================================================
#ifndef MK_FLUIDSMULTIPHASE_H
#define MK_FLUIDSMULTIPHASE_H

#include "mkFluidsMRT.h"

class MK_API mkFluidsMultiphase;

class mkFluidsMultiphase : virtual public mkFluidsMRT
{
public:
	mkFluidsMultiphase();

	mkFluidsMultiphase(const mkSpace & space);

	~mkFluidsMultiphase();

	//override the functions in class mkFluidsMRT, mkFluidsLBM
	void initialize(const std::string & xmlfname);

	//override the mkFluidsLBM::initialize_geometry()
	void initialize_geometry();

	void initialize_wetting(const std::string& xmlfname);

	void update_geometry(mkFluidsMRT & dendrite);

	//reset the functions in class mkPhaseField
	void phasefield_initialize();

	//bool compute_DD_phi(mkReal & DD_phi, const int & x, const int & y, const int & z);
	//bool compute_DD_phi_LB(mkReal& DD_phi, const int& x, const int& y, const int& z);
	//bool compute_Dn_phi(mkVector3d & Dn_phi, const int & x, const int & y, const int & z);
	//bool compute_Dn_phi_LB(mkVector3d& Dn_phi, const int& x, const int& y, const int& z);
	//bool compute_Dn_rho(mkVector3d & Dn_rho, const int & x, const int & y, const int & z);
	//bool compute_Dn_rho_LB(mkVector3d & Dn_phi, const int & x, const int & y, const int & z);
	bool compute_Dn_phi_LB2(mkVector3d& Dn_phi, const int& x, const int& y, const int& z);

	mkReal ATcurrent2(const int& n, const int& x, const int& y, const int& z);

	void propagate();

	//reset the functions in class mkPhaseField
	void relaxation();

	void relaxation_phi();

	void evolution_phi(const mkNode* nptr);

	//override the functions in class mkSolutalField
	void initialize_solute(const std::string & filename);

	void bdy_constX();
	void bdy_nonflux();
	void bdy_RBC();

	void boundary_vel();
	void boundary_Couette();

	//override the functions in class mkFluidsMRT
	void write_vtkfile(int loops);
	void write_velocity(int loops);

private:
	void readParameters(const std::string& xmlfname);

	mkReal rho_l;// = 10.0;
	mkReal rho_g;// = 1.0000;
	mkReal sigma;// = 0.001;//  //表面张力系数
	mkReal W_0;// = 5.0;//界面厚度影响各向异性的显现出来的程度。
	mkReal mu_l;// 
	mkReal mu_g;//
	mkReal niu_ratio;// = 1.0;
	mkReal niu_l;// = 0.1;
	mkReal niu_g;// = niu_l * niu_ratio;

	mkReal beta;// = 12.0 * sigma / W_0;
	mkReal kappa;// = 1.5 * sigma * W_0;  //与界面厚度、表面张力相关，参考Liang PRE14
	mkReal theta;// wetting 

	mkReal mobility_dimless;// = 0.1;

	mkReal omega_g;// = 1.25;

	mkReal eta; //Liang PRE2014 controls the mobility

	mkPDFs F_term, G_term;
};

#endif
