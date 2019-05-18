OBJS = main.o rect_poly.o
CC = g++
DEBUG = -g -O3
CFLAGS = -std=c++11 -Wall -fPIC -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

runProg : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o runProg

main.o : main.cpp rect_poly.cpp rect_poly.h
	$(CC) $(CFLAGS) main.cpp

rect_poly.o : rect_poly.cpp rect_poly.h
	$(CC) $(CFLAGS) rect_poly.cpp

clean:	
	\rm *.o runProg
