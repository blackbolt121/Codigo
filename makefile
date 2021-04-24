all: 
	g++ -std=c++11 -o main main.cpp
	./main
	
compile:
	g++ -std=c+17 -o main main.cpp
run:
	./main