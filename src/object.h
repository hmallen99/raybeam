#pragma once
#include "vec3.h"
#include "ray.h"

class object
{
private:
public:
    virtual bool intersect(ray* r, vec3* pHit, vec3* nHit) = 0;
};
