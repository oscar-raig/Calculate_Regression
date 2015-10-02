#include "gtest/gtest.h"
#include "PurgeGraphXY.hpp"
#include "GraphXY.hpp"

TEST(PurgeGraphXYTest,purge_a_graph_with_different_numbers_should_not_purge_anything) {
	
	double *x = NULL,*y = NULL;
	GraphXY graphXY;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));

	y[0]=1;
	y[1]=2;
	y[2]=3;
	y[3]=4;
	
	PurgeGraphXY purgeGraphXY(x,y,nSize);
  	purgeGraphXY.purgeSimilarConsecutiveElements( x, y, &nSize);	

	EXPECT_EQ(4,nSize);
}


TEST(PurgeGraphXYTest,moveArrayOnePositionLeft_should_decrement_size) {
	
 	double *x = NULL,*y = NULL;
	int nCounter = 1 ;
	int nSize = 4;
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	PurgeGraphXY purgeGraphXY(x,y,nSize);
  	purgeGraphXY.moveArrayOnePositionLeft( x, y, nCounter, &nSize);	
  	EXPECT_EQ(nSize, 3);
	
	free(x);
	free(y);
}

TEST(PurgeGraphXYTest,moveArrayOnePositionLeft_should_move_position) {
	 
 	double *x = NULL,*y = NULL;
	int nCounter = 1 ;
	int nSize = 4;
	
	x = (double*)malloc(nSize * sizeof(double));
	y = (double*)malloc(nSize * sizeof(double));
	
	x[0]=1;
	x[1]=2;
	
	PurgeGraphXY purgeGraphXY(x,y,nSize); 
  	purgeGraphXY.moveArrayOnePositionLeft( x, y, nCounter, &nSize);	
  	EXPECT_EQ(x[0], 2);
	
	free(x);
	free(y);
}


TEST(UtilVectorTest,similar_similar_should_return_true_when_similar) {
	PurgeGraphXY purgeGraphXY(NULL,NULL,0);   
	double x = 4;
	double y = x + (RANGE_SIMILAR*0.9);
	ASSERT_TRUE(purgeGraphXY.similar(x,y));		
}

TEST(UtilVectorTest,similar_similar_should_return_false_when_not_similar) {
	PurgeGraphXY purgeGraphXY(NULL,NULL,0);  
	double x = 4;
	double y = x + (RANGE_SIMILAR*1.1);
	ASSERT_FALSE(purgeGraphXY.similar(x,y));		
}

TEST(UtilVectorTest,purgeSimilarConsecutiveElements_purge_one_when_are_similar) {

 	double *x = NULL,*y = NULL;
	int size = 4;
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	
	y[0]=1;
	y[1]=1;
	y[2]=1 +(RANGE_SIMILAR*2.1) ;
	y[3]=1 +(RANGE_SIMILAR*3.1) ;
	PurgeGraphXY purgeGraphXY(x,y,size); 
  	purgeGraphXY.purgeSimilarConsecutiveElements( x, y,  &size);	
  	EXPECT_EQ(size, 3);
	
	free(x);
	free(y);
}

TEST(UtilVectorTest,purgeSimilarConsecutiveElements_purge_two_when_are_similar) {
	
 	double *x = NULL,*y = NULL;
	int size = 4;
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	
	y[0]=1;
	y[1]=1;
	y[2]=1 +(RANGE_SIMILAR*2.1) ;
	y[3]=y[2];
	PurgeGraphXY purgeGraphXY(x,y,size); 
  	purgeGraphXY.purgeSimilarConsecutiveElements( x, y,  &size);	
  	EXPECT_EQ(size, 2);
	
	free(x);
	free(y);
}



TEST(UtilVectorTest,purgeSimilarConsecutiveElements_not_purge_when_no_consecutive) {

 	double *x = NULL,*y = NULL;
	int size = 4;
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	
	y[0]=1;
	y[1]=1 + (RANGE_SIMILAR*2.1);
	y[2]=1 + (RANGE_SIMILAR*3.1);
	y[3]=1;
	
	PurgeGraphXY purgeGraphXY(x,y,size); 
  	purgeGraphXY.purgeSimilarConsecutiveElements( x, y,  &size);	
  	EXPECT_EQ(size, 4);
	
	free(x);
	free(y);
}

TEST(UtilVectorTest,purgeSimilarConsecutiveElements_not_purge_if_ar_not_similar) {
	 
 	double *x = NULL,*y = NULL;
	int size = 4;
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	
	y[0]=1;
	y[1]=1 +(RANGE_SIMILAR*1.1) ;
	y[2]=1 +(RANGE_SIMILAR*2.1) ;
	y[3]=1 +(RANGE_SIMILAR*3.1) ;
	
	PurgeGraphXY purgeGraphXY(x,y,size); 
  	purgeGraphXY.purgeSimilarConsecutiveElements( x, y,  &size);	
  	EXPECT_EQ(size, 4);
	
	free(x);
	free(y);
}

TEST(UtilVectorTest,purgeSimilarConsecutiveElements_if_vector_have_similar_values_should_remove_elements) {
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {1,2,2,2,2,5,6};
	int size = 7;

	PurgeGraphXY purgeGraphXY(x,y,size); 
	purgeGraphXY.purgeSimilarConsecutiveElements(x,y,&size);

	EXPECT_EQ(size,4);
	EXPECT_EQ(y[0],1);
	EXPECT_EQ(y[1],2);
	EXPECT_EQ(y[2],5);
	EXPECT_EQ(y[3],6);

}
TEST(UtilVectorTest,purgeSimilarConsecutiveElements_if_vector_have_NO_similar_values_should_NOT_remove_elements) {
	double x[7] = {0,1,2,3,4,5,6};
	double y[7] = {1,2,3,4,5,6,7};
	int size = 7;
	PurgeGraphXY purgeGraphXY(x,y,size); 
	purgeGraphXY.purgeSimilarConsecutiveElements(x,y,&size);

	EXPECT_EQ(size,7);
	
}







