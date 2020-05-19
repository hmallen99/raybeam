#pragma once
#include "object.h"
#include <math.h>
#include <algorithm>
#include "material.h"
#include <memory.h>

class sphere : public object {
    private:
        std::shared_ptr<vec3> center;
        double radius;

    public:
        sphere(std::shared_ptr<vec3> c, double r) {
            center = std::move(c);
            radius = r;
            setMaterial(new lambertian(std::make_shared<vec3>(1, 1, 1)));
        }
        sphere(std::shared_ptr<vec3> c, double r, material* m) {
            center = std::move(c);
            radius = r;
            setMaterial(m);
        }

        virtual bool intersect (ray* r, std::shared_ptr<vec3> &pHit, std::shared_ptr<vec3> &nHit);
};

bool sphere::intersect(ray* r, std::shared_ptr<vec3> &pHit, std::shared_ptr<vec3> &nHit){
    std::shared_ptr<vec3> oc = vec3::sub(r->origin(), center);

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