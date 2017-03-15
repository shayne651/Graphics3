Raytracer C++ framework for "Introduction to Computer Graphics"
===============================================================

This is a C++ framework for a raytracer. It was created for the Computer
Science course "Introduction to Computer Graphics" taught at the 
University of Groningen by Dr. Tobias Isenberg and is used with permission 
for "Graphics and Scientific Visualization" at UOIT taught by Dr. Christopher
Collins.

Author: Maarten Everts

Description of the included files
---------------------------------

### The raytracer source files:

main.cpp
:	Contains main(), starting point. Responsible for parsing command-line
	arguments.
	
raytracer.cpp/.h
:	Raytracer class. Responsible for reading the scene description, starting
	the raytracer and writing the result to an image file.
	
scene.cpp/.h
:	Scene class. Contains code for the actual raytracing.
	
image.cpp/.h
:	Image class, includes code for reading from and writing to PNG files.
	
light.cpp/.h
:	Light class and Ray class.

object.cpp/.h
:	Object class. Represents an object in the scene.

sphere.cpp/.h
:	Sphere class, which is a subclass of the Object class. Respresents a
	sphere in the scene.
	
triple.cpp/.h
:	Triple class. Represents a 3-dimensional vector which is used for colors,
	points,	and vectors. Includes a number of useful functions and operators,
	see the comments in triple.h.

### Supporting source files:

lodepng.cpp/.h
:	Code for reading from and writing to PNG files, used by the Image class.
	LodePNG is created by Lode Vandevenne and can be found at
	<http://members.gamedev.net/lode/projects/LodePNG/>.

yaml/*
:	Code for parsing YAML documents. Created by Jesse Beder, can be obtained 
	from <http://code.google.com/p/yaml-cpp/>. See also yaml/license.txt.
	
### Data files:

Scene01-05.yaml are encoded with UNIX style EOL characters.  This should work with 
the provided YAML parsing code using DevCPP.  If you want to edit these files in 
Windows, you should use an editor which is compatible with this EOL style, such as
Notepad++ (freeware).	
	