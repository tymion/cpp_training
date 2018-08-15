SRC:=$(wildcard *.cpp)

CXX:=g++
CFLAGS=-Wall -pedantic -g
CXXFLAGS=-std=c++11

.PHONY: test

all:
	$(CXX) $(SRC) $(CFLAGS) $(CXXFLAGS) -I./

test:
	$(CXX) test/main.cpp pixel.cpp pixel_24.cpp $(CFLAGS) $(CXXFLAGS) -I./

clean:
	rm a.out
