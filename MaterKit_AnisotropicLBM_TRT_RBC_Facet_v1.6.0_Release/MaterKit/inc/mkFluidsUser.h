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
#ifndef MK_MKFLUIDSUSER_H
#define MK_MKFLUIDSUSER_H

#include "mkFluidsMRT.h"

class mkFluidsUser;

class mkFluidsUser : virtual public mkFluidsMRT
{
public:
	mkFluidsUser();
	mkFluidsUser(const mkSpace & space);
	~mkFluidsUser();

	//override the functions in class mkFluidsMRT, mkFluidsLBM
	void initialize(const std::string & xmlfname);

	//override the mkFluidsLBM::initialize_geometry()
	void initialize_geometry();

	//reset the functions in class mkPhaseField
	void initialize_phasefield(const std::string& xmlfname);

	//override the functions in class mkSolutalField
	void initialize_solutalfield(const std::string & filename);

	void bdy_constX();
	void bdy_nonflux();
	void bdy_RBC();

	void boundary_vel();
	void boundary_Couette();

	//override the functions in class mkFluidsMRT
	void write_vtkfile(int loops);
};

#endif
