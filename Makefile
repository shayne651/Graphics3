all:
	g++ -Wfatal-errors  -Wall -lGL -lglut -lGLU -lGLEW -lm -lfreeimage *.cpp yaml/*.cpp -o raytracer

clean:
	rm raytracer
