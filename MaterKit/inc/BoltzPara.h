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

#ifndef MK_BOLTZPARA_H
#define MK_BOLTZPARA_H

#include "mkFluidsLBM.h"

namespace mkt
{
	static void initParaSpace(mkSpace *space);

	static void initParaFluids(mkFluidsLBM & flow, mkSpace & space);

	static void initParaBodies(mkSphere & ball, const mkSpace & space);
}
#endif
