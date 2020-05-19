#pragma once
#include "object.h"

class plane : object {
    private:
        vec3* normal;
        vec3* point;
    public:
        plane(vec3* p, vec3* n) {
            point = p;
            normal = n;
        }
        ~plane();
        virtual bool intersect(ray* r, vec3* &pHit, vec3* &nHit);
};

bool plane::intersect(ray* r, vec3* &pHit, vec3* &nHit) {
    double t = vec3::dot(vec3::sub(point, r->origin()), normal) / vec3::dot(r->direction(), normal);
    if (t >= 0) {
        nHit = normal;
        pHit = r->getVec3(t);
        return true;
    }
    return false;
}
