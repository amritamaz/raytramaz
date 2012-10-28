//
//  Plane.cc
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "plane.h"

/* * * * * * * * * * * *
 Constructors
 * * * * * * * * * * * */

//default constructor
Plane::Plane(){
    normal = myVector(0,0,0);
    d = 0;
}

//plane from three pts
Plane::Plane(Point a, Point b, Point c){
    //make a vector from two points
    
    normal = cross(myVector(b,a),myVector(c,a));
    d = -dot(a,normal);
}

//copy constructor
Plane::Plane(const Plane& p){
    normal = p.normal;
    d = p.d;
}

Plane::Plane(myVector v, float dist){
    normal = v;
    d = dist;
}


Plane::~Plane(){}

// maybe the t is wrong here, check that. that's most likely the problem
Intersection Plane::getIntersection(const Ray &myRay){
    
    float raydirdotn = dot(myRay.direction, normal);
    
    //if parallel, no intersection
    if(raydirdotn==0){
        return Intersection();
    }
    
    else {
        float pdotn = dot(myRay.origin, normal);
        float num_mag = pdotn + d;
        float numerator = -1*(num_mag);
        float t = numerator/raydirdotn;
        if (t > 0){
        return Intersection(true, t, normal);
        }
        else { return Intersection(); }
    }
}

myVector Plane::getSurfaceNorm(const Ray &myRay, const float t) const{
    return normal;
}
