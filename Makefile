NAME=algo
NAME_TEST=$(NAME)_tests
LIB_NAME=libsrs.so

TOP=$(shell pwd)

SRC:=$(wildcard src/*.cpp)
SRC_TEST:=$(wildcard test/*.cpp)

GTEST=$(TOP)/../googletest/
GTEST_LIB_DIR=$(GTEST)/build/googlemock/gtest/
GTEST_INC=$(GTEST)/googletest/include
GTEST_LIB=-lgtest -lpthread

PNG_LIB=-lpng16

ROOTFS_DIR=$(TOP)/../cpp_training_rootfs/
ROOTFS_LIB_DIR=$(ROOTFS_DIR)/lib/

CXX:=g++
CFLAGS=-Wall -pedantic -g
CXXFLAGS=-std=c++17
LD_FLAGS=-Wl,--rpath=$(ROOTFS_LIB_DIR)

EXTRA_FLAGS=-DINDEX_JACARDA
FLAGS=$(CFLAGS) $(CXXFLAGS) $(LD_FLAGS) $(EXTRA_FLAGS)
FLAGS_TEST=$(FLAGS) -DDEBUG

PNG_INC_DIR=-I$(ROOTFS_DIR)/include
INC_DIR=-I$(TOP)/include
INC_DIR_TEST=$(INC_DIR) -I$(GTEST_INC) $(PNG_INC_DIR)

LIB_DIR=-L$(ROOTFS_LIB_DIR)
LIB_DIR_TEST=$(LIB_DIR) -L$(GTEST_LIB_DIR)

LIB=-lsrs -lpng16
LIB_TEST=$(LIB) $(GTEST_LIB)

.PHONY: test tools

all: libsrs.so test tools
	$(CXX) main.cpp -o $(NAME).out $(FLAGS) $(INC_DIR) $(LIB_DIR) $(LIB)

test: libsrs.so
	$(CXX) $(SRC_TEST) -o $(NAME_TEST).out $(LIB_TEST) $(LIB_DIR_TEST) $(FLAGS_TEST) $(INC_DIR_TEST)

libsrs.so:
	$(CXX) $(SRC) -shared -fPIC -o $(LIB_NAME) $(FLAGS) $(INC_DIR) $(PNG_INC_DIR) $(LIB_DIR) $(PNG_LIB)
	cp $(LIB_NAME) $(ROOTFS_LIB_DIR)

tools: libsrs.so
	$(CXX) tools/cnt_max.cpp -o cnt_max.out $(FLAGS_TEST) $(INC_DIR) $(LIB_DIR) $(LIB)
	$(CXX) tools/start_point.cpp -o start_point.out $(FLAGS_TEST) $(INC_DIR) $(LIB_DIR) $(LIB)
	$(CXX) tools/generate_data.cpp -o generate_data.out $(FLAGS_TEST) $(INC_DIR) $(LIB_DIR) $(LIB)

clean:
	rm -f $(NAME).out $(NAME_TEST).out
	rm -f cnt_max.out
	rm -f start_point.out
	rm -f generate_data.out
	rm -f libsrs.so
