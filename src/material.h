#pragma once
#include "vec3.h"

class material {
    public:
        virtual vec3  getColor() = 0;
        virtual ray* getOutRay(ray* in, vec3  origin, vec3 normal) = 0;

        vec3 refract(vec3 v, vec3 n, double ref_idx) {
            v = v.normalize();
            double cosine_val = vec3::dot(-v, n);
            double k = 1 - ref_idx * ref_idx * (1 - cosine_val * cosine_val);
            
            vec3 refrdir = v.mul(ref_idx).add(n.mul(ref_idx * cosine_val - sqrt(k)));
            return refrdir.normalize();
        }

        vec3 reflect(vec3 v, vec3 n) {
            return vec3::sub(v, n.mul(2 * vec3::dot(v, n)));
        }
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

class dielectric : public material {
    private:
        vec3 color;
        double refractiveIndex;
        

    public:
        dielectric(vec3 rgb, double r) {
            color = rgb;
            refractiveIndex = r;
        }

        ray* getOutRay(ray* in, vec3 origin, vec3 normal) {
            double ref_idx;
            if (vec3::dot(normal, in->direction()) < 0) {
                ref_idx = 1.0 / refractiveIndex;
                //normal = -normal;
            }
            else {
                ref_idx = refractiveIndex;
                
                
            }
            vec3 refracted = refract(in->direction(), normal, ref_idx);
            vec3 reflected = reflect(in->direction(), normal);
            return new ray(origin, refracted);
        }
        
        vec3 getColor() {
            return color;
        }
};

