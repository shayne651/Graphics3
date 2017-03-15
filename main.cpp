//
//  Framework for a raytracer
//  File: main.cpp
//
//  Created for the Computer Science course "Introduction Computer Graphics"
//  taught at the University of Groningen by Tobias Isenberg and used with permission
//  in "Computer Graphics and Scientific Visualization" taught at UOIT by
//  Christopher Collins.
//
//  Authors:
//    Maarten Everts
//    Jasper van de Gronde
//
#include <stdlib.h>
#include "raytracer.h"

int main(int argc, char *argv[])
{
    cout << "Computer Graphics and Scientific Visualization - Raytracer" << endl << endl;
    if (argc < 2 || argc > 5) {
        cerr << "Usage: " << argv[0] << " in-file [out-file.png] [width] [height]" << endl;
        return 1;
    }

    Raytracer raytracer;

    if (!raytracer.readScene(argv[1])) {
        cerr << "Error: reading scene from " << argv[1] << " failed - no output generated."<< endl;
        return 1;
    }
    std::string ofname;
    if (argc>=3) {
        ofname = argv[2];
    } else {
        ofname = argv[1];
        if (ofname.size()>=5 && ofname.substr(ofname.size()-5)==".yaml") {
            ofname = ofname.substr(0,ofname.size()-5);
        }
        ofname += ".png";
    }

    // read width and height arguments
    int w = 400;
    int h = 400;
    if (argc>=5) {
        w = atoi(argv[3]);
        h = atoi(argv[4]);
    }

    raytracer.renderToFile(ofname, w, h);

    return 0;
}
