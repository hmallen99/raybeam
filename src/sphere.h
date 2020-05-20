#pragma once
#include "object.h"
#include <math.h>
#include <algorithm>
#include "material.h"
#include <memory.h>

class sphere : public object {
    private:
        vec3  center;
        double radius;
        vec3 color;

    public:
        sphere(vec3 c, double r) {
            center = c;
            radius = r;
            color = vec3(1, 1, 1);
            setMaterial(new lambertian(color));
        }
        sphere(vec3 c, double r, material* m) {
            center = c;
            radius = r;
            setMaterial(m);
        }

        ~sphere() {
            deleteMaterial();
        }

        virtual bool intersect (ray* r, vec3  &pHit, vec3  &nHit);
};

bool sphere::intersect(ray* r, vec3  &pHit, vec3  &nHit){
    vec3  oc = vec3::sub(r->origin(), center);

    double a = vec3::dot(r->direction(), r->direction());
    double b = 2 * vec3::dot(oc, r->direction());
    double c = vec3::dot(oc, oc) - (radius * radius);
    double det = b * b - 4 * a * c;
    if (det < 0) {
        
        return false;
    }
    double t1 = (-b + sqrt(det)) / (2*a);
    double t2 = (-b - sqrt(det)) / (2*a);

    if (std::max(t1, t2) < 0) {
        return false;
    }
    double t;
    if (std::min(t1, t2) >= 0) {
        t = std::min(t1, t2);
    }
    else {
        t = std::max(t1, t2);
    }
    pHit = r->getVec3(t);
    vec3 tempNorm = vec3::sub(pHit, center);
    double norm = tempNorm.l2norm();
    nHit = tempNorm.div(norm);
    return true;
}