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
// E-Mail      : dksun@seu.edu.cn 
//============================================================================
#include "AiLBFlow.h"
#include "BoltzPara.h"
#include "mkFluidsUser.h"
#include "mkFluidsMultiphase.h"

int write_document(char *fn, const int & maxLoops, const int & maxFrame);
int write_document(const char *fn, mkFluidsMRT & flow, const int & frame, const int & loops);

int run_dendrite_test(mkFluidsMRT & dendrite, int & loops);

int run_flow_solutal_dendrite(mkFluidsMRT & dendrite, int & loops);
int run_flow_thermal_dendrite(mkFluidsMRT & dendrite, int & loops);
int run_solutal_dendrite(mkFluidsMRT & dendrite, int & loops);
int run_thermal_dendrite(mkFluidsMRT & dendrite, int & loops);

int run_solutal_only(mkFluidsMRT& flow, int& loops);

int run_flow_Poiseuille(mkFluidsMRT& flow, int & loops);
int run_flow_AllenCahn(mkFluidsMRT & flow, int & loops);
int run_flow_multiphase(mkFluidsMultiphase& flow, int& loops);

int run_flow_multiphase_dendrite(mkFluidsMultiphase& flow, mkFluidsMRT& dendrite, int& loops);

int main(int argc, char *argv[])
{
	char fn[512];
	int  frame(0);
	int  maxLoops(300);
	int  maxFrame(100);

	//string   xmlfname(argv[1]);
	string   xmlfname("BoltzTechs.xml");
	if (xmlfname == string(""))
	{
		paraXmlFileName = "BoltzTechs.xml";
	}
	else
	{
		paraXmlFileName = xmlfname;
	}
	//cout << "argv[1]=" << argv[1] << "\n";
	//cout << "argv[2]=" << argv[2] << "\n";

	readParameters(maxLoops, maxFrame, xmlfname); //

    make_datafolder();
    make_numthreads();
	
	timer = new mkCPUTimer("Initialization");

	mkSpace space(error);

	mkFluidsUser dendrite(space);
	//mkFluidsMRT dendrite(space);
	dendrite.initialize(paraXmlFileName);
	dendrite.initialize_geometry();

	//mkFluidsMultiphase flow(space);
	//flow.initialize(paraXmlFileName);
	//flow.initialize_geometry();

    write_document(fn, maxLoops, maxFrame); 
	
	//delete timer;
	//for(loops=0;TRUE;loops++)
	for (int loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			//delete timer;
			//record the results
            //write_document(fn, dendrite, frame, loops);

			//flow.write_result(frame);
			//flow.write_2D_vtkfile(loops);
			//flow.write_pltfile2D(frame, 'z');
			
			write_document(fn, dendrite, frame, loops);
			//dendrite.write_vtkfile(loops);
			dendrite.mkFluidsLBM::write_vtkfile(loops);
			//dendrite.write_velocity(loops);

			//write_document(fn, flow, frame, loops);
			//flow.write_vtkfile(loops);

			frame++;
			//timer = new mkCPUTimer;
		}
		//end recording the results
		
		//start the calculation
		{
			//run_flow_multiphase(flow, loops);
			////run_flow_Poiseuille(flow, loops);
			////run_flow_AllenCahn(flow, loops);
			////run_flow_multiphase_dendrite(flow, dendrite, loops);

			run_flow_solutal_dendrite(dendrite, loops);
			//run_solutal_dendrite(dendrite, loops);
			//run_flow_thermal_dendrite(dendrite, loops);
			//run_thermal_dendrite(dendrite, loops);
			//run_solutal_only(dendrite, loops);
		}
		//end the calculation
	}
	//timer = new mkCPUTimer;
	delete timer;
	return 0;
}

