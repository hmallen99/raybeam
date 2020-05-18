#pragma once
#include "object.h"
#include <math.h>
#include <algorithm>

class sphere : public object {
    private:
        vec3* center;
        double radius;

    public:
        sphere(vec3* c, double r) {
            center = c;
            radius = r;
        }
        ~sphere();

        virtual bool intersect (ray* r, vec3* pHit, vec3* nHit);
};

bool sphere::intersect(ray* r, vec3* pHit, vec3* nHit){
    vec3* oc = vec3::sub(r->origin(), center);

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
    nHit = vec3::sub(pHit, center);
    nHit = nHit->div(nHit->l2norm());

    return true;
}