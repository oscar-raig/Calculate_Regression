#include <iostream>
#include <iostream>
#include <math.h>

#include "UtilVector.hpp"

using namespace std;

#define MAX_TIMES_WORST 1
#define MAX_TIMES_EQUAL 1

GraphXY* UtilVector::getGraphXYResult() {

	return deletePointCommand->getGraphXY();
}




void UtilVector::nextIteration()
{
	LOG4CPLUS_DEBUG(logger,"UtilVector::nextIteration>>");
	deletePointCommand->execute();
	LOG4CPLUS_DEBUG(logger,"UtilVector::nextIteration<<");

}

void UtilVector::restoreDeletedValues(int numberElementsToRecover)
{
	deletePointCommand->undo(numberElementsToRecover);
}

Maths::Regression::Linear UtilVector::calculateRegression(){

	LOG4CPLUS_DEBUG(logger,"UtilVector::calculateRegression>>");
	GraphXY *graphXY = deletePointCommand->getGraphXY();

	double *xx = new double[graphXY->getSize()];
	double *yy = new double[graphXY->getSize()];
	GraphXYIterator *it = graphXY->createIterator(0);
	PointXY * pointXY = it->current();
	int vectorPosition = 0;

	xx[vectorPosition] = pointXY->getX();
	yy[vectorPosition] = pointXY->getY();
	while( !it->isEnd()) {
		xx[vectorPosition] = pointXY->getX();
		yy[vectorPosition] = pointXY->getY();

		pointXY = it->next();
		vectorPosition++;
	}


	Maths::Regression::Linear A( graphXY->getSize(), xx, yy );
	delete []xx;
	delete []yy;
	delete it;
	LOG4CPLUS_DEBUG(logger,"UtilVector::calculateRegression<<");
	return A;
}

bool UtilVector::decideWithCoeffiecient(CompareCoefficients compareCoefficients) {
   	if ( COEFFICIENT_WORST == compareCoefficients  ) {
		timesWorst++;
		if ( timesWorst > MAX_TIMES_WORST ) {
				restoreDeletedValues(timesWorst);
				LOG4CPLUS_DEBUG(logger,"UtilVector::decideWithCoeffiecient true due to MAX_TIMES_WORST");
		        return true;
		}
           
    } else if (compareCoefficients == COEFFICIENT_EQUAL) {
       	timesWorst=0;
        timesEqual++;
        if( timesEqual > MAX_TIMES_EQUAL ) {
        	restoreDeletedValues(timesEqual);
        	LOG4CPLUS_DEBUG(logger,"UtilVector::decideWithCoeffiecient true due to MAX_TIMES_EQUAL");
		        return true;
			return true;

        }
	} else if ( compareCoefficients == COEFFICIENT_BETTER) {
		timesWorst=0;
	}
	return false;
}

GraphXY*  UtilVector::deleteBadPointsFromBeginingOrFromEnd()
{
	
  	double 	CoefficientOld = 0.0;
    double 	CoefficientCurrent = 0.0;
  
    timesWorst = 0;
    timesEqual = 0;

	
	Maths::Regression::Linear regression = calculateRegression();
	CoefficientOld = regression.getCoefficient( );
	nextIteration();
	GraphXY *graphXY = deletePointCommand->getGraphXY();
    while(graphXY->getSize() > 1) {
    		LOG4CPLUS_DEBUG(logger,"UtilVector::deleteBadPointsFromBeginingOrFromEnd " << graphXY->getSize() );
        Maths::Regression::Linear regression = calculateRegression();
        CoefficientCurrent = regression.getCoefficient();
        CompareCoefficients compareCoefficients = UtilVector::coefficientGetWorst( CoefficientOld , CoefficientCurrent );
     	if(decideWithCoeffiecient(compareCoefficients)) {
     		LOG4CPLUS_DEBUG(logger,"UtilVector::deleteBadPointsFromBeginingOrFromEnd exiting");
     		break;
     	}

	    CoefficientOld = CoefficientCurrent;
		nextIteration( );
    }

	return graphXY;
  	
}





UtilVector::CompareCoefficients UtilVector::coefficientGetWorst( double OldCoefficient, double CurrentCoefficient )
{

	if(OldCoefficient == CurrentCoefficient) {

		return COEFFICIENT_EQUAL;
	}

	if( (OldCoefficient > CurrentCoefficient ) > MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT ) {
			return COEFFICIENT_WORST;
	}
	else {
		if ( (  CurrentCoefficient - OldCoefficient  ) > MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT ) {
			return COEFFICIENT_BETTER;
		}
	}	
	return COEFFICIENT_EQUAL;
}
