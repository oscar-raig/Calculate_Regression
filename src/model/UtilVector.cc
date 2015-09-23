#include <iostream>
#include <math.h>

#include "UtilVector.hpp"

using namespace std;


void UtilVector::NextIteration( double **x, double **y, int *nEnd, int bDeletingFromEnd )
{
	(*nEnd)--;
	if ( !bDeletingFromEnd )
	{
		cout << "Deleting x " << **x << " Deleting y " << **y << endl;
		(*x) = (*x) + 1;
		(*y) = (*y) + 1;
	}
}

void UtilVector::RestoreDeletedValues( bool bDeletingFromEnd, int nTimesWorst, int *nEnd, double *x, double *y )
{
	cout << "Recovering " << nTimesWorst << " Elements" << endl; 
	if ( bDeletingFromEnd )
	{
		( *nEnd ) = ( *nEnd ) + nTimesWorst;
	}
	else
	{
		( *nEnd ) = ( *nEnd ) + nTimesWorst;
		x = x - ( nTimesWorst );
		y = y - ( nTimesWorst );

	}
}



void UtilVector::DeleteBadPointsFromBeginingOrFromEnd( double *x, double *y,  int *nEnd, int bDeletingFromEnd )
{
	#define MAX_TIMES_WORST 1
	#define MAX_TIMES_EQUAL 1
  	double 	CoefficientOld = 0.0;
    double 	CoefficientCurrent = 0.0;

    int 	timesWorst = 0;
    int		timesEqual = 0;
	cout << "DeleteBadPointsFromBeginingOrFromEnd>>" << endl; 
	cout << "We are Deleting From " << (bDeletingFromEnd ? "End" : "Begin") << endl; 

	cout << "First Element" << endl;
	
	Maths::Regression::Linear A( *nEnd, x, y );
	CoefficientOld = A.getCoefficient( );
	NextIteration( &x, &y, nEnd, bDeletingFromEnd );

        while  ( *nEnd > 1 ){
			cout << "End :" << *nEnd << endl;
            Maths::Regression::Linear A(*nEnd, x, y);
            cout << "Regression coefficient = " << A.getCoefficient() << endl;
            CoefficientCurrent = A.getCoefficient();
            int result = UtilVector::CoefficientGetWorst( CoefficientOld , CoefficientCurrent );
            if ( COEFFICIENT_WORST == result  ) {
				cout << "We are getting worst " << timesWorst << " with position: " << *nEnd << " value: " << y[*nEnd] << endl;
                 timesWorst++;
                if ( timesWorst > MAX_TIMES_WORST ) {
                        cout << "We are getting worst we quit" << endl;
						RestoreDeletedValues( bDeletingFromEnd, timesWorst, nEnd, x, y );
                        break;
                }
               
            } else if (result == COEFFICIENT_EQUAL) {
				//cout << "We are Not getting worst Old: " << CoefficientOld << " Current: " << CoefficientCurrent << endl;
                timesWorst=0;
                timesEqual++;
                if( timesEqual > MAX_TIMES_EQUAL ) {
                	cout << "Max times equal we quit" << endl;
                	RestoreDeletedValues( bDeletingFromEnd, timesEqual, nEnd, x, y );
                	break;

                }
			} else if ( result == COEFFICIENT_BETTER) {
				timesWorst=0;
			}
		    CoefficientOld = CoefficientCurrent;
		
			NextIteration( &x, &y, nEnd, bDeletingFromEnd );

			cout << "Deleting one position " << endl;

        }
	cout << "DeleteBadPointsFromBeginingOrFromEnd<<" << endl;
  	
}


void UtilVector::moveArrayOnePositionLeft(double *x, double *y, int nPosition, int *nSize)
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


//
// This Function Delete elements if they are very similar

void UtilVector::purgeSimilarConsecutiveElements( double *x, double *y, int *nSize )
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
			cout << "The values " << fPrevious << " And " << y[nCounter] << " Are very similar "  << endl;
			cout << "Then We Shal delete " << x[nCounter] << " Position "  << endl;
			fPrevious = y[nCounter];
			UtilVector::moveArrayOnePositionLeft( x, y, nCounter, nSize);
			
			
		}
		else
		{
			fPrevious= y[nCounter];
			nCounter++;
		}	
	}
	
	cout << "PurgeArrays<<" << endl;
}






bool UtilVector::similar( double a, double b )
{
	if ( fabs ( a - b ) < RANGE_SIMILAR)
		return  true;
	else
		return 	false;
}




int UtilVector::CoefficientGetWorst( double OldCoefficient, double CurrentCoefficient )
{
	LOG4CPLUS_INFO(logger,"CoefficientGetWorst");
	cout << "CoefficientGetWorst>>" << endl;
	double difference =  OldCoefficient - CurrentCoefficient;

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
