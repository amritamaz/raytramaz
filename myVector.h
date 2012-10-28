//
//  myVector.h
//  hw1
//
//  Created by Amrita Mazumdar on 9/22/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1__myVector__
#define __hw1__myVector__

#include <math.h>
#include "point.h"

class Point;

class myVector {
public:
	
    float	x, y, z;
    
    /* * * * * * * * * * * *
     Basic Constructors
     * * * * * * * * * * * */
	
    // default constructor
    myVector();
    
    // constructor from 3 floats
    myVector(float x1, float y1, float z1);
    
    // constructor from 1 float
    // happens in the Ray class
    myVector(float p1);
    
    // copy constructor
    myVector(const myVector& v);
    
    // construct a myVector from one point
    myVector(const Point& p);
    
    // construct a myVector from two points
    myVector(const Point& p1, const Point& p2);
    
    // destructor
    ~myVector ();
    
    
    // assignment operator
    myVector& operator= (const myVector& rhs);
    
    // equivalency
    int operator== (const myVector& p);
    
    int operator!= (const myVector& p);
    
    
    /* * * * * * * * * * * *
     myVector Methods
     * * * * * * * * * * * */
    
    float length() const;                    //length
    float length_sqrd() const;               //length squared
    void normalize();                   //normalize myVector
    friend float dot(myVector v, myVector w) ;   // dot product of two myVectors
    friend myVector cross(myVector v, myVector w) ;   // cross product
    
    
    /* * * * * * * * * * * *
     Scalar Math
     * * * * * * * * * * * */
    
	friend myVector operator*( float d, myVector v);
	friend myVector operator*( myVector v, float d);
	friend myVector operator/( myVector v, float d);
    
    /* * * * * * * * * * * *
     myVector Math
     * * * * * * * * * * * */
    
	myVector operator+( myVector v);        // myVector add
    Point operator+( Point p);        // add a vector to a point to get a point
	myVector operator-( myVector v);        // myVector subtract
    myVector operator-() const;                 // unary myVector minus
	float operator*( myVector v);        // inner dot product
    
};

inline myVector myVector::operator- () const {
    return (myVector(-x, -y, -z));
}

inline float myVector::length() const{

    float x2 = x*x;
    float y2 = y*y;
    float z2 = z*z;
    float ans = sqrt(x2+y2+z2);
    return (ans);
}

inline float myVector::length_sqrd() const{
    return (x*x + y*y+z*z);
}


#endif /* defined(__hw1__myVector__) */
