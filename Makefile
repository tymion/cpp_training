SRC:=$(wildcard *.cpp)
SRC_TEST:=$(wildcard test/*.cpp)
SRC_TEST += pixel_3x8.cpp pixel_4x8.cpp mask.cpp filebuffer.cpp pngfile.cpp

TOP=$(shell pwd)

GTEST=$(TOP)/../googletest/
GTEST_LIB_DIR=$(GTEST)/build/googlemock/gtest/
GTEST_INC=$(GTEST)/googletest/include
GTEST_LIB=-lgtest -lpthread
PNG_LIB=-lpng
PNG_DIR=$(TOP)/../cpp_training_rootfs/
PNG_LIB_DIR=$(PNG_DIR)/lib/

NAME=algo
NAME_TEST=$(NAME)_tests
CXX:=g++
CFLAGS=-Wall -pedantic -g
CXXFLAGS=-std=c++11
INCLUDE_DIR=-I$(TOP)/include -I$(PNG_DIR)/include
LD_FLAGS=-Wl,--rpath=$(PNG_LIB_DIR)

.PHONY: test

all: test
	$(CXX) $(SRC) -o $(NAME) $(CFLAGS) $(CXXFLAGS) $(INCLUDE_DIR) -L$(PNG_LIB_DIR) $(PNG_LIB) $(LD_FLAGS)

test:
	$(CXX) $(SRC_TEST) -o $(NAME_TEST) $(GTEST_LIB) -L$(GTEST_LIB_DIR) $(CFLAGS) $(CXXFLAGS) $(INCLUDE_DIR) -I$(GTEST_INC) -DDEBUG

clean:
	rm -f $(NAME) $(NAME_TEST)
