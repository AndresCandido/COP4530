CC = g++
CFLAGS = -std=c++11

all: proj6.x 

proj6.x: proj6.cpp hashtable.h hashtable.hpp passserver.h passserver.hpp base64.h
	$(CC) $(CFLAGS) proj6.cpp base64-1.cpp -o proj6.x

clean:
	rm -f proj6.x