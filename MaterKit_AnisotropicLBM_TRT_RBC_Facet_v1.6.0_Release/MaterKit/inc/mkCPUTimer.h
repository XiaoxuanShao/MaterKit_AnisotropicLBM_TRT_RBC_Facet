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
#ifndef		MK_CPUTIMER_H
#define		MK_CPUTIMER_H

#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cassert>
#include<cstdlib>
#include<cstddef>
#include<ctime>
#include<cstring>
#include<conio.h>
#include <sys/types.h>
#include <sys/timeb.h>

#include"MaterKit.h"

class MK_API mkCPUTimer;

//计时员，定时器－完成计时功能
class mkCPUTimer
{
public:
	mkCPUTimer();
	mkCPUTimer(const std::string label);
	~mkCPUTimer();
	double GetTime(int flag);
	double GetSystemTime();
private:
	FILE * file;
    char fn[512];
	long s;
	long start_second;
	long end_second;

	long long t_sta;   // = GetSystemTime();
	long long t_end;   // = GetSystemTime();

	std::string label;

};
#endif
