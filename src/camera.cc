//
//  camera.cc
//  hw1
//
//  Created by Amrita Mazumdar on 9/23/12.
//  Copyright (c) 2012 Amrita Mazumdar. All rights reserved.
//


//Point eye;
//float d; // focal length
//myVector u; // camera "right"
//myVector v; // camera "up"
//myVector w; // opposite camera viewing dir
//int nx; // width of img in pixels
//int ny; // height of img in pixels
//float l, r, t, b; //left right top bottom edges

#include "camera.h"

/* * * * * * * * * * * *
 Constructors
 * * * * * * * * * * * */

// default constructor, no params
Camera::Camera(){
    eye = Point(0,0,0);
    focal = 0;
    u = myVector(0);
    v = myVector(0);
    w = myVector(0);
    nx = 0;
    ny = 0;
    l = 0;
    r = 0;
    t = 0;
    b = 0;
}

// camera at position [x y z] looking in direction [vx vy vz], with
// focal length d,
//an image plane sized iw by ih (width, height) and number of pixels pw ph.
//c x y z vx vy vz d iw ih pw ph
Camera::Camera(const float x, const float y, const float z,
               const float vx, const float vy, const float vz,
               const float dist, const float iw, const float ih,
               const float pw, const float ph, int ps, int ss){
    Point temp = Point(x,y,z);
    eye = temp;
    focal = dist;
    nx = pw;
    ny = ph;
    l = -iw/2;
    r = iw/2;
    b = -ih/2;
    t = ih/2;
    raysamps = ps;
    shadowsamps = ss;
    raysampsqrd = raysamps*raysamps;
    shadsampsqrd = shadowsamps*shadowsamps;
    
    // set up camera frame
    myVector direction = myVector(vx, vy, vz);
    direction.normalize();
    w = -direction;
    w.normalize();
    
    if (1.0 - fabs (w.y) < .0001) {
        // camera is pointing up or down - make an arbitrary
        // right-handed coordinate system:
        u = myVector(1.0, 0.0, 0.0);
        v = cross(w,u);
    }
    else {
        myVector up = myVector(0., 1., 0.);
        u = myVector(cross(up, w));
        v = myVector(cross(w, u));
    }
    
    u.normalize();
    v.normalize();
    
}

// copy constructor
Camera::Camera(const Camera& c){
    eye = c.eye;
    focal = c.focal;
    nx = c.nx;
    ny = c.ny;
    l = c.l;
    r = c.r;
    b = c.b;
    t = c.t;
    u = c.u;
    v = c.v;
    w = c.w;
    raysamps = c.raysamps;
    shadowsamps = c.shadowsamps;
    raysampsqrd = raysamps*raysamps;
    shadsampsqrd = shadowsamps*shadowsamps;
}

// destructor
Camera::~Camera(){}

//operloaded op=
Camera& Camera::operator= (const Camera& c) {
	
	if (this == &c)
		return (*this);
    
    eye = c.eye;
    focal = c.focal;
    nx = c.nx;
    ny = c.ny;
    l = c.l;
    r = c.r;
    b = c.b;
    t = c.t;
    u = c.u;
    v = c.v;
    w = c.w;
    raysamps = c.raysamps;
    shadowsamps = c.shadowsamps;
    raysampsqrd = raysamps*raysamps;
    shadsampsqrd = shadowsamps*shadowsamps;
    
    
	return (*this);
}


/* * * * * * * * * * * *
 Primary Ray Generation
 * * * * * * * * * * * */

Ray Camera::makeRay(float i, float j) const{
    float u_pxl =  l + (r - l) * (i + .05) / nx;
    float v_pxl = t + (b - t) * (j + .05) / ny;
    
    myVector tempW = -focal*w;
    myVector tempU = u_pxl*u;
    
    myVector tempV = v_pxl*v;
    
    myVector tempTotal = tempW + tempU + tempV;
    
    tempTotal.normalize();
    
    Ray camRay = Ray(eye, tempTotal);
    camRay.normalize();
    
    return camRay;
    
    
}


/* * * * * * * * * * * *
 Render Scene
 * * * * * * * * * * * */

