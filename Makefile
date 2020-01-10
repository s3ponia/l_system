CXXFLAGS=$(shell pkg-config --cflags sfml-graphics) -std=c++17 -Wall -Wextra -g
LDFLAGS=$(shell pkg-config --libs sfml-graphics)

l_system: main.o L_system.o Turtle.o
	$(CXX) $(CXXFLAGS) main.o L_system.o Turtle.o -o l_system $(LDFLAGS)

clean:
	rm *.o
	rm l_system
