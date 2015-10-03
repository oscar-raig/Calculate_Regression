#include "gtest/gtest.h"
#include "PointXY.hpp"
#include "GraphXYIterator.hpp"



TEST (GraphXYIteratorTest,create_GraphXYIterator_and_get_current_item_should_return_first_elem) {
	
	int graphSize = 1;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);

	GraphXYIterator graphXYIterator(x, y, graphSize);

	PointXY* point = graphXYIterator.current();
 	
  	EXPECT_EQ(1, point->getX());
	
	
}


TEST (GraphXYIteratorTest,create_GraphXYIterator_and_get_current_item_more_times_than_size_should_return_NULL) {
	
	int graphSize = 1;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);

	GraphXYIterator graphXYIterator(x, y, graphSize);
	graphXYIterator.next();
	PointXY* point = graphXYIterator.next();
 	
  	EXPECT_EQ(NULL, point);
	
	
}


TEST (GraphXYIteratorTest,create_GraphXYIterator_and_get_previous_just_after_create_iterator_should_return_NULL) {
	
	int graphSize = 1;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);

	GraphXYIterator graphXYIterator(x, y, graphSize);
	
	PointXY* point = graphXYIterator.previous();
 	
  	EXPECT_EQ(NULL, point);
	
	
}


TEST (GraphXYIteratorTest,create_GraphXYIterator_and_get_next_previous_return_first_elem) {
	
	int graphSize = 1;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);

	GraphXYIterator graphXYIterator(x, y, graphSize);
	graphXYIterator.next();
	PointXY* point = graphXYIterator.previous();
 	
  	EXPECT_EQ(1, point->getX());
	
}

TEST (GraphXYIteratorTest,create_GraphXYIterator_and_get_2next_1previous_return_second_elem) {
	
	int graphSize = 3;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);
	x.push_back(2);
	y.push_back(2);
	x.push_back(3);
	y.push_back(3);

	GraphXYIterator graphXYIterator(x, y, graphSize);
	graphXYIterator.next();
	graphXYIterator.next();
	PointXY* point = graphXYIterator.previous();
 	
  	EXPECT_EQ(2, point->getX());
	
	
}

TEST (GraphXYIteratorTest,first_should_positionate_first_elem) {

	int graphSize = 3;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);
	x.push_back(2);
	y.push_back(2);
	x.push_back(3);
	y.push_back(3);

	GraphXYIterator graphXYIterator(x, y, graphSize);
	graphXYIterator.next();
	graphXYIterator.next();
	graphXYIterator.first();
	PointXY *pointXY = graphXYIterator.current();
 	
  	EXPECT_EQ(1, pointXY->getX());
}

TEST (GraphXYIteratorTest,current_should_not_increment_position) {

	int graphSize = 3;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);
	x.push_back(2);
	y.push_back(2);
	x.push_back(3);
	y.push_back(3);

	GraphXYIterator graphXYIterator(x, y, graphSize);
	graphXYIterator.next();
	PointXY *pointXY = graphXYIterator.current();
	graphXYIterator.current();
 	
  	EXPECT_EQ(2, pointXY->getX());
}

TEST (GraphXYIteratorTest,isEnd_should_true_if_we_are_at_the_end) {

	int graphSize = 3;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);
	x.push_back(2);
	y.push_back(2);
	x.push_back(3);
	y.push_back(3);

	GraphXYIterator graphXYIterator(x, y, graphSize);
	graphXYIterator.next();
	graphXYIterator.next();
	graphXYIterator.next();
	
 	
  	EXPECT_EQ(true, graphXYIterator.isEnd());
}

TEST (GraphXYIteratorTest,isEnd_should_false_if_we_are_at_the_begin) {

	int graphSize = 3;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);
	x.push_back(2);
	y.push_back(2);
	x.push_back(3);
	y.push_back(3);

	GraphXYIterator graphXYIterator(x, y, graphSize);
 	
  	EXPECT_EQ(false, graphXYIterator.isEnd());
}

TEST (GraphXYIteratorTest,isBegin_should_true_if_we_are_at_the_begin) {

		int graphSize = 3;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);
	x.push_back(2);
	y.push_back(2);
	x.push_back(3);
	y.push_back(3);

	GraphXYIterator graphXYIterator(x, y, graphSize);
 	
  	EXPECT_EQ(true, graphXYIterator.isBegin());
}
TEST (GraphXYIteratorTest,isBegin_should_false_if_we_are_at_the_end) {

		int graphSize = 3;
	std::vector<double> x;
	std::vector<double> y;

	x.push_back(1);
	y.push_back(1);
	x.push_back(2);
	y.push_back(2);
	x.push_back(3);
	y.push_back(3);

	GraphXYIterator graphXYIterator(x, y, graphSize);
	graphXYIterator.next();
	graphXYIterator.next();
	graphXYIterator.next();
	
 	
  	EXPECT_EQ(false, graphXYIterator.isBegin());
}



