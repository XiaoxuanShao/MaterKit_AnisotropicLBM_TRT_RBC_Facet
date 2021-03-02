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

#include "mkFluidsUser.h"

mkFluidsUser::mkFluidsUser() : mkFluidsMRT()
{
}

///Please pay attention to "mkFluidsLBM(space)": It should obeys the fast derived class rule.
// It's the "最远派生类调用原则" of virtual derived classes.
mkFluidsUser::mkFluidsUser(const mkSpace & space) : mkFluidsLBM(space), mkFluidsMRT(space)
{
}

mkFluidsUser::~mkFluidsUser()
{
}

void mkFluidsUser::initialize(const std::string & xmlfname)
{
	mkFluidsLBM::initialize(xmlfname);
	mkFlowField::initialize(xmlfname);

	lattice.initialize(omega_f);
	initialize_seeds(xmlfname);//To replace mkPhaseField::initialize(xmlfname);

	mkThermalField::initialize(xmlfname);
	mkSolutalField::initialize(xmlfname);
}

//override the mkFluidsLBM::initialize_geometry()
void mkFluidsUser::initialize_geometry()
{
	//..initialize boundary node-flags
#pragma omp parallel for
	for (int x = 0; x < Mx; x++)
	{
		for (int y = 0; y < My; y++)
		{
			for (int z = 0; z < Mz; z++)
			{
				int index = (x * My + y) * Mz + z;
				//if (y == 0 || y == My - 1)
				//{
				//	node[index].initialFlag(is_walls);
				//}
				//else
				{
					node[index].initialFlag(is_fluid);
				}
			}
		}
	}
}

