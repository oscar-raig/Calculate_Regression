#include "gtest/gtest.h"
#include "UtilVector.hpp"


TEST(moveArrayOnePositionLeft, should_decrement_size) {
 	double *x = NULL,*y = NULL;
	int nCounter = 1 ;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	
  	UtilVector::moveArrayOnePositionLeft( x, y, nCounter, &nSize);	
  	EXPECT_EQ(nSize, 3);
	
	free(x);
	free(y);
}

TEST(moveArrayOnePositionLeft, should_move_position) {
 	double *x = NULL,*y = NULL;
	int nCounter = 1 ;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	
	x[0]=1;
	x[1]=2;
	
  	UtilVector::moveArrayOnePositionLeft( x, y, nCounter, &nSize);	
  	EXPECT_EQ(x[0], 2);
	
	free(x);
	free(y);
}

TEST(similar, similar_should_return_true_when_similar) {
	double x = 4;
	double y = x + (RANGE_SIMILAR*0.9);
	ASSERT_TRUE(UtilVector::similar(x,y));		
}

TEST(similar, similar_should_return_false_when_not_similar) {
	double x = 4;
	double y = x + (RANGE_SIMILAR*1.1);
	ASSERT_FALSE(UtilVector::similar(x,y));		
}


TEST(purgeSimilarConsecutiveElements, not_purge_if_ar_not_similar) {
 	double *x = NULL,*y = NULL;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	
	y[0]=1;
	y[1]=1 +(RANGE_SIMILAR*1.1) ;
	y[2]=1 +(RANGE_SIMILAR*2.1) ;
	y[3]=1 +(RANGE_SIMILAR*3.1) ;
	
  	UtilVector::purgeSimilarConsecutiveElements( x, y,  &nSize);	
  	EXPECT_EQ(nSize, 4);
	
	free(x);
	free(y);
}


TEST(purgeSimilarConsecutiveElements, purge_one_when_are_similar) {
 	double *x = NULL,*y = NULL;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	
	y[0]=1;
	y[1]=1;
	y[2]=1 +(RANGE_SIMILAR*2.1) ;
	y[3]=1 +(RANGE_SIMILAR*3.1) ;
	
  	UtilVector::purgeSimilarConsecutiveElements( x, y,  &nSize);	
  	EXPECT_EQ(nSize, 3);
	
	free(x);
	free(y);
}

TEST(purgeSimilarConsecutiveElements, purge_two_when_are_similar) {
 	double *x = NULL,*y = NULL;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	
	y[0]=1;
	y[1]=1;
	y[2]=1 +(RANGE_SIMILAR*2.1) ;
	y[3]=y[2];
	
  	UtilVector::purgeSimilarConsecutiveElements( x, y,  &nSize);	
  	EXPECT_EQ(nSize, 2);
	
	free(x);
	free(y);
}



TEST(purgeSimilarConsecutiveElements, not_purge_when_no_consecutive) {
 	double *x = NULL,*y = NULL;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	
	y[0]=1;
	y[1]=1 + (RANGE_SIMILAR*2.1);
	y[2]=1 + (RANGE_SIMILAR*3.1);
	y[3]=1;
	
  	UtilVector::purgeSimilarConsecutiveElements( x, y,  &nSize);	
  	EXPECT_EQ(nSize, 4);
	
	free(x);
	free(y);
}


TEST(CoefficientGetWorst, should_return_EQUALS_when_are_equals) {
	double coefficientold = 0.0;
	double coefficientnew = 0.0;
	int result = UtilVector::CoefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(COEFFICIENT_EQUAL,result);
}

TEST(CoefficientGetWorst, should_return_BETTER_when_are_not_equals_and_new_x2_positive) {
	double coefficientold = 0.0;
	double coefficientnew = 0.0 + (2 * MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT);
	int result = UtilVector::CoefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(COEFFICIENT_BETTER,result);
}

TEST(CoefficientGetWorst, should_return_WORST_when_are_not_equals_and_new_x2_negative) {
	double coefficientold = 0.0;
	double coefficientnew = 0.0 - (2 * MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT);
	int result = UtilVector::CoefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(result,COEFFICIENT_WORST);
}


TEST(CoefficientGetWorst, should_return_EQUALS_when_are_not_equals_and_new_not_enough_positve) {
	double coefficientold = 0.0;
	double coefficientnew = 0.0 + ( MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT);
	int result = UtilVector::CoefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(result,COEFFICIENT_EQUAL);
}

TEST(DeleteBadPointsFromBeginingOrFromEnd,if_something_not_get_wrost_not_delete) {
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {0.5,1.8,7,3,4,5,6};
	int size = 7;
	UtilVector::DeleteBadPointsFromBeginingOrFromEnd(x,y,&size,true);

	EXPECT_EQ(size,7);


}

TEST(DeleteBadPointsFromBeginingOrFromEnd,if_something_get_wrost_delete) {
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {0,1,2,3,4,7,6};
	int size = 7;
	UtilVector::DeleteBadPointsFromBeginingOrFromEnd(x,y,&size,true);

	EXPECT_EQ(size,5);

}

