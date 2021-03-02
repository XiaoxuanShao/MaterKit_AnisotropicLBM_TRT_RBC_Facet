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
#ifndef MATERKIT_H
#define MATERKIT_H

///used in codeblocks
#ifdef MK_LINUX
#ifndef MK_EXPORT
#define MK_EXPORT
#endif
#ifndef MK_API
#define MK_API
#endif
#endif // MK_LINUX

///used in VS2017/2019
#ifdef MK_WINDOWS
#ifdef MK_BUILD_DLL
#define MK_API __declspec(dllexport)
#else
#define MK_API _declspec(dllimport)    //Open it when using the dll/lib code, or
//#define MK_API //_declspec(dllimport)//open it when using the full devloping code
#endif
#endif
 
//#ifdef MK_WINDOWS
//#ifdef MK_BUILD_DLL
//#define MK_TEMPLATE __declspec(dllexport)
//#else
//#define MK_TEMPLATE  //_declspec(dllimport)
//#endif
//#endif

#endif

