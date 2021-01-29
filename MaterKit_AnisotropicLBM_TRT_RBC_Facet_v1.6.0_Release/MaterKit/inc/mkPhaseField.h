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
#ifndef MK_PHASEFIELD_H
#define MK_PHASEFIELD_H

#include "mkFluidsLBM.h"

class MK_API mkFluidsMRT;
class MK_API mkPhaseField;

using namespace mkt;

class mkPhaseField : virtual public mkFluidsLBM
{
public:
	mkPhaseField();
	~mkPhaseField();

	mkPhaseField(const mkSpace & space) : mkFluidsLBM(space) 
	{
		
	};

    void readparameters(mkt::XMLreader const& document);

	//void phase_compute_prefer_array(const mkReal & x, const mkReal & y, const mkReal & z);
	bool compute_normal(mkVector3d & normal, const int & x, const int & y, const int & z);
	bool compute_normal_LB(mkVector3d& normal, const int& x, const int& y, const int& z);
	bool compute_Dn_phi_LB(mkVector3d& Dn_phi, const int& x, const int& y, const int& z);
	bool compute_DD_phi_LB(mkReal& DD_phi, const int& x, const int& y, const int& z);
	
	bool compute_curvature(mkReal & curvature, mkVector3d & normal, mkReal & Qn_xyz, \
		const int & x, const int & y, const int & z);
	void reset_flags(); //reset domain flags according to volume fraction of solid phases
	
	bool anisotropy(const int & id, mkVector3d & N_v, mkReal & A_s, mkVector3d & normal, const int & x, const int & y, const int & z);
	bool anisotropy_facet(const int & id, mkVector3d & N_v, mkReal & A_s, mkVector3d & normal, const int & x, const int & y, const int & z);
	bool anisotropy_cbc(const int & id, mkVector3d & N_v, mkReal & A_s, mkVector3d & normal, const int & x, const int & y, const int & z);
	bool anisotropy_hcp(const int & id, mkVector3d & N_v, mkReal & A_s, mkVector3d & normal, const int & x, const int & y, const int & z);

	bool compute_phi_n();

	void initialize(const std::string & parafilename);
	void evolution(const mkNode * nptr);
	void propagate();
	void relaxation();
	void relaxation_AllenCahn();
	void relaxation_anisotropy();
	void relaxation_anisotropy_thermal(); // 
	void relaxation_anisotropy_thermal(const mkFluidsMRT & flow);
	void relaxation_anisotropy_solute(const int loops);
	void relaxation_anisotropy_cbc();    ///on LBM£¬fcc/bcc/cubic
	void relaxation_anisotropy_hcp();    ///on LBM, hcp/snowflakes
	void evolution_anisotropy();         ///on FVM
};


#endif
