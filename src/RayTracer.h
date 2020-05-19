#pragma once
#include <iostream>
#include <vector>
#include "vec3.h"
#include "ray.h"
#include "object.h"
#include "triangle.h"
#include "sphere.h"
#include "camera.h"
#include <fstream>
#include <float.h>


class RayTracer {
    private:
        camera* cam;
        int width;
        int height;
        int** frame;
        std::vector<object* > objList;
        vec3* intersect(ray* r, vec3* pHit, vec3* nHit);


    public:
        RayTracer(camera* c, int h, int w);
        void writeframe();
        int** getFrame();
        void trace();
        void addObject(object* obj) {
            objList.push_back(obj);
        }

};

RayTracer::RayTracer(camera* c, int h, int w) {
    cam = c;
    height = h;
    width = w;
    frame = new int* [h * w];
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
            vec3* color = intersect(r, pHit, nHit);
            frame[pix] = new int[3];
            frame[pix][0] = color->getx();
            frame[pix][1] = color->gety();
            frame[pix][2] = color->getz();
            pix++;
        }
    }
}


vec3* RayTracer::intersect(ray* r, vec3* pHit, vec3* nHit) {
    double minDist = DBL_MAX;
    vec3* minPHit = new vec3();
    vec3* minNHit = new vec3();
    vec3* color = new vec3(134, 204, 235);
    for (int i = 0; i < objList.size(); i++) {
        if (objList[i]->intersect(r, pHit, nHit)) {
            if (pHit->l2norm() < minDist) {
                minPHit = pHit;
                minNHit = nHit;
                color = objList[i]->getMaterial()->getColor();
            }
        }
    }
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