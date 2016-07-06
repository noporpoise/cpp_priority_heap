CXXFLAGS=-Wall -Wextra -std=c++11

ifdef DEBUG
	OPT=-O0 -g
else
	OPT=-O2
endif

all: test

test: test.cpp PriorityHeap.tpp PriorityHeap.h
	$(CXX) $(CXXFLAGS) $(OPT) -o $@ test.cpp

clean:
	rm -rf test

.PHONY: all clean
