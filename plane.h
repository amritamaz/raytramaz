//
//  Plane.h
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1__Plane__
#define __hw1__Plane__

#include <iostream>

class myVector;
class Point;
class Intersection;
class Ray;
class Surface;

#include "intersection.h"
#include "myVector.h"
#include "plane.h"
#include "point.h"
#include "ray.h"
#include "sphere.h"
#include "surface.h"
#include "material.h"
#include "math.h"

class Plane: public Surface{
    
    
public:
    myVector normal;
    float d; //distance to origin
    
    /* * * * * * * * * * * *
     Constructors
     * * * * * * * * * * * */
    
    Plane();													// default constructor
    Plane(Point a, Point b, Point c);               // construct Plane from 3 pts
    Plane(const Plane& p);                                      // copy constructor
    Plane(myVector v, float dist);
    ~Plane();													// destructor
    
    Intersection getIntersection(const Ray& myRay);
    myVector getSurfaceNorm(const Ray& myRay, const float t) const;
        
        
    };
    
    
#endif /* defined(__hw1__Plane__) */
