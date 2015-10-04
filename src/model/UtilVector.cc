#include <iostream>
#include <iostream>
#include <math.h>

#include "UtilVector.hpp"

using namespace std;

#define MAX_TIMES_WORST 1
#define MAX_TIMES_EQUAL 1


void UtilVector::nextIteration()
{
	(*end)--;
	// Moving to graph delete Graph last element
	// And pushing to stack
	if ( !deletingFromEnd )
	{
		cout << "Deleting x " << *x << " Deleting y " << *y << endl;
		(x) = (x) + 1;
		(y) = (y) + 1;
		// Moving to graph delete Graph begining
		// Pushing to stack
	}
}

void UtilVector::restoreDeletedValues(int numberElementsToRecover)
{
	cout << "Recovering " << numberElementsToRecover << " Elements" << endl; 
	if ( deletingFromEnd )
	{
		( *end ) = ( *end ) + numberElementsToRecover;
		// Moving to graph Pop to end
	}
	else
	{
		( *end ) = ( *end ) + numberElementsToRecover;
		x = x - ( numberElementsToRecover );
		y = y - ( numberElementsToRecover );
		// Moving to graph Pop to begin

	}
}

bool UtilVector::decideWithCoeffiecient(int result) {
   	if ( COEFFICIENT_WORST == result  ) {
		cout << "We are getting worst " << timesWorst << " with position: " << *end << " value: " << y[*end] << endl;
		timesWorst++;
		if ( timesWorst > MAX_TIMES_WORST ) {
		        cout << "We are getting worst we quit" << endl;
				restoreDeletedValues(timesWorst);
		        return true;
		}
           
    } else if (result == COEFFICIENT_EQUAL) {
		//cout << "We are Not getting worst Old: " << CoefficientOld << " Current: " << CoefficientCurrent << endl;
        timesWorst=0;
        timesEqual++;
        if( timesEqual > MAX_TIMES_EQUAL ) {
        	cout << "Max times equal we quit" << endl;
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
    this->x = x;
    this->y = y;
    end = new int;
    *end = graphXY->getSize(); 

    timesWorst = 0;
    timesEqual = 0;
	cout << "DeleteBadPointsFromBeginingOrFromEnd>>" << endl; 
	cout << "We are Deleting From " << (deletingFromEnd ? "End" : "Begin") << endl; 

	cout << "First Element" << endl;
	
	Maths::Regression::Linear A( *end, x, y );
	CoefficientOld = A.getCoefficient( );
	nextIteration();

    while  ( *end > 1 ){
		cout << "End :" << *end << endl;
		cout << "TimesWorst :" << timesWorst << endl;
        Maths::Regression::Linear A(*end, x, y);
        cout << "Regression coefficient = " << A.getCoefficient() << endl;
        CoefficientCurrent = A.getCoefficient();
        int result = UtilVector::coefficientGetWorst( CoefficientOld , CoefficientCurrent );
     	if( decideWithCoeffiecient(result) ) {
     		break;
     	}
	    CoefficientOld = CoefficientCurrent;
		nextIteration( );
		cout << "Deleting one position " << endl;

    }
	cout << "DeleteBadPointsFromBeginingOrFromEnd<<" << endl;

	return new GraphXY(x,y,*end);
  	
}





int UtilVector::coefficientGetWorst( double OldCoefficient, double CurrentCoefficient )
{
	LOG4CPLUS_DEBUG(logger,"coefficientGetWorst>>");
	cout << "CoefficientGetWorst>>" << endl;
	

	if(OldCoefficient == CurrentCoefficient) {
		cout << "Coeficient equals =>not worst";
		return COEFFICIENT_EQUAL;
	}

	if( OldCoefficient > CurrentCoefficient )
        {
		cout << "OldCoefficient  Greater than CurrentCoefficient  ==> We are getting worst " << OldCoefficient << " " << CurrentCoefficient << endl;
	
		if ( ( OldCoefficient - CurrentCoefficient ) > MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT )
		{
			cout << "We are Get worst because OldCoefficient -  CurrentCoefficient " 
			<< 	( OldCoefficient -  CurrentCoefficient ) << " is GreatER the " 
			<<  MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT  << endl;  
			cout << "CoefficientGetWorst<<" << endl;
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
