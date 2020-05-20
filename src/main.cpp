
#include <iostream>
#include <fstream>
#include <vector>
#include "vec3.h"
#include "ray.h"
#include "object.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "RayTracer.h"
#include "dummyObject.h"


using namespace std;

int main () {
    camera* cam = new camera();
    light* lt = new light();
    RayTracer* rt = new RayTracer(cam, lt, 1080, 1920);
    vector<vec3> vecList = {
        vec3(-2, 1, -1),
        vec3(2, 1, -1),
        vec3(2, -1, -1),
        vec3(-2, -1, -1),
        vec3(-2, -1, -2),
        vec3(-2, 1, -2),
        vec3(2, 1, -2),
        vec3(2, -1, -2)
    };
    material* green = new lambertian(vec3(0, 1, 0));
    material* blue = new lambertian(vec3(0, 0, 1));
    material* red = new lambertian(vec3(1, 0, 0));
    material* yellow = new lambertian(vec3(1, 1, 0));
    material* white = new lambertian(vec3(1, 1, 1));
    rt->addObject(new triangle(vecList[0], vecList[5], vecList[3], green));
    rt->addObject(new triangle(vecList[5], vecList[3], vecList[4], green));
    rt->addObject(new triangle(vecList[0], vecList[5], vecList[6], red));
    rt->addObject(new triangle(vecList[0], vecList[1], vecList[6], red));
    rt->addObject(new triangle(vecList[1], vecList[2], vecList[6], blue));
    rt->addObject(new triangle(vecList[2], vecList[7], vecList[6], blue));
    rt->addObject(new triangle(vecList[7], vecList[2], vecList[3], white));
    rt->addObject(new triangle(vecList[3], vecList[7], vecList[4], white));
    rt->addObject(new triangle(vecList[7], vecList[5], vecList[4], yellow));
    rt->addObject(new triangle(vecList[7], vecList[6], vecList[5], yellow));
    rt->addObject(new sphere(vec3(-1.0, 0, -1), 0.5, blue));
    rt->addObject(new sphere(vec3(1.0, 0, -1), 0.5, green));
    rt->trace();
    
    rt->writeframe();
    
    return 0;
}