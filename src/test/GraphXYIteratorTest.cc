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

	PointXY* point = graphXYIterator.next();
 	
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

	EXPECT_EQ(2, 3);
}

TEST (GraphXYIteratorTest,current_should_not_increment_position) {

	EXPECT_EQ(2, 3);
}

TEST (GraphXYIteratorTest,isEnd_should_true_if_we_are_at_the_end) {

	EXPECT_EQ(2, 3);
}

TEST (GraphXYIteratorTest,isEnd_should_false_if_we_are_at_the_begin) {

	EXPECT_EQ(2, 3);
}

TEST (GraphXYIteratorTest,isBegin_should_true_if_we_are_at_the_begin) {

	EXPECT_EQ(2, 3);
}
TEST (GraphXYIteratorTest,isBegin_should_false_if_we_are_at_the_end) {

	EXPECT_EQ(2, 3);
}



