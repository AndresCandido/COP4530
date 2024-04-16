CC = g++
CFLAGS = -std=c++11 -Wall -Wextra

all: proj4.x 

proj4.x: proj4_driver.o
	$(CC) $(CFLAGS) proj4_driver.o -o proj4.x

proj4_driver.o: proj4_driver.cpp BET.h
	g++ -c proj4_driver.cpp

clean:
	rm -f *.o proj4.x