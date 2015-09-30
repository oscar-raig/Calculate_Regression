#ifndef __utilvector
#define __utilvector
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "linear.h"

using namespace log4cplus;

#define RANGE_SIMILAR 0.05
#define MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT 0.000001
#define COEFFICIENT_WORST  0
#define COEFFICIENT_BETTER 1
#define COEFFICIENT_EQUAL  2

class UtilVector {
	Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("UtilVector"));
	std::vector <double> x;
	std::vector <double> y;
public:	
	UtilVector(double *x, double *y, int sizeOfArray){
		logger.setLogLevel(INFO_LOG_LEVEL);
		for (int i=0;i < sizeOfArray; i++) {
			this->x.push_back(x[i]);
			this->y.push_back(y[i]);
		}

	}
	void moveArrayOnePositionLeft(double *x, double *y, int nPosition, int *nSize);
	void purgeSimilarConsecutiveElements( double *x, double *y, int *nSize );
	bool similar( double a, double b );
	int  coefficientGetWorst( double OldCoefficient, double CurrentCoefficient );
	void nextIteration( double **x, double **y, int *nEnd, int bDeletingFromEnd );
	void restoreDeletedValues( bool bDeletingFromEnd, int nTimesWorst, int *nEnd, double *x, double *y );
	void deleteBadPointsFromBeginingOrFromEnd( double *x, double *y,  int *nEnd, int bDeletingFromEnd );
};


#endif