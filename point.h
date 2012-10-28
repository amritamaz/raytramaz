//
//  point.h
//  hw1
//
//  Created by Amrita Mazumdar on 9/22/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1__point__
#define __hw1__point__

class myVector;

class Point {
public:
	
    float x, y, z;
    
    /* * * * * * * * * * * *
     Constructors
     * * * * * * * * * * * */
	
    Point();								// default constructor
    Point(float a, float b, float c);      // constructor
    Point(const Point& p);                // copy constructor
    ~Point();                           // destructor
    
    /* * * * * * * * * * * *
     Useful Operators
     * * * * * * * * * * * */
    
    Point& operator= (const Point& p);                   // assignment operator
    
    Point operator- () const;                               // unary minus
    
    Point operator+ (const Point& p);                    // adding two points
    
    Point operator+ (const myVector& v);        // adding a myVector to a point
    
    Point operator- (const Point& p);     // subtracting one point from another
	
    Point operator* (const float a) const;         // multiplication by a float
    
    int operator== (const Point& p);                          // equivalency
    
    int operator!= (const Point& p);
    
    
};

//operator-
// subtracting one point from another

inline Point Point::operator-(const Point& p){
    return (Point(x-p.x, y-p.y, z-p.z));
}

// operator-
// unary minus

inline Point Point::operator- () const {
	return (Point(-x, -y, -z));
}

// operator*
// mutliplication by a float on the right

inline Point Point::operator* (const float a) const {
	return (Point(x * a,y * a,z * a));
}

// operator*
// multiplication by a float on the left

inline Point operator* (float a, const Point& p) {
	return (Point(a * p.x, a * p.y, a * p.z));
}

/* * * * * * * * * * * *
 Scalar Math
 * * * * * * * * * * * */

float dist(const Point& p1, const Point& p2);             // distance btwn 2 pts

float dist2(const Point& p1, const Point& p2);            // distance squared


#endif /* defined(__hw1__point__) */

