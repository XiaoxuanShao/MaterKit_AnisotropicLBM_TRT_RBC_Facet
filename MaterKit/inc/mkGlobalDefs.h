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
#ifndef MK_GLOBAL_DEFS_H
#define MK_GLOBAL_DEFS_H

#ifndef MK_OMP_CHUNKSIZE
#define MK_OMP_CHUNKSIZE  16
#endif

////omp_get_num_procs() 函数会返回机器的核心数
//#ifndef MK_OMP_NUMTHREADS
//#define MK_OMP_NUMTHREADS 7
////#define MK_OMP_NUMTHREADS omp_get_num_procs()-1
//#endif

//#ifndef MC_FREE_TRIALS
//#define MC_FREE_TRIALS
//#endif

///used in mcFunction.cpp
///in Microsoft Visual Studio 2010, it must be defined!
///to create .dll file used in Windows 7~8.1_x64, it must NOT be defined!
//#ifndef MK_WINDOWS
//#define MK_WINDOWS
//#endif

///to be used for the GNU GCC compiler
///to create .dll file used in Windows 7~8.1_x64, it must be defined!
//#ifndef MK_LINUX
//#define MK_LINUX
//#endif


///You are probably including windows.h somewhere, which defines macros named max and min.
///You can #define NOMINMAX before including windows.h to prevent it from defining those macros,
///or you can prevent macro invocation by using an extra set of parentheses:
///column = (std::max)(1u, column + count);
#if defined(MK_WINDOWS)
#ifdef MK_LINUX
#error You can only #define MK_WINDOWS or MK_LINUX, not both.
#endif
#define NOMINMAX
#include <windows.h>
#include <io.h>
#include <direct.h>
#elif defined(MK_LINUX)
#include <sys/types.h>
#include <dirent.h>
#else
#error You must define MK_WINDOWS or MK_LINUX
#endif

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

#include <cassert>
#include <climits>

#include <iostream> // for the use of 'cout'
#include <fstream>  // file streams
#include <sstream>  // string streams
#include <iomanip>

#include <string>
#include <vector>
#include <map>

#include <omp.h>

using namespace std;

static const string workspace = "..\\data\\";
//static const string workspace = "../data/";

extern char dir_subworkspace[FILENAME_MAX];

#ifdef MK_WINDOWS
  const char dir_workspace[] = "..\\workspace\\";
  const char workspaceTecPath[] = "..\\workspace\\tec";
  const char workspaceVtkPath[] = "..\\workspace\\vtk";
  const char workspaceElePath[] = "..\\workspace\\ele";
  const char workspaceDatPath[] = "..\\workspace\\dat";
  const char makeWorkspaceTecPath[] = "mkdir ..\\workspace\\tec";
  const char makeWorkspaceVtkPath[] = "mkdir ..\\workspace\\vtk";
  const char makeWorkspaceElePath[] = "mkdir ..\\workspace\\ele";
  const char makeWorkspaceDatPath[] = "mkdir ..\\workspace\\dat";
#else
  const char dir_workspace[] = "../workspace/";
  const char workspaceTecPath[] = "../workspace/tec";
  const char workspaceVtkPath[] = "../workspace/vtk";
  const char workspaceElePath[] = "../workspace/ele";
  const char workspaceDatPath[] = "../workspace/dat";
  const char makeWorkspaceTecPath[] = "mkdir -p ../workspace/tec";
  const char makeWorkspaceVtkPath[] = "mkdir -p ../workspace/vtk";
  const char makeWorkspaceElePath[] = "mkdir -p ../workspace/ele";
  const char makeWorkspaceDatPath[] = "mkdir -p ../workspace/dat";
#endif

#ifndef PI
#define PI      3.14159265358979323846 //3.14159265
#endif

#ifndef GRAVITY
#define GRAVITY 0.0	    // the global gravity to use
#endif


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef K_BOLTZMANN
#define K_BOLTZMANN 1.3806515E-23	    //Boltzmann constant, J/K
#endif

#define QF  9   //for D3Q19/D2Q9 Flow/Phase Fields
#define QT  9   //for D3Q19/D3Q7/D2Q5  Temperature Field


///Attention： the labels below must not modified!
///They are used in mkMeshgen.dll
const int  is_inlet  =-1;
const int  is_outlet =-2;
const int  is_fluid  = 0;
const int  is_inter  = 1;
const int  is_solid  = 2;
const int  is_walls  = 3; //walls flags

