SRC:=$(wildcard *.cpp)

TOP=$(shell pwd)

CXX:=g++
CFLAGS=-Wall -pedantic -g
CXXFLAGS=-std=c++11
INCLUDE_DIR=-I$(TOP)/include

.PHONY: test

all:
	$(CXX) $(SRC) $(CFLAGS) $(CXXFLAGS) $(INCLUDE_DIR)

test:
	$(CXX) test/main.cpp pixel.cpp pixel_24.cpp $(CFLAGS) $(CXXFLAGS) $(INCLUDE_DIR)

clean:
	rm a.out
