01: src/01-vertex-coloring.cpp
	g++ ./src/01-vertex-coloring.cpp -o ./bin/run01
	./bin/run01

02: src/02-bacon-degrees.cpp
	g++ ./src/02-bacon-degrees.cpp -o ./bin/run02
	./bin/run02

03: src/03-two-way.cpp
	g++ ./src/03-two-way.cpp -o ./bin/run03
	./bin/run03

clean:
	rm -rf bin/*