# file Makefile
# author Mangos
# date 2024-12-04
# brief Makefile


CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

all: deque_test

deque_test: main.o
	$(CXX) $(CXXFLAGS) -o deque_test main.o

main.o: main.cpp deque.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o deque_test
