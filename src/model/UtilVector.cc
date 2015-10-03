#include <iostream>
#include <iostream>
#include <math.h>

#include "UtilVector.hpp"

using namespace std;

#define MAX_TIMES_WORST 1
#define MAX_TIMES_EQUAL 1


void UtilVector::nextIteration( double **x, double **y, int *nEnd)
{
	(*nEnd)--;
	if ( !deletingFromEnd )
	{
		cout << "Deleting x " << **x << " Deleting y " << **y << endl;
		(*x) = (*x) + 1;
		(*y) = (*y) + 1;
	}
}

void UtilVector::restoreDeletedValues(int numberElementsToRecover)
{
	cout << "Recovering " << numberElementsToRecover << " Elements" << endl; 
	if ( deletingFromEnd )
	{
		( *end ) = ( *end ) + numberElementsToRecover;
	}
	else
	{
		( *end ) = ( *end ) + numberElementsToRecover;
		x = x - ( numberElementsToRecover );
		y = y - ( numberElementsToRecover );

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

void UtilVector::deleteBadPointsFromBeginingOrFromEnd( double *x, double *y,  int *nEnd)
{
	
  	double 	CoefficientOld = 0.0;
    double 	CoefficientCurrent = 0.0;
    this->x = x;
    this->y = y;
    this->end = nEnd;

    timesWorst = 0;
    timesEqual = 0;
	cout << "DeleteBadPointsFromBeginingOrFromEnd>>" << endl; 
	cout << "We are Deleting From " << (deletingFromEnd ? "End" : "Begin") << endl; 

	cout << "First Element" << endl;
	
	Maths::Regression::Linear A( *nEnd, x, y );
	CoefficientOld = A.getCoefficient( );
	nextIteration( &x, &y, nEnd);

        while  ( *nEnd > 1 ){
			cout << "End :" << *nEnd << endl;
			cout << "TimesWorst :" << timesWorst << endl;
            Maths::Regression::Linear A(*nEnd, x, y);
            cout << "Regression coefficient = " << A.getCoefficient() << endl;
            CoefficientCurrent = A.getCoefficient();
            int result = UtilVector::coefficientGetWorst( CoefficientOld , CoefficientCurrent );
         	if( decideWithCoeffiecient(result) ) {
         		break;
         	}
		    CoefficientOld = CoefficientCurrent;
			nextIteration( &x, &y, nEnd );
			cout << "Deleting one position " << endl;

        }
	cout << "DeleteBadPointsFromBeginingOrFromEnd<<" << endl;
  	
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
