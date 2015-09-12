OBJS = regression.o FileResult.o 
CC = c++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@
	

run_example:	regression
	LD_LIBRARY_PATH=LD_LIBRARY_PATH:/usr/local/lib/ ./regression example.csv 

regression : $(OBJS)
	$(CC) $(LFLAGS) $(DEBUG)  $(OBJS) -llog4cplus -o regression

clean:
	rm -f $(OBJS)