void Camera::renderScene(std::vector<Surface *> surfaces,
                         std::vector<Light *> lights,
                         Array2D<Imf::Rgba> &pixels){
    
    std::cout << "rendering" << std::flush;
    int printProgress = ny * nx / 10.0;
    Rgb current = Rgb(0,0,0);
    
    for (int y = 0; y < ny; ++y) {
        for (int x = 0; x < nx; ++x) {
            
            Imf::Rgba &px = pixels[y][x];  // get the pixel desired
            
            if ((y * ny + x) % printProgress == 0) std::cout << "." << std::flush;
            
            //color it black for starters
            px.r = 0;
            px.b = 0;
            px.g = 0;
            px.a = 1;
            
            if (raysamps == 1){
                Ray primRay = makeRay(x,y); //make primary ray through pixel
                current = L(primRay, 0, INFINITY, 5, 0, *lights.front(), lights, surfaces);
                
            }
            
            else {
                
                float temp_x, temp_y;
                
                for (int p = 0; p < raysamps; ++p){
                    for (int q = 0; q < raysamps; q++){
                        double rando1 = ((double) rand() / (RAND_MAX));
                        double rando2 = ((double) rand() / (RAND_MAX));
                        float i_offset = (p + rando1)/raysamps;
                        float j_offset = (q + rando2)/raysamps;
                        temp_x = x + i_offset;
                        temp_y = y + j_offset;
                        Ray primRay = makeRay(temp_x,temp_y); //make primary ray through pixel
                        current = current + L(primRay, 0, INFINITY, 3, 0, *lights.front(), lights, surfaces);
                    }
                }
                
                current.r = current.r/raysampsqrd;
                current.g = current.g/raysampsqrd;
                current.b = current.b/raysampsqrd;
            }
            
            px.r = current.r;
            px.g = current.g;
            px.b = current.b;
            px.a = 1;
            
        }
        
    }
    
    std::cout << "done!" << std::endl;
    
    
}

