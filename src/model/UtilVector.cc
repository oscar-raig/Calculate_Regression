#include <iostream>
#include <iostream>
#include <math.h>

#include "UtilVector.hpp"

using namespace std;

#define MAX_TIMES_WORST 1
#define MAX_TIMES_EQUAL 1


void UtilVector::nextIteration()
{
	deletePointCommand->execute();
	LOG4CPLUS_DEBUG(logger,"UtilVector::nextIteration size: " << graphXY->getSize());

}

void UtilVector::restoreDeletedValues(int numberElementsToRecover)
{
	LOG4CPLUS_DEBUG(logger,"UtilVector::restoreDeletedValues size: " << graphXY->getSize());
	deletePointCommand->undo(numberElementsToRecover);
	LOG4CPLUS_DEBUG(logger,"UtilVector::restoreDeletedValues size: " << graphXY->getSize());
}

Maths::Regression::Linear UtilVector::calculateRegression(){

	LOG4CPLUS_DEBUG(logger,"UtilVector::calculateRegression>>");
	double *xx = (double*) malloc(sizeof(double)*graphXY->getSize());
	double *yy = (double*)malloc(sizeof(double)*graphXY->getSize());
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
	LOG4CPLUS_DEBUG(logger,"UtilVector::calculateRegression<<");
	return A;
}

bool UtilVector::decideWithCoeffiecient(int result) {
   	if ( COEFFICIENT_WORST == result  ) {
		timesWorst++;
		if ( timesWorst > MAX_TIMES_WORST ) {
				restoreDeletedValues(timesWorst);
		        return true;
		}
           
    } else if (result == COEFFICIENT_EQUAL) {
		//cout << "We are Not getting worst Old: " << CoefficientOld << " Current: " << CoefficientCurrent << endl;
        timesWorst=0;
        timesEqual++;
        if( timesEqual > MAX_TIMES_EQUAL ) {
        	restoreDeletedValues(timesEqual);
			return true;

        }
	} else if ( result == COEFFICIENT_BETTER) {
		timesWorst=0;
	}
	return false;
}

GraphXY*  UtilVector::deleteBadPointsFromBeginingOrFromEnd()
{
	
  	double 	CoefficientOld = 0.0;
    double 	CoefficientCurrent = 0.0;
    end = new int;
    *end = graphXY->getSize(); 

    timesWorst = 0;
    timesEqual = 0;

	
	Maths::Regression::Linear regression = calculateRegression();
	CoefficientOld = regression.getCoefficient( );
	nextIteration();

    while  ( *end > 1 ){
        Maths::Regression::Linear regression = calculateRegression();
        CoefficientCurrent = regression.getCoefficient();
        int result = UtilVector::coefficientGetWorst( CoefficientOld , CoefficientCurrent );
     	if( decideWithCoeffiecient(result) ) {
     		break;
     	}
	    CoefficientOld = CoefficientCurrent;
		nextIteration( );
    }
	return graphXY;
  	
}





int UtilVector::coefficientGetWorst( double OldCoefficient, double CurrentCoefficient )
{
	LOG4CPLUS_DEBUG(logger,"coefficientGetWorst>>");

	if(OldCoefficient == CurrentCoefficient) {

		return COEFFICIENT_EQUAL;
	}

	if( OldCoefficient > CurrentCoefficient )
        {
	
		if ( ( OldCoefficient - CurrentCoefficient ) > MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT )
		{
			return COEFFICIENT_WORST;
		}
		else
		{
			cout << "We are NOT Get worst (not enough) because OldCoefficient -  CurrentCoefficient  " 
			<< 	( OldCoefficient -  CurrentCoefficient ) << " is  Not GreatER the " 
			<<  MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT  << endl;  
			cout << "CoefficientGetWorst<<" << endl;
			return COEFFICIENT_EQUAL;
		}
	}
	else
	{
		cout << "CurrentCoefficient("  << CurrentCoefficient << ") Greater than OldCoeficient (" <<  OldCoefficient << ") We are Geting Better but how much better? " << OldCoefficient << endl;
		if ( (  CurrentCoefficient - OldCoefficient  ) > MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT )
		{
			cout << "We are Get better yes  because CurrentCoefecient -  OldCoefficient " 
			<< 	(  CurrentCoefficient - OldCoefficient ) << " is GreatER the " 
			<<  MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT  << endl;  
			cout << "CoefficientGetWorst<<" << endl;
			return COEFFICIENT_BETTER;
		}
		else
		{
			cout << "We are going better ( we are not going worst ) but not enough because CurrentCoefficient - OldCoefficient  " 
			<< 	(   CurrentCoefficient - OldCoefficient   ) << " is  LowER the CurrentCoefficient" 
			<<   MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT << endl;  
			cout << "CoefficientGetWorst<<" << endl;		}

			return COEFFICIENT_EQUAL;
		}
	cout << "CoefficientGetWorst<<" << endl;
}
