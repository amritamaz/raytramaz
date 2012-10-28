//
//  Intersection.h
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1__Intersection__
#define __hw1__Intersection__

#include <iostream>
#include "myVector.h"

class Intersection {
    
public:
    
    bool isIntersected; // greater than 1 if yes, else 0
    float t; //intersection points (two for quadratics
    myVector geomNorm;
    
    /* * * * * * * * * * * *
     Constructors
     * * * * * * * * * * * */
	
    Intersection();										// default constructor
    Intersection(bool i, float t1, myVector vec);
    Intersection(const Intersection& inter);                 // copy constructor
    ~Intersection();							// destructor
    
    Intersection& operator= (const Intersection& p);      // assignment operator
    
    
};

#endif /* defined(__hw1__Intersection__) */
