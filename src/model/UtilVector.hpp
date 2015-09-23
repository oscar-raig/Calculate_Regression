#ifndef __utilvector
#define __utilvector
#include <log4cplus/logger.h>
#include "linear.h"

using namespace log4cplus;

#define RANGE_SIMILAR 0.05
#define MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT 0.000001
#define COEFFICIENT_WORST  0
#define COEFFICIENT_BETTER 1
#define COEFFICIENT_EQUAL  2

class UtilVector {
	Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("UtilVector"));
public:	
	static void moveArrayOnePositionLeft(double *x, double *y, int nPosition, int *nSize);
	static void purgeSimilarConsecutiveElements( double *x, double *y, int *nSize );
	static bool similar( double a, double b );
	static int  CoefficientGetWorst( double OldCoefficient, double CurrentCoefficient );
	static void NextIteration( double *x, double *y, int *nEnd, int bDeletingFromEnd );
	static void RestoreDeletedValues( bool bDeletingFromEnd, int nTimesWorst, int *nEnd, double *x, double *y );
	static void DeleteBadPointsFromBeginingOrFromEnd( double *x, double *y,  int *nEnd, int bDeletingFromEnd );
};


#endif