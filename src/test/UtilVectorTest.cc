#include <log4cplus/configurator.h>
#include "gtest/gtest.h"
#include "UtilVector.hpp"

class UtilVectorTest : public ::testing::Test {
 protected:
  	virtual void SetUp() {
  		BasicConfigurator config;
    	config.configure(); 
  }  
};


TEST_F(UtilVectorTest,moveArrayOnePositionLeft_should_decrement_size) {
	
 	double *x = NULL,*y = NULL;
	int nCounter = 1 ;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	UtilVector utilVector(x,y,nSize);
  	utilVector.moveArrayOnePositionLeft( x, y, nCounter, &nSize);	
  	EXPECT_EQ(nSize, 3);
	
	free(x);
	free(y);
}

TEST_F(UtilVectorTest,moveArrayOnePositionLeft_should_move_position) {
	 
 	double *x = NULL,*y = NULL;
	int nCounter = 1 ;
	int nSize = 4;
	
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	
	x[0]=1;
	x[1]=2;
	
	UtilVector utilVector(x,y,nSize); 
  	utilVector.moveArrayOnePositionLeft( x, y, nCounter, &nSize);	
  	EXPECT_EQ(x[0], 2);
	
	free(x);
	free(y);
}

TEST_F(UtilVectorTest,similar_similar_should_return_true_when_similar) {
	UtilVector utilVector(NULL,NULL,0);   
	double x = 4;
	double y = x + (RANGE_SIMILAR*0.9);
	ASSERT_TRUE(utilVector.similar(x,y));		
}

TEST_F(UtilVectorTest,similar_similar_should_return_false_when_not_similar) {
	UtilVector utilVector(NULL,NULL,0);  
	double x = 4;
	double y = x + (RANGE_SIMILAR*1.1);
	ASSERT_FALSE(utilVector.similar(x,y));		
}


TEST_F(UtilVectorTest,purgeSimilarConsecutiveElements_not_purge_if_ar_not_similar) {
	 
 	double *x = NULL,*y = NULL;
	int size = 4;
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	
	y[0]=1;
	y[1]=1 +(RANGE_SIMILAR*1.1) ;
	y[2]=1 +(RANGE_SIMILAR*2.1) ;
	y[3]=1 +(RANGE_SIMILAR*3.1) ;
	
	UtilVector utilVector(x,y,size); 
  	utilVector.purgeSimilarConsecutiveElements( x, y,  &size);	
  	EXPECT_EQ(size, 4);
	
	free(x);
	free(y);
}


TEST_F(UtilVectorTest,purgeSimilarConsecutiveElements_purge_one_when_are_similar) {

 	double *x = NULL,*y = NULL;
	int size = 4;
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	
	y[0]=1;
	y[1]=1;
	y[2]=1 +(RANGE_SIMILAR*2.1) ;
	y[3]=1 +(RANGE_SIMILAR*3.1) ;
	UtilVector utilVector(x,y,size); 
  	utilVector.purgeSimilarConsecutiveElements( x, y,  &size);	
  	EXPECT_EQ(size, 3);
	
	free(x);
	free(y);
}

TEST_F(UtilVectorTest,purgeSimilarConsecutiveElements_purge_two_when_are_similar) {
	
 	double *x = NULL,*y = NULL;
	int size = 4;
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	
	y[0]=1;
	y[1]=1;
	y[2]=1 +(RANGE_SIMILAR*2.1) ;
	y[3]=y[2];
	UtilVector utilVector(x,y,size); 
  	utilVector.purgeSimilarConsecutiveElements( x, y,  &size);	
  	EXPECT_EQ(size, 2);
	
	free(x);
	free(y);
}



TEST_F(UtilVectorTest,purgeSimilarConsecutiveElements_not_purge_when_no_consecutive) {

 	double *x = NULL,*y = NULL;
	int size = 4;
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	
	y[0]=1;
	y[1]=1 + (RANGE_SIMILAR*2.1);
	y[2]=1 + (RANGE_SIMILAR*3.1);
	y[3]=1;
	
	UtilVector utilVector(x,y,size); 
  	utilVector.purgeSimilarConsecutiveElements( x, y,  &size);	
  	EXPECT_EQ(size, 4);
	
	free(x);
	free(y);
}


