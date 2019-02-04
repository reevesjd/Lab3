CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main:
	$(CXX) y86dis.cpp -o main

clean:
	rm -f *.o
	rm -f main
