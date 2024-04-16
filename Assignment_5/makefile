CC = g++
CFLAGS = -std=c++11

all: proj4.x 

proj4.x: proj4_driver.cpp bet.h bet.hpp 
	$(CC) $(CFLAGS) proj4_driver.cpp -o proj4.x

clean:
	rm -f *.o proj4.x