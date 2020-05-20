#pragma once
#include "vec3.h"
#include <memory>

class ray
{
private:
    vec3 o;
    vec3 d;

public:
    ray(vec3 origin, vec3 direction);
    vec3 origin() {return o;}
    vec3 direction() {return d;}
    vec3 getVec3(double t);
};

ray::ray(vec3 origin, vec3 direction)
{
    o = origin;
    d = direction;
}

vec3 ray::getVec3(double t) {
    vec3 dt = d.mul(t);
    vec3 retVec = vec3::add(o, dt);
    return retVec;
}
