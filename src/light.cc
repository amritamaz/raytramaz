//
//  light.cc
//  hw1-2
//
//  Created by Amrita Mazumdar on 9/27/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "light.h"

Light::Light(){
}// default constructor

// point
Light::Light(float type, float lx, float ly, float lz, float lr, float lg, float lb){
    this->type = type;
    r = lr;
    g = lg;
    b = lb;
    x = lx;
    y = ly;
    z = lz;
    
}


//directional
Light::Light(float type, myVector lvec, float lr, float lg, float lb){
    this->type = type;
    r = lr;
    g = lg;
    b = lb;
    litVec = lvec;
    litVec.normalize();
}

Light::Light(float type, float lr, float lg, float lb){
    this->type = type;
    r = lr;
    g = lg;
    b = lb;
}// ambient


// area
Light::Light(float type, float lx, float ly, float lz, myVector lvec, myVector luvec, float llen, float lr, float lg, float lb){
    this->type = type;
    r = lr;
    g = lg;
    b = lb;
    x = lx;
    y = ly;
    z = lz;
    litVec = lvec;
    litVec.normalize();
    uVec = luvec;
    uVec.normalize();
    length = llen;
}


Light::Light(const Light& l){
    type = l.type;
    switch((int) l.type){
        case 1:{
            r = l.r;
            g = l.g;
            b = l.b;
            x = l.x;
            y = l.y;
            z = l.z;
        }
            break;
            
        case 2:{
            r = l.r;
            g = l.g;
            b = l.b;
            litVec = l.litVec;
        }
            break;
            
        case 3:{
            r = l.r;
            g = l.g;
            b = l.b;
            
        }
            break;
    }
}

// copy constructor
Light::~Light(){}										// destructor