//const   int is_obstacle = 1002; //obstacle flags fixed(not moving)
const int is_particle = 1003; //particle flags can moving(not fixed)
const int is_fs_inter = 1513; //interface of fluids and solids(particles)
const int is_fw_inter = 1511; //interface of fluids and walls/obstacle
const int is_bdy_rot  = 1530; //boundary with a rotation velocity
//static const int is_outlet   = 1521; //inlet flags

///Attention： the labels below can be modified！
const int  isLeftplate      = -3;
const int  isRightplate     = -4;
const int  isBdyPeriodic    = 0;
const int  isBdyVelocity    = 100;
const int  isBdyPressure    = 200;
const int  isBdyQuaterShear = 300;
const int  isBdyCouette     = 301;
const int  isBdyFreeslip    = 400;
const int  isBdySolidwalls  = 600;
const int  isBdySFieldConst = 700;

const int  isBdyRoller      = 800;


// small const，in mkFluids::phasefield_anisotropy();
#define MK_EPSILON 1.0E-12

typedef int mkInte;

#if defined(MK_SINGLE)
typedef float mkReal;
#ifdef MK_DOUBLE
#error You can only #define MK_SINGLE or MK_DOUBLE, not both.
#endif // mcDOUBLE
#elif defined(MK_DOUBLE)
typedef double mkReal;
#else
#error You must #define MK_SINGLE or MK_DOUBLE
#endif

/* precision dependent scalar math functions */

#if defined(MK_SINGLE)

#define REAL(x) (x ## f)					/* form a constant */
#define mkRecip(x) ((1.0f/(x)))				/* reciprocal */
#define mkSqrt(x) (sqrtf(x))			/* square root */
#define mkRecipSqrt(x) ((1.0f/sqrtf(x)))		/* reciprocal square root */
#define mkSin(x) (sinf(x))				/* sine */
#define mkCos(x) (cosf(x))				/* cosine */
#define mkFabs(x) (fabsf(x))			/* absolute value */
#define mkAtan2(y,x) (atan2f(y,x))		/* arc tangent with 2 args */
#define mkFMod(a,b) (fmodf(a,b))		/* modulo */
#define mkFloor(x) floorf(x)			/* floor */

#ifdef HAVE___ISNANF
#define mkIsNan(x) (__isnanf(x))
#elif defined(HAVE__ISNANF)
#define mkIsNan(x) (_isnanf(x))
#elif defined(HAVE_ISNANF)
#define mkIsNan(x) (isnanf(x))
#else
  /*
     fall back to _isnan which is the VC way,
     this may seem redundant since we already checked
     for _isnan before, but if isnan is detected by
     configure but is not found during compilation
     we should always make sure we check for __isnanf,
     _isnanf and isnanf in that order before falling
     back to a default
  */
#define mkIsNan(x) (_isnan(x))
#endif

#define mkCopySign(a,b) ((mkReal)copysignf(a,b))

#elif defined(MK_DOUBLE)

#define REAL(x) (x)
#define mkRecip(x) (1.0/(x))
#define mkSqrt(x) sqrt(x)
#define mkRecipSqrt(x) (1.0/sqrt(x))
#define mkSin(x) sin(x)
#define mkCos(x) cos(x)
#define mkFabs(x) fabs(x)
#define mkAtan2(y,x) atan2((y),(x))
#define mkFMod(a,b) (fmod((a),(b)))
#define mkFloor(x) floor(x)

#ifdef HAVE___ISNAN
#define mkIsNan(x) (__isnan(x))
#elif defined(HAVE__ISNAN)
#define mkIsNan(x) (_isnan(x))
#elif defined(HAVE_ISNAN)
#define mkIsNan(x) (isnan(x))
#else
#define mkIsNan(x) (_isnan(x))
#endif

#define mkCopySign(a,b) (copysign((a),(b)))

#define mkSQ(x) ((x) * (x)) // square function;

#define mkSign(x) (x>0.0?1.0:-1.0) // square function;

//#define mkMax(a, b)  (((a) > (b)) ? (a) : (b))
//#define mkMin(a, b)  (((a) < (b)) ? (a) : (b))

#else
#error You must #define MK_SINGLE or MK_DOUBLE
#endif


#ifdef MK_DEBUG
    #define MC_ASSERT( COND )        assert( COND );
    #define MC_PRECONDITION( COND )  assert( COND );
    #define MC_POSTCONDITION( COND ) assert( COND );
    #define MC_STATECHECK( A,B )     assert( (A) == (B) );
#else
    #define MK_ASSERT( COND )
    #define MK_PRECONDITION( COND )
    #define MK_POSTCONDITION( COND )
    #define MK_STATECHECK( A,B )
#endif  // MK_DEBUG


#endif
