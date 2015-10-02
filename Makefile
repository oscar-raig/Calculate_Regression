.DEFAULT_GOAL := run_example
SRC_MODEL=src/model
SRC_APP=src/app
SRC_IO=src/io
INCLUDE=-I $(SRC_MODEL) -I$(SRC_IO)
SOURCES=$(SRC_MODEL)/UtilVector.cc
SOURCES += $(SRC_MODEL)/PurgeGraphXY.cc
OBJS = $(SRC_APP)/regression.o $(SRC_IO)/FileResult.o $(SRC_MODEL)/UtilVector.o 
OBJS += $(SRC_MODEL)/PurgeGraphXY.o
CC = c++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) $(INCLUDE)
LFLAGS = -Wall $(DEBUG) -llog4cplus



TARGET=regression

%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@
	

run_example:	regression
	LD_LIBRARY_PATH=LD_LIBRARY_PATH:/usr/local/lib/ ./regression example.csv 

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(DEBUG)  $(OBJS)  -o $(TARGET)

test:
	make -C src/test
test_iterator:
	make -C src/test test_iterator

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
	make -C src/test clean
