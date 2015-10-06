#ifndef __utilvector
#define __utilvector
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "linear.h"
#include "GraphXY.hpp"
#include "DeletePointCommand.hpp"

using namespace log4cplus;


#define MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT 0.000001


class UtilVector {
	
	Logger 	logger;
	DeletePointCommand *deletePointCommand;
	int 	timesWorst;
    int		timesEqual;

public:	
	enum CompareCoefficients { COEFFICIENT_EQUAL, COEFFICIENT_BETTER, COEFFICIENT_WORST };
	UtilVector(DeletePointCommand *deletePointCommand){
		logger = Logger::getInstance(LOG4CPLUS_TEXT("UtilVector"));
		logger.setLogLevel(INFO_LOG_LEVEL);
		LOG4CPLUS_ERROR(logger,"Injected DeletePoint Command Work with Mocks in test");
		this->deletePointCommand = deletePointCommand;
	}
	void setLogLevel(log4cplus::LogLevel logLevel ) {
		logger.setLogLevel(logLevel);
	}
	GraphXY* getGraphXYResult();
	GraphXY*  deleteBadPointsFromBeginingOrFromEnd( );

	CompareCoefficients  coefficientGetWorst( double OldCoefficient, double CurrentCoefficient );
	void nextIteration();
	void restoreDeletedValues(int numberElementsToRecover);


private:
	bool decideWithCoeffiecient(CompareCoefficients result);
	Maths::Regression::Linear calculateRegression();
};


#endif