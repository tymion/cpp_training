SRC:=$(wildcard *.cpp)
SRC_TEST:=$(wildcard test/*.cpp)
SRC_TEST += pixel_3x8.cpp pixel_4x8.cpp mask.cpp

TOP=$(shell pwd)

GTEST=$(TOP)/../googletest/
GTEST_LIB_DIR=$(GTEST)/build/googlemock/gtest/
GTEST_INC=$(GTEST)/googletest/include
GTEST_LIB=-lgtest -lpthread

CXX:=g++
CFLAGS=-Wall -pedantic -g
CXXFLAGS=-std=c++11
INCLUDE_DIR=-I$(TOP)/include

.PHONY: test

all:
	$(CXX) $(SRC) $(CFLAGS) $(CXXFLAGS) $(INCLUDE_DIR)

test:
	$(CXX) $(SRC_TEST) -o tests $(GTEST_LIB) -L$(GTEST_LIB_DIR) $(CFLAGS) $(CXXFLAGS) $(INCLUDE_DIR) -I$(GTEST_INC)

clean:
	rm -f a.out tests
