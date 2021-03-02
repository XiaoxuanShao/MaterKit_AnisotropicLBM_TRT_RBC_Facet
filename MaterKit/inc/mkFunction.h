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
#ifndef MK_FUNCTION_H
#define MK_FUNCTION_H

#include "MaterKit.h"
#include "mkGlobalDefs.h"
#include "mkGlobalDefsMkt.h"

#include "mkPDFs.h"
#include "mkVectors.h"


#include "AiLBFlow.h"
#include "mkFluidsLBM.h"

#include <iostream>
#include <algorithm>
#include <cstring>
#include <assert.h>


#ifdef MK_WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace mkt
{
    extern MK_API int global_iter;
    extern MK_API mkReal global_time;

    extern MK_API FILE * docfp;
    extern MK_API char filename[];

    extern MK_API std::string scmpSwitch;
    extern MK_API std::string mcmpSwitch;

	static bool error(FALSE);

	extern "C"
	{
		MK_API void   SystemPause();
		MK_API int    make_datafolder();
		MK_API int    make_numthreads();
	}

    extern MK_API void readParameters(int & maxLoops, int & maxFrame, const string & xmlFileName);

	extern MK_API mkReal mkRandNumber(mkReal);//
	extern MK_API mkReal mkGaussianNumber(mkReal mean, mkReal variance); // Gaussian 
	extern MK_API mkReal mkAverageRandom(mkReal min, mkReal max);        // 

    extern MK_API bool dirExists(const std::string& dirName_in);

    extern MK_API mkReal ** mkDefine2DArray(int lx, int ly);
    extern MK_API void      mkDelete2DArray(mkReal **pa, int lx);

    extern MK_API void   mkShowMatrix(const char * matrix_name, mkReal **p, int m, int n);
    extern MK_API void   mkMatrixInverse(mkReal Mi[QF][QF], int R);

    extern MK_API void   mkMultiplyVector(mkReal pC[QF], mkReal *pA, mkReal *pB, int m = QF, int n = QF);
    extern MK_API void   mkMultiplyVector(mkPDFs & pC, mkReal *pA, mkPDFs & pB);
    extern MK_API mkPDFs mkMultiplyVector(mkReal *pA, mkPDFs & pB);

    extern MK_API void   mkMultiplyMatrix(mkReal pC[361], mkReal *pA, mkReal *pB, int m, int n, int k);

    extern MK_API mkReal angleBetweenVectors(const mkVector3d & v1, const mkVector3d & v2);

    extern MK_API mkReal dist(mkReal x1, mkReal y1, mkReal x2, mkReal y2);

    extern MK_API void mkTensorProduct(mkReal *pResult, const mkVector3d & a, const mkVector3d & b);

    //判断文件名后缀是不是支持的格式最快的方案
    extern MK_API std::string mkGetFilePosfix(const char* path);
    extern MK_API bool IsSupportPos(const std::string& posfix, const std::string& support);

    template <typename T>
    inline const T& mkMax(const T&a, const T& b)
    {
        return a > b ? a : b;
    }

    template <typename T>
    inline const T& mkMin(const T&a, const T& b)
    {
        return a < b ? a : b;
    }

    template <typename T>
    inline const T& mkMax(const T& a, const T& b, const T& c)
    {
        return ((a)>(b)) ? ((a)>(c)?(a):(c)) : ((b)>(c)?(b):(c));
    }

    template <typename T>
    inline const T& mkMin(const T& a, const T& b, const T& c)
    {
        return ((a)<(b)) ? ((a)<(c)?(a):(c)) : ((b)<(c)?(b):(c));
    }

//#define mkMax(a,b)    (((a)>(b)) ? (a) : (b))
//#define mkMin(a,b)    (((a)<(b)) ? (a) : (b))
//
//#define mkMax(a,b,c)  (((a)>(b)) ? ((a)>(c)?(a):(c)) : ((b)>(c)?(b):(c)))
//#define mkMin(a,b,c)  (((a)<(b)) ? ((a)<(c)?(a):(c)) : ((b)<(c)?(b):(c)))

}

///definition in "mkFunctionAdv.cpp"
namespace mkt
{
	using namespace std;

	extern void alarm(const int times);

	extern MK_API const double epsilon;
	extern MK_API string paraXmlFileName;

	extern MK_API int  str_erase(string &str, const string src);
	extern MK_API int  str_replace(string &str, const string &src, const string &dest);
	extern MK_API bool folder_exist(const string &strPath);
	extern MK_API bool dir_exists(const string& dirName_in);

	extern MK_API bool search_elements(vector<string> & target_element);
	extern MK_API bool create_batchfiles(const string * result_pname, const string * sample_fname);

	extern MK_API void IterativeNestedLoop(const int depth, const int max);

	extern MK_API void create_possible_component_1(vector<vector<double > > & X_target, vector<vector<double > > & X_range, int N);
	extern MK_API int  create_possible_component_2(vector<vector<double > > & X_target, vector<vector<double > > & X_range, int N_element);

	extern MK_API bool vectors_are_equal(vector<double> & vector_lhs, vector<double> vector_rhs);
	extern MK_API void clear_redundance_compoents(vector<vector<double > > & X_target);

	extern MK_API void create_reasonable_component(vector<vector<double > > & X_target, vector<vector<double > > & X_range, int N);
}


#endif
