SRC_MODEL=../src/model/
INCLUDE=$(SRC_MODEL)
CFLAGS = -Wall  $(DEBUG) -I$(INCLUDE)

TARGET=UtilVectorTest
SOURCES=$(SRC_MODEL)UtilVector.cc
SOURCES+=UtilVectorTest.cc

$(TARGET):
	g++ $(CFLAGS) -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread $(SOURCES) -o $(TARGET)

run:
	LD_LIBRARY_PATH=LD_LIBRARY_PATH:/usr/local/lib/ ./$(TARGET)

clean:
	rm -Rf $(TARGET)
	rm -Rf *.o
