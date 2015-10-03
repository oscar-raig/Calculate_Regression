#include "gtest/gtest.h"
#include "GraphXY.hpp"


TEST(GraphXYTest,add_should_increase_size) {
	GraphXY *graphXY = new GraphXY();
	PointXY *pointXY = new PointXY(5.4,6.7);
	int graphSizeOriginal = graphXY->getSize();
	graphXY->addPoint(pointXY);
	
	EXPECT_EQ(graphSizeOriginal + 1 , graphXY->getSize() );


}

TEST(GraphXYTest,erase_should_decrease_size) {
	GraphXY *graphXY = new GraphXY();
	PointXY *pointXY = new PointXY(5.4,6.7);
	graphXY->addPoint(pointXY);
	int graphSize = graphXY->getSize();
	graphXY->erase(0);
	EXPECT_EQ(graphSize -1 , graphXY->getSize() );


}