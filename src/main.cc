//
//  main.cc
//  raytra 1.2
//
//  Created by amritamaz on 9/24/12.
//  Copyright 2012 coms4160. All rights reserved.
//


#include "main.h"

void
writeRgba (const char fileName[],
           const Rgba *pixels,
           int width,
           int height)
{
    //
    // Write an RGBA image using class RgbaOutputFile.
    //
    //	- open the file
    //	- describe the memory layout of the pixels
    //	- store the pixels in the file
    //
    
    
    RgbaOutputFile file (fileName, width, height, WRITE_RGBA);
    file.setFrameBuffer (pixels, 1, width);
    file.writePixels (height);
}



void
readRgba (const char fileName[],
          Array2D<Rgba> &pixels,
          int &width,
          int &height)
{
    //
    // Read an RGBA image using class RgbaInputFile:
    //
    //	- open the file
    //	- allocate memory for the pixels
    //	- describe the memory layout of the pixels
    //	- read the pixels from the file
    //
    
    RgbaInputFile file (fileName);
    Box2i dw = file.dataWindow();
    
    width  = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;
    pixels.resizeErase (height, width);
    
    file.setFrameBuffer (&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
    file.readPixels (dw.min.y, dw.max.y);
}

int primsamp, shadsamp;

int main (int argc, char *argv[])
{
    
    try{
        
        /* * * * * * * * * * * *
         Read in the Scene File
         * * * * * * * * * * * */
        
        if (argc < 3) {
            cerr << "useage: raytra scenefilename outputimgname" << endl;
            return -1;
        }
        
        char* scenefile = argv[1];
        char* outputimg = argv[2];
        
        if (argc == 5){
            primsamp = atoi(argv[3]);
            shadsamp = atoi(argv[4]);
        }
        else if (argc == 4){
            primsamp = atoi(argv[3]);
            shadsamp = atoi(argv[3]);

        }
        else {
            primsamp = 3;
            shadsamp = 1;
        }
        
        
        cout << "input: " << scenefile << ", " << primsamp << ", " << shadsamp << " and output: " << outputimg << endl;
        Camera mycam = Camera();
        vector<Surface *> surfaces = vector<Surface *>();
        vector<Light *> lights = vector<Light *>();
        
#ifdef IM_DEBUGGING
        cout << "reading " << scenefile << endl;
#endif
        
        // parse the scene file, fill in the camera definition
        // and the list of surfaces (all spheres in this case!
        parseSceneFile(scenefile, mycam, surfaces, lights);
        
        Array2D<Imf::Rgba> p(mycam.ny, mycam.nx);
        assert(surfaces.size() != 0);
        //render the scene:
        mycam.renderScene(surfaces, lights, p);
        
        //save the image:
        mycam.writeImage(outputimg, &p[0][0]);
#ifdef IM_DEBUGGING
        cout << "output img written to " << outputimg << endl;
#endif
        
    }
    
    catch (const std::exception &exc){
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    
    return 0;
    
}



// this is called from the parseSceneFile function, which uses
// it to get the float from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
float getTokenAsFloat (string inString, int whichToken)
{
    
    float thisFloatVal = 0.;    // the return value
    
    if (whichToken == 0) {
        cerr << "error: the first token on a line is a character!" << endl;
        exit (-1);
    }
    
    // c++ string class has no super-easy way to tokenize, let's use c's:
    char *cstr = new char [inString.size () + 1];
    
    strcpy (cstr, inString.c_str());
    
    char *p = strtok (cstr, " ");
    if (p == 0) {
        cerr << "error: the line has nothing on it!" << endl;
        exit (-1);
    }
    
    for (int i = 0; i < whichToken; i++) {
        p = strtok (0, " ");
        if (p == 0) {
            cerr << "error: line is not long enough for token request!" << endl;
            exit (-1);
        }
    }
    
    thisFloatVal = atof (p);
    
    delete[] cstr;
    
    return thisFloatVal;
}


//
// read the scene file.
//
// You'll need a few globals (or add arguments to this function): for the
// list of surfaces (geometric objects like spheres, triangles, planes) and
// another for the lights. These can be of type std::vector. You'll also
// need a global (or other parameter) for the camera.
//
// This should be pretty self-explanatory: it reads through the lines, and
// using the first character figures out what kind of command it is. It
// then calls the "getTokenAsFloat" routine to pull out the needed values.
// NOTE: since different commands take different number of arguments, you
// must take care not to call getTokenAsFloat for an index that is beyond the
// end of the line!
//
// One tricky bit: when a material is read in, we want
// to keep a pointer to it so that for the next geometric object read in ,
// we can add that material to the object. In the code that follows, I use the
// variable "lastSurfaceLoaded" to do that, but the code is commented out since
// I don't know the class names you will be using.
//
// Very minimal error check here. You might improve it slightly, but we'll
// only use "correct" scene files.
//
//
void parseSceneFile (const char *filnam, Camera &thecam, vector<Surface *> &s,
                     vector<Light *> &l)
{
    
    ifstream inFile(filnam);    // open the file
    string line;
    
    if (! inFile.is_open ()) {  // if it's not open, error out.
        cerr << "can't open scene file" << endl;
        exit (-1);
    }
    
    
    // Note: you'll have to keep track of whatever the last material
    // you loaded in was, so you can apply it to any geometry that gets loaded.
    // So here, you'll have something like:
    //
    // myMaterialClass *lastMaterialLoaded = 0;
    // 0 or maybe a default material?
    //
    // and each time you load a new piece of geometry (sphere, triangle, plane)
    // you will set its material to lastMaterialLoaded.
    float x, y, z, r, vx, vy, vz, d, iw, ih;
    int pw, ph;
    vector< int > tris;
    vector< float > verts;
    Material lastMaterialLoaded;

    
    while (! inFile.eof ()) {   // go through every line in file until finished
        
        getline (inFile, line); // get the line
        
        
#ifdef IM_DEBUGGING
        cout << line << endl;
#endif
        
        switch (line[0])  {     // decide which command based on first character
                
                //
                // geometry types:
                //
                // NOTE: whichever type of geo you load in, set its material to
                // be "lastMaterialLoaded"
                //
            case 's': {
                // it's a sphere, load in the parameters
                
                x = getTokenAsFloat (line, 1);
                y = getTokenAsFloat (line, 2);
                z = getTokenAsFloat (line, 3);
                r = getTokenAsFloat (line, 4);
                
                // build your sphere here from the parameters
                // i.e. you must call your sphere constructor and set its position
                // and radius from the above values. You must also put your new
                // sphere into the objects list (which can be global)
                // So something like;
                // mySphereClass *ms = new mySphereClass (x, y, z, r);
                // make a new instance of your sphere class
                // ms->setMaterial (lastMaterialLoaded)
                // objectsList->push_back (ms);
                // objectsList is a global std:vector<surface *> for example.
                
                Sphere *nsphere = new Sphere(x,y,z,r);
                nsphere->setMaterial(lastMaterialLoaded);
                s.push_back( nsphere);
                
#ifdef IM_DEBUGGING
                // if we're debugging, show what we got:
                cout << "got a sphere with ";
                cout << "parameters: " << x << " " << y <<
                " " << z << " " << r << endl;
#endif
            }
                break;
                
                //t x1 y1 z1 x2 y2 z2 x3 y3 z3
            case 't': {
                float x1 = getTokenAsFloat(line, 1);
                float y1 = getTokenAsFloat(line, 2);
                float z1 = getTokenAsFloat(line, 3);
                float x2 = getTokenAsFloat(line, 4);
                float y2 = getTokenAsFloat(line, 5);
                float z2 = getTokenAsFloat(line, 6);
                float x3 = getTokenAsFloat(line, 7);
                float y3 = getTokenAsFloat(line, 8);
                float z3 = getTokenAsFloat(line, 9);
                
                Point p1 = Point(x1,y1,z1);
                Point p2 = Point(x2,y2,z2);
                Point p3 = Point(x3,y3,z3);
                
                Triangle *ntri = new Triangle(p1,p2,p3);
                ntri->setMaterial(lastMaterialLoaded);
                s.push_back(ntri);

            }  // triangle
                break;
                
            case 'p': {
                vx = getTokenAsFloat(line, 1);
                vy = getTokenAsFloat(line, 2);
                vz = getTokenAsFloat(line, 3);
                d = getTokenAsFloat(line, 4);
                myVector vect = myVector(vx, vy, vz);
                
                Plane *nplane = new Plane(vect, d);
                nplane->setMaterial(lastMaterialLoaded);
                s.push_back(nplane);

            }  // plane
                          // plane with normal n and scalar value d: p nx ny nz d
                break;
                
                //
                // camera:
                //
            case 'c':{   // camera
                x = getTokenAsFloat (line, 1);
                y = getTokenAsFloat (line, 2);
                z = getTokenAsFloat (line, 3);
                vx = getTokenAsFloat (line, 4);
                vy = getTokenAsFloat (line, 5);
                vz = getTokenAsFloat (line, 6);
                d = getTokenAsFloat (line, 7);
                iw = getTokenAsFloat (line, 8);
                ih = getTokenAsFloat (line, 9);
                pw = (int) getTokenAsFloat (line, 10);
                ph = (int) getTokenAsFloat (line, 11);
                
                int ps = primsamp;
                int ss = shadsamp;
                
                Camera tempCam = Camera(x, y, z, vx, vy, vz, d, iw, ih, pw, ph, ps, ss);
                thecam = tempCam;
                
            }
                break;
                
                //
                // lights:
                //
            case 'l': {  // light
                
                // slightly different from the rest, we need to
                //examine the second param,
                // which is at the third position on the line:
                // / a point light at position x y z, color & intensity coded as l p x y z r g b
                // a directional light with direction vx vy vz and color & intensity coded as l d vx vy vz r g b
                // the ambient light (there will be, at most, only one of these): l ar g b
                Light *nlight;

                switch (line[2]) {
                        
                    case 'p':   // point light
                    {
                        float lx = getTokenAsFloat (line, 2);
                        float ly = getTokenAsFloat (line, 3);
                        float lz = getTokenAsFloat (line, 4);
                        float lr = getTokenAsFloat (line, 5);
                        float lg = getTokenAsFloat (line, 6);
                        float lb = getTokenAsFloat (line, 7);
                        nlight = new Light(1, lx, ly, lz, lr, lg, lb);
                    }
                        break;
                        
                    case 'd':   // directional light
                    {
                         vx = getTokenAsFloat (line, 2);
                         vy = getTokenAsFloat (line, 3);
                         vz = getTokenAsFloat (line, 4);
                        float lr = getTokenAsFloat (line, 5);
                        float lg = getTokenAsFloat (line, 6);
                        float lb = getTokenAsFloat (line, 7);

                        myVector litvec = myVector(vx, vy, vz);
                        nlight = new Light(2, litvec, lr, lg, lb);
                    }
                        break;
                        
                    case 'a':   // ambient light
                    {
                        float lr = getTokenAsFloat (line, 2);
                        float lg = getTokenAsFloat (line, 3);
                        float lb = getTokenAsFloat (line, 4);
                        nlight = new Light(3, lr, lg, lb);
                    }
                        break;
                        
                    case 's':
                    {
                         x = getTokenAsFloat (line, 2);
                         y = getTokenAsFloat (line, 3);
                         z = getTokenAsFloat (line, 4);
                         vx = getTokenAsFloat (line, 5);
                         vy = getTokenAsFloat (line, 6);
                         vz = getTokenAsFloat (line, 7);
                        
                        myVector litvec = myVector(vx, vy, vz);

                        float ux = getTokenAsFloat (line, 8);
                        float uy = getTokenAsFloat (line, 9);
                        float uz = getTokenAsFloat (line, 10);
                        
                        myVector udirVect = myVector(ux, uy, uz);

                        float len = getTokenAsFloat (line, 11);
                        r = getTokenAsFloat (line, 12);
                        float g = getTokenAsFloat (line, 13);
                        float b = getTokenAsFloat(line, 14);
                        
                        nlight = new Light(4, x,y,z, litvec, udirVect, len, r, g, b);

                    }
                        break;
                }
                
                l.push_back( nlight);
            }
                break;
                
                //
                // materials:
                //
            case 'm':{
                Material m = Material();
                m.dr = getTokenAsFloat (line, 1);
                m.dg = getTokenAsFloat (line, 2);
                m.db = getTokenAsFloat (line, 3);
                m.sr = getTokenAsFloat (line, 4);
                m.sg = getTokenAsFloat (line, 5);
                m.sb = getTokenAsFloat (line, 6);
                m.r = getTokenAsFloat (line, 7);
                m.ir = getTokenAsFloat (line, 8);
                m.ig = getTokenAsFloat (line, 9);
                m.ib = getTokenAsFloat (line, 10);
                lastMaterialLoaded = m;

            }   // material

                
                break;
                
            case 'w':{      // read in an object file
				string newStr = line.substr(2);
				const char * obj_filename = newStr.c_str();
				cout << "Got an obj file: " << obj_filename << endl;
				read_wavefront_file(obj_filename, tris, verts);
				//make triangles, push them onto surfaces vector
                
				
				for(int i = 0; i < (int) tris.size(); i+=3)
				{
					//get vertices numbers
					int v1 = tris[i];
					int v2 = tris[i + 1];
					int v3 = tris[i + 2];
					//cout << "Triangle: " << "(" << v1 << "," << v2 << "," << v3 << ")" << endl;
					
					//get components of v1, v2, v3
					float v1_x = verts[v1 * 3];
					float v1_y = verts[v1 * 3 + 1];
					float v1_z = verts[v1 * 3 + 2];
                    
					float v2_x = verts[v2 * 3];
					float v2_y = verts[v2 * 3 + 1];
					float v2_z = verts[v2 * 3 + 2];
                    
					float v3_x = verts[v3 * 3];
					float v3_y = verts[v3 * 3 + 1];
					float v3_z = verts[v3 * 3 + 2];
					
					//make triangle pointer
                    
                    Point p1 = Point(v1_x, v1_y, v1_z);
                    Point p2 = Point(v2_x, v2_y, v2_z);
                    Point p3 = Point(v3_x, v3_y, v3_z);
					Triangle *ntri = new Triangle(p1, p2, p3);
                    ntri->setMaterial(lastMaterialLoaded);
                    s.push_back(ntri);
				}
                
            }
                break;
            case '/':{}
                // don't do anything, it's a comment
                break;
                
                
                //
                // options
                //
            case 'o': {}  // make your own options if you wish
                break;
        }
        
    }
}

// Given the name of a wavefront (OBJ) file that consists JUST of
// vertices, triangles, and comments, read it into the tris and verts
// vectors.
//
// tris is a vector of ints that is 3*n long, where n is the number of
// triangles. The ith triangle has vertex indexes 3*i, 3*i+1, and 3*i+2.
//
// The ith vertex has components verts[3*i], verts[3*i+1], and verts[3*i+2],
// given in counterclockwise order with respect to the surface normal
//
// If you are using the supplied Parser class, you should probably make this
// a method on it: Parser::read_wavefront_file().
//
void read_wavefront_file (
                          const char *file,
                          std::vector< int > &tris,
                          std::vector< float > &verts)
{
    
    // clear out the tris and verts vectors:
    tris.clear ();
    verts.clear ();
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        cmd="";
        
        istringstream iss (buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='#' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        }
        else if (cmd=="v") {
            // got a vertex:
            
            // read in the parameters:
            double pa, pb, pc;
            iss >> pa >> pb >> pc;
            
            verts.push_back (pa);
            verts.push_back (pb);
            verts.push_back (pc);
        }
        else if (cmd=="f") {
            // got a face (triangle)
            
            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;
            
            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }
        
    }
    
    in.close();
    std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  " << verts.size () / 3.0 << std::endl;
}


