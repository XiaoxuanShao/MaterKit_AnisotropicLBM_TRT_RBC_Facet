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
#ifndef MK_FLUIDSMRT_H
#define MK_FLUIDSMRT_H

#include "mkFluidsLBM.h"
#include "mkFlowField.h"
#include "mkPhaseField.h"
#include "mkThermalField.h"
#include "mkSolutalField.h"

class MK_API mkFluidsMRT;

// MRT single phase flow
class mkFluidsMRT : 
	virtual public mkFluidsLBM, \
    virtual public mkFlowField, \
    virtual public mkThermalField, \
    virtual public mkSolutalField, \
    virtual public mkPhaseField
{
public:
	mkFluidsMRT();
	~mkFluidsMRT();

	mkFluidsMRT(const mkSpace & space);

	void initialize(const std::string & xmlfname);

	void bounceback();
	void propagate(); //...propagate
	void propagate_PBB(); //...propagate
	void relaxation();//...relaxation
	void relaxation(const mkNode * nptr);

	virtual void write_vtkfile(int loops);
};


#endif
