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
#ifndef MK_AILBFLOW_H
#define MK_AILBFLOW_H

#include "MaterKit.h"

#include "mkPDFs.h"
#include "mkLattice.h"

#include "mkGlobalDefs.h"
#include "mkGlobalDefsMkt.h"
#include "mkTriangleSet.h"
#include "mkCPUTimer.h"

#include "mkTINYXMLIO.h"
#include "mkTINYXMLIO.hh"

#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include <iostream> // for the use of 'cout'
#include <fstream>  // file streams
#include <sstream>  // string streams
#include <iomanip>



#ifndef MK_RAYLEIGHBERNARD_C
#define MK_RAYLEIGHBERNARD_C
#endif
#ifndef MK_RAYLEIGHBERNARD_T
#define MK_RAYLEIGHBERNARD_T
#endif


////considering the the moving ball inside the fluids
//#ifndef COUPLED_BALL
//#define COUPLED_BALL
//#endif

////considering the rotation of the moving body
//#ifndef WITH_ROTATION
//#define WITH_ROTATION
//#endif

//#ifndef TWODIMENSIONAL
//#define TWODIMENSIONAL
//#endif
//
//#ifndef TWODIM_COUETTE
//#define TWODIM_COUETTE
//#endif

//#ifndef CURVED_CHANNEL
//#define CURVED_CHANNEL
//#endif

//#ifdef CURVED_CHANNEL
//#ifndef SPIRAL_CHANNEL
//#define SPIRAL_CHANNEL
//#endif
//#endif

using namespace std; // permanently use the standard namespace

extern MK_API mkLattice lattice;

extern MK_API mkCPUTimer *timer;

#endif
