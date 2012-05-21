#include <iostream>
using namespace std;
#include <vector>

class CFileResult
{
public:
	CFileResult(std::string szFileName);
	int GetNumberResults(){ return m_X.size();}
	void GetXArray(double *x);
	void GetYArray(double *y);
	void Print();

public:
	std::vector<double> m_X;
	std::vector<double> m_Y;



};


