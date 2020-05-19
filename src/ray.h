#pragma once
#include "vec3.h"
#include <memory>

class ray
{
private:
    std::shared_ptr<vec3> o;
    std::shared_ptr<vec3> d;

public:
    ray(std::shared_ptr<vec3> origin, std::shared_ptr<vec3> direction);
    ~ray();
    std::shared_ptr<vec3> origin() {return o;}
    std::shared_ptr<vec3> direction() {return d;}
    std::shared_ptr<vec3> getVec3(double t);
};

ray::ray(std::shared_ptr<vec3> origin, std::shared_ptr<vec3> direction)
{
    o = std::move(origin);
    d = std::move(direction);
}

std::shared_ptr<vec3> ray::getVec3(double t) {
    return vec3::add(o, d->mul(t));
}

ray::~ray()
{
}
