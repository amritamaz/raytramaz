//
//  Sphere.cc
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "sphere.h"

/* * * * * * * * * * * *
 Constructors
 * * * * * * * * * * * */

// default constructor

Sphere::Sphere()
{}


// constructor from args

Sphere::Sphere(float a, float b, float c, float r)
{
    orig = Point(a,b,c);
    rad = r;
}


// copy constructor

Sphere::Sphere(const Sphere& p)
:orig(p.orig), rad(p.rad)
{}


// destructor

Sphere::~Sphere()
{}

void Sphere::setBbox(const myVector& camdir){
    myVector u, v, w;
    w = -camdir;
    w.normalize();
    
    if (1.0 - fabs (w.y) < .0001) {
        // camera is pointing up or down - make an arbitrary
        // right-handed coordinate system:
        u = myVector(1.0, 0.0, 0.0);
        v = cross(w,u);
    }
    else {
        myVector up = myVector(0., 1., 0.);
        u = myVector(cross(up, w));
        v = myVector(cross(w, u));
    }
    
    u.normalize();
    v.normalize();
    
    Point px1, px2, py1, py2, pz1, pz2;
    
    px1 = orig + u*rad;
    px2 = orig + (-1*u)*rad;
    py1 = orig + v*rad;
    py2 = orig + (-1*v)*rad;
    pz1 = orig + camdir*rad;
    pz2 = orig + w*rad;
    
    float xmax = fmax(fmax(fmax(px1.x, px2.x),fmax(py1.x, py2.x)),fmax(pz1.x, pz2.x));
    float xmin = fmin(fmin(fmin(px1.x, px2.x),fmin(py1.x, py2.x)),fmin(pz1.x, pz2.x));
    
    float ymax = fmax(fmax(fmax(px1.y, px2.y),fmax(py1.y, py2.y)),fmax(pz1.y, pz2.y));
    float ymin = fmin(fmin(fmin(px1.y, px2.y),fmin(py1.y, py2.y)),fmin(pz1.y, pz2.y));
    
    float zmax = fmax(fmax(fmax(px1.z, px2.z),fmax(py1.z, py2.z)),fmax(pz1.z, pz2.z));
    float zmin = fmin(fmin(fmin(px1.z, px2.z),fmin(py1.z, py2.z)),fmin(pz1.z, pz2.z));
    
    Point t_max_p = Point(xmax, ymax, zmax);
    Point t_min_p = Point(xmin, ymin, zmin);
    
    bounds = Bbox(t_min_p, t_max_p, camdir);
    hasBbox = true;
    
}


Intersection Sphere::getIntersection(const Ray &myRay, bool withBbox){
    
    if (withBbox && hasBbox){
        Intersection bboxInters = bounds.getIntersection(myRay);
        if (!bboxInters.isIntersected){
            return Intersection();
        }
        else {
            return bboxInters;
        }
    }
    
    myVector e_c = myVector(myRay.origin, orig);
    myVector d = myRay.direction;
    float d_dot_d = dot(d, d);
    float d_dot_ec = dot(d,e_c);
    float e_c_dot = dot(e_c,e_c);
    float r2 = rad*rad;
    float innersqrt = (d_dot_ec*d_dot_ec)-(d_dot_d*(e_c_dot-r2));
    
    if (innersqrt < 0){ // discriminant negative, no intersection
        return Intersection();
    }
    
    else {
        
        // check if it's one or two intersection pts
        
        float tA, tB;
        myVector negd = -1*d;
        float negd_ec = dot(negd, e_c);
        myVector norm;
        tA = (negd_ec + sqrt(innersqrt))/(d_dot_d);
        
        if (innersqrt == 0){
            if (tA > 0){
                norm = getSurfaceNorm(myRay, tA);
                return Intersection(true, tA, norm);
            }
            else { return Intersection(); }
        }
        
        else {
            tB = (negd_ec - sqrt(innersqrt))/(d_dot_d);
            
            
            if ((tA < tB) && (tA > 0)){
                norm = getSurfaceNorm(myRay, tA);
                return Intersection(true, tA, norm);
            }
            else {
                if (tB > 0){
                    norm = getSurfaceNorm(myRay, tB);
                    return Intersection(true, tB, norm);
                }
                else {
                    return Intersection();
                }
            }
        }
    }
}

myVector Sphere::getSurfaceNorm(const Ray &myRay, const float t){
    myVector norm;
    float intersection_x = (myRay.origin).x + ((myRay.direction).x)*t;
    float intersection_y = (myRay.origin).y + ((myRay.direction).y)*t;
    float intersection_z = (myRay.origin).z + ((myRay.direction).z)*t;
    
    Point intersP = Point(intersection_x, intersection_y, intersection_z);
    myVector temp = myVector(intersP, orig);
    norm = temp/rad;
    norm.normalize();
    return norm;
}