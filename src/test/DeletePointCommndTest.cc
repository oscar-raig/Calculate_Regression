#include "gtest/gtest.h"
#include <log4cplus/configurator.h>
#include "GraphXY.hpp"
#include "DeletePointCommand.hpp"


class DeletePointCommandTest : public ::testing::Test {
 protected:
 	Logger 	logger;
  	virtual void SetUp() {
  		BasicConfigurator config;
    	config.configure(); 
    	logger = Logger::getInstance(LOG4CPLUS_TEXT("DeletePointCommandTest"));
  }  
};


TEST_F(DeletePointCommandTest,executesreturSamePointerAsInConstruction) {

	GraphXY *graphXY = new GraphXY();
	PointXY point1(1,1);
	graphXY->addPoint(&point1);
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY,false);

	GraphXY *graphXYResult = deletePointCommand->execute();
	ASSERT_TRUE(graphXYResult == graphXY);
	delete graphXY;
	delete deletePointCommand;
}

TEST_F(DeletePointCommandTest,deletesOnePositionAtTheEndIftrueIsSuppliedInConstruction) {
	GraphXY *graphXY = new GraphXY();

	PointXY *point1 = new PointXY(1,1);
	PointXY *point2 = new PointXY(2,2);

	
	graphXY->addPoint(point1);
	graphXY->addPoint(point2);
	
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY,false);

	GraphXY *graphXYResult = deletePointCommand->execute();

	EXPECT_EQ( 1,graphXYResult->getSize());
	delete deletePointCommand;
	delete graphXY;
	delete point1;
	delete point2;

}

TEST_F(DeletePointCommandTest,deletestheLast_PositionAtTheEndIf_true_IsSuppliedInConstruction) {


	GraphXY *graphXY = new GraphXY();
	PointXY *point1 = new PointXY(1,1);
	PointXY *point2 = new PointXY(2,2);
	
	graphXY->addPoint(point1);
	graphXY->addPoint(point2);
	
	
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY,true);

	GraphXY *graphXYResult = deletePointCommand->execute();


	EXPECT_EQ( 1,graphXYResult->getPoint(0).getX());


	delete deletePointCommand;
	delete point1;
	delete point2;
	delete graphXY;

}

TEST_F(DeletePointCommandTest,deletestheLast_PositionAtTheEndIf_false_IsSuppliedInConstruction) {
	GraphXY *graphXY = new GraphXY();
	PointXY *point1 = new PointXY(1,1);
	PointXY *point2 = new PointXY(2,2);
	
	graphXY->addPoint(point1);
	graphXY->addPoint(point2);
	delete point1;
	delete point2;
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY,false);

	GraphXY *graphXYResult = deletePointCommand->execute();

	;

	EXPECT_EQ( 2,graphXYResult->getPoint(0).getX());

	delete graphXY;
	delete deletePointCommand;


}

TEST_F(DeletePointCommandTest,undo_Command_leave_should_leave_things_like_at_the_begining) {

	GraphXY *graphXY = new GraphXY();

	PointXY *point1 = new PointXY(1,1);
	PointXY *point2 = new PointXY(2,2);
	
	graphXY->addPoint(point1);
	graphXY->addPoint(point2);
	delete point1;
	delete point2;

	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY,false);

	deletePointCommand->execute();

	GraphXY *graphXYResult = deletePointCommand->undo(1);

	EXPECT_EQ( 2,graphXYResult->getSize());

	delete deletePointCommand;
	delete graphXY;

}

TEST_F(DeletePointCommandTest,two_executes_should_delete_2_points) {

	GraphXY *graphXY = new GraphXY();

	PointXY point1(1,1);
	PointXY point2(2,2);

	
	graphXY->addPoint(&point1);
	graphXY->addPoint(&point2);
	
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY,false);

	deletePointCommand->execute();

	GraphXY *graphXYResult = deletePointCommand->execute();

	EXPECT_EQ( 0,graphXYResult->getSize());

	delete deletePointCommand;
	delete graphXY;

}


TEST_F(DeletePointCommandTest,two_executes_and_one_unodo_should_leave_things_like_at_the_begining) {

	GraphXY *graphXY = new GraphXY();
	
	PointXY point1(1,1);
	PointXY point2(2,2);

	graphXY->addPoint(&point1);
	graphXY->addPoint(&point2);
	
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY,false);

	deletePointCommand->execute();

	deletePointCommand->execute();

	GraphXY *graphXYResult = deletePointCommand->undo(2);

	EXPECT_EQ( 2,graphXYResult->getSize());

	delete deletePointCommand;
	delete graphXY;


}





TEST_F(DeletePointCommandTest,throwsExceptionIfgraphIsEmpty) {

	GraphXY *graphXY = new GraphXY();
	
	DeletePointCommand *deletePointCommand = new DeletePointCommand(graphXY,false);

	ASSERT_THROW(deletePointCommand->execute(),std::runtime_error);
	
	delete graphXY;
	delete deletePointCommand;
}
