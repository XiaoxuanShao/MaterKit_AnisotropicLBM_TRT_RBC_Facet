#include <iostream>
#include <fstream>
#include <cmath>
#include <windows.h>
#include <time.h>


using namespace std;

clock_t beginTime, stopTime; 

class Cell //细胞
{
public:
	float vac; //细胞速度

	float phi[100][100];  //100x100的格点

	float lap_phi[100][100];
	float phi_dx[100][100];
	float phi_dy[100][100];

	float vinteg;
	float vintegx;
	float vintegy;

	float sum_phi[100][100];

	float df_dphi;
	Cell()
	{
		vac = 0;

		phi[100][100] = { 0 };
		lap_phi[100][100] = { 0 };
		phi_dx[100][100] = { 0 };
		phi_dy[100][100] = { 0 };

		vinteg = 0;
		vintegx = 0;
		vintegy = 0;

		sum_phi[100][100] = { 0 };

		df_dphi = 0;
	}
};


class Grow
{
public:
	Cell cell[40];

	float phi_point[100][100];

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
	int dtime;

	void initialize_cell();       //初始化一群细胞
	void set_cell_velocity();     //random一个速度
	void cell_grow();             //算phi的
	void cal_laplacian_gradient(int icell, int i,int j,float phi[][100]);
	void cal_volomn_integral(int icell, int i, int j, float phi[][100]);   //求体积分、df dphi
	void write_into_vtk(int nx,int ny,int istep, float phi[][100]);        //写入vtk

	Grow()
	{
		phi_point[100][100] = { 0 };

		R = 12;

		gamma = 20;
		lamda = 70;
		kappa = 60;
		mu = 40;
		kisa = 1500;

		pi = 3.1415926;
		con1 = 30.0 / (lamda * lamda);
		con2 = 2.0 * mu / (pi * R * R);
		con3 = 60.0 * kappa / (lamda * lamda * kisa);

		ncell = 0;

		nx = 100;
		ny = 100;
		nz = 1;

		nxny = nx * ny;

		dx = 1.0;
		dy = 1.0;

		nstep = 50000;
		nprint = 500;
		dtime = 0.005;
	}
};

void Grow::initialize_cell()
{
	int xmin = 0;
	int ymin = 0;
	int xmax = nx;
	int ymax = ny;
	
	float xc[40] = { 0 };            //40cells
	float yc[40] = { 0 };
	for (int iter = 0; iter < 500000; iter++)
	{
		int cellflag = 1;
		float xnc = nx * rand();
		float ync = ny * rand();

		if (((xnc - R) < xmin) || ((xnc + R) > xmax))                     //细胞边界是否在格点外
			cellflag = 0;

		if (((ync - R) < ymin) || ((ync + R) > ymax))
			cellflag = 0;

		if (cellflag == 1)
		{
			for (int i = 0; i < 40; i++)
			{
				float dist = sqrt((xc[i] - xnc) * (xc[i] - xnc) + (yc[i] - ync) * (yc[i] - ync));     //细胞重叠度不要太大
				if (dist <= R * 1.2)
					cellflag = 0;
			}
		}

		if (cellflag == 1)
		{
			ncell = ncell++;
			xc[ncell] = xnc;
			yc[ncell] = ync;

			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{
					if ((i - xnc) * (i - xnc) + (j - ync) * (j - ync) < R * R)
						cell[ncell].phi[i][j] = 1;
				}
			}
		}

		if (ncell == 40)
			break;

		cout << "Number of cell created:" << ncell << endl;
	}

}
void Grow::set_cell_velocity()
{
	float vel;
	cout << "Please set up cell velocity!"<< endl;
	cin >> vel;
	for (int i = 0; i < 40; i++)
	{
		float seed = rand();
		if (seed <= 0.5)
			cell[i].vac = vel;
		else
			cell[i].vac = -vel;
	}
}

