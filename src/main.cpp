
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

using namespace std;

int main () {
    camera* cam = new camera();
    RayTracer* rt = new RayTracer(cam, 600, 800);
    vector<vec3*> vecList = {
        new vec3(-2, 1, -1),
        new vec3(2, 1, -1),
        new vec3(2, -1, -1),
        new vec3(-2, -1, -1),
        new vec3(-2, -1, -2),
        new vec3(-2, 1, -2),
        new vec3(2, 1, -2),
        new vec3(2, -1, -2)
    };
    material* green = new material(new vec3(0, 255, 0));
    material* blue = new material(new vec3(0, 0, 255));
    material* red = new material(new vec3(255, 0, 0));
    material* yellow = new material(new vec3(255, 255, 0));
    material* white = new material(new vec3(255, 255, 255));
    rt->addObject(new triangle(vecList[0], vecList[5], vecList[3], green));
    rt->addObject(new triangle(vecList[5], vecList[3], vecList[4], green));
    rt->addObject(new triangle(vecList[0], vecList[5], vecList[6], red));
    rt->addObject(new triangle(vecList[0], vecList[1], vecList[6], red));
    rt->addObject(new triangle(vecList[1], vecList[2], vecList[6], blue));
    rt->addObject(new triangle(vecList[2], vecList[7], vecList[6], blue));
    rt->addObject(new triangle(vecList[7], vecList[2], vecList[3], yellow));
    rt->addObject(new triangle(vecList[3], vecList[7], vecList[4], yellow));
    rt->addObject(new triangle(vecList[7], vecList[5], vecList[4], white));
    rt->addObject(new triangle(vecList[7], vecList[6], vecList[5], white));

    rt->trace();
    rt->writeframe();
    return 0;
}