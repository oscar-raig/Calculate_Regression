#include "gtest/gtest.h"
#include "GraphXY.hpp"
#include "GraphXYIterator.hpp"


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
	GraphXYIterator *iterator = graphXY->createIterator(0);
	graphXY->erase(iterator);
	EXPECT_EQ(graphSize -1 , graphXY->getSize() );


}