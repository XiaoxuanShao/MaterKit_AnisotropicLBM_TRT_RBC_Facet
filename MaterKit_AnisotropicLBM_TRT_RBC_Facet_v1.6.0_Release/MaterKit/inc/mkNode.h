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
#ifndef MK_NODE_H
#define MK_NODE_H

#include "AiLBFlow.h"
#include "mkFunction.h"

class MK_API mkNode;
class MK_API mkSpace;
class MK_API mkBody;

using namespace mkt;

class mkNode //
{
public:

	mkNode();

	~mkNode();

	mkPDFs getEquPDFs(const mkReal &rho, const mkVector3d &vel);

	mkPDFs getEquPDFsHe(const mkReal &rho, const mkVector3d &vel);

	mkPDFs getEquPDFsLiang(const mkReal& prs, const mkReal& rho, const mkVector3d& vel);

	mkPDFs getEquPDFsPhiLiang(const mkReal& ptl, const mkReal& phi, const mkVector3d& vel);

	mkPDFs getTEquPDFs(const mkReal &T_loc, const mkVector3d &vel);

	mkPDFs getXEquPDFs(const mkReal &X_loc, const mkVector3d &vel);

	mkPDFs getXEquPDFs(const mkReal &X_loc, const mkReal &V_loc, const mkVector3d &vel);

	mkPDFs getXEquPDFsChai(const mkReal &X_loc, const mkReal &V_loc, const mkVector3d &vel);

	const mkPDFs equ_moment(const mkReal & d_loc, const mkVector3d & u_loc);

	mkPDFs getAddedPDFs(const mkReal & d_loc, const mkReal &omega, const mkVector3d &vel,
		const mkVector3d &accel);

	mkPDFs getAddedPDFsTRT(const mkReal &omega, const mkVector3d &vel,
		const mkVector3d &force, const mkReal omega_minus);

	mkPDFs getAddedPDFsMRT(const mkReal & d_loc, const mkVector3d & u_loc, \
		const mkVector3d & force, mkLattice & lattice);

	mkPDFs getAddedTPDFs(const mkReal &omega, const mkVector3d &vel,
		const mkVector3d &force);

	mkPDFs getAddedTPDFs(const mkReal &omega, const mkVector3d &vel, \
		const mkVector3d &force, const mkReal &kappa_d);

	mkPDFs getAddedPhasePDFs(const mkReal &omega, const mkVector3d &vel_growth, \
		const mkVector3d &normal);

	mkReal su(const int& i, const mkVector3d& vel);

	void collision(const mkReal &omega);

	void collision_BGK(const mkReal &omega, const mkVector3d &force);

	void collision_TRT(const mkReal &omega, const mkVector3d &force);

	void collision(mkReal *Lambda);

	/// Lambda*(f-f_eq)
	void collision_MRT0(mkReal omega, const mkVector3d &force);

	/// Lambda*(f-f_eq)
	void collision_MRT1(mkReal omega, const mkVector3d &force);

	/// MiS*(m_pre-m_equ)
	void collision_MRT2(mkReal omega, const mkVector3d &force);

	void collision_MRT1_solute(mkReal omega);

	void initialPDFs(mkReal rho, mkVector3d vel);

	void initialFlag(int flag_type);

	void resetFlag(int flag_type);

	void calcRho(mkReal &rho) const;

	void calcVelocity(mkReal &rho, mkVector3d &vel) const;

	void calcRhoVelocity(mkReal &rho, mkVector3d &vel) const;

	void phasefield_initialPDFs(mkReal phi, mkVector3d vel);

	void phasefield_collision(const mkReal &omega);

	void phasefield_collision(const mkReal &omega, const mkVector3d &v_loc, const mkVector3d &normal);

	void phasefield_collision_add(const mkReal &omega, const mkVector3d &v_loc, const mkVector3d &normal);

	void calcPhiVelocity(mkReal &phi, mkVector3d &vel) const;

	mkReal getPhase() const;

	mkReal getDeltaPhase() const;

	void temperature_initialPDFs(mkReal temper, mkVector3d vel);

	mkReal getTemperature() const;

	void temperature_collision(const mkReal &omega);

	void temperature_collision(const mkReal &omega, const mkVector3d &v_loc);

	void concentration_initialPDFs(mkReal &X_loc, mkReal &V_loc, mkVector3d &vel);

	mkReal getConcentration() const;

	void concentration_collision(const mkReal &omega, const mkReal &k_p, const mkVector3d &v_loc);

	int getFlag() const;
	int getGrainId() const;

	///For fluid flows
	mkPDFs f_out;
	mkPDFs f_hlp;
	mkPDFs f_equ;

	mkVector3d vel;
	mkVector3d vel_old;

	double density;
	mkReal omega_f;

	//// for TRT flows
	//mkPDFs f_plus, f_minus;
	//mkPDFs f_neq_plus, f_neq_minus;

	///For phase field
	mkPDFs g_out;
	mkPDFs g_hlp;
	mkPDFs g_nbr;//neighbor nodes

	double phi;
	double phi_old;
	double d_phi;

	mkVector3d N_v;//The "growth velocity" in general; used in PF::evolution
	mkReal D_p;    //Phase diffusion coefficients; used in PF::evolution
	mkReal A2s;    // used in PF::evolution

	//phi_n = (phi(x_n) - phi(x))/(x_n - x);Gradient of phi
	mkVector3d phi_n;
	mkVector3d normal;

	///For temperature field
	mkPDFs h_out;
	mkPDFs h_hlp;
	mkReal temperature;    // temperature
	mkVector19d index_nb;

	///For concentration field
	mkPDFs x_out;
	mkPDFs x_hlp;
	//std::vector<mkPDFs> x_out;
	//std::vector<mkPDFs> x_hlp;

    std::vector<mkReal> X_potents;    //solute potential
	std::vector<mkReal> X_solutes;    //solute amount
	std::vector<mkReal> X_DCs;        //diffusion coefficent of C-fields m^2/s

	mkReal ptl_mp; //potential caused by multiphases
	mkReal prs_mp; //pressure in multiphase flows
	mkReal rho_mp; //rho(density) in multiphase flows

	mkReal eta;// It influences the numerical stability.

	double k_d;                       //k_d = density_solid/density_liquid;
	int    flag;
	int    grain_id;

private:

};


#endif