void mkFluidsUser::propagate()
{
#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE)
	for (int index = 0; index < Mx * My * Mz; index++)
	{
		int x = (index / Mz) / My;
		int y = (index / Mz) % My;
		int z = (index % Mz);

		for (int i = 0; i < QF; i++)
		{
			int index_nb = neighbor(x, y, z, i);
			int index_nv = neighbor(x, y, z, lattice.inv[i]);
			//.Plan A for Bounceback
			if (node[index].flag != is_fluid && node[index_nv].flag != is_fluid)
			{
				node[index].g_hlp[i] = node[index].g_out[lattice.inv[i]];
				for (int j = 0; j < phase_number; j++)
				{
					node[index].gVec_hlp[j][i] = node[index].gVec_out[j][lattice.inv[i]];
				}
			}
			else
			{
				node[index].g_hlp[i] = node[index_nv].g_out[i];
				for (int j = 0; j < phase_number; j++)
				{
					node[index].gVec_hlp[j][i] = node[index_nv].gVec_out[j][i];
				}
			}
			////.Plan B for Bounceback
			//if (node[index].flag != is_fluid && node[index_nb].flag != is_fluid)
			//{
			//	node[index].g_hlp[lattice.inv[i]] = node[index].g_out[i];
			//}
			//else
			//{
			//	node[index_nb].g_hlp[i] = node[index].g_out[i];
			//}

			node[index].g_nbr[i] = node[index_nb].g_hlp[i];
			for (int j = 0; j < phase_number; j++)
			{
				node[index].gVec_nbr[j][i] = node[index_nb].gVec_hlp[j][i];
			}
		}
	}

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE)
	for (int index = 0; index < Mx * My * Mz; index++)
	{
		//int x = (index / Mz) / My;
		//int y = (index / Mz) % My;
		//int z = (index % Mz);
		if (node[index].flag != is_fluid)
		{
			for (int i = 0; i < QF; i++)
			{
				node[index].g_out[i] = node[index].g_hlp[i];
				for (int j = 0; j < phase_number; j++)
				{
					node[index].gVec_out[j][i] = node[index].gVec_hlp[j][i];
				}
			}
		}
	}
}
//MultiphaseField in Programming Phase-Field Modelling[M], Page37 Eq.(4.35)
void mkFluidsUser::relaxation()
{
	int i, n, x, y, z, id;
	int nx, ny, nz, index_nb;
	mkVector3d N_v, v_loc;//
	mkVector3d normal(0, 0, 0);
	mkReal A_s(1.0), A2s(1.0), omega_g(1.0);
	mkReal d_tmp, phi_loc;
	mkPDFs g_equ, dG_phi, dQ_phi, dS_phi, dZ_phi;
	mkReal Q_phi(0);

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE)
	for (int index = 0; index < Mx * My * Mz; index++)
	{
		mkReal phi_loc;
		//phi_loc = node[index].phi;
		//node[index].phi = node[index].g_hlp.density();
		//node[index].d_phi = node[index].phi - phi_loc;

		for (int j = 0; j < phase_number; j++)
		{
			phi_loc = node[index].phiVec[j];
			node[index].phiVec[j] = node[index].gVec_hlp[j].density();
			node[index].d_phiVec[j] = node[index].phiVec[j] - phi_loc;
		}

		mkReal sum_phi = 0;
		for (int j = 0; j < phase_number; j++)
		{
			sum_phi += node[index].phiVec[j];
		}
		sum_phi = (phase_number - 1.0) + sum_phi;

		phi_loc = node[index].phi;
		node[index].phi = sum_phi;
		node[index].d_phi = node[index].phi - phi_loc;
	}

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) \
			private (i, n,x,y,z,id,nx, ny, nz, index_nb, phi_loc, d_tmp) \
 			private (A_s, N_v, v_loc, g_equ, dG_phi, dQ_phi, dS_phi, dZ_phi) \
			firstprivate(normal,A2s,omega_g,Q_phi)
	for (int index = 0; index < Mx * My * Mz; index++)
	{
		n = 0;
		x = (index / Mz) / My;
		y = (index / Mz) % My;
		z = (index % Mz);
		id = node[index].getGrainId();

		if (node[index].flag != is_fluid)
		{
			continue;
		}

		vector<mkPDFs> g_equVec(phase_number);
		vector<mkPDFs> dQ_phiVec(phase_number);
		vector<mkPDFs> dZ_phiVec(phase_number);
		vector<mkReal> phi_locVec(phase_number);
		vector<mkVector3d> normalVec(phase_number);

		phi_loc = node[index].phi;
		for (int j = 0; j < phase_number; j++)
		{
			phi_locVec[j] = node[index].phiVec[j];
		}

		//A_s and N_v.set(0, 0, 0.0) means non-anisotropic-effect
		//anisotropy(id, N_v, A_s, normal, x, y, z);
		//A_s = 1.0;// for test here; to be removed
		N_v.set(0, 0, 0);// for test here; to be removed
		compute_normal_LB(normal, x, y, z);

		for (int j = 0; j < phase_number; j++)
		{
			mkVector3d phi_n(0, 0, 0);
			for (int i = 0; i < QF; i++)
			{
				index_nb = neighbor(x, y, z, i);
				phi_n += lattice.c[i] * lattice.weight[i] * node[index_nb].phiVec[j];
			}
			normalVec[j] = -phi_n / (phi_n.length() + epsilon);
		}

		mkVector3d vel_loc(0.02, 0, 0);
		//g_equ = node[index].getEquPDFsHe(phi_loc, vel_loc);
		g_equ = node[index].getEquPDFs(phi_loc, vel_loc);
		for (int j = 0; j < phase_number; j++)
		{
			if (j == 1)
				vel_loc.set(0.02, 0.0, 0);
			else
				vel_loc.set(0, 0, 0);
			//g_equVec[j] = node[index].getEquPDFsHe(phi_locVec[j], vel_loc);//phiVec_loc[j]

			g_equVec[j] = node[index].getEquPDFs(phi_locVec[j], vel_loc);//phiVec_loc[j]
		}

		d_tmp = 1.0 - mkSQ(phi_loc);

		vector<mkReal> P_phiVec(phase_number);

		for (int j = 0; j < phase_number; j++)
		{
			P_phiVec[j] = 0;
			for (int k = 0; k < phase_number; k++)
			{
				if (j != k)
				{
					P_phiVec[j] += mkSQ(phi_locVec[k] * 0.5 + 0.5);
				}
			}
			P_phiVec[j] *= -2.0 * (phi_locVec[j] * 0.5 + 0.5);//这里应该是负.

			int kappa(0);

			if (j == 0)
				kappa = 0;
			else
				kappa = 1;

			P_phiVec[j] *= kappa * 1.0e-0;              //To be checked. 0.001, 0.01, 1.0: ok. 
		}

		////0*phi_loc and dC_phi means non-curature-effect
		//Q_phi = 1 * (phi_loc - mk_lambda * (mk_X_ml[n] * node[index].X_potents[n]) * d_tmp) * d_tmp;
		Q_phi = 0 * (phi_loc - mk_lambda * node[index].temperature * d_tmp) * d_tmp;

		dQ_phi = lattice.weight * mk_dt * Q_phi;

		for (int j = 0; j < phase_number; j++)
		{
			d_tmp = 1.0 - mkSQ(phi_locVec[j]);
			//Q_phi = 1 * (phi_locVec[j] - mk_lambda * (mk_X_ml[n] * node[index].X_potents[n]) * d_tmp) * d_tmp;
			Q_phi = 0 * (phi_locVec[j] - mk_lambda * node[index].temperature * d_tmp) * d_tmp;
			dQ_phiVec[j] = lattice.weight * mk_dt * (P_phiVec[j] + Q_phi);
		}

		//Z. Chai et al. Int J Heat Mass Transfer 122 (2018) 631–642
		dZ_phi = node[index].getAddedPhasePDFs(omega_g, phi_loc, -normal);
		for (int j = 0; j < phase_number; j++)
		{
			dZ_phiVec[j] = node[index].getAddedPhasePDFs(omega_g, phi_locVec[j], -normalVec[j]);
		}

		//A2s = A_s * A_s;
		omega_g = 1.0 / (mk_dt / mkSQ(mk_dx) / lattice.cs_squ + 0.5);//omega_g = 1.0;// 

		//Z. Chai et al. Int J Heat Mass Transfer 122 (2018) 631–642
		//..Growth without anisotropy  
		node[index].g_out = node[index].g_hlp \
			- (node[index].g_hlp - g_equ) * omega_g \
			+ dQ_phi + dZ_phi;

		//int j = 0;
		for (int j = 0; j < phase_number; j++)
		{
			node[index].gVec_out[j] = node[index].gVec_hlp[j] \
				- (node[index].gVec_hlp[j] - g_equVec[j]) * omega_g \
				+ dQ_phiVec[j] + dZ_phiVec[j];
		}
	}
	reset_flags();
}

