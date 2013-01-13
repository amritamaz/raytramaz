//
//  triangle.cc
//  hw3
//
//  Created by Amrita Mazumdar on 10/7/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "triangle.h"

Triangle::Triangle(){
    
}// default constructor
Triangle::Triangle(Point p1, Point p2, Point p3){
    p_a = p1;
    p_b = p2;
    p_c = p3;
    
}

// constructor
Triangle::Triangle(const Triangle& tri)
:p_a(tri.p_a), p_b(tri.p_b), p_c(tri.p_c), normal(tri.normal)
{
}// copy constructor


Triangle::~Triangle(){}											// destructor

Intersection Triangle::getIntersection(const Ray& myRay, bool withBbox){
    
    if (withBbox && hasBbox){
        Intersection bboxInters = bounds.getIntersection(myRay);
        if (!bboxInters.isIntersected){
            return Intersection();
        }
        else {
            return bboxInters;
        }
    }
    
    float a = p_a.x - p_b.x;
	float b = p_a.y - p_b.y;
	float c = p_a.z - p_b.z;
    
	float d = p_a.x - p_c.x;
	float e = p_a.y - p_c.y;
	float f = p_a.z - p_c.z;
    
	float g = (myRay.direction).x;
	float h = (myRay.direction).y;
	float i = (myRay.direction).z;
    
	//calculate M first
    
	float ei_hf = e * i - h * f;
	float gf_di = g * f - d * i;
	float dh_eg = d * h - e * g;
    
	float M = a * ei_hf + b * gf_di + c * dh_eg;
    
    //no intersection
	if(M == 0) {
        return Intersection();
    }
    
    //compute t
	float j = p_a.x - (myRay.origin).x; //v1.getX() - o.getX();
	float k = p_a.y - (myRay.origin).y; //v1.getY() - o.getY();
	float l = p_a.z - (myRay.origin).z; //v1.getZ() - o.getZ();
    
	float ak_jb = a * k - j * b;
	float jc_al = j * c - a * l;
	float bl_kc = b * l - k * c;
    
	float t_numerator = f * ak_jb + e * jc_al + d * bl_kc;
    
	float t = (-1) * t_numerator / M;
    
	//if t negative, no intersection
	if(t < 0){
        return Intersection();
    }
    
	//calculate Gamma
    
	float gamma_numerator = i * ak_jb + h * jc_al + g * bl_kc;
	float gamma = gamma_numerator / M;
    
	if((gamma < 0) || (gamma > 1)){
        return Intersection();
    }
    
	//calculate beta
    
	float beta_numerator = j * ei_hf + k * gf_di + l * dh_eg;
	float beta = beta_numerator / M;
    
	if((beta < 0) || (beta > (1-gamma)))
	{
        return Intersection();
	}
    
	//cout << "gets past beta check sometimes" << endl;
    
	//if got through all of that, then there's an intersection at t
	//plug t into the ray equation to get the point of intersection
    
	//ray equation: point = p0 + td
    myVector norm = getSurfaceNorm(myRay, t);
    return Intersection(true, t, norm);
    
}

myVector Triangle::getSurfaceNorm(const Ray& myRay, const float t){
    myVector vA = myVector(p_c,p_a);
    myVector vB = myVector(p_b,p_a);
    normal = cross(vB, vA);
    normal.normalize();
    return normal;
}

void Triangle::setBbox(const myVector& camdir){
    
    float max_x = fmax(fmax(p_a.x, p_b.x), p_c.x);
    float max_y = fmax(fmax(p_a.y, p_b.y), p_c.y);
    float max_z = fmax(fmax(p_a.z, p_b.z), p_c.z);
    
    float min_x = fmin(fmin(p_a.x, p_b.x), p_c.x);
    float min_y = fmin(fmin(p_a.y, p_b.y), p_c.y);
    float min_z = fmin(fmin(p_a.z, p_b.z), p_c.z);
    
    Point t_max_p = Point(max_x, max_y, max_z);
    Point t_min_p = Point(min_x, min_y, min_z);
    
    bounds = Bbox(t_min_p, t_max_p, camdir);
    hasBbox = true;
    
}

