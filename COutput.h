#ifndef _COUTPUT_H_
#define _COUTPUT_H_

#include "c1dproblem.h"
#include "c1dfield.h"

enum RPSolutionType {SWRW, RWSW, SWSW, RWRW, VacRW, RWVac, RWVacRW, nowaves};

struct RPSolutionPrimitive {
	RPSolutionPrimitive() : roL(0.), roR(0.), v(0.), p(0.), type(RPSolutionType::nowaves) {}
	double roL, roR, v, p;
	RPSolutionType type;
};

struct CVectorPrimitive {
	double ro;
	double v;
	double p;
};

class COutput {
	string subDir;
	vector<double> dtt; // Vector of time moments to write .dat files to disk
	string tUnit;
	double tMul;
	int nDump, tPrecision, dtPrecision;	
	string getProgressBar(C1DProblem& _pr, double t);
	int print(void);
	//int dump(C1DProblem& pr, C1DField& fld, CEOSMieGruneisen& eos, string fName);	
	int dump(C1DProblem& pr, C1DField& fld, FEOS& eos, string fName);	
	double fL(FEOS& eos, double p, double roL, double vL, double pL);
	double dfLdp(FEOS& eos, double p, double roL, double vL, double pL);
	double fR(FEOS& eos, double p, double roR, double vR, double pR);
	double dfRdp(FEOS& eos, double p, double roR, double vR, double pR);
	RPSolutionPrimitive solveRP(FEOS& eos, double roL, double vL, double pL, double roR, double vR, double pR);
	CVectorPrimitive calcRPAnalyticalSolution(FEOS& eos, double roL, double vL, double pL, double roR, double vR, double pR, double x, double t);
public:
	COutput(C1DProblem& _pr, string _subdir, vector<double> _dtt);

	//int manageFileOutput(C1DProblem& pr, C1DField& fld, CEOSMieGruneisen& eos);
	int manageFileOutput(C1DProblem& pr, C1DField& fld, FEOS& eos);
	int manageScreenOutput(C1DProblem& pr, int iteration, double t, double dt, double cfl, double tCalc);
};



#endif