#include <iostream>
#include <fstream>;
#include <cmath>
#include <windows.h>
#include <time.h>


using namespace std;

clock_t beginTime, stopTime; 

class Cell //细胞
{
public:
	float vac; //细胞速度

	float phi[60][60];  //50x50的格点

	float lap_phi[60][60];
	float phi_dx[60][60];
	float phi_dy[60][60];

	float vinteg;
	float vintegx;
	float vintegy;

	float sum_phi;

	float df_dphi;
	Cell()
	{
		vac = 0;

		phi[60][60] = { 0 };
		lap_phi[60][60] = { 0 };
		phi_dx[60][60] = { 0 };
		phi_dy[60][60] = { 0 };

		vinteg = 0;
		vintegx = 0;
		vintegy = 0;

		sum_phi=0;

		df_dphi = 0;
	}
};


class Grow
{
public:
	Cell cell[17];

	float R;
	float gamma;
	float kappa;
	float lamda;
	float mu;
	float kisa;

	float pi;
	float con1;
	float con2;
	float con3;

	int ncell;

	int nx;
	int ny;
	int nz;

	int nxny;

	float dx;
	float dy;

	int nstep;
	int nprint;
	float dtime;

	void initialize_cell();       //初始化一群细胞
	void set_cell_velocity();     //random一个速度
	void cell_grow();             //算phi的
	void cal_laplacian_gradient(int icell, int nx, int ny,float phi[][60]);
	void cal_volomn_integral(int icell, float phi[][60]);   //求体积分、df dphi
	void write_into_vtk(int nx,int ny,int istep, float phi[][60]);        //写入vtk
	//void write_into_vtk(int nx, int ny, float phi[][60]);

	Grow()
	{
		R = 6;

		gamma = 8;
		lamda = 7;
		kappa = 60;
		mu = 40;
		kisa = 1500;

		pi = 3.1415926;
		con1 = 30.0 / (lamda * lamda);
		con2 = 2.0 * mu / (pi * R * R);
		con3 = 60.0 * kappa / (lamda * lamda * kisa);

		ncell = 0;

		nx = 60;
		ny = 60;
		nz = 1;

		nxny = nx * ny;

		dx = 1;
		dy = 1;

		nstep = 10000;
		nprint = 100;
		dtime = 0.005;
	}
};

void Grow::initialize_cell()
{
	int xmin = 0;
	int ymin = 0;
	int xmax = nx;
	int ymax = ny;

	float xc[17] = { 0 };            //2cells
	float yc[17] = { 0 };

	/*ncell = 2;
	xc[0] = nx / 2 - 1.25 * R;
	yc[0] = ny / 2;

	xc[1] = nx / 2 + 1.25 * R;
	yc[1] = ny / 2;*/

	/*for (int icell = 0; icell < 2; icell++)
	{
		for (int i = 0; i < nx; i++)
		{
			for (int j = 0; j < ny; j++)
			{
				if (((i - xc[icell]) * (i - xc[icell]) + (j - yc[icell]) * (j - yc[icell])) < R * R)
					cell[icell].phi[i][j] = 0.999;
			}
		}
	}*/
	for (int iter = 0; iter < 100000; iter++)
	{
		int cellflag = 1;

		int xnc = nx * (rand() % 1000 + 1) / 1000;
		int ync = ny * (rand() % 1000 + 1) / 1000;

		if (((xnc - R) < xmin) || ((xnc + R) > xmax))                     //细胞边界是否在格点外
			cellflag = 0;

		if (((ync - R) < ymin) || ((ync + R) > ymax))
			cellflag = 0;

		if (cellflag == 1)
		{
			for (int i = 0; i < ncell; i++) 
			{
				float dist = sqrt((xc[i] - xnc) * (xc[i] - xnc) + (yc[i] - ync) * (yc[i] - ync));     //细胞重叠度不要太大
				if (dist <= R * 1.7)
					cellflag = 0;
			}
		}

		if (cellflag == 1)
		{
			ncell = ncell + 1;

			xc[ncell-1] = xnc;
			yc[ncell-1] = ync;

			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{
					if ((i - xnc) * (i - xnc) + (j - ync) * (j - ync) <= (R * R))
						cell[ncell-1].phi[i][j] = 0.99;
				}
			}
			cout << xnc << "******" << ync << endl;
		
		}

		if (ncell == 17)
			break;

	}
	cout << "Number of cell created:" << ncell << endl;

}
void Grow::set_cell_velocity()
{
	float vel = 0.2;
	for (int i = 0; i < ncell; i++)
	{
		float seed = (rand() % 100 + 1) / 100;
		if (seed <= 0.5)
			cell[i].vac = vel;
		else
			cell[i].vac = -vel;
	}
	/*cell[0].vac = 0.5;
	cell[1].vac = -0.5;*/
}

