//
//  Intersect.cc
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "intersection.h"

Intersection::Intersection(){
    isIntersected = false;
    t = 0;
    geomNorm = myVector();
    
}

Intersection::Intersection(bool i, float t1, myVector vec){
    isIntersected = i;
    t = t1;
    geomNorm = vec;
}// constructor

Intersection::Intersection(const Intersection& inter){
    isIntersected = inter.isIntersected;
    t = inter.t;
    geomNorm = inter.geomNorm;
    
}// copy constructor

Intersection::~Intersection(){}									// destructor

Intersection& Intersection::operator= (const Intersection& rhs){
    if (this == &rhs)
		return (*this);
    
    isIntersected = rhs.isIntersected;
    t = rhs.t;
    geomNorm = rhs.geomNorm;
    geomNorm.normalize();
	return (*this);
    
}// assignment operator
