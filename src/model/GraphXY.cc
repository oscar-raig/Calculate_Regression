
#include "GraphXY.hpp"

GraphXY::GraphXY(double *x, double *y, int size) {
	for(int i = 0; i < size; i++){
		PointXY point1(x[i],y[i]);
		addPoint(&point1);
	}

}

GraphXY::~GraphXY(){
	graph.clear();	 
	
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

void GraphXY::addPoint(PointXY *pointXY, int position) {
	std::vector<PointXY>::iterator it;
	it = graph.begin() + position;
  	it = graph.insert ( it , *pointXY );
}


void GraphXY::erase(GraphXYIterator *graphIterator) {
	
	graph.erase( graphIterator->iterator);
}

