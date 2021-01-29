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
	mkFluidsMRT::initialize(xmlfname);

	//Override  mkSolutalField::initialize(xmlfname);
	//initialize_solutalfield(xmlfname);
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
				{
					node[index].initialFlag(is_fluid);
				}
			}
		}
	}
}

void mkFluidsUser::initialize_phasefield(const std::string& xmlfname)
{

}

void mkFluidsUser::initialize_solutalfield(const std::string & xmlfname)
{
	mkt::XMLreader document_para(xmlfname);

	document_para["MaterKit"]["composition"]["number"].read(num_components);

	document_para["MaterKit"]["composition"]["diffFluid"].read(DC_fluid);
	document_para["MaterKit"]["composition"]["diffSolid"].read(DC_solid);

	document_para["MaterKit"]["composition"]["beta"].read(mk_X_beta);
	document_para["MaterKit"]["composition"]["iniValue"].read(mk_X_init);
	document_para["MaterKit"]["composition"]["highValue"].read(mk_X_high);
	document_para["MaterKit"]["composition"]["lowValue"].read(mk_X_low);

	// equlibrium composition, i.e. liquidus concentration value
	document_para["MaterKit"]["composition"]["equValue"].read(mk_X_equ);
	document_para["MaterKit"]["composition"]["partition"].read(mk_X_kp);

	if (num_components < 0)
	{
		std::cout << "Error in reading num_components in mkNode!!!\n";
		std::cin.get();
		exit(0);
	}
	else if (num_components > 0)
	{
		for (int n = 0; n < DC_fluid.size(); n++)
		{
			dimless_DC_fluid.push_back(DC_fluid[n] / (delta_x*delta_x / delta_t));
		}
		for (int n = 0; n < DC_solid.size(); n++)
		{
			dimless_DC_solid.push_back(DC_solid[n] / (delta_x*delta_x / delta_t));
		}

		cout << "dimless_DC_solid[0] = " << dimless_DC_solid[0] << endl;
		cout << "dimless_DC_fluid[0] = " << dimless_DC_fluid[0] << endl;
		

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE)
		for (int index = 0; index < Mx*My*Mz; index++)
		{
			//int index = (x*ly + y)*lz + z;
			int x = (index / Mz) / My;
			int y = (index / Mz) % My;
			int z = (index%Mz);

			mkReal f_s = 0;//node[index].getPhase()*0.5 + 0.5;//phase_n's fraction;//0.0;//
			mkReal n_s(0);
			n_s = f_s < 0 ? 0 : f_s;
			n_s = f_s > 1 ? 1 : f_s;

			for (int n = 0; n < num_components; n++)
			{
				node[index].X_DCs.push_back(n_s*dimless_DC_solid[n] + (1.0 - n_s)*dimless_DC_fluid[n]);

				mkReal X_loc = mk_X_init[n];
				mkReal N_phi = -1;//suppose it's liquid

				//X_loc = (X_loc / mk_X_equ[n] / p(n, N_phi) - 1) / (1 - mk_X_kp[n]);

				if (mkFabs(mk_X_beta[0]) > MK_EPSILON)
				{
					double perturbation = 1.0 + 0.001*cos(2.0*PI*x / double(Mx));
					X_loc = mk_X_init[n] * perturbation;
				}

				//cout << "mk_X_init[n] = " << mk_X_init[n] << endl;
				//cout << "X_loc = " << X_loc << endl;

				node[index].X_potents.push_back(X_loc);
				node[index].X_solutes.push_back(X_loc);
			}
		}
	}

	updateDCs(this->node);//Close it when using ATC phase field.
	//for (int n = 0; n < num_components; n++)
	//{
	//	cout << "node[20].X_potents = " << node[20].X_potents[n]<<endl;
	//}

	//write_vtkfile(0);
	//SystemPause();

	///Compute some parameters which should be tranlated from the readin ones.
	FILE *out;
	char fn[512];
	sprintf(fn, "%sdocSoluteField.txt", workspace.c_str()); //..\\results\\  //
	out = fopen(fn, "a+");

	mkReal mk_delta_C = mk_X_high[0] - mk_X_low[0];
	mkReal mk_beta_C = mk_X_beta[0];

	fprintf(out, " *** Parameters of the solute field \n");

	printf("%20s= %-8.6e\n", "X_init[0] ", mk_X_init[0]);
	fprintf(out, "%20s= %-8.6e\n\n", "X_init[0] ", mk_X_init[0]);

	printf("%20s= %-8.6e\n", "X_beta[0] ", mk_X_beta[0]);
	fprintf(out, "%20s= %-8.6e\n\n", "X_beta[0] ", mk_X_beta[0]);


	mkReal Ra_C = mk_Gravity.length() * mk_beta_C * mk_delta_C * (My - 2)*(My - 2)*(My - 2)  \
		/ (lattice.cs_squ * (1.0 / omega_f - 0.5)) \
		/ dimless_DC_fluid[0];
	cout << " *** Rayleigh numer of Rayleigh_Bernard_Convection \n";
	printf("%20s= %-8.6e\n", "Ra_C ", Ra_C);
	fprintf(out, " *** Rayleigh numer of Rayleigh_Bernard_Convection \n");
	fprintf(out, "%20s= %-8.6e\n", "Ra_C ", Ra_C);

	mkReal nu_ph = mk_nu / (mk_t_0 / mkSQ(mk_W_0));

	Ra_C = mk_Gravity.length() * (delta_x / delta_t / delta_t)  * mk_beta_C * mk_delta_C \
		* (My - 2)*(My - 2)*(My - 2) * delta_x*delta_x*delta_x / (DC_fluid[0] * nu_ph);

	cout << " *** Rayleigh numer of RBC in a square cavity:\n";
	printf("%20s= %-8.6e\n\n", "Ra_C ", Ra_C);
	fprintf(out, " *** Rayleigh numer of RBC in a square cavity:\n");
	fprintf(out, "%20s= %-8.6e\n\n", "Ra_C ", Ra_C);
	fclose(out);
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


