//
//  rgb.h
//  hw4
//
//  Created by Amrita Mazumdar on 10/14/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw4__rgb__
#define __hw4__rgb__

#include <iostream>

class Rgb {
public:
	
    float r, g, b;
    
    /* * * * * * * * * * * *
     Constructors
     * * * * * * * * * * * */
	
    Rgb();								// default constructor
    Rgb(float r_a, float g_a, float b_a);      // constructor
    Rgb(const Rgb& p);                // copy constructor
    ~Rgb();                           // destructor
    
    /* * * * * * * * * * * *
     Useful Operators
     * * * * * * * * * * * */
    
    Rgb& operator= (const Rgb& p);                   // assignment operator
    
    Rgb operator- () const;                               // unary minus
    
    Rgb operator+ (const Rgb& p);                    // adding two points
        
    Rgb operator- (const Rgb& p);     // subtracting one point from another
	
    Rgb operator* (const float a) const;         // multiplication by a float
    
    int operator== (const Rgb& p);                          // equivalency
    
    int operator!= (const Rgb& p);
    
    
};

//operator-
// subtracting one point from another

inline Rgb Rgb::operator-(const Rgb& p){
    return (Rgb((r - p.r), (g-p.g), (b-p.b)));
}

// operator-
// unary minus

inline Rgb Rgb::operator- () const {
	return (Rgb(-1*r, -1*g, -1*b));
}

// operator*
// mutliplication by a float on the right

inline Rgb Rgb::operator* (const float a) const {
	return (Rgb(r * a,g * a,b * a));
}

// operator*
// multiplication by a float on the left

inline Rgb operator* (float a, const Rgb& p) {
	return (Rgb(a * p.r, a * p.g, a * p.b));
}


#endif /* defined(__hw4__rgb__) */
