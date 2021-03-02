//============================================================================
//              Anisotropic LBM 3D code
//============================================================================
// Author      : DongKe SUN and Yuting CAO
// Version     : 2010.09.30 MoonLight
// Copyright   : All rights reserved.
// Description : C++, Ansi-style
// Last updated: 2021.01.28 by DongKe SUN and Yuting CAO
//============================================================================
// SUN DongKe, Ph.D
// Website     : http://www.materkit.com
// E-Mail      : dksun@seu.edu.cn and ytcao@seu.edu.cn
//============================================================================
#include "AiLBFlow.h"
#include "BoltzPara.h"
#include "mkFluidsUser.h"
#include "mkMultiphaseField.h"
#include "mkFluidsMultiphase.h"

int write_document(char *fn, const int & maxLoops, const int & maxFrame);
int write_document(const char *fn, mkFluidsMRT & flow, const int & frame, const int & loops);

int run_flow_AllenCahn(mkFluidsMRT& flow, const string& xmlFileName);
int run_flow_Poiseuille(mkFluidsMRT& flow, const string& xmlFileName);
int run_flow_multiphase(mkFluidsMultiphase& flow, const string& xmlFileName);
int run_flow_multiphase_wetting(mkFluidsMultiphase& flow, const string& xmlFileName);
int run_flow_solutal_dendrite(mkFluidsMRT& flow, const string& xmlFileName);
int run_flow_thermal_dendrite(mkFluidsMRT& flow, const string& xmlFileName);
int run_multiPhaseField(mkFluidsMRT& flow, const string& xmlFileName);
int run_solutal_dendrite(mkFluidsMRT & dendrite, const string& xmlFileName);
int run_solutal_only(mkFluidsMRT& flow, const string& xmlFileName);
int run_thermal_dendrite(mkFluidsMRT& flow, const string& xmlFileName);

int run_flow_multiphase_dendrite(mkFluidsMultiphase& flow, mkFluidsMRT& dendrite, int& loops);

int main(int argc, char *argv[])
{
	make_datafolder();
	make_numthreads();

	//string   xmlfname(argv[1]);
	paraXmlFileName = string("BoltzTechs.xml");
	mkSpace space(paraXmlFileName);

	mkFluidsUser dendrite(space);   //Please pay attention to virtual function
	//mkFluidsMRT dendrite(space);
	//mkMultiphaseField dendrite(space);//Attention: base class pointer points to a derived object
	mkFluidsMultiphase flow(space);   //Attention: base class pointer points to a derived object

	int choice = 8;
	//cout << " *** Please input your choice (1-8) to run the cases:" << endl;
	//cin >> choice;
	switch (choice)
	{
	case 0:
		cout << " *** You are excuting multiphase flows by Liang's model. " << endl;
		paraXmlFileName = string("BoltzTechs - multiPhaseFlow.xml");
		flow.reset(paraXmlFileName);
		run_flow_multiphase(flow, paraXmlFileName);
		break;

	case 1:
		cout << " *** You are excuting wetting process by Liang's model. " << endl;
		paraXmlFileName = string("BoltzTechs - wetting.xml");
		flow.reset(paraXmlFileName);
		run_flow_multiphase_wetting(flow, paraXmlFileName);
		break;

	case 2:
		cout << " *** You are excuting flow solutal multi-dendritic growth. " << endl;
		paraXmlFileName = string("BoltzTechs - solutalMultiDendrites.xml");
		dendrite.reset(paraXmlFileName);
		run_flow_solutal_dendrite(dendrite, paraXmlFileName);
		break;

	case 3:
		cout << " *** You are excuting flow thermal dendritic growth. " << endl;
		paraXmlFileName = string("BoltzTechs - flowThermal.xml");
		dendrite.reset(paraXmlFileName);
		run_flow_thermal_dendrite(dendrite, paraXmlFileName);
		break;

	case 4:
		cout << " *** You are excuting solutal dendritic growth. " << endl;
		paraXmlFileName = string("BoltzTechs - solutal.xml");
		dendrite.reset(paraXmlFileName);
		run_solutal_dendrite(dendrite, paraXmlFileName);
		break;

	case 5:
		cout << " *** You are excuting thermal dendritic growth. " << endl;
		paraXmlFileName = string("BoltzTechs - thermal.xml");
		dendrite.reset(paraXmlFileName);
		run_thermal_dendrite(dendrite, paraXmlFileName);
		break;

	case 6:
		/// BGK/MRT are OK. TRT - OK.
		cout << " *** You are excuting Poiseuille flow. " << endl;
		paraXmlFileName = string("BoltzTechs - Poiseuille.xml");
		dendrite.reset(paraXmlFileName);
		run_flow_Poiseuille(dendrite, paraXmlFileName);
		break;

	case 7:
		cout << " *** You are excuting AllenCahn solver. " << endl;
		paraXmlFileName = string("BoltzTechs - AllenCahn.xml");
		flow.reset(paraXmlFileName);
		run_flow_AllenCahn(flow, paraXmlFileName);
		break;

	case 8:
		cout << " *** You are excuting multiPhaseField. " << endl;
		paraXmlFileName = string("BoltzTechs - multiPhaseField.xml");
		dendrite.reset(paraXmlFileName);
		run_multiPhaseField(dendrite, paraXmlFileName);
		break;

	default:
		cout << " *** You have NOT done anything. " << endl;
		break;
	}
	return 0;
}

