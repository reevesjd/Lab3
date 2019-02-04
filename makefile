CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.o: y86dis.cpp
	$(CXX) $(CXXFLAGS) -c y86dis.cpp -o main.o

clean:
	rm -f *.o