void mkFluidsUser::bdy_constX()
{
#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE)
	for (int index = 0; index < Mx*My*Mz; index++)
	{
		int x = (index / Mz) / My;
		int y = (index / Mz) % My;
		int z = (index%Mz);
		if (x == 0)
		{
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				node[index].X_potents[n] = mk_X_high[n];
				node[index].X_solutes[n] = mk_X_high[n];
			}
		}
		else if (x == Mx - 1)
		{
			int index_n = ((x - 1) * My + y) * Mz + z;
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				node[index].X_potents[n] = mk_X_low[n];//node[index_n].X_potents[n];
				node[index].X_solutes[n] = mk_X_low[n];//node[index_n].X_solutes[n];
			}
		}
	}


#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE)
	for (int index = 0; index < Mx*My*Mz; index++)
	{
		int x = (index / Mz) / My;
		int y = (index / Mz) % My;
		int z = (index%Mz);
		if (y == 0)
		{
			int index_n = (x * My + y + 1) * Mz + z;
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				//no-flux BCs
				node[index].X_potents[n] = node[index_n].X_potents[n];
				node[index].X_solutes[n] = node[index_n].X_solutes[n];
			}
		}
		else if (y == My - 1)
		{
			int index_n = (x * My + y - 1) * Mz + z;
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				//no-flux BCs
				node[index].X_potents[n] = node[index_n].X_potents[n];
				node[index].X_solutes[n] = node[index_n].X_solutes[n];
			}
		}
	}
}

void mkFluidsUser::bdy_RBC()
{
#pragma omp parallel for schedule(static, MK_OMP_CHUNKSIZE)
	for (int index = 0; index < Mx*My*Mz; index++)
	{
		int x = (index / Mz) / My;
		int y = (index / Mz) % My;
		int z = (index%Mz);
		if (y == 0)
		{
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				node[index].X_potents[n] = mk_X_high[n];
				node[index].X_solutes[n] = mk_X_high[n];
			}
			//cout << mk_X_high[n] << endl;
			//SystemPause();
		}
		else if (y == My - 1)
		{
			//int index_n = (x * My + y-1) * Mz + z;
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				node[index].X_potents[n] = mk_X_low[n];//node[index_n].X_potents[n];
				node[index].X_solutes[n] = mk_X_low[n];//node[index_n].X_solutes[n];
			}
		}
	}
}

