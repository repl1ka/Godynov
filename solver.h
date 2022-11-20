#ifndef _SOLVER_H_
#define _SOLVER_H_

#include<vector>


#include "feos.h"


using namespace std;

// User-defined data-type for structure of Riemann problem solution
enum RPSolutionType {SWRW, RWSW, SWSW, RWRW, VacRW, RWVac, RWVacRW, nowaves};

// Structure for the Riemann problem solution vector of primitive variables -- (roL, roR, v ,p)
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


class CSolver {
public:
	CSolver();
	CSolver(CTask& _pr) : task(_pr) {}
   	// �������, ���������� �� ���� ������:
	void go(char* fName);
	void goAuSpall(char *fName);
	void goEuler(char* fName=0);
	void goGlass(char* fName);
	void goEulerMovingMesh(char* fName);
	// �������, ����������� ���� ��� ��������� ��������� ����������������
	void testHeatStage(char* inputFileName, char* outputFileName);
	// �������, ����������� ���� ��� �������� ������� ��������� ������
	void testExchangeStage(char* inputFileName, char* outputFileName);
	int getSpallFlag(void) {return spallFlag; }
	void setSpallCellNum(int i) { spallFlag = 1; spallCellNum = i; }
	// ������� ��� ������������ ��������� ��������� ��������� �� ����������� ������ c ������� �� �����
	// ����� ������������ �����������, ���� ������ ��������� ����������
	void testEOSControlNumbers(double _ro, double _ti, double _te);
	CVectorPrimitive calcRPAnalyticalSolution(double roL, double vL, double pL, double roR, double vR, double pR, double x, double t);
	RPSolutionPrimitive solveRP(double roL, double vL, double pL, double roR, double vR, double pR);
	double fL(double p, double roL, double vL, double pL);
	double dfLdp(double p, double roL, double vL, double pL);
	double fR(double p, double roR, double vR, double pR);
	double dfRdp(double p, double roR, double vR, double pR);
	CVectorPrimitive calcRPAnalyticalSolutionEOSBin(double roL, double vL, double pL, double roR, double vR, double pR, double x, double t);
	RPSolutionPrimitive solveRPEOSBin(double roL, double vL, double pL, double roR, double vR, double pR);
	double fLEOSBin(double p, double roL, double vL, double pL);
	double dfLdpEOSBin(double p, double roL, double vL, double pL);
	double fREOSBin(double p, double roR, double vR, double pR);
	double dfRdpEOSBin(double p, double roR, double vR, double pR);
	// ������� ��� ������� ������� ������ � ������� ������� � ��� ��-���������� 
	CVectorPrimitive calcRPExactMillerPuckett(FEOSMieGruneisen& eos, double roL, double vL, double pL, double roR, double vR, double pR, double x, double t);	
	double getdx(); 	

	CTask task;
private:
	//double getEntropy(double ro, double ti, double te);
	double	calcTimeStep(double t);
	double  calcTimeStepEuler(double t);
	int	calcHydroStage(double t, double tau);
	int	calcHydroStageGlass(double t, double tau);
	void	calcHydroStageDebugging(double t, double tau);
	void	calcHydroStageSpallation(double t, double tau);
	int	calcHeatStage(double t, double tau);
	int	calcHeatStageGlass(double t, double tau);
	void	calcHeatStageSpallation(double t, double tau);
	void    calcHeatStage5LayersSi(double t, double tau);
	int calcIonicHeatStageGlass(double t, double tau);
	int	calcExchangeStage(double tau);
	int	calcExchangeStageGlass(double tau);
	void    calcExchangeStage5LayersSi(double tau);
	void	calcHydroStageNoElectron(double t, double tau);
	void	calcHydroStageGushchin(double t, double tau);
	void	calcHydroStageGushchinMovingGrid(double t, double tau);
	void    calcHydroStageGushchinIdealSimple(double t, double tau);
	void    calcHydroStageSimpleCIR(double t, double tau);
	void	calcHydroStageGodunov(double t, double tau);
	void	calcHydroStageGodunovMovingMesh(double t, double tau);
	void	calcHydroStageGodunovEOSBin(double t, double tau);
	void	calcHydroStageMccormack(double t, double tau);
	void	calcHydroStageMHM(double t, double tau);
	void    calcHydroStageRoe(double t, double tau);
	void    calcHydroStageGPS(double t, double tau);
	void    calcHydroStageG2(double t, double tau);
	void	calcHydroStageENO3G(double t, double tau);
	void	calcHydroStageENO2G(double t, double tau);
	void	calcHydroStageLaxFriedrichs(double t, double tau);
	void calcHydroStageMieGruneisen(FEOSMieGruneisen& eos, double t, double tau);
	double calcInterpolationPolynomialDerivative3(double xim32, double xim12, double xip12, double xip32, double fim32, double fim12, double fip12, double fip32, double x);
	// Limiters
	Vector4 calcMinmodSlope(Vector4 deltaMinus, Vector4 deltaplus);
	Vector4 calcMinmodSlopeModified(Vector4 deltaMinus, Vector4 deltaplus); // Probably ENO-2

