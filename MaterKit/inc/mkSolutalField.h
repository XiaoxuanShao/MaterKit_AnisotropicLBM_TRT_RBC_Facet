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
#ifndef MK_SOLUTALFIELD_H
#define MK_SOLUTALFIELD_H

#include "AiLBFlow.h"
#include "mkFunction.h"
#include "mkFluidsLBM.h"

class MK_API mkSolutalField;

using namespace mkt;

class mkSolutalField : virtual public mkFluidsLBM //single phase flow
{
public:
	mkSolutalField(){};
	~mkSolutalField(){};

	mkSolutalField(const mkSpace & space) : mkFluidsLBM(space) {};
	
	virtual void initialize(const std::string & xmlfname);

	virtual void propagate();
	virtual void propagate_PBB();
	virtual void relaxation();
	virtual void relaxation_anisotropy();

	virtual void updateDCs(const mkNode * nptr);
	virtual void evolution(const mkNode * nptr);

	///ATC: Evolution wiht AntiTrappingCurrent
	virtual void evolution_ATC1(const mkNode * nptr);
	virtual void evolution_ATC2(const mkNode * nptr);

	//Here, potential is temperature in evolution_Thermal();
	virtual void evolution_thermal(const mkNode * nptr);
	virtual void evolution_old(const mkNode * nptr);

	void bdy_constX();
	void bdy_RBC();
	void bdy_LBflowin();

protected:

	mkReal p(const int & n, const mkReal & phi);
	mkReal p(const mkReal & k_p, const mkReal & phi);
	mkReal q(const int & n, const mkReal & phi);
	mkReal q(const mkReal & k_p, const mkReal & phi);

private:

	///ATC: Get AntiTrappingCurrent
	mkReal ATcurrent(const int & n, const int & x, const int & y, const int & z);
	mkReal NPcurrent(const int & n, const int & x, const int & y, const int & z);

};

#endif
