CXX = g++
CXXFLAGS = -std=c++20
OUTPUT_FILE = server
SRC_DIR = src
ROOT_DIR = webroot

SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.h)

EXCLUDE_WINDOWS := $(SRC_DIR)/linux_socket.cpp $(SRC_DIR)/linux_socket.h
EXCLUDE_LINUX := $(SRC_DIR)/win_socket.cpp $(SRC_DIR)/win_socket.h

.PHONY: run

# exclude files
ifeq ($(OS),Windows_NT)
	SRCS := $(filter-out $(EXCLUDE_WINDOWS),$(SRCS))
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
		SRCS := $(filter-out $(EXCLUDE_LINUX),$(SRCS))
    endif
endif

# default target
all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(ROOT_DIR)/$@ $(SRCS)

# change directory in subshell
run:
	(cd webroot && sudo ./server 192.168.56.1)