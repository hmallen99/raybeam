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
        vec3* intersect(ray* r, int depth);
        vec3* minPHit;
        vec3* minNHit;
        vec3* pHit;
        vec3* nHit;
        int maxDepth;
        light* lt;


    public:
        RayTracer(camera* c, light* l, int h, int w);
        ~RayTracer();
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
    spp = 10;
    objList = std::vector<object*>();
}

RayTracer::~RayTracer() {
    delete minPHit;
    delete minNHit;
    delete pHit;
    delete nHit;
    delete lt;
    for (int i = 0; i < width*height; i++) {
        delete frame[i];
    }
    delete frame;
    delete cam;
}

int** RayTracer::getFrame() {
    return frame;
}

void RayTracer::trace() {
    int pix = 0;
    
    
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vec3* color = new vec3();
            
            for (int s = 0; s < spp; s++) {
                
                float u = (float(i) + random::drand48()) / float(width);
                float v = (float(j) + random::drand48()) / float(height);
                ray* r = cam->getRay(u, v);
                vec3* tempColor = intersect(r, 0);
                vec3* oldColor = color;
                color = color->add(tempColor);
                delete oldColor;
                delete tempColor;
                delete r;
            }
            vec3* oldColor = color;
            color = color->div(spp);
            delete oldColor;
            frame[pix] = new int[3];
            frame[pix][0] = int(color->getx() * 255);
            frame[pix][1] = int(color->gety() * 255);
            frame[pix][2] = int(color->getz() * 255);
            if (pix % 1000 == 0) {
                std::cout << pix << std::endl;
            }
            pix++;
            delete color;
        }
    }
    
}


vec3* RayTracer::intersect(ray* r, int depth) {
    if (depth >= maxDepth) {
        return new vec3();
    }
    double minDist = DBL_MAX;
    int objNum  = -1;
    minPHit = new vec3();
    minNHit = new vec3();
    for (int i = 0; i < objList.size(); i++) {
        if (objList[i]->intersect(r, pHit, nHit)) {
            vec3* toCam = vec3::sub(pHit, cam->origin);
            double t = toCam->l2norm();
            delete toCam;
            if (t < minDist) {
                vec3* tempPHit = minPHit;
                vec3* tempNHit = minNHit;
                minPHit = pHit;
                delete tempPHit;
                minNHit = nHit;
                delete tempNHit;
                minDist = t;
                objNum = i;
            }
        }
    }
    if (objNum < 0) {
        vec3* idVec = new vec3(1, 1, 1);
        vec3* retVec = lt->getColor()->mul(idVec);
        delete idVec;
        return retVec;
    }
    vec3* tempNHit = minNHit;
    minNHit = minNHit->normalize();
    delete tempNHit;
    ray* outRay = objList[objNum]->getMaterial()->getOutRay(minPHit, minNHit);
    vec3* tempIntersect = intersect(outRay, depth + 1);
    vec3* retColor = objList[objNum]->getMaterial()->getColor()->mul(tempIntersect);
    delete tempIntersect;
    delete outRay;
    return retColor;
}

void RayTracer::writeframe() {
    std::ofstream out("pic.ppm", std::ios::binary);
    out << "P3\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < width * height; i++) {
        out << frame[i][0] << " " << frame[i][1] << " " << frame[i][2] << "\n";
    }
    out.close();
}