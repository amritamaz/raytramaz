//
//  ray.cc
//  hw1
//
//  Created by Amrita Mazumdar on 9/22/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "ray.h"
#include "myVector.h"
#include "point.h"
#include <math.h>

/* * * * * * * * * * * *
 Basic Constructors
 * * * * * * * * * * * */

// default constructor
Ray::Ray(){
    origin = Point(0,0,0);
    direction = myVector(0,0,1);
}

Ray::Ray(const Point& o, const myVector& d)
:origin(o), direction(d){}

Ray::Ray(const Point& p1, const Point& p2){
    Point pa = p1;
    Point pb = p2;
    origin = Point(p1);
    direction = myVector(pa - pb);
}

Ray::Ray(const Ray& ray){
    origin = Point(ray.origin);
    direction = myVector(ray.direction);
}

// destructor
Ray::~Ray(){}


// assignment operator
Ray& Ray::operator= (const Ray& rhs){
    if (this == &rhs)
		return (*this);
    
	origin = rhs.origin; direction = rhs.direction;
	return (*this);
}

// equivalency
int Ray::operator== (const Ray& r){
    if ( (origin == r.origin) && (direction == r.direction))
        return 1;
    else return 0;
}

int Ray::operator!= (const Ray& r){
    if ( (origin == r.origin) && (direction == r.origin))
        return 0;
    else return 1;
}


/* * * * * * * * * * * *
 myVector Methods
 * * * * * * * * * * * */

Point Ray::getInterPt(float t){
    myVector ndir = t*direction;
    Point out = origin + ndir;
    return out;
}


void Ray::normalize(){
    direction.normalize();
}//normalize myVector
