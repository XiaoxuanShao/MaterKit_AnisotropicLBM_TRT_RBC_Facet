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
#ifndef MK_SPACE_H
#define MK_SPACE_H

#include "AiLBFlow.h"
#include "mkFunction.h"

class MK_API mkNode;
class MK_API mkSpace;
class MK_API mkBody;

using namespace mkt;

/// <summary>
/// Please don't use inline with codeblocks
/// </summary>
class mkSpace
{
public:
	mkSpace();
	mkSpace(mkReal Lx, mkReal Ly, mkReal Lz, int Mx, int My, int Mz);
	mkSpace(int Mx, int My, int Mz, mkReal delta);

	mkSpace(bool & error);
	~mkSpace();

	void set(int Mx, int My, int Mz, mkReal delta);
	void set(mkReal Lx, mkReal Ly, int Lz, int Mx, int My, int Mz);

	mkReal& Lx();
	mkReal& Ly();
	mkReal& Lz();

	int& Mx();
	int& My();
	int& Mz();

	mkReal& step();

	mkReal Lx() const;
	mkReal Ly() const;
	mkReal Lz() const;

	int Mx() const;
	int My() const;
	int Mz() const;

	mkReal step() const;

private:
	mkReal length_x;
	mkReal length_y;
	mkReal length_z;
	int    meshes_x;
	int    meshes_y;
	int    meshes_z;
	mkReal step_size;
};

#endif