Rgb Camera::L (Ray in_ray, float min_t, float max_t, int recurse_limit, int ray_type, Light lite, std::vector<Light *> lights, std::vector<Surface *> surfaces){
    
    Rgb zero_rgb = Rgb();
    Rgb current_rgb = Rgb();
    Rgb shadow_col = Rgb();
    zero_rgb.r = 0;
    zero_rgb.g = 0;
    zero_rgb.b = 0;
    current_rgb.r = 0;
    current_rgb.g = 0;
    current_rgb.b = 0;
    
    //recursion limit met
    if (recurse_limit == 0){
        return zero_rgb;
    }
    
    //shadow ray
    if (ray_type == 1){ // SHADOW RAY
        
        for(std::vector<Surface *>::iterator s_it = surfaces.begin();
            s_it != surfaces.end(); ++s_it){
            Surface *surf = *s_it;
            
            Intersection curr = surf->getIntersection(in_ray);
            if (curr.isIntersected) {
                //check to see if it's before or after the light
                
                if (max_t > curr.t){
                    return zero_rgb;
                }
                
            }
        }
        
        Rgb literr = Rgb((lights.front())->r, (lights.front())->g, (lights.front())->b);
        return literr;
        
    }
    
    
    
    // normal ray-scene intersection
    // get closest intersection with scene, if none return 0 0 0
    Surface hitSurface = *surfaces[0];
    bool isHit = false;
    myVector surfNorm;
    for(std::vector<Surface *>::iterator s_it = surfaces.begin();
        s_it != surfaces.end(); ++s_it){
        Surface *surf = *s_it;
        
        Intersection curr = surf->getIntersection(in_ray);
        if (curr.isIntersected) {
            if (curr.t < max_t){
                if (curr.t > .00001){
                    max_t = curr.t;
                    hitSurface = *surf;
                    isHit = true;
                    surfNorm = curr.geomNorm;
                    surfNorm.normalize();
                }
            }
        }
    }
    
    
    //no intersection
    if (!isHit){
        return zero_rgb;
    }
    
    float kdr = hitSurface.matInfo.dr;
    float kdg = hitSurface.matInfo.dg;
    float kdb = hitSurface.matInfo.db;
    float ksr = hitSurface.matInfo.sr;
    float ksg = hitSurface.matInfo.sg;
    float ksb = hitSurface.matInfo.sb;
    
    float inters_x = (in_ray.origin).x + ((in_ray.direction).x)*(max_t - .0001);
    float inters_y = (in_ray.origin).y + ((in_ray.direction).y)*(max_t- .0001);
    float inters_z = (in_ray.origin).z + ((in_ray.direction).z)*(max_t- .0001);
    Point intersP = Point(inters_x,inters_y,inters_z);
    
    //iterate over lights
    for(std::vector<Light *>::iterator l_it = lights.begin();
        l_it != lights.end(); ++l_it){
        Light *cur_lite = *l_it;
        
        Point lightSource;
        myVector lightvect;
        Ray s_ray;
        float t_light;
        int zero = int(0);
        bool inShadow = false;
        
        // first check for shadows
        
        if (cur_lite->type != 4){
            
            lightSource = Point(cur_lite->x, cur_lite->y, cur_lite->z);
            lightvect = myVector(lightSource, intersP);
            lightvect.normalize();
            
            // check for shadows
            s_ray = Ray(intersP, lightvect);
            
            t_light = (lightSource.x - (s_ray.origin).x)/((s_ray.direction).x);
            
            shadow_col = L(s_ray, 0.0001, t_light, 1, 1, *cur_lite, lights, surfaces);
            
            if ((shadow_col.r == 0) && (shadow_col.g == 0) && (shadow_col.b == 0)){
                inShadow = true;
            }
            
        }
        
        //if area light, soft shadows
        else {
            
            float lit_len = cur_lite->length;
            myVector li_u = cur_lite->uVec;
            myVector li_v = cur_lite->litVec;
            
            for (int i = 0; i < shadowsamps; i++){
                
                double ru = ((double) rand() / (RAND_MAX));
                double rv = ((double) rand() / (RAND_MAX));
                
                lightSource = Point(cur_lite->x, cur_lite->y, cur_lite->z);
                
                Point liteSrc = lightSource + (cur_lite->uVec)*lit_len*(ru-.5) + (cur_lite->litVec)*lit_len*(rv-.5);
                
                lightvect = myVector(liteSrc, intersP);
                lightvect.normalize();
                
                // check for shadows
                s_ray = Ray(intersP, lightvect);
                
                t_light = (liteSrc.x - (s_ray.origin).x)/((s_ray.direction).x);
                
                Rgb temp_shadcol = Rgb();
                
                temp_shadcol = L(s_ray, 0.0001, t_light, 1, 1, *cur_lite, lights, surfaces);
                
                if ((temp_shadcol.r == 0)
                    && (temp_shadcol.g == 0) && (temp_shadcol.b == 0)){
                    inShadow = true;
                }
                
                shadow_col = shadow_col + temp_shadcol;
            }
            
            shadow_col.r = (shadow_col.r/shadowsamps)/(cur_lite->r);
            shadow_col.g = shadow_col.g/shadowsamps/(cur_lite->g);
            shadow_col.b = shadow_col.b/shadowsamps/(cur_lite->b);
            
        }
        
        
        // if not in shadow, compute specular, etc etc
        
        float cur_r = 0;
        float cur_g = 0;
        float cur_b = 0;
        
        //compute lighting as normal
        switch((int) cur_lite->type){
            case 1: {  // point light source
                surfNorm.normalize();
                float dotprod = dot(surfNorm, lightvect);
                float angle = fmax(zero,dotprod);
                float invdistsq = 1/(dist2(intersP, lightSource));
                cur_r += invdistsq*kdr*angle*(cur_lite->r);
                cur_g += invdistsq*kdg*angle*(cur_lite->g);
                cur_b += invdistsq*kdb*angle*(cur_lite->b);
                
                
                // phong part
                myVector vplusl = (-1*(in_ray.direction)) + lightvect;
                float lengthof = vplusl.length();
                myVector bisect = vplusl/lengthof;
                bisect.normalize();
                
                dotprod = dot(surfNorm, bisect);
                angle = fmax(zero,dotprod);
                float exp = hitSurface.matInfo.r;
                float angle_phong = pow(angle, exp);
                cur_r += ksr*angle_phong;
                cur_g += ksg*angle_phong;
                cur_b += ksb*angle_phong;
                
            }
                break;
            case 2: { //directional
                
            }
                break;
            case 3: { //ambient
                cur_r += (cur_lite->r)*kdr;
                cur_b += (cur_lite->b)*kdb;
                cur_g += (cur_lite->g)*kdg;
            }
                break;
                
            case 4: { // area light
                      // get a sample like a point source
                
                surfNorm.normalize();
                float lit_len = cur_lite->length;
                myVector li_u = cur_lite->uVec;
                myVector li_v = cur_lite->litVec;
                Rgb temp;
                
                if (raysamps == 1){
                    
                    double ru = ((double) rand() / (RAND_MAX));
                    double rv = ((double) rand() / (RAND_MAX));
                    
                    Point liteSrc = lightSource + (cur_lite->uVec)*lit_len*(ru-.5) + (cur_lite->litVec)*lit_len*(rv-.5);
                    lightvect = myVector(liteSrc, intersP);
                    lightvect.normalize();
                    
                    float dotprod = dot(surfNorm, lightvect);
                    float angle = fmax(zero,dotprod);
                    float invdistsq = 1/(dist2(intersP, lightSource));
                    cur_r += invdistsq*kdr*angle*(cur_lite->r);
                    cur_g += invdistsq*kdg*angle*(cur_lite->g);
                    cur_b += invdistsq*kdb*angle*(cur_lite->b);
                    
                    // phong part
                    myVector vplusl = (-1*(in_ray.direction)) + lightvect;
                    float lengthof = vplusl.length();
                    myVector bisect = vplusl/lengthof;
                    bisect.normalize();
                    
                    dotprod = dot(surfNorm, bisect);
                    angle = fmax(zero,dotprod);
                    float exp = hitSurface.matInfo.r;
                    float angle_phong = pow(angle, exp);
                    cur_r += ksr*angle_phong;
                    cur_g += ksg*angle_phong;
                    cur_b += ksb*angle_phong;
                    
                }
                else {
                    for (int i = 0; i < raysamps; i++){
                        double ru = ((double) rand() / (RAND_MAX));
                        double rv = ((double) rand() / (RAND_MAX));
                        
                        Point liteSrc = lightSource + (cur_lite->uVec)*lit_len*(ru-.5) + (cur_lite->litVec)*lit_len*(rv-.5);
                        lightvect = myVector(liteSrc, intersP);
                        lightvect.normalize();
                        
                        float dotprod = dot(surfNorm, lightvect);
                        float angle = fmax(zero,dotprod);
                        float invdistsq = 1/(dist2(intersP, lightSource));
                        cur_r += invdistsq*kdr*angle*(cur_lite->r);
                        cur_g += invdistsq*kdg*angle*(cur_lite->g);
                        cur_b += invdistsq*kdb*angle*(cur_lite->b);
                        
                        // phong part
                        myVector vplusl = (-1*(in_ray.direction)) + lightvect;
                        float lengthof = vplusl.length();
                        myVector bisect = vplusl/lengthof;
                        bisect.normalize();
                        
                        dotprod = dot(surfNorm, bisect);
                        angle = fmax(zero,dotprod);
                        float exp = hitSurface.matInfo.r;
                        float angle_phong = pow(angle, exp);
                        cur_r += ksr*angle_phong;
                        cur_g += ksg*angle_phong;
                        cur_b += ksb*angle_phong;
                    }
                    
                    cur_r = cur_r/raysamps;
                    cur_g = cur_g/raysamps;
                    cur_b = cur_b/raysamps;
                }
                
            }
                break;
                
        }
        
        //        current_rgb.r += cur_r;
        //        current_rgb.g += cur_g;
        //        current_rgb.b += cur_b;
        
        
        if (!inShadow){
            current_rgb.r += cur_r;
            current_rgb.g += cur_g;
            current_rgb.b += cur_b;
        }
        
        else {
            current_rgb.r = cur_r*(shadow_col.r);
            current_rgb.g = cur_g*(shadow_col.g);
            current_rgb.b = cur_b*(shadow_col.b);
        }
        
    }
    
    // if material has no reflectivity
    if ((hitSurface.matInfo.ir == 0)
        && (hitSurface.matInfo.ig == 0)
        && (hitSurface.matInfo.ib == 0)){
        return current_rgb;
    }
    else {
        Ray ref_ray;
        myVector d = in_ray.direction; // is this right?
        float d_dot_n = dot(d, surfNorm);
        float twoxddn = 2*d_dot_n;
        myVector two_ddn_n = twoxddn*surfNorm;
        myVector refl_direction = d - two_ddn_n;
        
        ref_ray = Ray(intersP, refl_direction);
        //compute reflected ray
        Rgb reflect_rgb = L(ref_ray, .0001, INFINITY, recurse_limit - 1, 0, lite, lights, surfaces);
        Rgb final_rgb = Rgb();
        final_rgb.r = current_rgb.r + (hitSurface.matInfo.ir)*(reflect_rgb.r);
        final_rgb.g = current_rgb.g + (hitSurface.matInfo.ig)*(reflect_rgb.g);
        final_rgb.b = current_rgb.b + (hitSurface.matInfo.ib)*(reflect_rgb.b);
        
        
        return final_rgb;
    }
    
    return zero_rgb;
    
}


void Camera::writeImage(char* filename, const Imf::Rgba *pixels){
    
    try {
        
        Box2i displayWindow (V2i (0,0), V2i (nx-1,ny-1));
        Box2i dataWindow = displayWindow;
        RgbaOutputFile file(filename, displayWindow, dataWindow, WRITE_RGBA);
        file.setFrameBuffer(pixels, 1, nx);
        file.writePixels(dataWindow.max.y - dataWindow.min.y + 1);
        
    }
    catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl; }
    
}