void mkFluidsUser::bdy_nonflux()
{
#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE)
	for (int index = 0; index < Mx*My*Mz; index++)
	{
		int x = (index / Mz) / My;
		int y = (index / Mz) % My;
		int z = (index%Mz);
		if (x == 0)
		{
			int index_n = ((x + 1) * My + y) * Mz + z;
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				node[index].X_potents[n] = node[index_n].X_potents[n];
				node[index].X_solutes[n] = node[index_n].X_potents[n];
			}
		}
		else if (x == Mx - 1)
		{
			int index_n = ((x - 1) * My + y) * Mz + z;
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				node[index].X_potents[n] = node[index_n].X_potents[n];
				node[index].X_solutes[n] = node[index_n].X_potents[n];
			}
		}
	}

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE)
	for (int index = 0; index < Mx*My*Mz; index++)
	{
		int x = (index / Mz) / My;
		int y = (index / Mz) % My;
		int z = (index%Mz);
		if (y == 0)
		{
			int index_n = (x * My + y + 1) * Mz + z;
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				//no-flux BCs
				node[index].X_potents[n] = node[index_n].X_potents[n];
				node[index].X_solutes[n] = node[index_n].X_solutes[n];
			}
		}
		else if (y == My - 1)
		{
			int index_n = (x * My + y - 1) * Mz + z;
			int n = 0;
			//for (int n = 0; n < num_components; n++)
			{
				//no-flux BCs
				node[index].X_potents[n] = node[index_n].X_potents[n];
				node[index].X_solutes[n] = node[index_n].X_solutes[n];
			}
		}
	}
}

