# Variables
CC = g++
CFLAGS = -std=c++14 -Wall -Wextra -pthread
CXX_FLAGS = -std=c++14


# Libraries
GTEST_DIR = /usr/local/include/gtest
JSONCPP_INCLUDE = $(shell pkg-config --cflags jsoncpp)
JSONCPP_LIB = $(shell pkg-config --libs jsoncpp)

SRC_DIR = src
BIN_DIR = bin
TEST_DIR = tests
EXECUTABLES = $(BIN_DIR)/preprocessing $(BIN_DIR)/postprocessing
TEST_EXECUTABLE = $(SRC_DIR)/$(TEST_DIR)/test_preprocessing.cpp $(SRC_DIR)/$(TEST_DIR)/test_postprocessing.cpp 
REQUIREMENTS_FILE = model/requrements.txt

.PHONY: all prereqs build test clean

all: prereqs build test


prereqs:
	@echo "Installing dependencies..."
	@echo "Installing prerequisites..."
	apt update && apt install -y \
		curl vim nano \
		cmake libjsoncpp-dev \
  		build-essential python3 python3-pip pkg-config

	apt-get install -y libgtest-dev cmake
	mkdir -p /tmp/gtest_build && cd /tmp/gtest_build && \
	cmake /usr/src/googletest/googletest -DCMAKE_CXX_FLAGS="$(CXX_FLAGS)" && make && cp lib/libgtest* /usr/lib/
	rm -rf /tmp/gtest_build
	mkdir -p /usr/local/lib/googletest
	ln -sf /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
	ln -sf /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a

build:
	$(CC) $(CFLAGS) $< -o preprocessing /app/$(SRC_DIR)/preprocessing.cpp
	$(CC) $(CFLAGS) $< -o postprocessing /app/$(SRC_DIR)/postprocessing.cpp

test:
	@echo "Running tests..."
	$(CC) $(CFLAGS) $< -o tests_executable /app/$(SRC_DIR)/$(TEST_DIR)/test_preprocessing.cpp
	./tests_executable

clean:
	rm -rf $(BIN_DIR)/* $(TEST_DIR)/*
