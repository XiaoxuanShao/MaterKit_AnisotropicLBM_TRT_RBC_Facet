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
#ifndef MK_FLUIDSLBM_H
#define MK_FLUIDSLBM_H

#include "mkNode.h"
#include "mkSpace.h"
#include "mkSphere.h"

class MK_API mkNode;
class MK_API mkSpace;
class MK_API mkSphere;
class MK_API mkFluidsLBM;

using namespace mkt;

class mkFluidsLBM //single phase flow
{
public:
	mkFluidsLBM();
	~mkFluidsLBM();

	mkFluidsLBM(const mkSpace & space);

	void set(mkSpace space, mkReal Omega, mkReal Nu, mkVector3d f, mkVector3d ang, mkVector3d a);
	virtual void initialize(const std::string& xmlfname);
	virtual void initialize_geometry();
	//void initialize(const mkSphere & ball);
	void propagate();     // with standard bounceback
	void propagate_PBB(); // with porous bounceback
	void relaxation();
	void bounceback();
	void bounceback(const mkSphere& ball);
	//void relaxation(const mkVector3d & force);

	void phase_compute_prefer_array(const mkReal & x, const mkReal & y, const mkReal & z);

	//check mean velocity in a cross-section
	void check_variables(int loops, const char nPlane);
	void check_annular_channel(int loops);

	void boundary();
	void boundary_RBC();
	void boundary_walls();
	void bdyPeriod();
	void bdyCouette();
	void bdyVelocity();
	void bdyRotation();
	void bdySpiral();

	mkReal Thermal_NusseltRBC();
	mkReal Solutal_NusseltRBC();

	void write_pltfile(int frame);
	void write_pltfile_2D(int loops, char nPlane); //nPlane: x,y,z-Plane

	void write_vtkfile(int loops);
	void write_vtkfile_2D(int loops);

	void updateFlags(const mkSphere& ball);

	const mkNode * node_ptr() { return node; }

	mkNode *node;

	void read_parameters(const std::string & xmlfname);

	int  neighbor(const int &x, const int &y, const int &z, const int &i);
	void neighbor(int &nx, int &ny, int &nz, int x, int y, int z, int i);

	bool compute_Dn_phi(mkVector3d& Dn_phi, const int& x, const int& y, const int& z);
	bool compute_Dn_phi_LB(mkVector3d& Dn_phi, const int& x, const int& y, const int& z);

protected:

	int Mx;
	int My;
	int Mz;

	mkReal Lx;
	mkReal Ly;
	mkReal Lz;

	mkReal delta_x; //
	mkReal delta_t; //

	mkVector3d force; //force on each node

	mkVector3d vel_in; //velocity at the inlet

	mkReal density;     //density of the fluids
	mkReal den_solid;   //density of the solids
	mkReal mk_beta_D;   //density Coefficient, it should be beta_D = RT/(2\sqrt{2}W_0);
	mkReal mk_kappa_D;   //density ratio, mk_kappa_D = den_solid/density;

	mkReal density_0;   //initial density of the fluids
	mkReal mk_beta_T;   //thermal expansion coefficient

	mkVector3d mk_Gravity;  //the Gravity

	mkReal mk_d_0;

	mkReal mk_T_0; // The averaged initial temperature

	mkReal mk_alpha;

	mkReal omega_f;
	mkReal omega_g;
	mkReal omega_h;
	mkReal omega_x;

	//mkReal a11,a12,a13,a21,a22,a23,a31,a32,a33;
	mkReal a11, a12, a13, a21, a22, a23, a31, a32, a33;
	std::vector <mkt::Array<mkt::Array<double, 3>, 3> > prefer_array;
	std::vector <mkt::Array<mkt::Array<double, 3>, 3> > rot_array_x2u;
	std::vector <mkt::Array<mkt::Array<double, 3>, 3> > rot_array_u2x;

	mkReal mk_dx;
	mkReal mk_dt;
	mkReal mk_delta;
	mkReal mk_W_0;
	mkReal mk_t_0;
	mkReal mk_lambda;
	mkReal mk_aiss;

	mkReal mk_nu;

//	mkReal *nabla_phi;

    //number of componets in the solute fields
    int    num_components; // 1,2,3... read from file

    std::vector <mkReal> mk_X_low;
    std::vector <mkReal> mk_X_high;
    std::vector <mkReal> mk_X_init;

    std::vector <mkReal> mk_X_beta;

	std::vector <mkReal> mk_X_equ;// equlibrium composition, i.e. liquidus concentration value
	std::vector <mkReal> mk_X_kp; // composition partial fraction
	std::vector <mkReal> mk_X_ml; // composition liqidus slopes

    std::vector <mkReal> DC_fluid;
    std::vector <mkReal> DC_solid;
    std::vector <mkReal> dimless_DC_fluid;
    std::vector <mkReal> dimless_DC_solid;

	mkReal mk_G_temp;
	mkReal mk_V_pull;
	mkReal mk_R_cool;

protected:

	std::vector <mkVector3d>  mk_seed_center; //position of seed/obstacle center
	mkReal     mk_seed_radius; //position of seed/obstacle center
	int		   mk_seed_number;

public:

	mkVector3d accel_f; //  accel of fluids(on each node)
	mkVector3d force_b; //force on ball
	mkVector3d torque_b; //force on ball

	mkVector3d oz_axis;//(0, 0, 1);  //oz-axis
	mkVector3d accel_body;//(0, 0, 0);   //acceleration of moving bodies
	mkVector3d angVel_0;//(0, 0, 0); //angular velocity of moving bodies
};

#endif
