raytramaz
=========

![A physically incorrect Newton's Cradle made in Raytra](http://i.imgur.com/AIe0M.gif)

A raytracer from scratch in C++. Developed for COMS 4160 - Computer Graphics

### features:
+ monte carlo raytracing 
+ spheres, triangles, and planes
+ point, ambient, and area lights
+ reflection and shadow

### prereqs:
+ openEXR, ilmbase, zlib libraries
+ viewer capable of opening exr images (preview on mac, exrdisplay on linux) (or) exr -> png/jpg/gif image converter (exrtools, imagemagick, etc)

### installing:
+ for mac
    g++ -O2 *.cc -I. -I/usr/local/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra
+ linux
    g++ -O2 *.cc -I. -I/usr/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra

### upcoming:
+ speed improvements
+ refraction
+ batch rendering scripts
+ path tracing (!!)
