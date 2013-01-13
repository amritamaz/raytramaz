//
//  Sphere.h
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1__Sphere__
#define __hw1__Sphere__

#include <iostream>

class myVector;
class Point;
class Intersection;
class Ray;
class Surface;
class Bbox;

#include "intersection.h"
#include "myVector.h"
#include "plane.h"
#include "point.h"
#include "ray.h"
#include "sphere.h"
#include "surface.h"
#include "material.h"
#include "math.h"
#include "bbox.h"

class Sphere : public Surface{
    
public:
    Point orig;  // origin
    float rad;   // radius
    
    
    /* * * * * * * * * * * *
     Constructors
     * * * * * * * * * * * */
    
    Sphere();											// default constructor
    Sphere(float a, float b, float c, float r);      // constructor
    Sphere(const Sphere& p);                      // copy constructor
    ~Sphere();											// destructor
    
    Intersection getIntersection(const Ray& myRay, bool withBbox);
    myVector getSurfaceNorm(const Ray& myRay, const float t);
    void setBbox(const myVector& camdir);
    
};

#endif /* defined(__hw1__Sphere__) */
