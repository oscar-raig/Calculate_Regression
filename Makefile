.DEFAULT_GOAL := run_example
SRC_MODEL=src/model
INCLUDE=$(SRC_MODEL)
SOURCES=$(SRC_MODEL)/UtilVector.cc
OBJS = regression.o FileResult.o $(SRC_MODEL)/UtilVector.o
CC = c++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -I$(INCLUDE)
LFLAGS = -Wall $(DEBUG)



TARGET=regression

%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@
	

run_example:	regression
	LD_LIBRARY_PATH=LD_LIBRARY_PATH:/usr/local/lib/ ./regression example.csv 

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(DEBUG)  $(OBJS) -llog4cplus -o $(TARGET)

clean:
	rm -f $(OBJS)
	rm $(TARGET)
