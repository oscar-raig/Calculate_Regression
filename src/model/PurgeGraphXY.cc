
#include <vector>
#include <iostream>
#include "PurgeGraphXY.hpp"
#include "GraphXYIterator.hpp"

using namespace std;

PurgeGraphXY::PurgeGraphXY(GraphXY *graphXY){
	this->graphXY = graphXY;
}

bool PurgeGraphXY::similar( double a, double b )
{
	if ( fabs ( a - b ) < RANGE_SIMILAR)
		return  true;
	else
		return 	false;
}



//
// This Function Delete elements if they are very similar

GraphXY* PurgeGraphXY::purgeSimilarConsecutiveElements()
{
	GraphXYIterator *iterator = graphXY->createIterator(0);
	iterator->first();

	double previousY =  iterator->current()->getY();
	double currentY = iterator->next()->getY();
	while ( !iterator->isEnd()) {
		if (similar(previousY,currentY)) {
			std::cout << "The values " << previousY << " And " << currentY << " Are very similar "  << std::endl;
			moveArrayOnePositionLeft(iterator);		
		}
		else {
			iterator->next();
			cout << "Current " << endl;
		}	
		previousY= currentY;
		currentY = iterator->current()->getY();
	}
	return graphXY;
}


GraphXY* PurgeGraphXY::moveArrayOnePositionLeft(GraphXYIterator *iterator) {
	graphXY->erase(iterator);
	return graphXY;
}

GraphXY* PurgeGraphXY::moveArrayOnePositionLeft(int position) {
	GraphXYIterator *iterator = graphXY->createIterator(position);
	graphXY->erase(iterator);
	delete iterator;
	return graphXY;
}


