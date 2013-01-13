//
//  bbox.h
//  hw6
//
//  Created by Amrita Mazumdar on 10/26/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw5__bbox__
#define __hw5__bbox__

#include "ray.h"
#include "intersection.h"
#include "myVector.h"
#include "point.h"
#include <math.h>
#include <iostream>

class Sphere;
class Triangle;

class Bbox {
    
    Point min_p, max_p;
    myVector camdir;
    
public:
    
    
    /* * * * * * * * * * * *
     Constructors
     * * * * * * * * * * * */
	Bbox();
    Bbox(Point min, Point max, myVector cam);					// default constructor
    Bbox(const Bbox& p);                             // copy constructor
    ~Bbox();													// destructor
    
    Intersection getIntersection(const Ray& myRay);
    myVector getSurfaceNorm(const Ray& myRay, const float t);
    
};

#endif /* defined(__hw6__bbox__) */
