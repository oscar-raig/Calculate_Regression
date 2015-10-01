#ifndef graphxyiterator
#define graphxyiterator

#include <vector>
#include "PointXY.hpp"

class GraphXYIterator {

private:
	std::vector<double> x;
	std::vector<double> y;
	int position;
	int graphSize;

public:	
	GraphXYIterator(std::vector<double> x, std::vector<double> y , int graphSize);
	PointXY* next();
	PointXY* current();
	PointXY* previous();
	void first();
	bool isEnd();
	bool isBegin();


};


#endif