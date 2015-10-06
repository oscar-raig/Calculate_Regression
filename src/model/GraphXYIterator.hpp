#ifndef graphxyiterator
#define graphxyiterator

#include <vector>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "PointXY.hpp"

using namespace log4cplus;

class GraphXYIterator {
friend class GraphXY;
private:
	bool allocatedMemory;
	Logger 	logger;
	int position;
	std::vector<PointXY> *graph;

	std::vector<PointXY>::iterator iterator;

public:

GraphXYIterator(std::vector<double> x, std::vector<double> y , int graphSize);
GraphXYIterator(std::vector<PointXY> *graph,int position){
		logger = Logger::getInstance(LOG4CPLUS_TEXT("GraphXYIterator"));
		this->graph = graph;
		this->position = position;
		iterator = graph->begin() + position;
		allocatedMemory = false;
	}
~GraphXYIterator();

	PointXY* next();
	PointXY* current();
	PointXY* previous();

	void end();
	void first();
	bool isEnd();
	bool isBegin();
};


#endif