void mkFluidsUser::boundary_vel()
{
#pragma omp parallel for schedule(dynamic)
	for (int x = 0; x < Mx; x++)
	{
		for (int y = 0; y < My; y++)
		{
			for (int z = 0; z < Mz; z++)
			{
				if (y == My - 1 && 260 < x && x < Mx - 1)
				{
					int index = (x * My + y) * Mz + z;
					int index_n = (x * My + y - 1) * Mz + z;

					mkReal rho_b(1);
					mkVector3d vel_b(0, 0, 0);

					mkReal rho_n(1);
					mkVector3d vel_n(0, 0, 0);

					rho_n = node[index_n].f_out.density();

					if (QF == 9)
					{
						mkReal u_x = (node[index_n].f_hlp[1] - node[index_n].f_hlp[3] \
							+ node[index_n].f_hlp[5] - node[index_n].f_hlp[6] \
							+ node[index_n].f_hlp[8] - node[index_n].f_hlp[7]) / rho_n;

						mkReal u_y = (node[index_n].f_hlp[2] - node[index_n].f_hlp[4] \
							+ node[index_n].f_hlp[5] - node[index_n].f_hlp[7] \
							+ node[index_n].f_hlp[6] - node[index_n].f_hlp[8]) / rho_n;

						vel_n = mkVector3d(u_x, u_y, 0);
					}
					else
					{
						vel_n = node[index_n].f_out.velocity(rho_n);
					}

					rho_b = rho_n;
					vel_b.set(vel_in);

					mkPDFs equ_n = node[index_n].getEquPDFs(rho_n, vel_n);
					mkPDFs equ_b = node[index].getEquPDFs(rho_b, vel_b);

					node[index].f_out = node[index_n].f_out + equ_b - equ_n; //

					node[index].vel = vel_b;
					node[index].density = rho_b;
				}
				//if (y == 0 && 0 < x && x < 20)
				//{
				//	int index = (x * My + y) * Mz + z;
				//	int index_n = (x * My + y+1) * Mz + z;

				//	mkReal rho_b(1);
				//	mkVector3d vel_b(0, 0, 0);

				//	mkReal rho_n(1);
				//	mkVector3d vel_n(0, 0, 0);

				//	rho_n = node[index_n].f_out.density();

				//	if (QF == 9)
				//	{
				//		mkReal u_x = (node[index_n].f_hlp[1] - node[index_n].f_hlp[3] \
				//			+ node[index_n].f_hlp[5] - node[index_n].f_hlp[6] \
				//			+ node[index_n].f_hlp[8] - node[index_n].f_hlp[7]) / rho_n;

				//		mkReal u_y = (node[index_n].f_hlp[2] - node[index_n].f_hlp[4] \
				//			+ node[index_n].f_hlp[5] - node[index_n].f_hlp[7] \
				//			+ node[index_n].f_hlp[6] - node[index_n].f_hlp[8]) / rho_n;

				//		vel_n = mkVector3d(u_x, u_y, 0);
				//	}
				//	else
				//	{
				//		vel_n = node[index_n].f_out.velocity(rho_n);
				//	}

				//	rho_b = rho_n;
				//	vel_b.set(vel_n);

				//	mkPDFs equ_n = node[index_n].getEquPDFs(rho_n, vel_n);
				//	mkPDFs equ_b = node[index].getEquPDFs(rho_b, vel_b);

				//	node[index].f_out = node[index_n].f_out + equ_b - equ_n; //

				//	node[index].vel = vel_b;
				//	node[index].density = rho_b;
				//}
				else if (y == 0 && 0 < x && x < 20)
				{

					int index = (x * My + y) * Mz + z;

					int index_n = (x * My + y + 1) * Mz + z;

					mkReal rho_b(1);
					mkVector3d vel_b(0, 0, 0);

					mkReal rho_n(1);
					mkVector3d vel_n(0, 0, 0);

					rho_n = node[index_n].f_out.density();

					if (QF == 9)
					{
						mkReal u_x = \
							(node[index_n].f_hlp[1] - node[index_n].f_hlp[3] \
								+ node[index_n].f_hlp[5] - node[index_n].f_hlp[6] \
								+ node[index_n].f_hlp[8] - node[index_n].f_hlp[7]) / rho_n;

						mkReal u_y = \
							(node[index_n].f_hlp[2] - node[index_n].f_hlp[4] \
								+ node[index_n].f_hlp[5] - node[index_n].f_hlp[7] \
								+ node[index_n].f_hlp[6] - node[index_n].f_hlp[8]) / rho_n;

						vel_n = mkVector3d(u_x, u_y, 0);
					}
					else
					{
						vel_n = node[index_n].f_out.velocity(rho_n);
					}

					rho_b = rho_n;
					vel_b.set(vel_n);

					mkPDFs equ_n = node[index_n].getEquPDFs(rho_n, vel_n);
					mkPDFs equ_b = node[index].getEquPDFs(rho_b, vel_b);

					node[index].f_out = node[index_n].f_out + equ_b - equ_n; //

					node[index].vel = vel_b;
					node[index].density = rho_b;
				}
			}
		}
	}
	//#pragma omp parallel for
	//	for (int z = 0; z < Mz; z++) {
	//		for (int y = 0; y < My; y++) {
	//			for (int x = 0; x < Mx; x++) {
	//
	//				if (x == 0) {
	//					int index = (x * My + y) * Mz + z;
	//					int index_n = ((x + 1) * My + y) * Mz + z;
	//					int i(0);
	//					for (i = 0; i < QF; i++) {
	//						node[index].f_out[i] = node[index_n].f_out[i]; //
	//					}
	//				} else if (x == Mx - 1) {
	//					int index = (x * My + y) * Mz + z;
	//					int index_n = ((x - 1) * My + y) * Mz + z;
	//					int i(0);
	//					for (i = 0; i < QF; i++) {
	//						node[index].f_out[i] = node[index_n].f_out[i]; //
	//					}
	//				}
	//			}
	//		}
	//	}
}


