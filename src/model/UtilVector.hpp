#ifndef __utilvector
#define __utilvector

#define RANGE_SIMILAR 0.05

class UtilVector {
public:	
	static void moveArrayOnePositionLeft(double *x, double *y, int nPosition, int *nSize);
	static void purgeSimilarConsecutiveElements( double *x, double *y, int *nSize );
	static bool similar( double a, double b );
};


#endif