int run_dendrite_test(mkFluidsMRT & flow, int & loops)
{
	////timer = new mkCPUTimer("mkFluidsLBM Propagate");
	//flow.propagate();   //...implement streaming for cases without phase changes
	////flow.propagate_PBB();  //...implement streaming for cases with dendrite growth
	//flow.relaxation();     //...implement relaxation //
	////flow.mkFluidsLBM::relaxation();     //...implement relaxation //
	////////flow.relaxation(flow.node);     //...implement relaxation //
	////flow.bdyVelocity();
	////flow.boundary_RBC();//
	//////flow.bounceback();
	//////flow.boundary_walls();//Four sides are walls
	////flow.bdyVelocity();
	////flow.boundary_Couette();
	////delete timer;

	////timer = new mkCPUTimer("mkPhaseField Propagate and Relaxation");
	////timer = new mkCPUTimer("mkPhaseField Propagate");
	//flow.mkPhaseField::evolution(flow.node);//FVM
	//flow.mkPhaseField::evolution_anisotropy();
	flow.mkPhaseField::propagate();        //...implement streaming
	//flow.mkPhaseField::relaxation_AllenCahn(); //...implement relaxation //mkFluids::
	////flow.mkPhaseField::relaxation(); //...implement relaxation //mkFluids::
	////flow.mkPhaseField::relaxation_anisotropy0();
	////delete timer;
	//////timer = new mkCPUTimer("mkPhaseField Relaxation");
	//////flow.relaxation_anisotropy();
	flow.mkPhaseField::relaxation_anisotropy_solute(loops);//cubic or hcp
	//////flow.mkPhaseField::relaxation_anisotropy_thermal();//cubic or hcp
	//flow.mkPhaseField::relaxation_anisotropy_cbc();//singleden OK
	//////flow.mkPhaseField::relaxation_anisotropy_hcp();//singleden OK
	//////delete timer;

	//timer = new mkCPUTimer("mkSolutalField evolution_ATC");
	//flow.mkSolutalField::updateDCs(flow.node);//
	////flow.mkSolutalField::evolution(flow.node);//Use it to create RBC
	//flow.mkSolutalField::evolution_ATC2(flow.node);
	//flow.mkSolutalField::evolution_Thermal(flow.node);
	//flow.mkSolutalField::bdy_constX();
	////flow.mkSolutalField::bdy_RBC();
	//delete timer;

	////////flow.mkSolutalField::propagate_PBB();
	flow.mkSolutalField::propagate();
	flow.mkSolutalField::relaxation();

	//flow.mkSolutalField::propagate();
	////flow.mkSolutalField::propagate_PBB();
	//flow.mkSolutalField::relaxation_anisotropy();

	////Test mkFluidsUser
	//flow.updateDCs(flow.node);//Close it when using ATC phase field.
	//flow.evolution(flow.node);
	//flow.evolution_ATC(flow.node);
	////flow.bdy_constX();
	//flow.bdy_nonflux();
	//flow.bdy_RBC();

	////timer = new mkCPUTimer("ThermalField");
	//flow.mkThermalField::propagate();  //...implement streaming
	//flow.mkThermalField::relaxation(); //...implement relaxation //mkFluids::
	////flow.mkThermalField::bdy_RBC();    //...implement relaxation //Rayleigh-Bernard
	////flow.temperature_bdy_noflux();   //...implement relaxation //zero-flux
	//flow.mkThermalField::bdy_flowin();
	////flow.mkThermalField::bdy_constT();
	////delete timer; 

	return 0;
}

int run_flow_AllenCahn(mkFluidsMRT & flow, int & loops)
{
	flow.propagate();               //...implement streaming for cases without phase changes
	//flow.mkFluidsMRT::propagate_PBB();//...implement streaming for cases with dendrite growth
	flow.mkFluidsMRT::relaxation();   //...implement relaxation 
	//flow.mkFluidsLBM::relaxation(); //...implement relaxation 
	//flow.relaxation(flow.node);     //...implement relaxation 
	flow.bdyVelocity();
	//flow.boundary_RBC();            //
	//flow.bounceback();
	//flow.boundary_walls();          //Four sides are walls

	flow.mkPhaseField::propagate();                        //...implement streaming
	flow.mkPhaseField::relaxation_AllenCahn();// 

	return 0;
}


