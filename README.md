raytramaz
=========

![A physically incorrect Newton's Cradle made in Raytra](http://i.imgur.com/AIe0M.gif)

A raytracer from scratch in C++. A continuation of the raytracer project developed for for COMS 4160 - Computer Graphics

### features:
+ spheres, triangles, and planes
+ point, ambient, and area light sources (w/ soft shadows)
+ jittered monte-carlo antialiasing
+ triangulated meshes (obj file format)
+ axis-aligned bounding boxes for acceleration
+ support models for diffuse and reflective materials
+ direct sampling of area light sources
+ hdr format (.exr)

## upcoming:
+ bvh trees
+ support for glossy and dielectric materials
+ caustics
+ schlick approximation of fresnel equations for dielectric materials
+ uniform & importance sampling of lambertian and phong brdfs
+ depth-of-field
+ batch rendering scripts
+ path tracing

### prereqs:
+ openEXR, ilmbase, zlib libraries
+ viewer capable of opening exr images (preview on mac, exrdisplay on linux) (or) exr -> png/jpg/gif image converter (exrtools, imagemagick, etc)

### installing:
+ for mac
    g++ -O2 *.cc -I. -I/usr/local/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra
+ linux
    g++ -O2 *.cc -I. -I/usr/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra

### how to run:
  raytra scenefile.txt output.exr [numsamples] [numshadowrays] [showbboxes]