void Grow::cal_laplacian_gradient(int icell, int nx,int ny,float phi[][60])
{
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			int jp = j + 1;
			int jm = j - 1;
			int ip = i + 1;
			int im = i - 1;

			if (im < 0)
				im = nx;
			if (ip == nx-1)
				ip = 0;
			if (jm < 0)
				jm = ny;
			if (jp == ny-1)
				jp = 0;

			float hne = phi[ip][j];
			float hnw = phi[im][j];
			float hns = phi[i][jm];
			float hnn = phi[i][jp];
			float hnc = phi[i][j];

			cell[icell].lap_phi[i][j] = (hnw + hne + hns + hnn - 4 * hnc) / (dx * dy);
			cell[icell].phi_dx[i][j] = (hne - hnw) / dx;
			cell[icell].phi_dy[i][j] = (hnn - hns) / dy;
		}
	}
}

void Grow::cal_volomn_integral(int icell, float phi[][60])
{
	cell[icell].vinteg = 0.0;
	cell[icell].vintegx = 0.0;
	cell[icell].vintegy = 0.0;


	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			cell[icell].vinteg = cell[icell].vinteg + phi[i][j] * phi[i][j];

			cell[icell].sum_phi = 0.0;

			for (int jcell = 0; jcell < ncell; jcell++)
			{
				if (icell != jcell)
					cell[icell].sum_phi = cell[icell].sum_phi + cell[jcell].phi[i][j] * cell[jcell].phi[i][j];
			}

			cell[icell].vintegx = cell[icell].vintegx + phi[i][j] * cell[icell].phi_dx[i][j] * cell[icell].sum_phi;
			cell[icell].vintegy = cell[icell].vintegy + phi[i][j] * cell[icell].phi_dy[i][j] * cell[icell].sum_phi;

			//cell[icell].df_dphi = gamma * phi[i][j] * (1 - phi[i][j]) * (1 - 2 * phi[i][j]) + 2 * kappa * phi[i][j] * cell[icell].sum_phi;
		}
	}
}

void Grow::write_into_vtk(int nx, int ny, int istep, float phi[][60])
{
	fstream out;
	char filename[50] = { 0 };
	char num[15] = { 0 };
	strcpy_s(filename, "time");
	_itoa_s(istep, num, 10);
	strcat_s(filename, num);
	strcat_s(filename, ".vtk");

	ofstream outfile(filename);

	out.open(filename, ios::out);
	if (!out) {
		cout << "open failed" << endl;
	}
	out << "# vtk DataFile Version 3.0" << endl;
	out << filename << endl;
	out << "ASCII " << endl;
	out << "DATASET STRUCTURED_GRID" << endl;
	out << "DIMENSIONS " << nx << " " << ny << " " << 1 << endl;
	out << "POINTS " << nx * ny * 1 << " float" << endl;
	for (int i = 0; i < nx; i++) 
	{
		for (int j = 0; j < ny; j++) 
		{
			out << i << " " << j << " " << 0 << endl;
		}
	}
	out << "POINT_DATA " << nx * ny * 1 << endl;
	out << "SCALARS CON float 1" << endl;
	out << "LOOKUP_TABLE default" << endl;

	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			out << phi[i][j] << "\t";
		}
	}
	out.close();
}

