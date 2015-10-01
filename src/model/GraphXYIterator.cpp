#include "GraphXYIterator.hpp"
#include <cstring>

GraphXYIterator::GraphXYIterator(std::vector<double> x,std::vector<double> y, int graphSize ) {
	this->x = x;
	this->y = y;
	this->graphSize = graphSize;
	position = 0;
}


PointXY* GraphXYIterator::next() {

	if (isEnd()) {
		return NULL;
	}

	PointXY *pointXY =  new PointXY(x[position],y[position]);

	position++;

	return pointXY;
}

PointXY* GraphXYIterator::previous() {

	if ( position == 0) {
		return NULL;
	}

	position--;
	PointXY *pointXY =  new PointXY(x[position],y[position]);

	return pointXY;
}

void GraphXYIterator::first() {
	position = 0;
}


PointXY* GraphXYIterator::current() {

	
	PointXY *pointXY =  new PointXY(x[position],y[position]);

	return pointXY;
}

bool GraphXYIterator::isEnd() {
	return position == graphSize;
} 

bool GraphXYIterator::isBegin() {
	return position == 0;
} 
