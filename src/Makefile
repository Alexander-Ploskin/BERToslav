# Variables
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pthread
CXX_FLAGS = -std=c++17


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
		cmake libjsoncpp-dev \
  		pkg-config

	apt-get install -y libgtest-dev cmake
	mkdir -p /tmp/gtest_build && cd /tmp/gtest_build && \
	cmake /usr/src/googletest/googletest -DCMAKE_CXX_FLAGS="$(CXX_FLAGS)" && make && cp lib/libgtest* /usr/lib/
	rm -rf /tmp/gtest_build
	mkdir -p /usr/local/lib/googletest
	ln -sf /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
	ln -sf /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a

build:
	$(CC) -c $(CFLAGS) $< -o preprocessing.o /app/$(SRC_DIR)/preprocessing.cpp
	$(CC) -c $(CFLAGS) $< -o postprocessing.o /app/$(SRC_DIR)/postprocessing.cpp

	$(CC) -c $(CFLAGS) /app/src/tests/test_preprocessing.cpp -o tests_preprocessing.o -lgtest -lgtest_main
	$(CC) -c $(CFLAGS) /app/src/tests/test_postprocessing.cpp -o tests_postprocessing.o -lgtest -lgtest_main
	$(CC) -c $(CFLAGS) /app/src/preprocessing_exec.cpp -o test_preprocessing_exec.o
	$(CC) -c $(CFLAGS) /app/src/postprocessing.cpp -o test_postprocessing_exec.o
test:
	@echo "Running tests..."
	$(CC) $(CFLAGS) /app/src/tests_preprocessing.o /app/src/preprocessing.o -o tests_preprocessing_exec -lgtest -lgtest_main
	$(CC) $(CFLAGS) /app/src/tests_postprocessing.o /app/src/postprocessing.o -o tests_postprocessing_exec -lgtest -lgtest_main
	$(CC) $(CFLAGS) /app/src/test_postprocessing_exec.o /app/src/preprocessing.o -o test_preprocessing_exec
	$(CC) $(CFLAGS) /app/src/test_postprocessing_exec.o /app/src/postprocessing.o -o test_postprocessing_exec
 
	./tests_preprocessing_exec
	./tests_postprocessing_exec

clean:
	rm -rf $(BIN_DIR)/* $(TEST_DIR)/*
