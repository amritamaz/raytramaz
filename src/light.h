//
//  light.h
//  hw1-2
//
//  Created by Amrita Mazumdar on 9/27/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1_2__light__
#define __hw1_2__light__

#include <iostream>
#include "myVector.h"
#include "ray.h"
#include <stdio.h>
#include <vector>



class Light{
    

public: 
    float type, r, g, b, x, y, z;
    // type: 1 = point light, 2 = directional, 3 = ambient, 4 = area
    myVector litVec, uVec;
    
    // for an area light source
    float length;

    /* * * * * * * * * * * *
     Basic Constructors
     * * * * * * * * * * * */

    Light();
    Light(float type, float lx, float ly, float lz, float lr, float lg, float lb); // point light source
    Light(float type, myVector lvec, float lr, float lg, float lb); // directional light source
    Light(float type, float lr, float lg, float lb); // ambient
    Light(float type, float lx, float ly, float lz, myVector lvec, myVector luVec, float llen, float lr, float lg, float lb);
    Light(const Light& p); // copy
    ~Light();
    
    
};


#endif /* defined(__hw1_2__light__) */
