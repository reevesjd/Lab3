CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main: y86dis.o
	$(CXX) $(CXXFLAGS) -o y86dis y86dis.o

main.o: y86dis.cpp
	$(CXX) $(CXXFLAGS) -c y86dis.cpp -o y86dis.o

clean:
	rm -f *.o
