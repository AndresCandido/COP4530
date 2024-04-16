CC = g++
CFLAGS = -std=c++11 -Wall -Wextra

all: stack_test.x 

stack_test.x: in2post.cpp stack.h stack.hpp
	$(CC) $(CFLAGS) in2post.cpp -o stack_test.x

clean:
	rm -f stack_test.x