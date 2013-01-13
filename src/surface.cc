//
//  Surface.cc
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "surface.h"


Surface::Surface(){
}// default constructor

Surface::Surface(const Surface& p)
:matInfo(p.matInfo), bounds(p.bounds), hasBbox(p.hasBbox)
{}

Surface::~Surface(){}										// destructor



