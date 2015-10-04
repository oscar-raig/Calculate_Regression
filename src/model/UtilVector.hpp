#ifndef __utilvector
#define __utilvector
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "linear.h"
#include "GraphXY.hpp"
#include "DeletePointCommand.hpp"

using namespace log4cplus;


#define MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT 0.000001
#define COEFFICIENT_WORST  0
#define COEFFICIENT_BETTER 1
#define COEFFICIENT_EQUAL  2

class UtilVector {
	Logger logger;
	GraphXY *graphXY;
	bool deletingFromEnd;
	DeletePointCommand *deletePointCommand;

	double *x;
	double *y;
	int 	timesWorst;
    int		timesEqual;
    int *end;
public:	
	UtilVector(double *x, double *y, int sizeOfArray,bool deletingFromEnd){
		logger = Logger::getInstance(LOG4CPLUS_TEXT("UtilVector"));
		this->x = x;
    	this->y = y;
		logger.setLogLevel(INFO_LOG_LEVEL);
		graphXY = new GraphXY(x,y,sizeOfArray);
		this->deletingFromEnd = deletingFromEnd;
		deletePointCommand = new DeletePointCommand(graphXY,deletingFromEnd);
	}

	GraphXY* getGraphXYResult() {
		return graphXY;
	}
	int  coefficientGetWorst( double OldCoefficient, double CurrentCoefficient );
	void nextIteration( double **x, double **y, int *nEnd);
	void restoreDeletedValues(int numberElementsToRecover);
	GraphXY*  deleteBadPointsFromBeginingOrFromEnd( );
	void setDirectionForDeleting(bool deletingFromEnd) {
		this->deletingFromEnd = deletingFromEnd;		
	}

private:
	bool decideWithCoeffiecient(int result);
};


#endif