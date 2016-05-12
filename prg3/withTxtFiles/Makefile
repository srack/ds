CPPFLAGS=-I/opt/local/include -g

all: test_prog3 diameter1 diameter2 

test_prog3: test_prog3.o graph.o
	g++ $^ -o $@

test_prog3.o: test_prog3.cpp graph.hpp

diameter1: diameter1.o graph.o
	g++ $^ -o $@

diameter2: diameter2.o graph.o
	g++ $^ -o $@

diameter1.o: diameter1.cpp graph.hpp

diameter2.o: diameter2.cpp graph.hpp

graph.o: graph.cpp graph.hpp

clean:
	rm -f *.o test_prog3 diameter1 diameter2 *~
