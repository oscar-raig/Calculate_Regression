#include <cstring>
#include <iostream>
#include "FileResult.h"
#include "linear.h"

using namespace std;

#define RANGE_SIMILAR 0.05


void MoveArrayOnePositionLeft(double *x, double *y, int nPosition, int *nSize)
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

bool Similar( double a, double b )
{
	if ( fabs ( a - b ) < RANGE_SIMILAR)
		return  true;
	else
		return 	false;
}

//
// This Function Delete elements if they are very similar

void PurgeArrays( double *x, double *y, int *nSize )
{
	cout << "PurgeArrays>>" << endl;
	int nCounter = 0;

	double fPrevious = y[nCounter];
	nCounter++;
	while ( nCounter  < *nSize )
	{
//		cout << "Counter " << nCounter << " Size " << *nSize << endl; 
		if ( Similar(fPrevious,y[nCounter] ) )
		{
			cout << "The values " << fPrevious << " And " << y[nCounter] << " Are very similar "  << endl;
			cout << "Then We Shal delete " << x[nCounter] << " Position "  << endl;
			fPrevious = y[nCounter];
			MoveArrayOnePositionLeft( x, y, nCounter, nSize);
			
			
		}
		else
		{
			fPrevious= y[nCounter];
			nCounter++;
		}	
	}
	
	cout << "PurgeArrays<<" << endl;
}

#define MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT 0.000001

bool CoefficientGetWorst( double OldCoefficient, double CurrentCoefficient )
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

void NextIteration( double *x, double *y, int *nEnd, int bDeletingFromEnd )
{
	(*nEnd)--;
	if ( !bDeletingFromEnd )
	{
		cout << "Deleting x " << *x << " Deleting y " << *y << endl;
		x++;
		y++;
	}
}

void RestoreDeletedValues( bool bDeletingFromEnd, int nTimesWorst, int *nEnd, double *x, double *y )
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



void DeleteBadPointsFromBeginingOrFromEnd( double *x, double *y,  int *nEnd, int bDeletingFromEnd )
{
	#define MAX_TIMES_WORST 2
  	double 	CoefficientOld = 0.0;
        double 	CoefficientCurrent = 0.0;

        int 	nTimesWorst = 0;
	cout << "DeleteBadPointsFromBeginingOrFromEnd>>" << endl; 
	cout << "We are Deleting From " << (bDeletingFromEnd ? "End" : "Begin") << endl; 

	cout << "First Element" << endl;
	
	Maths::Regression::Linear A( *nEnd, x, y );
	CoefficientOld = A.getCoefficient( );
	NextIteration( x, y, nEnd, bDeletingFromEnd );

        while  ( *nEnd > 1 )
        {
		cout << "End :" << *nEnd << endl;
                Maths::Regression::Linear A(*nEnd, x, y);
                cout << "Regression coefficient = " << A.getCoefficient() << endl;
                CoefficientCurrent = A.getCoefficient();
                if ( CoefficientGetWorst( CoefficientOld , CoefficientCurrent ) )
                {
			cout << "We are getting worst " << nTimesWorst << endl;
 
                        if ( nTimesWorst > MAX_TIMES_WORST )
                        {
                                cout << "We are getting worst we quit" << endl;
				RestoreDeletedValues( bDeletingFromEnd, nTimesWorst, nEnd, x, y );
                                break;
                        }
                        nTimesWorst++;
                }
                else
		{
			cout << "We are Not getting worst Old: " << CoefficientOld << " Current: " << CoefficientCurrent << endl;
                        nTimesWorst=0;
		//	break;
		}
		// We store the coeficient
                CoefficientOld = CoefficientCurrent;
		// The Old Coeficient < CoefficientOld

		NextIteration( x, y, nEnd, bDeletingFromEnd );

		cout << "Deleting one position " << endl;

        }
	cout << "DeleteBadPointsFromBeginingOrFromEnd<<" << endl;
  	
}


// Introduce an intermediate, understandble abstraction

