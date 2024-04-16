CC = g++
CFLAGS = -std=c++11

all: driver.x mydriver.x

driver.x: driver.cpp tnode.h tlist.h tlist.hpp
	$(CC) $(CFLAGS) driver.cpp -o driver.x

mydriver.x: mydriver.cpp tnode.h tlist.h tlist.hpp
	$(CC) $(CFLAGS) mydriver.cpp -o mydriver.x

clean:
	rm -f driver.x mydriver.x
