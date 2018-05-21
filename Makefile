SRC:=$(wildcard *.cpp)

CXX:=g++
CFLAGS=-Wall -pedantic
CXXFLAGS=-std=c++11

all:
	$(CXX) $(SRC) $(CFLAGS) $(CXXFLAGS) -I./
