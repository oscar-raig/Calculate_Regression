OBJS = regression.o FileResult.o 
CC = c++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@
	

test:	regression
	./regression out.csv 

regression : $(OBJS)
	$(CC) $(LFLAGS) $(DEBUG)  $(OBJS) -o regression

clean:
	rm -f $(OBJS)
