//
//  Framework for a raytracer
//  File: scene.cpp
//
//  Created for the Computer Science course "Introduction Computer Graphics"
//  taught at the University of Groningen by Tobias Isenberg.
//
//  Authors:
//    Maarten Everts
//    Jasper van de Gronde
//
//  This framework is inspired by and uses code of the raytracer framework of 
//  Bert Freudenberg that can be found at
//  http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html 
//

#include "scene.h"
#include "material.h"

Color Scene::trace(const Ray &ray , int depth)
{
    // Find hit object and distance
    Hit min_hit(std::numeric_limits<double>::infinity(),Vector());
    Object *obj = NULL;
    for (unsigned int i = 0; i < objects.size(); ++i) {
        Hit hit(objects[i]->intersect(ray));
        if (hit.t<min_hit.t) {
            min_hit = hit;
            obj = objects[i];
        }
    }

    // No hit? Return background color.
    if (!obj) return Color(0.0, 0.0, 0.0);

    Material *material = obj->material;            //the hit objects material
    Point hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = -ray.D;                             //the view vector


    /****************************************************
    * This is where you should insert the color
    * calculation (Phong model).
    *
    * Given: material, hit, N, V, lights[]
    * Sought: color
    *
    * Hints: (see triple.h)
    *        Triple.dot(Vector) dot product
    *        Vector+Vector      vector sum
    *        Vector-Vector      vector difference
    *        Point-Point        yields vector
    *        Vector.normalize() normalizes vector, returns length
    *        double*Color        scales each color component (r,g,b)
    *        Color*Color        dito
    *        pow(a,b)           a to the power of b
    ****************************************************/
    N.normalize();
    //ambient calc
    Color ambient = material->color * material->ka;
    Color total = ambient;

    for(unsigned int i =0; i < lights.size();i++){
        //finding the shadows
        Ray shadows(hit,(lights[i]->position-hit).normalized());
        Point jiggle = shadows.at(0.001);
        //jiggling the poitns to get rid of the black dots
        shadows = Ray(jiggle,(lights[i]->position-hit).normalized());
    	bool isShadow=false;
        for (unsigned int x = 0; x < objects.size(); x++) {
            Hit lhit(objects[x]->intersect(shadows));
            if (lhit.t<min_hit.t) {
                isShadow = true;
                //if true break the loop and set isShadow to true 
                break;
            }
        }
        if(isShadow) continue;
            //skips the phong calc if it is in a shadow
            //total = total;
            
        
                Vector hpoint = (lights[i]->position-hit).normalized();
                Vector newV =(V + hpoint).normalized();
                //diffuse calc
                double holder = max(0.0,N.dot(hpoint));
                Color diffuse = material->kd * lights[i]->color * holder * material->color;
                //specular calc
                Color spec1 =lights[i]->color * material->ks;
                holder = newV.dot(N);
                Color spec =spec1*pow(holder,4* material->n);
                //adds spec + diffuse to the final color to be returned
                total += diffuse + spec;
        
    }

    //checks to see if the surface can reflect and if the max ray jumps has been met
    if(material->reflect!=0 && depth < 100){
        //ray dir calc (needed to be jiggled too)
        Vector dir = ray.D - 2 * (ray.D.dot(N))*N;
        Ray reflect(hit + N*0.001, dir);
        //recursivly follows the ray
        total += trace(reflect, depth++)* material->reflect;
    }
    //returns all of phong added together
    return total;
}

void Scene::render(Image &img)
{ 
   int w = img.width();
    int h = img.height();
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Point pixel(x, h-1-y, 0);
            Ray ray(eye, (pixel-eye).normalized());
            Color col = trace(ray,0);
            col.clamp();
            img(x,y) = col;
        }
    }
}

void Scene::addObject(Object *o)
{
    objects.push_back(o);
}

void Scene::addLight(Light *l)
{
    lights.push_back(l);
}

void Scene::setEye(Triple e)
{
    eye = e;
}