	Vector4 calcSuperBEESlope(double omega, Vector4 deltaMinus, Vector4 deltaPlus);
	Vector4 calcVanAlbadaSlope(double omega, Vector4 deltaMinus, Vector4 deltaPlus);
	Vector4 calcVanLeerSlope(double omega, Vector4 deltaMinus, Vector4 deltaPlus);
	// ������
	// ������ ������� �������� ������ F = ( ro*v, p+ro*v*v, v*(p+ro*E) )T
	Vector4	calcF(double ro, double v, double p, double e);
	Vector4 calcPhysicalFlux(double ro, double rou, double roE);
	Vector4 calcPhysicalFluxEOSBin(double ro, double rou, double roE);	
	Vector4 calcGodunovFlux(double roL, double rouL, double roEL, double roR, double rouR, double roER);
	Vector4 calcRoeFlux(double roL, double rouL, double roEL, double roR, double rouR, double roER);
	Vector4 calcGPSFlux(double roL, double rouL, double roEL, double roR, double rouR, double roER);
	Vector4 calcHLLCFluxEOSBin(double roL, double rouL, double roEL, double roR, double rouR, double roER);
	Vector4 calcHLLFluxEOSBin(double roL, double rouL, double roEL, double roR, double rouR, double roER);
	// ��� ����������� ���
	Vector4 calcGodunovFluxEOSBin(double roL, double rouL, double roEL, double roR, double rouR, double roER);	
	void	sweep(double *u, double *A, double *B, double *C, double *F, int size);
	// �������, �������� ���������� ��������� (pi, ei) � (pe, ee) 
	// ��� ����� ����������
	double	solveti(double tau, int i, double ro_temp, double dv_temp);
	double  solvete(double t, double tau, int i, double ro_temp, double dv_temp, double ti_temp);
	double  solveteSource(double t, double tau, int i, double ro_temp, double dv_temp, double ti_temp);
	double  solveteConservative(double t, double tau, int i, double ro_temp, double dv_temp, double ti_temp);
	bool	handleKeys(double t);
	void	sweepTe(CFieldOld& ms_temp, CFieldOld& ms_temp_temp, 
					double *A, double *B, double *C, double *F,
					double *alpha, double *beta, int size);
	void	sweepTi(CFieldOld& ms_temp, CFieldOld& ms_temp_temp, 
					double *A, double *B, double *C, double *F,
					double *alpha, double *beta, int size);
	double	compTe();
	double	compTi();
	double	compTe(CFieldOld &ms1, CFieldOld &ms2);
	double	compTi(CFieldOld &ms1, CFieldOld &ms2);
	double  compE(CFieldOld &ms1, CFieldOld &ms2);
	double  compEi(CFieldOld &ms1, CFieldOld &ms2);
	void	dumpToFile(double t);
	void    dumpToFileTestRP(double t, int num);
	void	dumpFlowToFile(double t);
	void	dumpToFileEuler(double t);
	void	setCFL(double _CFL);
	double  getCFL(void);
	// ������� ��� ���������� � �������� ���� ��������
	void	saveSolution(const char* fName, double t);
	double  loadSolution(char* fName);
	void	getEulerAnalyticApproximation(int i, double t, double *p_an, double *v_an, double *ro_an);
	void	getEulerAnalyticApproximationGrid(int i, double x, double t, double *p_an, double *v_an, double *ro_an);
	void	getLagrangeAnalyticApproximation(int i, double t, double *p_an, double *v_an, double *ro_an);
	int getSpallCellNum(void) {return spallCellNum;}
	// ��������� ������� ��� ������������� ���� ���������� 
	// ������� ��� ����� �������� ������.
	void initVars(void);
	CFieldOld ms, ms_temp, ms_temp_temp, ms_prev;
	double	CFL, epsE;
	int maxIt;
	double tauPulse, fluence, deltaSkin, x_pulse_min;
	int i_pulse_min;
	double tInit;
	int iWeak, spallFlag, spallCellNum;
	// ���������� ��� ������������ �������
	double xVacBound;
};


#endif