TEST_F(UtilVectorTest,CoefficientGetWorst_should_return_EQUALS_when_are_equals) {
	UtilVector utilVector(NULL,NULL,0); 
	double coefficientold = 0.0;
	double coefficientnew = 0.0;
	int result = utilVector.coefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(COEFFICIENT_EQUAL,result);
}

TEST_F(UtilVectorTest,CoefficientGetWorst_should_return_BETTER_when_are_not_equals_and_new_x2_positive) {
	UtilVector utilVector(NULL,NULL,0);  
	double coefficientold = 0.0;
	double coefficientnew = 0.0 + (2 * MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT);
	int result = utilVector.coefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(COEFFICIENT_BETTER,result);
}

TEST_F(UtilVectorTest,CoefficientGetWorst_should_return_WORST_when_are_not_equals_and_new_x2_negative) {
	UtilVector utilVector(NULL,NULL,0); 
	double coefficientold = 0.0;
	double coefficientnew = 0.0 - (2 * MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT);
	int result = utilVector.coefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(result,COEFFICIENT_WORST);
}


TEST_F(UtilVectorTest,CoefficientGetWorst_should_return_EQUALS_when_are_not_equals_and_new_not_enough_positve) {

	double coefficientold = 0.0;
	double coefficientnew = 0.0 + ( MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT);
	UtilVector utilVector(NULL,NULL,0); 
	int result = utilVector.coefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(result,COEFFICIENT_EQUAL);
}

TEST_F(UtilVectorTest,DeleteBadPointsFromBeginingOrFromEnd_if_something_not_get_wrost_not_delete) {
	
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {0.5,1.8,7,3,4,5,6};
	int size = 7;
	UtilVector utilVector(x,y,size); 
	utilVector.deleteBadPointsFromBeginingOrFromEnd(x,y,&size,true);

	EXPECT_EQ(size,7);


}

TEST_F(UtilVectorTest,DeleteBadPointsFromBeginingOrFromEnd_if_something_get_wrost_delete) {
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {0,1,2,3,4,7,6};
	int size = 7;
	UtilVector utilVector(x,y,size); 
	utilVector.deleteBadPointsFromBeginingOrFromEnd(x,y,&size,true);

	EXPECT_EQ(size,5);

}


TEST_F(UtilVectorTest,DeleteBadPointsFromBeginingOrFromEnd_if_something_not_get_wrost_not_delete_begining_from_begin) {

	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {0,1,2,3,4,5,6};
	int size = 7;
	UtilVector utilVector(x,y,size); 
	utilVector.deleteBadPointsFromBeginingOrFromEnd(x,y,&size,false);

	EXPECT_EQ(size,7);
}


TEST_F(UtilVectorTest,DeleteBadPointsFromBeginingOrFromEnd_if_something_get_wrost_delete_begining_from_begin) {

	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {1,2,2,3,4,5,6};
	int size = 7;
	UtilVector utilVector(x,y,size); 
	utilVector.deleteBadPointsFromBeginingOrFromEnd(x,y,&size,false);

	EXPECT_EQ(size,5);

}

TEST_F(UtilVectorTest,purgeSimilarConsecutiveElements_if_vector_have_similar_values_should_remove_elements) {
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {1,2,2,2,2,5,6};
	int size = 7;

	UtilVector utilVector(x,y,size); 
	utilVector.purgeSimilarConsecutiveElements(x,y,&size);

	EXPECT_EQ(size,4);
	EXPECT_EQ(y[0],1);
	EXPECT_EQ(y[1],2);
	EXPECT_EQ(y[2],5);
	EXPECT_EQ(y[3],6);

}
TEST_F(UtilVectorTest,purgeSimilarConsecutiveElements_if_vector_have_NO_similar_values_should_NOT_remove_elements) {
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {1,2,3,4,5,6,7};
	int size = 7;
	UtilVector utilVector(x,y,size); 
	utilVector.purgeSimilarConsecutiveElements(x,y,&size);

	EXPECT_EQ(size,7);
	
}


