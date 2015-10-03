
#include "GraphXY.hpp"

GraphXY::GraphXY(double *x, double *y, int size) {
	for(int i = 0; i < size; i++){
		addPoint(new PointXY(x[i],y[i]));
	}
}

int GraphXY::getSize() {
	return graph.size();
}

PointXY GraphXY::getPoint(int position) {
	return graph[position];
}


void GraphXY::addPoint(PointXY *pointXY) {
	graph.push_back(*pointXY);
}


void GraphXY::erase(int position) {
	if( position < getSize()) {
		graph.erase( graph.begin() + position);
	}
}