int run_flow_Poiseuille(mkFluidsMRT& flow, int& loops)
{
	flow.propagate();               //...implement streaming for cases without phase changes
	//flow.mkFluidsMRT::propagate_PBB();//...implement streaming for cases with dendrite growth
	flow.mkFluidsMRT::relaxation();   //...implement relaxation 
	//flow.mkFluidsLBM::relaxation(); //...implement relaxation 
	//flow.relaxation(flow.node);     //...implement relaxation 

	return 0;
}


int run_flow_multiphase(mkFluidsMultiphase& flow, int& loops)
{
	flow.propagate();                   //...implement streaming for cases without phase changes
	//flow.mkFluidsMRT::propagate_PBB();//...implement streaming for cases with dendrite growth
	flow.relaxation();     //...implement relaxation 

	return 0;
}

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

int run_flow_solutal_dendrite(mkFluidsMRT & flow, int & loops)
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
	
	return 0;
}

int run_flow_thermal_dendrite(mkFluidsMRT & flow, int & loops)
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
	
	return 0;
}



int run_thermal_dendrite(mkFluidsMRT & flow, int & loops)
{
	flow.mkPhaseField::propagate();                    //...implement streaming
	flow.mkPhaseField::relaxation_anisotropy_thermal();//cubic or hcp
	//flow.mkPhaseField::relaxation_anisotropy_cbc();  //singleden OK
	//flow.mkPhaseField::relaxation_anisotropy_hcp();  //singleden OK
	//flow.mkPhaseField::evolution(flow.node);         //FVM
	//flow.mkPhaseField::evolution_anisotropy();

	flow.mkThermalField::propagate();  //...implement streaming
	flow.mkThermalField::relaxation(); //...implement relaxation //mkFluids::
	//flow.mkThermalField::bdy_RBC();    //...implement relaxation //Rayleigh-Bernard
	//flow.mkThermalField::bdy_flowin();
	//flow.mkThermalField::bdy_constT();

	return 0;
}

int run_solutal_dendrite(mkFluidsMRT& flow, int& loops)
{
	flow.mkPhaseField::propagate();                        //...implement streaming
	flow.mkPhaseField::relaxation_anisotropy_solute(loops);//cubic or hcp
	//flow.mkPhaseField::relaxation_anisotropy_hcp();      //singleden OK
	//flow.mkPhaseField::evolution(flow.node);             //FVM
	//flow.mkPhaseField::evolution_anisotropy();

	////flow.mkSolutalField::propagate_PBB();
	//flow.mkSolutalField::propagate();
	//flow.mkSolutalField::relaxation();
	//flow.mkSolutalField::updateDCs(flow.node);           //
	//flow.mkSolutalField::evolution(flow.node);           //Use it to create RBC
	flow.mkSolutalField::evolution_ATC2(flow.node);        //
	//flow.mkSolutalField::bdy_constX();
	//flow.mkSolutalField::bdy_RBC();

	return 0;
}

int run_solutal_only(mkFluidsMRT& flow, int& loops)
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

	return 0;
}

int write_document(char *fn, const int & maxLoops, const int & maxFrame)
{
    FILE *out;

    sprintf(fn, "%sdocument.txt", workspace.c_str()); //

    out = fopen(fn, "wt");
    fprintf(out, "TITLE     = \" document \"\n");
    fclose(out);

    //information
    printf("%20s= %d \n", "maxLoops ", maxLoops);
    printf("%20s= %d \n\n", "maxFrame ", maxFrame);
    printf("Well done! Initialized successfully. ");
    printf("Now, the main loops are starting... \n\n");

    //start write record's titles (before main loops)
    printf("frame\n");
    printf("informations: a,b,c,d,e......\n");
    out = fopen(fn, "a+");
    fprintf(out, "frame\t");

    fprintf(out, "\n");
    fclose(out);
    //end write record's titles (before main loops)

    return EXIT_SUCCESS;
}


int write_document(const char *fn, mkFluidsMRT & flow, const int & frame, const int & loops)
{
    FILE *out;

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

