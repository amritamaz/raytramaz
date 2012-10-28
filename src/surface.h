//
//  Surface.h
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1__Surface__
#define __hw1__Surface__

#include <iostream>
#include "intersection.h"
#include "myVector.h"
#include "point.h"
#include "ray.h"
#include "material.h"

class myVector;
class Intersection;
class Ray;

class Surface {
    
    
public:
    
    Material matInfo;
    
    /* * * * * * * * * * * *
     Constructors
     * * * * * * * * * * * */
	
    Surface();								// default constructor
    Surface(const Surface& p);                             // copy constructor
    ~Surface();													// destructor
    
    virtual Intersection getIntersection(const Ray& myRay){
        return Intersection();
    }
    
    void setMaterial(const Material& myMat){
        matInfo = myMat;
        
    }
    
    
};


#endif /* defined(__hw1__Surface__) */