void mkFluidsUser::boundary_Couette()
{
#pragma omp parallel for schedule(dynamic)
	for (int z = 0; z < Mz; z++)
	{
		for (int y = 0; y < My; y++)
		{
			for (int x = 0; x < Mx; x++)
			{
				if (y == 0)
				{
					int index = (x * My + y) * Mz + z;
					int index_n = (x * My + y) * Mz + z + 1;

					int i(0);

					mkReal rho_b(1);
					mkVector3d vel_b(0, 0, 0);

					mkReal rho_n(1);
					mkVector3d vel_n(0, 0, 0);

					rho_n = node[index_n].f_out.density();
					vel_n = node[index_n].f_out.velocity(rho_n);

					rho_b = rho_n;
					vel_b.set(0, 0, 0);

					mkPDFs equ_n = node[index_n].getEquPDFs(rho_n, vel_n);
					mkPDFs equ_b = node[index].getEquPDFs(rho_b, vel_b);
					for (i = 0; i < QF; i++) {
						node[index].f_out[i] = node[index_n].f_out[i] + equ_b[i]
							- equ_n[i]; //
					}
				}
				else if (y == My - 1)
				{

					int index = (x * My + y) * Mz + z;

					int index_n = (x * My + y) * Mz + z - 1;

					int i(0);

					mkReal rho_b(1);
					mkVector3d vel_b(0, 0, 0);

					mkReal rho_n(1);
					mkVector3d vel_n(0, 0, 0);

					rho_n = node[index_n].f_out.density();
					vel_n = node[index_n].f_out.velocity(rho_n);

					rho_b = rho_n;
					vel_b.set(vel_in);

					mkPDFs equ_n = node[index_n].getEquPDFs(rho_n, vel_n);
					mkPDFs equ_b = node[index].getEquPDFs(rho_b, vel_b);
					for (i = 0; i < QF; i++) {
						node[index].f_out[i] = node[index_n].f_out[i] + equ_b[i]
							- equ_n[i]; //
					}
				}
			}
		}
	}

#pragma omp parallel for schedule(dynamic)
	for (int z = 0; z < Mz; z++) {
		for (int y = 0; y < My; y++) {
			for (int x = 0; x < Mx; x++) {

				if (x == 0) {
					int index = (x * My + y) * Mz + z;
					int index_n = ((x + 1) * My + y) * Mz + z;
					int i(0);
					for (i = 0; i < QF; i++) {
						node[index].f_out[i] = node[index_n].f_out[i]; //
					}
				}
				else if (x == Mx - 1) {
					int index = (x * My + y) * Mz + z;
					int index_n = ((x - 1) * My + y) * Mz + z;
					int i(0);
					for (i = 0; i < QF; i++) {
						node[index].f_out[i] = node[index_n].f_out[i]; //
					}
				}
			}
		}
	}
}


