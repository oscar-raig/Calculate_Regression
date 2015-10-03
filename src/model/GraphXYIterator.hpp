#ifndef graphxyiterator
#define graphxyiterator

#include <vector>
#include "PointXY.hpp"

class GraphXYIterator {
friend class GraphXY;
private:

	int position;
	std::vector<PointXY> *graph;

	std::vector<PointXY>::iterator iterator;

public:

GraphXYIterator(std::vector<double> x, std::vector<double> y , int graphSize);
GraphXYIterator(std::vector<PointXY> *graph,int position){
		this->graph = graph;
		this->position = position;
		iterator = graph->begin() + position;
	}


	PointXY* next();
	PointXY* current();
	PointXY* previous();
	void first();
	bool isEnd();
	bool isBegin();
};


#endif