int write_document(char* fn, const int& maxLoops, const int& maxFrame)
{
	FILE* out;
	sprintf(fn, "%sdocument.txt", workspace.c_str()); //

	out = fopen(fn, "wt");
	fprintf(out, "TITLE     = \" document \"\n");
	fclose(out);

	//information
	printf("%20s= %d \n", "maxLoops ", maxLoops);
	printf("%20s= %d \n\n", "maxFrame ", maxFrame);
	printf(" *** Well done! Initialized successfully! ");
	printf("Now, the main loops are running... \n\n");

	//start write record's titles (before main loops)
	printf("frame \t\t\t loops\n");
	printf(" information: a,b,c,d,e......\n\n");
	out = fopen(fn, "a+");
	fprintf(out, " *** Frame\t");

	fprintf(out, "\n");
	fclose(out);
	//end write record's titles (before main loops)

	return EXIT_SUCCESS;
}

int write_document(const char* fn, mkFluidsMRT& flow, const int& frame, const int& loops)
{
	FILE* out;

	out = fopen(fn, "a+");
	//watching the flow

	printf("%05d\t%18d\n", frame, loops);
	//#ifdef MK_RAYLEIGHBERNARD_C
	//    printf("12.10%lf\n", flow.Solutal_NusseltRBC());
	//#endif
	//#ifdef MK_RAYLEIGHBERNARD_T
	//	printf("%12.10lf\n", flow.Thermal_NusseltRBC());
	//#endif
	//
	//    fprintf(out, "%03d\t", frame);
	//#ifdef MK_RAYLEIGHBERNARD_C
	//    fprintf(out, "%12.10lf", flow.Solutal_NusseltRBC());
	//#endif
	//#ifdef MK_RAYLEIGHBERNARD_T
	//	fprintf(out, "%12.10lf", flow.Thermal_NusseltRBC());
	//#endif

	flow.check_variables(loops, 'x');

	printf("\n");
	fprintf(out, "\n");
	fclose(out);

	return EXIT_SUCCESS;
}

