build:
	mkdir build
	g++ ./src/*.cpp -o ./bin/terrain -lraylib -lglfw -lGL -lopenal -lm -pthread -ldl -I./include
run:
	./bin/terrain
remove:
	rm ./bin/*
