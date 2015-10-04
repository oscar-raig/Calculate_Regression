#ifndef graphxy
#define graphxy

#include "PointXY.hpp"
#include "GraphXYIterator.hpp"

class GraphXY {
	std::vector<PointXY> graph;
public:	
	GraphXY(){};
	GraphXY(double *x, double *y, int size);
	int getSize();

	void addPoint(PointXY *pointXY);
	void addPoint(PointXY *pointXY,int position);
	void erase(GraphXYIterator *graphIterator);

	GraphXYIterator * createIterator(int position){
		return new GraphXYIterator(&graph,position);
	}
	PointXY getPoint(int position);

};
#endif 