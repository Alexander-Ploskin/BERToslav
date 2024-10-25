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
TEST_EXECUTABLE_PREPROCESSING = $(SRC_DIR)/$(TEST_DIR)/test_preprocessing
TEST_EXECUTABLE_POSTPROCESSING = $(SRC_DIR)/$(TEST_DIR)/test_postprocessing
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

build: $(EXECUTABLES)

$(BIN_DIR)/preprocessing: $(SRC_DIR)/preprocessing.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $(BIN_DIR)/preprocessing

$(BIN_DIR)/postprocessing: $(SRC_DIR)/postprocessing.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $(BIN_DIR)/postprocessing


test: $(TEST_EXECUTABLE_PREPROCESSING) $(TEST_EXECUTABLE_POSTPROCESSING)

# Rule to build the preprocessing test executable
$(TEST_EXECUTABLE_PREPROCESSING): $(SRC_DIR)/$(TEST_DIR)/test_preprocessing.cpp
	@mkdir -p $(SRC_DIR)/$(TEST_DIR) # Ensure the output directory exists
	$(CC) $(CFLAGS) $< -o $@

# Rule to build the postprocessing test executable
$(TEST_EXECUTABLE_POSTPROCESSING): $(SRC_DIR)/$(TEST_DIR)/test_postprocessing.cpp
	@mkdir -p $(SRC_DIR)/$(TEST_DIR) # Ensure the output directory exists
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)/* $(TEST_DIR)/*
