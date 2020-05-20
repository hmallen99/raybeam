#pragma once
#include "object.h"

class dummyObject : public object {
    public:
        dummyObject() {

        }
        bool intersect(ray* r, vec3 &pHit, vec3 &nHit) {
            nHit = vec3();
            pHit = vec3();
            return true;
        }
};