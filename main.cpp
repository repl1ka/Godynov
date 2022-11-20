#define _CRT_SECURE_NO_WARNINGS

#include<string.h>


#include "C1DProblem.h"
#include "F1DSimulation.h"



char* INPUT_FOLDER = new char[_MAX_PATH];  //"calc/";
char* OUTPUT_FOLDER = new char[_MAX_PATH]; //"calc/output/";

//#include <vld.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

int main(int argc, char *argv[]) {
	
	string outputDir = string("output");
	FEOSIdeal eos = FEOSIdeal(1.4);
	C1DProblem pr = prSashaAl2;
	C1DField *fldptr = new C1DField(pr);
	CExactRiemannSolver ex;
	
	C1DGodunovTypeMethod mtd = C1DGodunovTypeMethod(ex);

	double _dtt[] = {pr.tmin, pr.tmax};
	vector<double> dtt = vector<double>(_dtt, _dtt+sizeof(_dtt)/sizeof(double));
	COutput outp = COutput(pr, outputDir, dtt);
	F1DSimulation sim = F1DSimulation(pr, eos, *fldptr, mtd, outp);
	sim.run();
	delete fldptr;




	delete INPUT_FOLDER;
	delete OUTPUT_FOLDER;
	int p;
	cin>>p;
	return 0;
}



