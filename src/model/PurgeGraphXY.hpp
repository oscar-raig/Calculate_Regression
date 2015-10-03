#ifndef purgegraphxy
#define purgegraphxy

#include <math.h>
#include "GraphXY.hpp"

#define RANGE_SIMILAR 0.05

class PurgeGraphXY {

private:
	GraphXY* graphXY;

public:
	PurgeGraphXY(GraphXY *graphXY);
	PurgeGraphXY(double *x, double *y, int size){
		graphXY = new GraphXY(x,y,size);
	};
	bool similar( double a, double b );
	GraphXY* purgeSimilarConsecutiveElements();	
	GraphXY* moveArrayOnePositionLeft(int nPosition);
	GraphXY* getGraphXY() {
		return graphXY;
	}

};


#endif