//void Grow::write_into_vtk(int nx, int ny, float phi[][60])
//{
//	fstream out;
//	char filename[50] = { "test" };
//	strcat_s(filename, ".vtk");
//
//	ofstream outfile(filename);
//
//	out.open(filename, ios::out);
//	if (!out) {
//		cout << "open failed" << endl;
//	}
//	out << "# vtk DataFile Version 3.0" << endl;
//	out << filename << endl;
//	out << "ASCII " << endl;
//	out << "DATASET STRUCTURED_GRID" << endl;
//	out << "DIMENSIONS " << nx << " " << ny << " " << 1 << endl;
//	out << "POINTS " << nx * ny * 1 << " float" << endl;
//	for (int i = 0; i < nx; i++)
//	{
//		for (int j = 0; j < ny; j++)
//		{
//			out << i << " " << j << " " << 0 << endl;
//		}
//	}
//	out << "POINT_DATA " << nx * ny * 1 << endl;
//	out << "SCALARS CON float 1" << endl;
//	out << "LOOKUP_TABLE default" << endl;
//
//	for (int i = 0; i < nx; i++)
//	{
//		for (int j = 0; j < ny; j++)
//		{
//			out << phi[j][i] << "\t";
//		}
//	}
//	out.close();
//}

void Grow::cell_grow()
{
	float phi_temp[60][60] = { 0 };
	float term2 = 0;
	float term3 = 0;
	float term4 = 0;

	for (int istep = 0; istep < nstep; istep++)
	{
		for (int icell = 0; icell < ncell; icell++)
		{
			/*if (istep <= 200)
				cell[icell].vac = 0;*/
			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{
					phi_temp[i][j] = cell[icell].phi[i][j];
				}
			}

			cal_laplacian_gradient(icell, nx, ny, phi_temp);
			cal_volomn_integral(icell, phi_temp);	

			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{
					cell[icell].sum_phi = 0.0;

					for (int jcell = 0; jcell < ncell; jcell++)
					{
						if (icell != jcell)
							cell[icell].sum_phi = cell[icell].sum_phi + cell[jcell].phi[i][j] * cell[jcell].phi[i][j];
					}

					cell[icell].df_dphi = gamma * phi_temp[i][j] * (1 - phi_temp[i][j]) * (1 - 2 * phi_temp[i][j]) + 2 * kappa * phi_temp[i][j] * cell[icell].sum_phi;

					term2 = -con1 * cell[icell].df_dphi;
					term3 = -con2 * (cell[icell].vinteg - pi * R * R) * phi_temp[i][j];

					float vnx = cell[icell].vac + con3 * cell[icell].vintegx;
					float vny = cell[icell].vac + con3 * cell[icell].vintegy;

					/*float vnx = cell[icell].vac;
					float vny = 0;
					term4 = vnx * cell[icell].phi_dx[i][j];*/
					term4 = vnx * cell[icell].phi_dx[i][j] + vny * cell[icell].phi_dy[i][j];
					
					//if (icell == 0 && i == 27 && j == 30) {
					//	cout << vnx << "\t***\t" << cell[icell].phi_dx[i][j] << "\t***\t" << term4 << "\n";
					//}

					phi_temp[i][j] = phi_temp[i][j] + dtime * (gamma * cell[icell].lap_phi[i][j] + term2 + term3 - term4);
				}
			}
			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{				
					if (phi_temp[i][j] >= 0.9999)
						phi_temp[i][j] = 0.9999;
					if (phi_temp[i][j] < 0.000)
						phi_temp[i][j] = 0.0;

					cell[icell].phi[i][j] = phi_temp[i][j];
				}
			}

		}

		if ((istep % nprint == 0) || (istep == 1))
		{
			cout << "done step:" << istep << endl;

			float phi_point[60][60] = { 0 };
			
			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{
					for (int count = 0; count < ncell; count++)
					{
						phi_point[i][j] = phi_point[i][j] + cell[count].phi[i][j] * cell[count].phi[i][j];
					}
				}
			}
			write_into_vtk(nx, ny, istep, phi_point);
		}
	}
}



int main()
{
	Grow dynamic_cells;
	dynamic_cells.initialize_cell();
	dynamic_cells.set_cell_velocity();
	dynamic_cells.cell_grow();
	return 0;
}

