//
//  bbox.cc
//  hw6
//
//  Created by Amrita Mazumdar on 1/12/13.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "bbox.h"

Bbox::Bbox(){
    min_p = Point(0,0,0);
    max_p = Point(0,0,0);
    camdir = myVector(0,0,0);
}

Bbox::Bbox(Point min, Point max, myVector cam){
    min_p = min;
    max_p = max;
    camdir = cam;
}

Bbox::Bbox(const Bbox& p){
    min_p = p.min_p;
    max_p = p.max_p;
    camdir = p.camdir;
}

Bbox::~Bbox(){
    
}// destructor

Intersection Bbox::getIntersection(const Ray& myRay){
    Point eee = myRay.origin;
    myVector ddd = myRay.direction;
    
    float txmin, txmax, tymin, tymax, tzmin, tzmax;
    
    float dx = 1/(ddd.x);
    float dy = 1/(ddd.y);
    float dz = 1/(ddd.z);
    if (dx > 0){
        txmin = (min_p.x - eee.x)*dx;
        txmax = (max_p.x - eee.x)*dx;
    }
    else {
        txmin = (max_p.x - eee.x)*dx;
        txmax = (min_p.x - eee.x)*dx;
    }
    if (dy > 0){
        tymin = (min_p.y - eee.y)*dy;
        tymax = (max_p.y - eee.y)*dy;
    }
    else {
        tymax = (min_p.y - eee.y)*dy;
        tymin = (max_p.y - eee.y)*dy;
        
    }
    if (dz > 0){
        tzmin = (min_p.z - eee.z)*dz;
        tzmax = (max_p.z - eee.z)*dz;
    }
    else {
        tzmax = (min_p.z - eee.z)*dz;
        tzmin = (max_p.z - eee.z)*dz;
        
    }
    
    bool condx = (txmin > tymax) || (txmin > tzmax);
    bool condy = (tymin > txmax) || (tymin > tzmax);
    bool condz = (tzmin > txmax) || (tzmin > tymax);
    
    if (condx || condy || condz){
        return Intersection();
    }
    else {
        float tmin;
        if ((txmin > tymin) && (txmin > tzmin) && (txmin > 0)){
            tmin = txmin;
        }
        else if ((tymin > txmin) && (tymin > tzmin) && (tymin > 0)){
            tmin = tymin;
        }
        else if ((tzmin > txmin) && (tzmin > tymin) && (tzmin > 0)){
            tmin = tzmin;
        }
        else {
            return Intersection();
        }
        myVector norm = getSurfaceNorm(myRay, tmin);
        return Intersection(true, tmin, norm);
    }
    
}
myVector Bbox::getSurfaceNorm(const Ray& myRay, const float t){
    myVector posx, posy, posz, negx, negy, negz, norm;
    
    
    posz = camdir;
    negz = -camdir;
    
    if (1.0 - fabs (negz.y) < .0001) {
        // camera is pointing up or down - make an arbitrary
        // right-handed coordinate system:
        posx = myVector(1.0, 0.0, 0.0);
        posy = cross(negz,posx);
    }
    else {
        myVector up = myVector(0., 1., 0.);
        posx = myVector(cross(up, negz));
        posy = myVector(cross(negz, posx));
    }
    
    negx = -1*posx;
    negy = -1*posy;
    
    
    float intersection_x = (myRay.origin).x + ((myRay.direction).x)*t;
    float intersection_y = (myRay.origin).y + ((myRay.direction).y)*t;
    float intersection_z = (myRay.origin).z + ((myRay.direction).z)*t;
    if (intersection_x < .00001 && intersection_x > -.00001){
        intersection_x = 0;
    }
    if (intersection_y < .00001 && intersection_y > -.00001){
        intersection_y = 0;
    }
    if (intersection_z < .00001 && intersection_z > -.00001){
        intersection_z = 0;
    }
    
    
    Point intersP = Point(intersection_x, intersection_y, intersection_z);
    
    if ((intersection_x - max_p.x < .0001) && (intersection_x - max_p.x > -.0001)){
        norm = negx;
    }
    else if ((intersection_x - min_p.x < .001) && (intersection_x - min_p.x > -.001)){
        norm = posx;
    }
    else if ((intersection_y - max_p.y < .001) && (intersection_y - max_p.y > -.001)){
        norm = posy;
    }
    else if ((intersection_y - min_p.y < .001) && (intersection_y - min_p.y > -.001)){
        norm = negy;
    }
    else if ((intersection_z - max_p.z < .001) && (intersection_z - max_p.z > -.001)){
        norm = negz;
    }
    else if ((intersection_z - min_p.z < .001) && (intersection_z - min_p.z > -.001)){
        norm = posz;
    }
    else {
        norm = myVector(0, 0, 0);
    }
    
    norm.normalize();
    return norm;
}