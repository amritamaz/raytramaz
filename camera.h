//
//  camera.h
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef __hw1__camera__
#define __hw1__camera__

#include <iostream>
#include <math.h>
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <vector>

using namespace Imf;
using namespace Imath;

#include "intersection.h"
#include "myVector.h"
#include "plane.h"
#include "point.h"
#include "ray.h"
#include "sphere.h"
#include "surface.h"
#include "light.h"
#include "rgb.h"

class Surface;
class Ray;
class Light;

class Camera {
    
    int raysamps, shadowsamps, raysampsqrd, shadsampsqrd;

    
public:
    Point eye;
    float focal; // focal length
    myVector u; // camera "right"
    myVector v; // camera "up"
    myVector w; // opposite camera viewing dir
    int nx; // width of img in pixels
    int ny; // height of img in pixels
    float l, r, t, b; //left right top bottom edges
    
    /* * * * * * * * * * * *
     Constructors
     * * * * * * * * * * * */
	
    Camera();					// default constructor
    
    // camera at position [x y z] looking in direction [vx vy vz],
    // with focal length d, / an image plane sized iw by ih (width, height)
    // and number of pixels pw ph.
    //c x y z vx vy vz d iw ih pw ph
    Camera(const float x, const float y, const float z,
           const float vx, const float vy, const float vz,
           const float dist, const float iw, const float ih,
           const float pw, const float ph, int ray_samp, int shad_samp);      // constructor
    
    Camera(const Camera& c);                                // copy constructor
    ~Camera();                                              // destructor
    
    Camera& operator= (const Camera& p);                  // assignment operator
    
    
    /* * * * * * * * * * * *
     Primary Ray Generation
     * * * * * * * * * * * */
    
    Ray makeRay(float i, float j) const;           // primary ray generation function
    
    void renderScene(std::vector<Surface *> surfaces, std::vector<Light *> lights, Array2D<Imf::Rgba> &pixels);
    
    void writeImage(char* filename,const Imf::Rgba *pixels);
    
    Rgb L (Ray in_ray, float min_t, float max_t, int recurse_limit, int ray_type, Light lite, std::vector<Light *> lights, std::vector<Surface *> surfaces);

};




#endif /* defined(__hw1__camera__) */
