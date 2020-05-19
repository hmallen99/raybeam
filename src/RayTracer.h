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
#include "random.h"
#include <memory>



class RayTracer {
    private:
        camera* cam;
        int width;
        int height;
        int spp;
        int** frame;
        std::vector<object* > objList;
        std::shared_ptr<vec3> intersect(ray* r, int depth);
        std::shared_ptr<vec3> minPHit;
        std::shared_ptr<vec3> minNHit;
        std::shared_ptr<vec3> pHit;
        std::shared_ptr<vec3> nHit;
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
    maxDepth = 25;
    spp = 10;
    objList = std::vector<object*>();
}

int** RayTracer::getFrame() {
    return frame;
}

void RayTracer::trace() {
    int pix = 0;
    ray* r;
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            std::shared_ptr<vec3> color = std::make_shared<vec3>();
            for (int s = 0; s < spp; s++) {
                float u = (float(i) + random::drand48()) / float(width);
                float v = (float(j) + random::drand48()) / float(height);
                r = cam->getRay(u, v);
                color = color->add(intersect(r, 0));
            }
            color = color->div(spp);
            frame[pix] = new int[3];
            frame[pix][0] = int(color->getx() * 255);
            frame[pix][1] = int(color->gety() * 255);
            frame[pix][2] = int(color->getz() * 255);
            pix++;
        }
    }
}


std::shared_ptr<vec3> RayTracer::intersect(ray* r, int depth) {
    if (depth >= maxDepth) {
        return std::make_shared<vec3>();
    }
    double minDist = DBL_MAX;
    std::shared_ptr<vec3> color;
    int objNum  = -1;
    for (int i = 0; i < objList.size(); i++) {
        if (objList[i]->intersect(r, pHit, nHit)) {
            double t = vec3::sub(pHit, cam->origin)->l2norm();
            if (t < minDist) {
                minPHit = std::move(pHit);
                minNHit = std::move(nHit);
                minDist = t;
                objNum = i;
            }
        }
    }
    if (objNum < 0) {
        return lt->getColor();
    }
    minNHit = minNHit->normalize();
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