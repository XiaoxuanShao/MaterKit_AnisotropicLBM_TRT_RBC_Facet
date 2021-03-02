//============================================================================
//              Anisotropic LBM 3D code
//============================================================================
// Author      : DongKe SUN
// Version     : 2010.09.30 MoonLight
// Copyright   : All rights reserved.
// Description : C++, Ansi-style
// Last updated: 2021.02.01 by DongKe SUN
//============================================================================
// SUN DongKe, Ph.D
// Website     : http://www.materkit.com
// E-Mail      : dksun@seu.edu.cn 
//============================================================================
#ifndef MK_MULTIPHASEFIELD_H
#define MK_MULTIPHASEFIELD_H

#include "mkFluidsMRT.h"

class MK_API mkMultiphaseField;

using namespace mkt;

//Designed for multiphase(denrites/grains/cells) interactions
class mkMultiphaseField : virtual public mkFluidsMRT
{
public:
	mkMultiphaseField();
	~mkMultiphaseField();

	mkMultiphaseField(const mkSpace& space);
	
	bool anisotropy(const int & id, mkVector3d & N_v, mkReal & A_s, mkVector3d & normal, const int & x, const int & y, const int & z);
	bool anisotropy_facet(const int & id, mkVector3d & N_v, mkReal & A_s, mkVector3d & normal, const int & x, const int & y, const int & z);
	bool anisotropy_cbc(const int & id, mkVector3d & N_v, mkReal & A_s, mkVector3d & normal, const int & x, const int & y, const int & z);
	bool anisotropy_hcp(const int & id, mkVector3d & N_v, mkReal & A_s, mkVector3d & normal, const int & x, const int & y, const int & z);

	void initialize(const std::string & xmlfname);
	void evolution(const mkNode * nptr);
	void propagate();
	void relaxation();

	void relaxation_AllenCahn();
	void relaxation_anisotropy_thermal(); // 
	void relaxation_solute();
	void relaxation_thermal();

	void evolution_anisotropy();         ///on FVM

	void write_vtkfile(int loops);

protected:
	void initialize_seeds(const std::string& xmlfname);

protected:
	int seed_number;    //the number of seeds
	int phase_number;   //the number of phases
	double * id_counter;
	vector<double> vec_angle;
	vector<double> vec_center;
};

#endif
