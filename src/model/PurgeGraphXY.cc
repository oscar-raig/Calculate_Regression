
#include <vector>
#include <iostream>
#include "PurgeGraphXY.hpp"

using namespace std;

bool PurgeGraphXY::similar( double a, double b )
{
	if ( fabs ( a - b ) < RANGE_SIMILAR)
		return  true;
	else
		return 	false;
}

PurgeGraphXY::PurgeGraphXY(GraphXY *graphXY){
	this->graphXY = graphXY;
}

//
// This Function Delete elements if they are very similar

void PurgeGraphXY::purgeSimilarConsecutiveElements( double *x, double *y, int *nSize )
{
	cout << "PurgeArrays>>" << endl;
	int nCounter = 0;

	double fPrevious = y[nCounter];
	nCounter++;
	while ( nCounter  < *nSize )
	{
//		cout << "Counter " << nCounter << " Size " << *nSize << endl; 
		if ( similar(fPrevious,y[nCounter] ) )
		{
			std::cout << "The values " << fPrevious << " And " << y[nCounter] << " Are very similar "  << std::endl;
			std::cout << "Then We Shal delete " << x[nCounter] << " Position "  << std::endl;
			fPrevious = y[nCounter];
			moveArrayOnePositionLeft( x, y, nCounter, nSize);			
		}
		else
		{
			fPrevious= y[nCounter];
			nCounter++;
		}	
	}
	
	cout << "PurgeArrays<<" << endl;
}


void PurgeGraphXY::moveArrayOnePositionLeft(double *x, double *y, int nPosition, int *nSize)
{
	int i = 0;
	for ( i = nPosition-1; i < *nSize-1; i++)
	{
		x[i]=x[i+1];
	}
	
	for ( i = nPosition-1; i < *nSize-1; i++)
	{
		y[i]=y[i+1];
	}

	*nSize= *nSize - 1;
}


