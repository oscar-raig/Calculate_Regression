
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
	cout << "PurgeArrays1>>" << endl;
	GraphXYIterator *iterator = graphXY->createIterator(0);
	iterator->first();

	double previousY =  iterator->current()->getY();
	double currentY = iterator->next()->getY();
	int nCounter = 1;
	while ( !iterator->isEnd())
	{
		cout << "Counter " << nCounter << " Size " << graphXY->getSize() << endl; 
		double currentY = iterator->current()->getY();
		double currentX = iterator->current()->getX();
		if ( similar(previousY,currentY ) )
		{
			std::cout << "The values " << previousY << " And " << currentY << " Are very similar "  << std::endl;
			std::cout << "Then We Shal delete " << currentX << " Position "  << std::endl;
			previousY = currentY;
			moveArrayOnePositionLeft(nCounter);		
			iterator = 	 graphXY->createIterator(nCounter) ;
		}
		else
		{
			previousY= currentY;
			nCounter++;
			iterator->next();
			cout << "Current " << endl;
		}	
	}
	
	cout << "PurgeArrays<<" << endl;
	return graphXY;
}


GraphXY* PurgeGraphXY::moveArrayOnePositionLeft(int nPosition)
{
	
	graphXY->erase(nPosition);

	return graphXY;
}


