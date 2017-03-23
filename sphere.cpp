//
//  Framework for a raytracer
//  File: sphere.cpp
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

#include "sphere.h"
#include <iostream>
#include <math.h>

/************************** Sphere **********************************/

Hit Sphere::intersect(const Ray &ray)
{
    /****************************************************
    * RT1.1: INTERSECTION CALCULATION
    *
    * Given: ray, position, r
    * Sought: intersects? if true: *t
    * 
    * Insert calculation of ray/sphere intersection here. 
    *
    * You have the sphere's center (C) and radius (r) as well as
    * the ray's origin (ray.O) and direction (ray.D).
    *
    * If the ray does not intersect the sphere, return false.
    * Otherwise, return true and place the distance of the
    * intersection point from the ray origin in *t (see example).
    ****************************************************/

    double t;
    double a =(ray.D.dot(ray.D));
    double b =2*(ray.D.dot(ray.O-position));
    double c =(ray.O-position).dot(ray.O-position)-pow(r,2);
    double delta = pow(b,2)-4*(a*c);

    if (delta <0) {
        return Hit::NO_HIT();
    }else if (delta == 0){
        t= -(b/2*a);
        Vector N = ((ray.O + ray.D * t) - position)/r;
        return Hit(t,N);
    }else{
        delta = sqrt(delta);
        double r1=(-b+delta)/2*a;
        double r2= (-b-delta)/2*a;
        if (r1<0 && r2 <0){
            return Hit::NO_HIT();
        }
        if (r1>r2){
            t=r2;
            Vector N = ((ray.O + ray.D * t) - position)/r;
            return Hit(t,N);
        }else{
            t=r1;
            Vector N = ((ray.O + ray.D * t) - position)/r;
            return Hit(t,N);
        }
    }
    return Hit::NO_HIT();
}
