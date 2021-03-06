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



TEST_F(UtilVectorTest,CoefficientGetWorst_should_return_EQUALS_when_are_equals) {

	UtilVector utilVector(NULL); 
	double coefficientold = 0.0;
	double coefficientnew = 0.0;
	int result = utilVector.coefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(UtilVector::COEFFICIENT_EQUAL,result);
}

TEST_F(UtilVectorTest,CoefficientGetWorst_should_return_BETTER_when_are_not_equals_and_new_x2_positive) {
	UtilVector utilVector(NULL);  
	double coefficientold = 0.0;
	double coefficientnew = 0.0 + (2 * MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT);
	int result = utilVector.coefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(UtilVector::COEFFICIENT_BETTER,result);
}

TEST_F(UtilVectorTest,CoefficientGetWorst_should_return_WORST_when_are_not_equals_and_new_x2_negative) {
	UtilVector utilVector(NULL); 
	double coefficientold = 0.0;
	double coefficientnew = 0.0 - (2 * MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT);
	int result = utilVector.coefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(result,UtilVector::COEFFICIENT_WORST);
}


TEST_F(UtilVectorTest,CoefficientGetWorst_should_return_EQUALS_when_are_not_equals_and_new_not_enough_positve) {

	double coefficientold = 0.0;
	double coefficientnew = 0.0 + ( MAXIM_DIFFERENCE_BETWEEN_TWO_COEFFICIENT);
	UtilVector utilVector(NULL); 
	int result = utilVector.coefficientGetWorst(coefficientold,coefficientnew);
	EXPECT_EQ(result,UtilVector::COEFFICIENT_EQUAL);
}

TEST_F(UtilVectorTest,DeleteBadPointsFromBeginingOrFromEnd_if_something_not_get_wrost_not_delete) {
	
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {0.5,1.8,7,3,4,5,6};
	int size = 7;
	GraphXY *graphXY = new GraphXY(x,y,size);
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY, true);
	UtilVector utilVector(deletePointCommand); 
	graphXY = utilVector.deleteBadPointsFromBeginingOrFromEnd();


	EXPECT_EQ(graphXY->getSize(),7);

	delete graphXY;
	delete deletePointCommand;
}

TEST_F(UtilVectorTest,DeleteBadPointsFromBeginingOrFromEnd_if_something_get_wrost_delete) {
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {0,1,2,3,4,7,6};
	int size = 7;
	GraphXY *graphXY = new GraphXY(x,y,size);
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY, true);
	UtilVector utilVector(deletePointCommand); 
	graphXY = utilVector.deleteBadPointsFromBeginingOrFromEnd();

	EXPECT_EQ(graphXY->getSize(),5);

	delete graphXY;
	delete deletePointCommand;
}


TEST_F(UtilVectorTest,DeleteBadPointsFromBeginingOrFromEnd_if_something_not_get_wrost_not_delete_begining_from_begin) {

	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {0,1,2,3,4,5,6};
	int size = 7;
	GraphXY *graphXY = new GraphXY(x,y,size);
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY, false);
	UtilVector utilVector(deletePointCommand); 
	graphXY = utilVector.deleteBadPointsFromBeginingOrFromEnd();

	EXPECT_EQ(graphXY->getSize(),7);
	delete graphXY;
	delete deletePointCommand;
}


TEST_F(UtilVectorTest,DeleteBadPointsFromBeginingOrFromEnd_if_something_get_wrost_delete_begining_from_begin) {

	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {1,2,2,3,4,5,6};
	int size = 7;
	GraphXY *graphXY = new GraphXY(x,y,size);
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY, false);
	UtilVector utilVector(deletePointCommand); 	
	graphXY = utilVector.deleteBadPointsFromBeginingOrFromEnd();

	EXPECT_EQ(graphXY->getSize(),5);
	delete graphXY;
	delete deletePointCommand;

}