int PrintFinalResults(const double *x, const double *y,int nVectorLength, int nDeletedFromBegin, int nDeletedFromEnd, int nElementAtBegin)
{
	// Protecting the program for ivalid input: Parameter invalid

	if ( x == NULL  || y == NULL )
	{
		cout << "X or Y arrays are NULL" << endl;
		return -1;		
	}
	
	cout << endl << endl; 
	cout << "Printing the Results of the Improved regression" << endl;
	cout << endl << endl;
	cout << "At the begining we have " << nElementAtBegin << endl; 
	cout << "We have delete " << nDeletedFromBegin << " From the begining" << endl;
	cout << "We have delete " << nDeletedFromEnd << " From the End" << endl;
	cout << "We are working from " << nDeletedFromBegin << " To " << nVectorLength + nDeletedFromBegin <<  " ( " <<  nVectorLength << " ) " << endl; 	

	cout << "The Final Results are " << endl;

	int nIterator = 0;
	while ( nIterator < nVectorLength )
	{
		cout << "We x " << x[nIterator] << " Y " << y[nIterator] << endl;
		nIterator++; 
	}	

	return 0;

}

#define ARG_POS_CSV   		1
#define ARG_POS_NO_DELETE_BAD_POINTS_FOR_REGRESSION 2
#define ARG_POS_PRINT_ONLY_FILE			    2


int main( int argc, char *argv[] )
{
	bool bDeletePoints = true;
	bool bPrintOnlyFile = false;
	cout << "main>>" << endl;

	// Protecting the program for invalid input : Number of Parameter incorrects
	if ( argc < 2 )
	{
		cout << "Usage: regression FileName [--NoDeletePoints] [--PrintOnlyInputFile]" << endl;
		return -1;
	}

	// Protecting the program for invalid input : Parameter invalid

	if ( argv[ ARG_POS_CSV ] == NULL )
	{
		cout << "FileName is Null" << endl;
		return -1;
	}	
	
	if ( argv[ ARG_POS_NO_DELETE_BAD_POINTS_FOR_REGRESSION ] != NULL )
	{
		if (strcmp( argv[ARG_POS_NO_DELETE_BAD_POINTS_FOR_REGRESSION],"--NoDeletePoints") == 0 ) 
		{
			bDeletePoints = false;
		}	
	}

	if ( argv[ ARG_POS_PRINT_ONLY_FILE ] != NULL )
	{
		if ( strcmp( argv[ARG_POS_PRINT_ONLY_FILE],"--PrintOnlyInputFile" ) == 0 )
		{
			bPrintOnlyFile = true;
		}
	}
	
	// Reading the values from a file
	CFileResult File(argv[1]);
	
	if ( bPrintOnlyFile )
	{
		File.Print();
		return 1;
	}

	double *x =  NULL;
	x = new  double[File.m_X.size()];
	
	if ( x == NULL)
	{
		cout <<  "Error: Allocating X"  << endl;
		return -1;
	}
	
        cout << "Allocating " << File.m_X.size() << "Num Elemepnts :"  << endl;

    	double *y = new  double[File.m_Y.size()];
	
	if ( y == NULL )
	{
		cout << "Error Allocating Y"  << endl;
		return -1;
	}
        
	File.GetXArray( x );
	File.GetYArray( y );

	int nSize =  File.m_X.size(); 
	cout << "We have " << nSize << " elements" << endl;
	
	PurgeArrays( x, y, &nSize );
	
	cout << "And now we have only :"  << nSize <<  " elements" << endl;

	int nFreezeEnd = nSize;
	int nDeletedFromBegin = 0;
	if ( bDeletePoints )
	{
		DeleteBadPointsFromBeginingOrFromEnd( x, y, &nSize, 1);
		nFreezeEnd = nFreezeEnd - nSize;
		nDeletedFromBegin = nSize;
		DeleteBadPointsFromBeginingOrFromEnd( x, y, &nSize, 0);
		nDeletedFromBegin = nDeletedFromBegin - nSize;
	}
	
	if ( PrintFinalResults(x, y, nSize, nDeletedFromBegin, nFreezeEnd, File.m_Y.size()) < 0 )
	{	
		cout << "Error Printing Final Results"  << endl;
		return -1;	
	}

	cout << "main<<" << endl;
	return 1;
}