void Grow::cal_laplacian_gradient(int icell, int i,int j,float phi[][100])
{
	int jp = j + 1;
	int jm = j - 1;
	int ip = i + 1;
	int im = i - 1;

	if (im == 0)
		im = nx;
	if (ip == nx + 1)
		ip = 1;
	if (jm == 0)
		jm = ny;
	if (jp == ny + 1)
		jp = 1;

	float hne = phi[ip][j];
	float hnw = phi[im][j];
	float hns = phi[i][jm];
	float hnn = phi[i][jp];
	float hnc = phi[i][j];

	cell[icell].lap_phi[i][j] = (hnw + hne + hns + hnn + hnc) / (dx * dy);
	cell[icell].phi_dx[i][j] = (hne-hnw) / dx;
	cell[icell].phi_dy[i][j] = (hnn - hns) / dy;
	
}

void Grow::cal_volomn_integral(int icell, int i, int j, float phi[][100])
{
	cell[icell].vinteg = cell[icell].vinteg + phi[i][j] * phi[i][j];
	for (int jcell = 0; jcell < ncell; jcell++)
	{
		if (icell != jcell)
			cell[icell].sum_phi[i][j] = cell[icell].sum_phi[i][j] + cell[jcell].phi[i][j] * cell[jcell].phi[i][j];
	}

	cell[icell].vintegx = cell[icell].vintegx + phi[i][j] * cell[icell].phi_dx[i][j] * cell[icell].sum_phi[i][j];
	cell[icell].vintegy = cell[icell].vintegy + phi[i][j] * cell[icell].phi_dy[i][j] * cell[icell].sum_phi[i][j];

	cell[icell].df_dphi = gamma * phi[i][j] * (1 - phi[i][j]) * (1 - 2 * phi[i][j]) + 2 * kappa * phi[i][j] * cell[icell].sum_phi[i][j];
	}

void Grow::write_into_vtk(int nx, int ny, int istep, float phi[][100])
{
	fstream out;
	char filename[30] = { 0 };
	char num[6] = { 0 };
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
	system("pause");
}

void Grow::cell_grow()
{
	float phi_temp[100][100] = { 0 };

	for (int istep = 0; istep < nstep; istep++)
	{
		for (int icell = 0; icell < ncell; icell++)
		{
			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{
					phi_temp[i][j] = cell[icell].phi[i][j];
					cal_laplacian_gradient(icell, i, j, phi_temp);
					cal_volomn_integral(icell, i, j, phi_temp);
					float term2 = -con1 * cell[icell].df_dphi;
					float term3 = -con2 * (cell[icell].vinteg - pi * R * R) * phi_temp[i][j];
					float vnx = cell[icell].vac + con3 * cell[icell].vintegx;
					float vny = cell[icell].vac + con3 * cell[icell].vintegy;
					float term4 = -vnx * cell[icell].phi_dx[i][j] - vny * cell[icell].phi_dy[i][j];

					phi_temp[i][j] = phi_temp[i][j] + dtime * (gamma * cell[icell].lap_phi[i][j] + term2 + term3 + term4);
				}

			}

			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{
					if (phi_temp[i][j] >= 0.99)
						phi_temp[i][j] = 1;
					if (phi_temp[i][j] <= 0)
						phi_temp[i][j] = 0;

					cell[icell].phi[i][j] = phi_temp[i][j];
				}
			}
		}

		if((istep % nprint == 0)|| (istep == 1))
			cout << "done step:" << istep << endl;
		for (int icell = 0; icell < ncell; icell++)
		{
			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{
					phi_point[i][j] = phi_point[i][j] + cell[icell].phi[i][j] * cell[icell].phi[i][j];
				}
			}
		}
		write_into_vtk(nx, ny, istep, phi_point);
	}
}



int main()
{
	Grow dynamic_cells;
	dynamic_cells.initialize_cell();
	dynamic_cells.set_cell_velocity();
	dynamic_cells.cell_grow();
}

