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
	
	mkFluidsLBM(const string& xmlFileName);
	mkFluidsLBM(const mkSpace & space);

	void reset(const string& xmlFileName);
	void reset(const mkSpace& space);

	void set(mkSpace space, mkReal Omega, mkReal Nu, mkVector3d f, mkVector3d ang, mkVector3d a);

	virtual void read_parameters(const std::string& xmlfname);

	virtual void initialize(const std::string& xmlfname); //pay attention to virtual function
	virtual void initialize_geometry(); //pay attention to virtual function
	//void initialize(const mkSphere & ball);
	virtual void propagate();     // with standard bounceback
	virtual void propagate_PBB(); // with porous bounceback
	virtual void relaxation();
	virtual void bounceback();
	virtual void bounceback(const mkSphere& ball);
	//void relaxation(const mkVector3d & force);

	//check mean velocity in a cross-section
	virtual void check_variables(int loops, const char nPlane);
	virtual void check_annular_channel(int loops);

	virtual void boundary();
	virtual void boundary_RBC();
	virtual void boundary_walls();
	virtual void bdyPeriod();
	virtual void bdyCouette();
	virtual void bdyVelocity();
	virtual void bdyRotation();
	virtual void bdySpiral();

	virtual mkReal Thermal_NusseltRBC();
	virtual mkReal Solutal_NusseltRBC();

	virtual void write_pltfile(int frame);
	virtual void write_pltfile_2D(int loops, char nPlane); //nPlane: x,y,z-Plane

	virtual void write_vtkfile(int loops);
	virtual void write_vtkfile_2D(int loops);

	virtual void updateFlags(const mkSphere& ball);

	mkNode * node_ptr() { return node; }
	const mkNode * node_ref() const { return node; }

protected:
	int  neighbor(const int &x, const int &y, const int &z, const int &i);
	void neighbor(int &nx, int &ny, int &nz, int x, int y, int z, int i);

	virtual bool compute_DD_phi(mkReal& DD_phi, const int& x, const int& y, const int& z);
	virtual bool compute_DD_phi_LB(mkReal& DD_phi, const int& x, const int& y, const int& z);
	virtual bool compute_Dn_phi(mkVector3d& Dn_phi, const int& x, const int& y, const int& z);
	virtual bool compute_Dn_phi_LB(mkVector3d& Dn_phi, const int& x, const int& y, const int& z);
	virtual bool compute_normal(mkVector3d& normal, const int& x, const int& y, const int& z);
	virtual bool compute_normal_LB(mkVector3d& normal, const int& x, const int& y, const int& z);
	virtual bool compute_phi_n();
	virtual bool compute_phi_n_LB();

public:
	mkNode* node;

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

	mkVector3d accel_f; //  accel of fluids(on each node)
	mkVector3d force_b; //force on ball
	mkVector3d torque_b; //force on ball

	mkVector3d oz_axis;//(0, 0, 1);  //oz-axis
	mkVector3d accel_body;//(0, 0, 0);   //acceleration of moving bodies
	mkVector3d angVel_0;//(0, 0, 0); //angular velocity of moving bodies
};

#endif
