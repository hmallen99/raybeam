#pragma once
#include "vec3.h"

class material {
    public:
        virtual vec3*  getColor() = 0;
        virtual ray* getOutRay(vec3*  origin, vec3*  normal) = 0;
};


class lambertian : public material {
    private:
        vec3*  color;
    public:
        lambertian(vec3*  rgb) {
            color = rgb;
        }

        ~lambertian() {
            delete color;
        }

        ray* getOutRay(vec3*  origin, vec3*  normal) {
            vec3* r = vec3::randomVec();
            vec3* origCopy = new vec3(origin);
            vec3* dirCopy = normal->add(r);
            ray* retRay = new ray(origCopy, dirCopy);
            delete r;
            return retRay;
        }

        vec3*  getColor() {return color;}
};