void mkFluidsUser::write_vtkfile(int loops)
{
	//	int z = Mz / 2;
	//	mkReal u_ref = delta_x/delta_t;
	//	mkReal x_ref = 1.0;//delta_x;

		// Create filename
	stringstream output_filename;
	output_filename << workspace << "vtk/fluid_t" << loops << ".vtk";
	ofstream output_file;

	// Open file
	output_file.open(output_filename.str().c_str());

	// Write VTK header
	output_file << "# vtk DataFile Version 3.0\n";
	output_file << "fluid_state\n";
	output_file << "ASCII\n";
	output_file << "DATASET RECTILINEAR_GRID\n";
	output_file << "DIMENSIONS " << Mx << " " << My << " " << Mz << "\n";

	output_file << "X_COORDINATES " << Mx << " float\n";
	for (int x = 0; x < Mx; ++x) {
		output_file << x + 0.5 << " ";
	}
	output_file << "\n";

	output_file << "Y_COORDINATES " << My << " float\n";
	for (int y = 0; y < My; ++y) {
		output_file << y + 0.5 << " ";
	}
	output_file << "\n";

	output_file << "Z_COORDINATES " << Mz << " float\n";
	for (int z = 0; z < Mz; ++z) {
		output_file << z + 0.5 << " ";
	}
	output_file << "\n";

	output_file << "POINT_DATA " << Mx * My * Mz << "\n";

	// Write density difference
	output_file << "SCALARS density_difference float 1\n";
	output_file << "LOOKUP_TABLE default\n";

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
	{

		//int index = (x * ly + y) * lz + z;
		int z = (index_d / Mx) / My;
		int y = (index_d / Mx) % My;
		int x = (index_d % Mx);
		int index = (x * My + y) * Mz + z;

		mkReal temp_rho(0);
		node[index].calcRho(temp_rho);
#pragma omp ordered
		{
			output_file << temp_rho - 1 << "\n";
		}
	}

	// Write flags
	output_file << "SCALARS grain_id float 1\n";
	output_file << "LOOKUP_TABLE default\n";

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
	{
		////int index = (x * ly + y) * lz + z;
		int z = (index_d / Mx) / My;
		int y = (index_d / Mx) % My;
		int x = (index_d % Mx);
		int index = (x * My + y) * Mz + z;
#pragma omp ordered
		{
			output_file << node[index].grain_id << "\n";
		}
	}

	// Write phase parameters
	output_file << "SCALARS order_parameter float 1\n";
	output_file << "LOOKUP_TABLE default\n";

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
	{
		////int index = (x * ly + y) * lz + z;
		int z = (index_d / Mx) / My;
		int y = (index_d / Mx) % My;
		int x = (index_d % Mx);
		int index = (x * My + y) * Mz + z;
#pragma omp ordered
		{
			output_file << node[index].getPhase() << "\n";
		}
	}

	// Write phase parameters
	output_file << "SCALARS delta_order_parameter float 1\n";
	output_file << "LOOKUP_TABLE default\n";

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
	{
		////int index = (x * ly + y) * lz + z;
		int z = (index_d / Mx) / My;
		int y = (index_d / Mx) % My;
		int x = (index_d % Mx);
		int index = (x * My + y) * Mz + z;
#pragma omp ordered
		{
			output_file << node[index].getDeltaPhase() << "\n";
		}
	}

	// Write solutes
	int n = 0;
	//for(n=0; n<num_components; n++)
	{
		output_file << "SCALARS X" << n << "_solutes float 1\n";
		output_file << "LOOKUP_TABLE default\n";

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
		for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
		{
			//int index = (x * ly + y) * lz + z;
			int z = (index_d / Mx) / My;
			int y = (index_d / Mx) % My;
			int x = (index_d % Mx);
			int index = (x * My + y) * Mz + z;
#pragma omp ordered
			{
				output_file << node[index].X_solutes[n] << "\n";
			}
		}

		// Write solutes
		output_file << "SCALARS X" << n << "_potentials float 1\n";
		output_file << "LOOKUP_TABLE default\n";

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
		for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
		{
			////int index = (x * ly + y) * lz + z;
			int z = (index_d / Mx) / My;
			int y = (index_d / Mx) % My;
			int x = (index_d % Mx);
			int index = (x * My + y) * Mz + z;
#pragma omp ordered
			{
				output_file << node[index].X_potents[n] << "\n";
			}
		}
 
		output_file << "SCALARS X" << n << "_solutes_dim float 1\n";
		output_file << "LOOKUP_TABLE default\n";

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
		for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
		{
			////int index = (x * ly + y) * lz + z;
			int z = (index_d / Mx) / My;
			int y = (index_d / Mx) % My;
			int x = (index_d % Mx);
			int index = (x * My + y) * Mz + z;
#pragma omp ordered
			{
				output_file << (node[index].X_potents[n] * (1 - mk_X_kp[n]) + 1) \
					* 0.5*(1 + mk_X_kp[n] - (1 - mk_X_kp[n])*node[index].phi) << "\n";
			}
		}
	}

	// Write temperature parameters
	output_file << "SCALARS temperature float 1\n";
	output_file << "LOOKUP_TABLE default\n";

#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
		//for (int z = 0; z < lz; ++z)
	{
		//for(int y=0; y<ly; y++)
		{
			//for(int x = 0; x < lx; ++x)
			{
				////int index = (x * ly + y) * lz + z;
				int z = (index_d / Mx) / My;
				int y = (index_d / Mx) % My;
				int x = (index_d % Mx);
				int index = (x * My + y) * Mz + z;
#pragma omp ordered
				{
					output_file << node[index].getTemperature() << "\n";
				}
			}
		}
	}

	// Write velocity
	output_file << "VECTORS velocity_vector float\n";
#pragma omp parallel for schedule(static,MK_OMP_CHUNKSIZE) ordered
	for (int index_d = 0; index_d < Mx*My*Mz; index_d++)
		//for (int z = 0; z < lz; ++z)
	{
		//for(int y=0; y<ly; y++)
		{
			//for(int x = 0; x < lx; ++x)
			{
				////int index = (x * ly + y) * lz + z;
				int z = (index_d / Mx) / My;
				int y = (index_d / Mx) % My;
				int x = (index_d % Mx);
				int index = (x * My + y) * Mz + z;

				mkReal temp_rho(0);
				node[index].calcRho(temp_rho);

				mkVector3d temp_vel(0, 0, 0);
				node[index].calcVelocity(temp_rho, temp_vel);
#pragma omp ordered
				{
					output_file << temp_vel.x() << " " << temp_vel.y() << " " \
						<< temp_vel.z() << "\n";
				}
			}
		}
	}

	// Close file
	output_file.close();
	return;
}

