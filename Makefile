NAME=algo
NAME_TEST=$(NAME)_tests

TOP=$(shell pwd)

SRC:=$(wildcard src/*.cpp)
SRC_TEST:=$(wildcard test/*.cpp) $(SRC)

GTEST=$(TOP)/../googletest/
GTEST_LIB_DIR=$(GTEST)/build/googlemock/gtest/
GTEST_INC=$(GTEST)/googletest/include
GTEST_LIB=-lgtest -lpthread

PNG_LIB=-lpng
PNG_DIR=$(TOP)/../cpp_training_rootfs/
PNG_LIB_DIR=$(PNG_DIR)/lib/

CXX:=g++
CFLAGS=-Wall -pedantic -g
CXXFLAGS=-std=c++11
LD_FLAGS=-Wl,--rpath=$(PNG_LIB_DIR)

FLAGS=$(CFLAGS) $(CXXFLAGS) $(LD_FLAGS)
FLAGS_TEST=$(FLAGS) -DDEBUG

INC_DIR=-I$(TOP)/include -I$(PNG_DIR)/include
INC_DIR_TEST=$(INC_DIR) -I$(GTEST_INC)

LIB_DIR=-L$(PNG_LIB_DIR)
LIB_DIR_TEST=$(LIB_DIR) -L$(GTEST_LIB_DIR)

LIB=$(PNG_LIB)
LIB_TEST=$(LIB) $(GTEST_LIB)

.PHONY: test

all: test
	$(CXX) $(SRC) main.cpp -o $(NAME).out $(FLAGS) $(INC_DIR) $(LIB_DIR) $(LIB)

test:
	$(CXX) $(SRC_TEST) -o $(NAME_TEST).out $(LIB_TEST) $(LIB_DIR_TEST) $(FLAGS_TEST) $(INC_DIR_TEST)

clean:
	rm -f $(NAME) $(NAME_TEST)
