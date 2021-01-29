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
#ifndef MK_THERMALFIELD_H
#define MK_THERMALFIELD_H

#include "mkFluidsLBM.h"

class MK_API mkThermalField;

using namespace mkt;

class mkThermalField : virtual public mkFluidsLBM
{
public:
	mkThermalField(){};
	~mkThermalField(){};

	mkThermalField(const mkSpace & space) : mkFluidsLBM(space) {};

	void initialize(const std::string& xmlfname);

    void propagate();
	void relaxation();
	void relaxation(const mkFluidsMRT & flow);
	void update_velocity(const mkFluidsMRT & flow);
	void bdy_RBC();
	void bdy_noflux();
	void bdy_flowin();
	void bdy_constT();
};

#endif
