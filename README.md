raytramaz
=========

![A physically incorrect Newton's Cradle made in Raytra](http://i.imgur.com/AIe0M.gif)

A raytracer from scratch in C++. Developed for COMS 4160 - Computer Graphics

### features:
+ monte carlo raytracing of spheres, triangles, and planes
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
+ directional light

### timeline:
week 5: monte-carlo methods, area lighting

week 4: reflection

week 3: triangles, planes, and shadows

week 2: basic surface shading

week 1: simple raytracing of spheres
