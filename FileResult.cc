/*******************************************************************





********************************************************************/

#include "FileResult.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;

/********************************************************************
FileResult::Print

Description: Print the m_X and m_Y members


*********************************************************************/
void CFileResult::Print()
{
	cout <<  "CFileResult::Print>>" << endl;
	vector<double>::iterator itX;
	vector<double>::iterator itY;
	
	itY = m_Y.begin();
	
  	for ( itX=m_X.begin() ; itX < m_X.end(); itX++ , itY++)
	{
		if ( *itX )
		{
			if (!( *itX != *itX ))
			{
				cout << "X " << *itX <<  " Y " << *itY << endl;
				
			}
		}
	}
	cout <<  "CFileResult::Print<<" << endl;
}
/*
Function: CFileResult::GetXArray
Desription: Returns in the out parameter x, an array 
with the content of the m_X member
*/
void CFileResult::GetXArray(double *x)
{
	
//	x = new  double[m_X.size()];
//	cout << "allocating " << m_X.size() << endl;
	vector<double>::iterator it;
	int i = 0;
  	for ( it=m_X.begin() ; it < m_X.end(); it++ )
	{
		if ( *it )
		{
			if (!( *it != *it ))
			{
			////	cout << "assiging " << *it << endl;
				x[i++] = *it;
			}
		}
	}
}
/*
Function: CFileResult::GetXArray
Desription: Returns in the out parameter y, an array 
with the content of the m_Y member
*/
void CFileResult::GetYArray(double *y)
{

//	y = new  double[m_Y.size()];
	
	vector<double>::iterator it;
	int i = 0;
  	for ( it=m_Y.begin() ; it < m_Y.end(); it++ )
	{
		if ( *it )
		{
			if (!( *it != *it ))
			{
			//	cout << "assiging " << *it << endl;
				y[i++] = *it;
			}
		}
	}
}
/*
Function: FileResult::CFileResult
Description:
	Open the file, parse and store the result
	in the m_X, and m_Y members.
*/


CFileResult::CFileResult( string szFileName )
{
	ifstream resultfile( szFileName.c_str() );
	
	if( !resultfile.is_open())
	{
		cout << "Result file is not open\n";
		return;
	}	

	int nResultlines = 0;
	cout << "Before while \n";
	while (  ! resultfile.eof() )
	{
		//char line[250];
		string line;
		double doubleResult = 0.0;

		resultfile >> line;
		
		if ( line.length() )
		{
//			cout << line << endl;

			std::vector<std::string> strs;
			boost::split(strs, line, boost::is_any_of(";"));
			if ( strs.size() < 2 )
			{
			
				cout << "Error Parsing the results" << endl;
				break;
			}
//			cout << strs[1] << endl;	
			doubleResult = atof(strs[0].c_str());
			m_X.push_back( doubleResult );

			doubleResult = atof(strs[1].c_str());
			m_Y.push_back( doubleResult );
	//		sprintf(line2,"%f",log(doublemd));
	//		nmdlines++;
	//		cout << line << endl;
	
		}
		else
		{
			cout << "Length is 0" << endl;
			cout << "The line is " << line << endl;
		}
	}
}
