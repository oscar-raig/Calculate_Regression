#include "gtest/gtest.h"
#include "UtilVector.hpp"


TEST(MoveArrayOnePositionLeft, Zero) {
 	double *x = NULL,*y = NULL;
	int nCounter = 1 ;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	
  	UtilVector::MoveArrayOnePositionLeft( x, y, nCounter, &nSize);	
  	EXPECT_EQ(nSize, 3);
}