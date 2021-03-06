#include "GraphXYIterator.hpp"
#include <cstring>
#include <iostream>


using namespace std;

GraphXYIterator::GraphXYIterator(std::vector<double> x,std::vector<double> y, int graphSize ) {
	logger = Logger::getInstance(LOG4CPLUS_TEXT("GraphXYIterator"));
	graph = new std::vector<PointXY>;
	for(int i =0; i < graphSize; i++) {
		PointXY point(x[i], y[i]);
		graph->push_back(point);
	}
	iterator = graph->begin();
	position = 0;
	allocatedMemory = true;

}

GraphXYIterator::~GraphXYIterator() {

	if( allocatedMemory) {
		delete graph;
	}
}


PointXY* GraphXYIterator::next() {

	if (isEnd()) {
		return NULL;
	}

	position++;
	iterator = graph->begin() + position;

	return &(*iterator);
}

PointXY* GraphXYIterator::previous() {

	if ( position == 0) {
		return NULL;
	}

	position--;
	iterator = graph->begin() + position;
	

	return &(*iterator);
}

void GraphXYIterator::first() {
	position = 0;
	iterator = graph->begin() + position;
}

void GraphXYIterator::end() {
	position = graph->size();
	iterator = graph->end();
}


PointXY* GraphXYIterator::current() {

	return &(*iterator);
}

bool GraphXYIterator::isEnd() {
//	cout << "isEnd:position" << position << endl;
//	cout << "isEnd:size" << graph->size() << endl;
	return (((unsigned int)position) == graph->size());
} 

bool GraphXYIterator::isBegin() {
	return position == 0;
} 
