#include <stack>
#include "PointXY.hpp"
#include "GraphXY.hpp"

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

using namespace log4cplus;

class DeletePointCommand {

private:
	std::stack<PointXY> pointStack;
	bool removeEnd;
	GraphXY* graphXY;
	Logger 	logger;


public:
	DeletePointCommand(){
		logger = Logger::getInstance(LOG4CPLUS_TEXT("UtilVector"));
	};
	void setParameters(GraphXY* graphXY,bool removeEnd);
	DeletePointCommand(GraphXY* graphXY,bool removeEnd);
	~DeletePointCommand();
	GraphXY* execute();
	GraphXY* undo(int numberElementsToRecover);
	GraphXY* getGraphXY(){
		return graphXY;
	}

};