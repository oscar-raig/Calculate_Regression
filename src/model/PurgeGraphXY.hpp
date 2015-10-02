#ifndef purgegraphxy
#define purgegraphxy

#include <math.h>
#include "GraphXY.hpp"

#define RANGE_SIMILAR 0.05

class PurgeGraphXY {

private:
	GraphXY *graphXY;

public:
	PurgeGraphXY(GraphXY *graphXY);
	PurgeGraphXY(double *x, double *y, int size){};
	bool similar( double a, double b );
	void purgeSimilarConsecutiveElements( double *x, double *y, int *nSize );	
	void moveArrayOnePositionLeft(double *x, double *y, int nPosition, int *nSize);

};


#endif