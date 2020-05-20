#pragma once
#include "vec3.h"
#include "ray.h"
#include "material.h"

class object
{
private:
    material* mat;
    
public:
    virtual bool intersect(ray* r, vec3 &pHit, vec3 &nHit) = 0;
    material* getMaterial() {return mat;}
    void setMaterial(material* m) {
        mat = m;
    }
    void deleteMaterial() {
        delete mat;
    }
    
};
