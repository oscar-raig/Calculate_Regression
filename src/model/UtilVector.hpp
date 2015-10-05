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
	Logger 	logger;
	GraphXY *graphXY;
	bool 	deletingFromEnd;
	DeletePointCommand *deletePointCommand;
	int 	timesWorst;
    int		timesEqual;

public:	
	UtilVector(GraphXY *graphXY, bool deletingFromEnd){
		logger = Logger::getInstance(LOG4CPLUS_TEXT("UtilVector"));
		logger.setLogLevel(INFO_LOG_LEVEL);
		this->graphXY = graphXY;
		this->deletingFromEnd = deletingFromEnd;
		LOG4CPLUS_ERROR(logger,"Injected DeletePoint Command Work with Mocks in test");
		deletePointCommand = new DeletePointCommand(graphXY,deletingFromEnd);
	}

	GraphXY* getGraphXYResult();
	GraphXY*  deleteBadPointsFromBeginingOrFromEnd( );
	void setDirectionForDeleting(bool deletingFromEnd);

	int  coefficientGetWorst( double OldCoefficient, double CurrentCoefficient );
	void nextIteration();
	void restoreDeletedValues(int numberElementsToRecover);


private:
	bool decideWithCoeffiecient(int result);
	Maths::Regression::Linear calculateRegression();
};


#endif