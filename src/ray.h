//
//  ray.h
//  hw1
//
//  Created by Amrita Mazumdar on 9/22/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1__ray__
#define __hw1__ray__

#include <iostream>
#include "point.h"
#include "myVector.h"

class Ray {
public:
	
    Point origin;  	// origin
    myVector direction; 		// direction
    
    /* * * * * * * * * * * *
     Basic Constructors
     * * * * * * * * * * * */
	
    // default constructor
    Ray();
    
    Ray(const Point& o, const myVector& d);
    
    Ray(const Point& p1, const Point& p2);
    
    Ray(const Ray& ray);
    
    // destructor
    ~Ray();
    
    
    // assignment operator
    Ray& operator= (const Ray& rhs);
    
    // equivalency
    int operator== (const Ray& r);
    
    int operator!= (const Ray& r);
    
    
    /* * * * * * * * * * * *
     myVector Methods
     * * * * * * * * * * * */
    
    Point getInterPt(float);
    void normalize();                   //normalize myVector
    
};


#endif /* defined(__hw1__ray__) */
