
TARGET=UtilVectorTest
SOURCES=UtilVectorTest.cc

$(TARGET):
	g++ -I $GTEST_HOME/include -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread $(SOURCES) -o $(TARGET)

run:
	LD_LIBRARY_PATH=LD_LIBRARY_PATH:/usr/local/lib/ ./$(TARGET)

clean:
	rm -Rf $(TARGET)
	rm -Rf *.o
