# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread

# Directories
SRC_DIR = /app/src
TEST_DIR = /app/src/tests
BUILD_DIR = build

# Libraries
GTEST_DIR = /usr/local/include/gtest
JSONCPP_INCLUDE = $(shell pkg-config --cflags jsoncpp)
JSONCPP_LIB = $(shell pkg-config --libs jsoncpp)

# Source files
SRCS = $(SRC_DIR)/postprocessing.cpp $(SRC_DIR)/preprocessing.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Test files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SRCS))

# Targets
TARGET = my_program
TEST_TARGET = run_tests

.PHONY: all prereqs build test clean

all: build test

prereqs:
	@echo "Installing prerequisites..."
	apt update && apt install -y \
	    curl vim nano \
	    cmake libjsoncpp-dev \
	    build-essential python3 python3-pip pkg-config	
	apt-get install -y libgtest-dev cmake
	mkdir -p /tmp/gtest_build && cd /tmp/gtest_build && \
	cmake /usr/src/googletest/googletest && make && cp lib/libgtest* /usr/lib/
	rm -rf /tmp/gtest_build
	mkdir -p /usr/local/lib/googletest
	ln -sf /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
	ln -sf /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a

build:
	@echo "Compiling source coe and creating binary files..."
	$(CXX) $(CXXFLAGS) preprocessing.cpp -o preprocessing1
	$(CXX) $(CXXFLAGS) postprocessing.cpp -o postprocessing1


test: prereqs $(TEST_TARGET)
	./$(TEST_TARGET)


$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR) $(JSONCPP_INCLUDE) $^ -lgtest -lgtest_main -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR) $(JSONCPP_INCLUDE) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET) $(TEST_TARGET)
