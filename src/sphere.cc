//
//  Sphere.cc
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "sphere.h"

/* * * * * * * * * * * *
 Constructors
 * * * * * * * * * * * */

// default constructor

Sphere::Sphere()
{}


// constructor from args

Sphere::Sphere(float a, float b, float c, float r)
{
    orig = Point(a,b,c);
    rad = r;
}


// copy constructor

Sphere::Sphere(const Sphere& p)
:orig(p.orig), rad(p.rad)
{}


// destructor

Sphere::~Sphere()
{}


Intersection Sphere::getIntersection(const Ray &myRay){
    myVector e_c = myVector(myRay.origin, orig);
    myVector d = myRay.direction;
    float d_dot_d = dot(d, d);
    float d_dot_ec = dot(d,e_c);
    float e_c_dot = dot(e_c,e_c);
    float r2 = rad*rad;
    float innersqrt = (d_dot_ec*d_dot_ec)-(d_dot_d*(e_c_dot-r2));
    
    if (innersqrt < 0){ // discriminant negative, no intersection
        return Intersection();
    }
    
    else {
        
        // check if it's one or two intersection pts
        
        float tA, tB;
        myVector negd = -1*d;
        float negd_ec = dot(negd, e_c);
        myVector norm;
        tA = (negd_ec + sqrt(innersqrt))/(d_dot_d);
        
        if (innersqrt == 0){
            if (tA > 0){
                norm = getSurfaceNorm(myRay, tA);
                return Intersection(true, tA, norm);
            }
            else { return Intersection(); }
        }
        
        else {
            tB = (negd_ec - sqrt(innersqrt))/(d_dot_d);
            
            
            if ((tA < tB) && (tA > 0)){
                norm = getSurfaceNorm(myRay, tA);
                return Intersection(true, tA, norm);
            }
            else {
                if (tB > 0){
                    norm = getSurfaceNorm(myRay, tB);
                    return Intersection(true, tB, norm);
                }
                else {
                    return Intersection();
                }
            }
        }
    }
}

myVector Sphere::getSurfaceNorm(const Ray &myRay, const float t){
    myVector norm;
    float intersection_x = (myRay.origin).x + ((myRay.direction).x)*t;
    float intersection_y = (myRay.origin).y + ((myRay.direction).y)*t;
    float intersection_z = (myRay.origin).z + ((myRay.direction).z)*t;
    
    Point intersP = Point(intersection_x, intersection_y, intersection_z);
    myVector temp = myVector(intersP, orig);
    norm = temp/rad;
    norm.normalize();
    return norm;
}
