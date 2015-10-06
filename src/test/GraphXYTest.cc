#include "gtest/gtest.h"
#include "GraphXY.hpp"
#include "GraphXYIterator.hpp"


TEST(GraphXYTest,add_should_increase_size) {
	GraphXY *graphXY = new GraphXY();
	PointXY *pointXY = new PointXY(5.4,6.7);
	int graphSizeOriginal = graphXY->getSize();
	graphXY->addPoint(pointXY);
	
	EXPECT_EQ(graphSizeOriginal + 1 , graphXY->getSize() );

	delete graphXY;
	delete pointXY;


}

TEST(GraphXYTest,erase_should_decrease_size) {
	GraphXY *graphXY = new GraphXY();
	PointXY *pointXY = new PointXY(5.4,6.7);
	graphXY->addPoint(pointXY);
	int graphSize = graphXY->getSize();
	GraphXYIterator *iterator = graphXY->createIterator(0);
	graphXY->erase(iterator);
	delete iterator;
	EXPECT_EQ(graphSize -1 , graphXY->getSize() );

	delete graphXY;
	delete pointXY;
}

TEST(GraphXYTest,iterator_should_return_first_point) {
	GraphXY *graphXY = new GraphXY();
	PointXY *pointXY1 = new PointXY(5.4,6.7);
	PointXY *pointXY2 = new PointXY(2,2);

	graphXY->addPoint(pointXY1);
	graphXY->addPoint(pointXY2);
	
	GraphXYIterator *iterator = graphXY->createIterator(0);
	
	PointXY *pointXYRead = iterator->current();
	
	EXPECT_EQ(pointXYRead->getX(),pointXY1->getX());
	
	delete iterator;
	delete graphXY;
	delete pointXY1;
	delete pointXY2;

}


TEST(GraphXYTest,addPoint_at_the_begining_should_works) {
	GraphXY *graphXY = new GraphXY();
	PointXY *pointXY1 = new PointXY(5.4,6.7);
	PointXY *pointXY2 = new PointXY(2,2);
	graphXY->addPoint(pointXY1);
	graphXY->addPoint(pointXY2,0);
	
	GraphXYIterator *iterator = graphXY->createIterator(0);
	
	PointXY *pointXYRead = iterator->current();
	EXPECT_EQ(2,pointXYRead->getX());

	delete iterator;
	delete graphXY;
	delete pointXY1;
	delete pointXY2;
}