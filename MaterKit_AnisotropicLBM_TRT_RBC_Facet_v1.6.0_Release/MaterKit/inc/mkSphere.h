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
#ifndef MK_SPHERE_H
#define MK_SPHERE_H

#include "AiLBFlow.h"
#include "mkFunction.h"

class MK_API mkNode;
class MK_API mkSpace;
class MK_API mkSphere;

using namespace mkt;

/// <summary>
/// Please don't use inline with codeblocks
/// </summary>

class mkSphere
{
public:
	mkSphere();

	mkSphere(const mkSpace space);

	void set(const mkSpace space, mkVector3d Position, mkReal Radius, mkReal Den_Ratio);
	void setCenter(const mkVector3d &rhs);
	void setRadius(const mkReal &rhs);
	void setLinVel(const mkVector3d &rhs);
	void setForce(const mkVector3d &rhs);
	void updateStatus();
	void updateStatus(const mkVector3d & pForce, const mkVector3d & pTorque, \
		const mkSpace & space, const mkVector3d & accel_body);

	mkReal density;
	mkReal mass;
	mkReal inertia;
	mkReal radius;

	mkVector3d center; //center of sphere
	mkVector3d linVel; //linear velocity
	mkVector3d angVel; //angular velocity

	mkVector3d force; //force on sphere
	mkVector3d torque; //torque on sphere
};

#endif