int run_flow_AllenCahn(mkFluidsMRT& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //

	flow.mkFluidsMRT::initialize(xmlFileName);
	flow.mkFluidsMRT::initialize_geometry();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.mkFluidsMRT::write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			flow.mkFluidsMRT::propagate();               //...implement streaming for cases without phase changes
			//flow.mkFluidsMRT::propagate_PBB();//...implement streaming for cases with dendrite growth
			flow.mkFluidsMRT::relaxation();   //...implement relaxation 
			//flow.mkFluidsLBM::relaxation(); //...implement relaxation 
			//flow.relaxation(flow.node);     //...implement relaxation 

			flow.mkPhaseField::propagate();	  //...implement streaming
			//.use relaxation_AllenCahn() a circle without growth
			{
				flow.mkPhaseField::relaxation_AllenCahn();
			}
			//.or use relaxation_AllenCahn() a circle growing up
			//{
			//	flow.mkPhaseField::relaxation_AllenCahn_growth_thermal();
			//	//.open the thermal field when using growth_thermal
			//	flow.mkThermalField::propagate();  //...implement streaming
			//	flow.mkThermalField::relaxation(); //...implement relaxation  
			//}
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}

int run_flow_Poiseuille(mkFluidsMRT& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //

	flow.mkFluidsMRT::initialize(xmlFileName);

	flow.mkFluidsMRT::initialize_geometry_Poiseuille();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.mkFluidsMRT::write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			flow.mkFluidsLBM::propagate();               //...implement streaming for cases without phase changes
			//flow.mkFluidsMRT::propagate_PBB();//...implement streaming for cases with dendrite growth
			//flow.mkFluidsMRT::relaxation();   //...implement relaxation£¬OK 
			flow.mkFluidsLBM::relaxation();     //...implement relaxation£¬OK 
			//flow.relaxation(flow.node);       //...implement relaxation, OK
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}

int run_flow_multiphase(mkFluidsMultiphase& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //

	flow.initialize(xmlFileName);
	flow.initialize_geometry();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			flow.propagate();                   //...implement streaming for cases without phase changes
			//flow.mkFluidsMRT::propagate_PBB();//...implement streaming for cases with dendrite growth
			flow.relaxation();     //...implement relaxation 
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0; 
}

int run_flow_multiphase_wetting(mkFluidsMultiphase& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //
		
	flow.initialize_wetting(xmlFileName);
	//flow.initialize_geometry();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			flow.propagate();                   //...implement streaming for cases without phase changes
			//flow.mkFluidsMRT::propagate_PBB();//...implement streaming for cases with dendrite growth
			flow.relaxation();     //...implement relaxation 
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}

//coding
int run_flow_multiphase_dendrite(mkFluidsMultiphase& flow, mkFluidsMRT& dendrite, int& loops)
{
	dendrite.mkPhaseField::propagate();                    //...implement streaming
	//dendrite.mkPhaseField::relaxation_anisotropy_thermal();//cubic or hcp
	dendrite.mkPhaseField::relaxation_anisotropy_thermal(flow);//cubic or hcp

	dendrite.update_velocity(flow);
	//dendrite.update_thermal_para(flow);

	dendrite.mkThermalField::propagate();  //...implement streaming
	//dendrite.mkThermalField::relaxation(); //...implement relaxation //mkFluids::
	dendrite.mkThermalField::relaxation(flow); //...implement relaxation //mkFluids::
	//dendrite.mkThermalField::bdy_flowin();

	flow.update_geometry(dendrite);

	flow.propagate();      //...implement streaming for cases without phase changes
	flow.relaxation();     //...implement relaxation 

	return 0;
}

int run_flow_solutal_dendrite(mkFluidsMRT& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //

	flow.mkFluidsMRT::initialize(xmlFileName);
	flow.initialize_geometry();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.mkFluidsMRT::write_vtkfile(loops);
			//flow.write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			//flow.propagate();               //...implement streaming for cases without phase changes
			flow.mkFluidsMRT::propagate_PBB();//...implement streaming for cases with dendrite growth
			flow.mkFluidsMRT::relaxation();   //...implement relaxation 
			//flow.mkFluidsLBM::relaxation(); //...implement relaxation 
			//flow.relaxation(flow.node);     //...implement relaxation 
			flow.bdyVelocity();
			//flow.boundary_RBC();            //
			//flow.bounceback();
			//flow.boundary_walls();          //Four sides are walls

			flow.mkPhaseField::propagate();                        //...implement streaming
			flow.mkPhaseField::relaxation_anisotropy_solute(loops);//cubic or hcp
			//flow.mkPhaseField::relaxation_anisotropy_hcp();      //singleden OK
			//flow.mkPhaseField::evolution(flow.node);             //FVM
			//flow.mkPhaseField::evolution_anisotropy();

			//flow.mkSolutalField::propagate_PBB();
			flow.mkSolutalField::propagate();
			flow.mkSolutalField::relaxation();
			//flow.mkSolutalField::updateDCs(flow.node);           //
			//flow.mkSolutalField::evolution(flow.node);           //Use it to create RBC
			////flow.mkSolutalField::evolution_ATC1(flow.node);
			//flow.mkSolutalField::evolution_ATC2(flow.node);

			flow.mkSolutalField::bdy_LBflowin();
			//flow.mkSolutalField::bdy_constX();
			//flow.mkSolutalField::bdy_RBC();
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}

