//
//  rgb.cc
//  hw4
//
//  Created by Amrita Mazumdar on 10/14/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "rgb.h"
// default constructor

Rgb::Rgb()
{}


// constructor from args

Rgb::Rgb(float a, float b, float c)
:r(a), g(b), b(c)
{}


// copy constructor

Rgb::Rgb(const Rgb& p)
:r(p.r), g(p.g), b(p.b)
{}


// destructor

Rgb::~Rgb()
{}


/* * * * * * * * * * * *
 Useful Operators
 * * * * * * * * * * * */

// assignment operator

Rgb& Rgb::operator= (const Rgb& rhs) {
	
	if (this == &rhs)
		return (*this);
    
	r = rhs.r; g = rhs.g; b = rhs.b;
    
	return (*this);
}

// operator+

Rgb Rgb::operator+ (const Rgb& p) {
    Rgb temp(r+p.r, g+p.g, b+p.b);
    return temp;
}

// equality test
int Rgb::operator== (const Rgb& p){
    if (r != p.r || g != p.g || b != p.b){
        return 1;
    }
    else return 0;
    
}

// inequality test
int Rgb::operator!= (const Rgb& p){
    if (r != p.r || g != p.g || b != p.b){
        return 0;
    }
    else return 1;
    
}







