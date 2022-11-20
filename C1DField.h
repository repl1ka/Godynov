#ifndef _C1DFIELD_H_
#define _C1DFIELD_H_

#include<vector>
#include"C1DProblem.h"
#include"feos.h"

using namespace std;


class C1DField {
public:
	const int imin, imax;
	vector<double> x;
	const double dx;
	double t, dt;
	vector<vector<double>> U, newU, F; 	// TODO: ����������� ������� � double ** ��� vector<CVector4> � �������� �� ������������������
	C1DField(C1DProblem& pr);
	~C1DField();	
};


#endif