int run_flow_thermal_dendrite(mkFluidsMRT& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //

	flow.mkFluidsMRT::initialize(xmlFileName);
	flow.mkFluidsMRT::initialize_geometry();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.mkFluidsMRT::write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			//flow.propagate();               //...implement streaming for cases without phase changes
			flow.mkFluidsMRT::propagate_PBB();//...implement streaming for cases with dendrite growth
			flow.mkFluidsMRT::relaxation();   //...implement relaxation 
			//flow.mkFluidsLBM::relaxation(); //...implement relaxation 
			//flow.relaxation(flow.node);     //...implement relaxation 
			flow.mkFluidsMRT::bdyVelocity();
			//flow.boundary_RBC();            //
			//flow.bounceback();
			//flow.boundary_walls();          //Four sides are walls

			flow.mkPhaseField::propagate();                    //...implement streaming
			flow.mkPhaseField::relaxation_anisotropy_thermal();//cubic or hcp
			//flow.mkPhaseField::relaxation_anisotropy_cbc();  //singleden OK
			//flow.mkPhaseField::relaxation_anisotropy_hcp();  //singleden OK
			//flow.mkPhaseField::evolution(flow.node);         //FVM
			//flow.mkPhaseField::evolution_anisotropy();

			flow.mkThermalField::propagate();  //...implement streaming
			flow.mkThermalField::relaxation(); //...implement relaxation //mkFluids::
			flow.mkThermalField::bdy_flowin();
			//flow.mkThermalField::bdy_RBC();    //...implement relaxation //Rayleigh-Bernard
			//flow.mkThermalField::bdy_constT();
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}

int run_multiPhaseField(mkFluidsMRT& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //

	flow.initialize(xmlFileName);
	flow.initialize_geometry();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			//flow.mkPhaseField::propagate();  //...implement streaming
			//flow.mkPhaseField::relaxation_anisotropy_thermal(); //cubic or hcp
			flow.propagate();                  //...implement streaming
			flow.relaxation();                 // 

			flow.mkThermalField::propagate();  //...implement streaming
			flow.mkThermalField::relaxation(); //...implement relaxation //mkFluids::
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}



//int run_solutal_dendrite(mkFluidsMRT& flow, const string& xmlFileName)
//{
//	char fn[512];
//	int  frame(0);
//	int  maxLoops(300);
//	int  maxFrame(100);
//
//	timer = new mkCPUTimer("Initialization");
//
//	readParameters(maxLoops, maxFrame, xmlFileName); //
//
//	flow.initialize(xmlFileName);
//	flow.initialize_geometry();
//
//	write_document(fn, maxLoops, maxFrame);
//
//	//delete timer;
//	//for(loops=0;TRUE;loops++)
//	for (int loops = 0; loops <= maxLoops; loops++)
//	{
//		//start recording the results
//		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
//		{
//			write_document(fn, flow, frame, loops);
//			flow.mkFluidsLBM::write_vtkfile(loops);
//			frame++;
//			//timer = new mkCPUTimer;
//		}
//		//end recording the results
//
//		//start the calculation
//		{
//			flow.mkPhaseField::propagate();                        //...implement streaming
//			flow.mkPhaseField::relaxation_anisotropy_solute(loops);//cubic or hcp
//			//flow.mkPhaseField::relaxation_anisotropy_hcp();      //singleden OK
//			//flow.mkPhaseField::evolution(flow.node);             //FVM
//			//flow.mkPhaseField::evolution_anisotropy();
//
//			////flow.mkSolutalField::propagate_PBB();
//			//flow.mkSolutalField::propagate();
//			//flow.mkSolutalField::relaxation();
//			//flow.mkSolutalField::updateDCs(flow.node);           //
//			//flow.mkSolutalField::evolution(flow.node);           //Use it to create RBC
//			flow.mkSolutalField::evolution_ATC2(flow.node);        //
//			//flow.mkSolutalField::bdy_constX();
//			//flow.mkSolutalField::bdy_RBC();
//
//		}
//		//end the calculation
//	}
//	//timer = new mkCPUTimer;
//	delete timer;
//	return 0;
//}

