#include <iostream>
#include <math.h>

#include "UtilVector.hpp"

using namespace std;

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




bool UtilVector::CoefficientGetWorst( double OldCoefficient, double CurrentCoefficient )
{
	cout << "CoefficientGetWorst>>" << endl;
	if ( OldCoefficient > CurrentCoefficient  )
        {
		cout << "OldCoefficient  Greater than CurrentCoefficient  ==> We are getting worst" << OldCoefficient << " " << CurrentCoefficient << endl;
	
		if ( ( OldCoefficient - CurrentCoefficient ) > MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT )
		{
			cout << "We are Get worst because OldCoefficient -  CurrentCoefficient " 
			<< 	( OldCoefficient -  CurrentCoefficient ) << " is GreatER the " 
			<<  MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT  << endl;  
			cout << "CoefficientGetWorst<<" << endl;
			return true;
		}
		else
		{
			cout << "We are NOT Get worst (not enough) because OldCoefficient -  CurrentCoefficient  " 
			<< 	( OldCoefficient -  CurrentCoefficient ) << " is  Not GreatER the " 
			<<  MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT  << endl;  
			cout << "CoefficientGetWorst<<" << endl;
			return false;
		}
	}
	else
	{
		cout << "CurrentCoefficient("  << CurrentCoefficient << ") Greater than OldCoeficient (" <<  OldCoefficient << ") We are Geting Better but how much better? " << OldCoefficient << endl;
		if ( (  CurrentCoefficient - OldCoefficient  ) > MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT )
		{
			cout << "We are Get better yes  because OldCoefficient -  CurrentCoefficient " 
			<< 	(  CurrentCoefficient - OldCoefficient ) << " is GreatER the " 
			<<  MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT  << endl;  
			cout << "CoefficientGetWorst<<" << endl;
			return false;
		}
		else
		{
			cout << "We are going better ( we are not going worst ) but not enough because CurrentCoefficient - OldCoefficient  " 
			<< 	(   CurrentCoefficient - OldCoefficient   ) << " is  LowER the CurrentCoefficient" 
			<<   MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT << endl;  
			cout << "CoefficientGetWorst<<" << endl;		}

			return true;
		}
	cout << "CoefficientGetWorst<<" << endl;
}
