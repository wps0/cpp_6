CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2 -g
OBJFILES = college_example.o
BINARIES = college_example

all: $(BINARIES)

college_example.o: college_example.cc

college_example: $(OBJFILES)
	g++ $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(BINARIES) *.o

.PHONY: clean all

