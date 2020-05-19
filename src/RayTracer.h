#pragma once
#include <iostream>
#include <vector>
#include "vec3.h"
#include "ray.h"
#include "object.h"
#include "triangle.h"
#include "sphere.h"
#include "camera.h"
#include "light.h"
#include <fstream>
#include <float.h>



class RayTracer {
    private:
        camera* cam;
        int width;
        int height;
        int** frame;
        std::vector<object* > objList;
        vec3* intersect(ray* r, int depth);
        int maxDepth;
        light* lt;


    public:
        RayTracer(camera* c, light* l, int h, int w);
        void writeframe();
        int** getFrame();
        void trace();
        void addObject(object* obj) {
            objList.push_back(obj);
        }

};

RayTracer::RayTracer(camera* c, light* l, int h, int w) {
    cam = c;
    height = h;
    width = w;
    lt = l;
    frame = new int* [h * w];
    maxDepth = 50;
    objList = std::vector<object*>();
}

int** RayTracer::getFrame() {
    return frame;
}

void RayTracer::trace() {
    vec3* pHit = new vec3();
    vec3* nHit = new vec3();
    int pix = 0;
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            ray* r = cam->getRay(u, v);
            vec3* color = intersect(r, 0);
            frame[pix] = new int[3];
            frame[pix][0] = int(color->getx() * 255);
            frame[pix][1] = int(color->gety() * 255);
            frame[pix][2] = int(color->getz() * 255);
            pix++;
        }
    }
}


vec3* RayTracer::intersect(ray* r, int depth) {
    if (depth >= maxDepth) {
        return new vec3();
    }
    double minDist = DBL_MAX;
    vec3* minPHit = new vec3();
    vec3* minNHit = new vec3();
    vec3* pHit = new vec3();
    vec3* nHit = new vec3();
    vec3* color;
    int objNum  = -1;
    for (int i = 0; i < objList.size(); i++) {
        if (objList[i]->intersect(r, pHit, nHit)) {
            double t = vec3::sub(pHit, cam->origin)->l2norm();
            if (t < minDist) {
                minPHit = pHit;
                minNHit = nHit;
                minDist = t;
                objNum = i;
            }
        }
    }
    if (objNum < 0) {
        return lt->getColor();
    }
    ray* outRay = objList[objNum]->getMaterial()->getOutRay(minPHit, minNHit);
    color = objList[objNum]->getMaterial()->getColor()->mul(intersect(outRay, depth + 1));
    return color;
}

void RayTracer::writeframe() {
    std::ofstream out("pic.ppm", std::ios::binary);
    out << "P3\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < width * height; i++) {
        out << frame[i][0] << " " << frame[i][1] << " " << frame[i][2] << "\n";
    }
    out.close();
}