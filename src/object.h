#pragma once
#include "vec3.h"
#include "ray.h"
#include "material.h"

class object
{
private:
    material* mat;
public:
    virtual bool intersect(ray* r, std::shared_ptr<vec3> &pHit, std::shared_ptr<vec3> &nHit) = 0;
    material* getMaterial() {return mat;}
    void setMaterial(material* m) {
        mat = m;
    }
};
