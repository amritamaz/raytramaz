//
//  triangle.h
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1__Triangle__
#define __hw1__Triangle__

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

class Triangle : public Surface{
    
public:
    Point p_a, p_b, p_c;  // origin
    myVector normal;   // radius
    
    /* * * * * * * * * * * *
     Constructors
     * * * * * * * * * * * */
    
    Triangle();											// default constructor
    Triangle(Point p1, Point p2, Point p3);      // constructor
    Triangle(const Triangle& tri);                      // copy constructor
    ~Triangle();											// destructor
    
    Intersection getIntersection(const Ray& myRay, bool withBbox);
    myVector getSurfaceNorm(const Ray& myRay, const float t);
    void setBbox(const myVector& camdir);
    
};

#endif /* defined(__hw1__Triangle__) */
