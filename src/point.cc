//
//  point.cc
//  hw1
//
//  Created by Amrita Mazumdar on 9/22/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "point.h"
#include "myVector.h"
#include <math.h>

/* * * * * * * * * * * *
 Constructors
 * * * * * * * * * * * */

// default constructor

Point::Point()
{}


// constructor from args

Point::Point(float a, float b, float c)
:x(a), y(b), z(c)
{}


// copy constructor

Point::Point(const Point& p)
:x(p.x), y(p.y), z(p.z)
{}


// destructor

Point::~Point()
{}


/* * * * * * * * * * * *
 Useful Operators
 * * * * * * * * * * * */

// assignment operator

Point& Point::operator= (const Point& rhs) {
	
	if (this == &rhs)
		return (*this);
    
	x = rhs.x; y = rhs.y; z = rhs.z;
    
	return (*this);
}

// operator+

Point Point::operator+ (const Point& p) {
    Point temp(x+p.x, y+p.y, z+p.z);
    return temp;
}

Point Point::operator+ (const myVector& v) {
    myVector tempV = myVector(v);
    Point temp(x+tempV.x, y+tempV.y, z+tempV.z);
    return temp;
}

// equality test
int Point::operator== (const Point& p){
    if (x != p.x || y != p.y || z != p.z){
        return 1;
    }
    else return 0;
    
}

// inequality test
int Point::operator!= (const Point& p){
    if (x != p.x || y != p.y || z != p.z){
        return 0;
    }
    else return 1;
    
}



/* * * * * * * * * * * *
 Scalar Math
 * * * * * * * * * * * */

// euclidean distance
float dist(const Point& p1, const Point& p2){
    float d1 = p2.x-p1.x;
    float d2 = p2.y-p1.y;
    float d3 = p2.z - p1.z;
    return sqrt(d1*d1 + d2*d2 + d3*d3);
}

float dist2(const Point& p1, const Point& p2){
    float d1 = p2.x-p1.x;
    float d2 = p2.y-p1.y;
    float d3 = p2.z - p1.z;
    return d1*d1 + d2*d2 + d3*d3;
}












