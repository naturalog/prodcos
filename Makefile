all: de.cpp
	g++ de.cpp -lmpfr -ode -O0 -W -Wall -Wpedantic -std=c++0x
gen: gen.cpp
	g++ gen.cpp -lmpfr -ogen -O0 -W -Wall -Wpedantic -std=c++0x -lgmp
