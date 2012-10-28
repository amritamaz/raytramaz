//
//  main.h
//  hw1-2
//
//  Created by Amrita Mazumdar on 9/24/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#ifndef hw1_2_Header_h
#define hw1_2_Header_h

#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <assert.h>

using namespace Imf;
using namespace Imath;
using namespace std;

//#define IM_DEBUGGING


#include "camera.h"
#include "intersection.h"
#include "myVector.h"
#include "plane.h"
#include "point.h"
#include "ray.h"
#include "sphere.h"
#include "surface.h"
#include "material.h"
#include "triangle.h"


void parseSceneFile (const char *filnam, Camera &c, vector<Surface *> &s, std::vector<Light *> &l);

void buildScene(char *file, Camera c, vector<Surface *> s, vector<Light *> &l);

void read_wavefront_file (const char *file, vector< int > &tris, vector< float > &verts);


#endif
