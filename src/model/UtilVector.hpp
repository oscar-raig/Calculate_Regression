#ifndef __utilvector
#define __utilvector

#define RANGE_SIMILAR 0.05
#define MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT 0.000001

class UtilVector {
public:	
	static void moveArrayOnePositionLeft(double *x, double *y, int nPosition, int *nSize);
	static void purgeSimilarConsecutiveElements( double *x, double *y, int *nSize );
	static bool similar( double a, double b );
	static bool CoefficientGetWorst( double OldCoefficient, double CurrentCoefficient );
};


#endif