#pragma once
#include "vec3.h"

class material {
    public:
        virtual vec3  getColor() = 0;
        virtual ray* getOutRay(ray* in, vec3  origin, vec3 normal) = 0;
};


class lambertian : public material {
    private:
        vec3 color;
    public:
        lambertian(vec3  rgb) {
            color = rgb;
        }

        ray* getOutRay(ray* in, vec3 origin, vec3 normal) {
            vec3 r = vec3::randomVec();
            vec3 dirCopy = normal.add(r);
            ray* retRay = new ray(origin, dirCopy);
            return retRay;
        }

        vec3 getColor() {return color;}
};

class metal : public material {
    private:
        vec3 color;
        vec3 reflect(vec3 v, vec3 n) {
            return vec3::sub(v, n.mul(2 * vec3::dot(v, n)));
        }
    public:
        metal(vec3 rgb) {
            color = rgb;
        }
        
        ray* getOutRay(ray* in, vec3 origin, vec3 normal) {
            vec3 reflected = reflect(in->direction(), normal);
            reflected = reflected.normalize();
            return new ray(origin, reflected);
        }

        vec3 getColor() {return color;}

        
};