//void mkFluidsUser::write_vtkfile(int loops)
//{
//	//	int z = Mz / 2;
//	//	mkReal u_ref = delta_x/delta_t;
//	//	mkReal x_ref = 1.0;//delta_x;
//
//	// Create filename
//	stringstream output_filename;
//	output_filename << workspace << "vtk/userFluid_t" << loops << ".vtk";
//	ofstream output_file;
//
//	// Open file
//	output_file.open(output_filename.str().c_str());
//
//	// Write VTK header
//	output_file << "# vtk DataFile Version 3.0\n";
//	output_file << "fluid_state\n";
//	output_file << "ASCII\n";
//	output_file << "DATASET RECTILINEAR_GRID\n";
//	output_file << "DIMENSIONS " << Mx << " " << My << " " << Mz << "\n";
//
//	output_file << "X_COORDINATES " << Mx << " float\n";
//	for (int x = 0; x < Mx; ++x) {
//		output_file << x + 0.5 << " ";
//	}
//	output_file << "\n";
//
//	output_file << "Y_COORDINATES " << My << " float\n";
//	for (int y = 0; y < My; ++y) {
//		output_file << y + 0.5 << " ";
//	}
//	output_file << "\n";
//
//	output_file << "Z_COORDINATES " << Mz << " float\n";
//	for (int z = 0; z < Mz; ++z) {
//		output_file << z + 0.5 << " ";
//	}
//	output_file << "\n";
//
//	output_file << "POINT_DATA " << Mx * My * Mz << "\n";
//
//	// Write density difference
//	output_file << "SCALARS density_difference float 1\n";
//	output_file << "LOOKUP_TABLE default\n";
//
//#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
//	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
//	{
//
//		//int index = (x * ly + y) * lz + z;
//		int z = (index_d / Mx) / My;
//		int y = (index_d / Mx) % My;
//		int x = (index_d % Mx);
//		int index = (x * My + y) * Mz + z;
//
//		mkReal temp_rho(0);
//		node[index].calcRho(temp_rho);
//#pragma omp ordered
//		{
//			output_file << temp_rho - 1 << "\n";
//		}
//	}
//
//	// Write flags
//	output_file << "SCALARS grain_id float 1\n";
//	output_file << "LOOKUP_TABLE default\n";
//
//#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
//	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
//	{
//		////int index = (x * ly + y) * lz + z;
//		int z = (index_d / Mx) / My;
//		int y = (index_d / Mx) % My;
//		int x = (index_d % Mx);
//		int index = (x * My + y) * Mz + z;
//#pragma omp ordered
//		{
//			output_file << node[index].grain_id << "\n";
//		}
//	}
//
//	// Write phase parameters
//	output_file << "SCALARS order_parameter float 1\n";
//	output_file << "LOOKUP_TABLE default\n";
//
//#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
//	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
//	{
//		////int index = (x * ly + y) * lz + z;
//		int z = (index_d / Mx) / My;
//		int y = (index_d / Mx) % My;
//		int x = (index_d % Mx);
//		int index = (x * My + y) * Mz + z;
//#pragma omp ordered
//		{
//			output_file << node[index].getPhase() << "\n";
//		}
//	}
//
//	// Write phase parameters
//	output_file << "SCALARS delta_order_parameter float 1\n";
//	output_file << "LOOKUP_TABLE default\n";
//
//#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
//	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
//	{
//		////int index = (x * ly + y) * lz + z;
//		int z = (index_d / Mx) / My;
//		int y = (index_d / Mx) % My;
//		int x = (index_d % Mx);
//		int index = (x * My + y) * Mz + z;
//#pragma omp ordered
//		{
//			output_file << node[index].getDeltaPhase() << "\n";
//		}
//	}
//
//	// Write solutes
//	int n = 0;
//	//for(n=0; n<num_components; n++)
//	{
//		output_file << "SCALARS X" << n << "_solutes float 1\n";
//		output_file << "LOOKUP_TABLE default\n";
//
//#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
//		for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
//		{
//			//int index = (x * ly + y) * lz + z;
//			int z = (index_d / Mx) / My;
//			int y = (index_d / Mx) % My;
//			int x = (index_d % Mx);
//			int index = (x * My + y) * Mz + z;
//#pragma omp ordered
//			{
//				output_file << node[index].X_solutes[n] << "\n";
//			}
//		}
//
//		// Write solutes
//		output_file << "SCALARS X" << n << "_potentials float 1\n";
//		output_file << "LOOKUP_TABLE default\n";
//
//#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
//		for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
//		{
//			////int index = (x * ly + y) * lz + z;
//			int z = (index_d / Mx) / My;
//			int y = (index_d / Mx) % My;
//			int x = (index_d % Mx);
//			int index = (x * My + y) * Mz + z;
//#pragma omp ordered
//			{
//				output_file << node[index].X_potents[n] << "\n";
//			}
//		}
// 
//		output_file << "SCALARS X" << n << "_solutes_dim float 1\n";
//		output_file << "LOOKUP_TABLE default\n";
//
//#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
//		for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
//		{
//			////int index = (x * ly + y) * lz + z;
//			int z = (index_d / Mx) / My;
//			int y = (index_d / Mx) % My;
//			int x = (index_d % Mx);
//			int index = (x * My + y) * Mz + z;
//#pragma omp ordered
//			{
//				output_file << (node[index].X_potents[n] * (1 - mk_X_kp[n]) + 1) \
//					* 0.5*(1 + mk_X_kp[n] - (1 - mk_X_kp[n])*node[index].phi) << "\n";
//			}
//		}
//	}
//
//	// Write temperature parameters
//	output_file << "SCALARS temperature float 1\n";
//	output_file << "LOOKUP_TABLE default\n";
//
//#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
//	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
//		//for (int z = 0; z < lz; ++z)
//	{
//		//for(int y=0; y<ly; y++)
//		{
//			//for(int x = 0; x < lx; ++x)
//			{
//				////int index = (x * ly + y) * lz + z;
//				int z = (index_d / Mx) / My;
//				int y = (index_d / Mx) % My;
//				int x = (index_d % Mx);
//				int index = (x * My + y) * Mz + z;
//#pragma omp ordered
//				{
//					output_file << node[index].getTemperature() << "\n";
//				}
//			}
//		}
//	}
//
//	// Write velocity
//	output_file << "VECTORS velocity_vector float\n";
//#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
//	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
//		//for (int z = 0; z < lz; ++z)
//	{
//		//for(int y=0; y<ly; y++)
//		{
//			//for(int x = 0; x < lx; ++x)
//			{
//				////int index = (x * ly + y) * lz + z;
//				int z = (index_d / Mx) / My;
//				int y = (index_d / Mx) % My;
//				int x = (index_d % Mx);
//				int index = (x * My + y) * Mz + z;
//
//				mkReal temp_rho(0);
//				node[index].calcRho(temp_rho);
//
//				mkVector3d temp_vel(0, 0, 0);
//				node[index].calcVelocity(temp_rho, temp_vel);
//#pragma omp ordered
//				{
//					output_file << temp_vel.x() << " " << temp_vel.y() << " " \
//						<< temp_vel.z() << "\n";
//				}
//			}
//		}
//	}
//
//	// Close file
//	output_file.close();
//	return;
//}