int run_solutal_dendrite(mkFluidsMRT& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //

	flow.mkFluidsMRT::initialize(xmlFileName);
	flow.mkFluidsMRT::initialize_geometry();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.mkFluidsMRT::write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			flow.mkPhaseField::propagate();                        //...implement streaming
			//flow.mkPhaseField::relaxation();//cubic anisotropy_solute
			flow.mkPhaseField::relaxation_anisotropy_solute(loops);//cubic or hcp
			//flow.relaxation_anisotropy_hcp();      //singleden OK
			//flow.evolution(flow.node);             //FVM
			//flow.evolution_anisotropy();

			////flow.mkSolutalField::propagate_PBB();
			flow.mkSolutalField::propagate();
			flow.mkSolutalField::relaxation();
			//flow.mkSolutalField::updateDCs(flow.node);           //
			//flow.mkSolutalField::evolution(flow.node);           //Use it to create RBC
			//flow.mkSolutalField::evolution_ATC2(flow.node);        //
			//flow.mkSolutalField::bdy_constX();
			//flow.mkSolutalField::bdy_RBC();

		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}

int run_solutal_only(mkFluidsMRT& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //

	flow.initialize(xmlFileName);
	flow.initialize_geometry();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			//flow.mkPhaseField::propagate();                        //...implement streaming
			//flow.mkPhaseField::relaxation_anisotropy_solute(loops);//cubic or hcp
			////flow.mkPhaseField::relaxation_anisotropy_hcp();      //singleden OK
			////flow.mkPhaseField::evolution(flow.node);             //FVM
			////flow.mkPhaseField::evolution_anisotropy();

			////flow.mkSolutalField::propagate_PBB();
			//flow.mkSolutalField::propagate();
			//flow.mkSolutalField::relaxation();
			//flow.mkSolutalField::updateDCs(flow.node);           //
			//flow.mkSolutalField::evolution(flow.node);           //Use it to create RBC
			flow.mkSolutalField::evolution_ATC2(flow.node);        //
			//flow.mkSolutalField::bdy_constX();
			//flow.mkSolutalField::bdy_RBC();
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}

int run_thermal_dendrite(mkFluidsMRT& flow, const string& xmlFileName)
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	timer = new mkCPUTimer("Initialization");

	readParameters(maxLoops, maxFrame, xmlFileName); //

	flow.mkFluidsMRT::initialize(xmlFileName);
	flow.mkFluidsMRT::initialize_geometry();

	write_document(fn, maxLoops, maxFrame);

	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			write_document(fn, flow, frame, loops);
			flow.mkFluidsMRT::write_vtkfile(loops);
			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results

		//start the calculation
		{
			flow.mkPhaseField::propagate();  //...implement streaming
			flow.mkPhaseField::relaxation_anisotropy_thermal(); //cubic or hcp
			//flow.propagate();                  //...implement streaming
			//flow.relaxation();         //cubic or hcp

			flow.mkThermalField::propagate();  //...implement streaming
			flow.mkThermalField::relaxation(); //...implement relaxation //mkFluids::
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}

