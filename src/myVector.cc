//
//  myVector.cc
//  hw1
//
//  Created by Amrita Mazumdar on 9/22/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//
#include <math.h>
#include "myVector.h"
#include "point.h"

/* * * * * * * * * * * *
 Basic Constructors
 * * * * * * * * * * * */


// default constructor
myVector::myVector()
{}

// constructor from 3 floats
myVector::myVector(float x1, float y1, float z1){
    x = x1;
    y = y1;
    z = z1;
}

// copy constructor
myVector::myVector(const myVector& v){
    x = v.x;
    y = v.y;
    z = v.z;
}

// construct a vector from 1 float, like in sphere or ray
myVector::myVector(float p1){
    x = p1;
    y = p1;
    z = p1;
}


// construct a vector from one point (assumes origin is other pt)
myVector::myVector(const Point& p1){
    x = p1.x;
    y = p1.y;
    z = p1.z;
}


// construct a myVector from two points
myVector::myVector(const Point& p1, const Point& p2){
    x = p1.x - p2.x;
    y = p1.y - p2.y;
    z = p1.z - p2.z;
}

// destructor
myVector::~myVector()
{}

// assignment operator
myVector& myVector::operator= (const myVector& rhs){
    if (this == &rhs)
		return (*this);
    
	x = rhs.x; y = rhs.y; z = rhs.z;
    
	return (*this);
}

// equality test
int myVector::operator== (const myVector& v){
    if (x != v.x || y != v.y || z != v.z){
        return 1;
    }
    else return 0;
    
}

// inequality test
int myVector::operator!= (const myVector& v){
    if (x != v.x || y != v.y || z != v.z){
        return 0;
    }
    else return 1;
    
}


/* * * * * * * * * * * *
 myVector Methods
 * * * * * * * * * * * */

//  normalize
// converts the myVector to a unit myVector

void myVector::normalize(void) {
	float lngt = length();
    
    x /= lngt;
    y /= lngt;
    z /= lngt;
}

float dot(myVector v, myVector w){
    return (v.x*w.x + v.y*w.y + v.z*w.z);
}

// cross product eqtn from wikipedia
myVector cross(myVector v, myVector w){
    myVector n;
    n.x = v.y*w.z - v.z*w.y;
    n.y = v.z*w.x - v.x*w.z;
    n.z = v.x*w.y - v.y*w.x;
    return n;
}


/* * * * * * * * * * * *
 Scalar Math
 * * * * * * * * * * * */


myVector operator*(float d, myVector v){
    myVector v_new;
    v_new.x = d*v.x;
    v_new.y = d*v.y;
    v_new.z = d*v.z;
    return v_new;
}

myVector operator*(myVector v, float d){
    myVector v_new;
    v_new.x = d*v.x;
    v_new.y = d*v.y;
    v_new.z = d*v.z;
    return v_new;
}

myVector operator/(myVector v, float d){
    myVector v_new;
    v_new.x = v.x/d;
    v_new.y = v.y/d;
    v_new.z = v.z/d;
    return v_new;
    
}

/* * * * * * * * * * * *
 myVector Math
 * * * * * * * * * * * */

myVector myVector::operator+(myVector v){
    myVector w;
	w.x = x+v.x;
    w.y = y+v.y;
    w.z = z+v.z;
    
    return w;
}

Point myVector::operator+( Point p){
    Point w;
    w.x = p.x + x;
    w.y = p.y + y;
    w.z = p.z + z;
    
    return w;
}


myVector myVector::operator-(myVector v){
    myVector w;
	w.x = x-v.x;
    w.y = y-v.y;
    w.z = z-v.z;
    
    return w;
}

float myVector::operator*(myVector v){
    return (x * v.x + y * v.y + z * v.z);
}


