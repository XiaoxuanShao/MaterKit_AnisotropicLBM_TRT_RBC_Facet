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
#ifndef MK_FLOWFIELD_H
#define MK_FLOWFIELD_H

#include "mkFluidsLBM.h"

class MK_API mkFlowField;

using namespace mkt;

class mkFlowField : virtual public mkFluidsLBM //single phase flow
{
public:
	mkFlowField();
	~mkFlowField();

	mkFlowField(const mkSpace & space);

	void initialize(const std::string& xmlfname);

	void initialize_geometry_Poiseuille();
};


#endif
