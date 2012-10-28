//
//  material.cc
//  hw2
//
//  Created by Amrita Mazumdar on 9/28/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//

#include "material.h"

/* * * * * * * * * * * *
 Basic Constructors
 * * * * * * * * * * * */

// default constructor
Material::Material(){
}

Material::Material(float dr, float dg, float db, float sr, float sg, float sb,
                   float r, float ir, float ig, float ib){
    
    this->dr = dr;
    this->dg = dg;
    this->db = db;
    this->sr = sr;
    this->sg = sg;
    this->sb = sb;
    this->r = r;
    this->ir = ir;
    this->ig = ig;
    this->ib = ib;
}

Material::Material(const Material& m){
    dr = m.dr;
    dg = m.dg;
    db = m.db;
    sr = m.sr;
    sg = m.sg;
    sb = m.sb;
    r = m.r;
    ir = m.ir;
    ig = m.ig;
    ib = m.ib;

}

// destructor
Material::~Material(){}


// assignment operator
Material& Material::operator= (const Material& rhs){
    if (this == &rhs)
		return (*this);
    
    dr = rhs.dr;
    dg = rhs.dg;
    db = rhs.db;
    sr = rhs.sr;
    sg = rhs.sg;
    sb = rhs.sb;
    r = rhs.r;
    ir = rhs.ir;
    ig = rhs.ig;
    ib = rhs.ib;
    
	return (*this);
}