//
//  material.h
//  hw2
//
//  Created by Amrita Mazumdar on 9/28/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw2__material__
#define __hw2__material__

#include <iostream>


class Material {
public:
	
    float	dr, dg, db, sr, sg, sb, r, ir, ig, ib;
    
    /* * * * * * * * * * * *
     Basic Constructors
     * * * * * * * * * * * */
	
    // default constructor
    Material();
    
    // constructor from 3 floats
    Material(float dr, float dg, float db, float sr, float sg, float sb,
             float r, float ir, float ig, float ib);
    
    // copy constructor
    Material(const Material& m);
            
    // destructor
    ~Material ();
    
    
    // assignment operator
    Material& operator= (const Material& rhs);
    
};


#endif /* defined(__hw2__material__) */
