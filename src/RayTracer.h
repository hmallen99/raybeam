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
#include <omp.h>
//#include <GL/freeglut.h>
#include <stdint.h>



class RayTracer {
    private:
        camera* cam;
        int width;
        int height;
        int spp;
        int** frame;
        std::vector<object* > objList;
        vec3 intersect(ray* r, int depth);
        int maxDepth;
        light* lt;


    public:
        RayTracer(camera* c, light* l, int h, int w);
        ~RayTracer();
        void writeframe();
        int** getFrame();
        void trace();
        void drawGL();
        void addObject(object* obj) {
            objList.push_back(obj);
        }
        void testVec(ray* in) {
            intersect(in, 0);
        }


};

RayTracer::RayTracer(camera* c, light* l, int h, int w) {
    cam = c;
    height = h;
    width = w;
    lt = l;
    frame = new int* [h * w];
    maxDepth = 50;
    spp = 50;
    objList = std::vector<object*>();
}

RayTracer::~RayTracer() {
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
    const int numThreads = 8;
    
    int*** pixels = new int**[numThreads];
    int countPix[numThreads];
    for (int i = 0; i < numThreads; i++) {
        pixels[i] = new int*[width*height/numThreads];
        countPix[i] = 0;
    }
    omp_set_num_threads(numThreads);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        #pragma omp for
        for (int j = height - 1; j >= 0; j--) {
            for (int i = 0; i < width; i++) {
                vec3 color = vec3();
                for (int s = 0; s < spp; s++) {
                    float u = (float(i) + random::drand48()) / float(width);
                    float v = (float(j) + random::drand48()) / float(height);
                    ray* r = cam->getRay(u, v);
                    color = color.add(intersect(r, 0));
                    delete r;
                }
                color = color.div(spp);
                pixels[id][countPix[id]] = new int[3];
                pixels[id][countPix[id]][0] = int(color.getx() * 255);
                pixels[id][countPix[id]][1] = int(color.gety() * 255);
                pixels[id][countPix[id]][2] = int(color.getz() * 255);
                countPix[id]++;
            
            }
        }
    }
    std::cout<<"reached"<<std::endl;
    int pix = 0;
    for (int i = 0; i < numThreads; i++) {
        for(int j = 0; j < width*height/numThreads; j++) {
            frame[pix] = pixels[i][j];
            pix++;
        }
    }
}


vec3 RayTracer::intersect(ray* r, int depth) {
    if (depth >= maxDepth) {
        return vec3();
    }
    double minDist = DBL_MAX;
    int objNum  = -1;
    vec3 minPHit = vec3();
    vec3 minNHit = vec3();
    int numObjects = objList.size();
    for (int i = 0; i < numObjects; i++) {
        vec3 pHit;
        vec3 nHit;
        if (objList[i]->intersect(r, pHit, nHit)) {
            vec3 toCam = vec3::sub(pHit, r->origin());
            double t = toCam.l2norm();
            if (t < minDist) {
                minPHit = pHit;
                minNHit = nHit;
                minDist = t;
                objNum = i;
            }
        }
    }
    if (objNum < 0) {
        double t = 0.5 * r->direction().normalize().gety() + 1;
        return vec3((1.0 - t), (1.0 - t), (1.0 - t)).add(vec3(t *0.5, t * 0.7, t));
    }
    minNHit = minNHit.normalize();
    ray* outRay = objList[objNum]->getMaterial()->getOutRay(r, minPHit, minNHit);
    vec3 tempIntersect = intersect(outRay, depth + 1);
    vec3 retColor = objList[objNum]->getMaterial()->getColor().mul(tempIntersect);
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

void RayTracer::drawGL() {
    uint8_t* pixels = new uint8_t[width*height*3];
    int count = 0;
    for (int i = 0; i < width * height; i++) {
        pixels[count] = uint8_t(frame[i][0]);
        pixels[count + 1] = uint8_t(frame[i][1]);
        pixels[count + 2] = uint8_t(frame[i][2]);
        count += 3;
    }
    std::cout<< "Reached" <<std::endl;
    
    //glDrawPixels(width, height, GL_UNSIGNED_BYTE, GL_RGB, pixels);
}