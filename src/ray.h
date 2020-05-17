#include "vec3.h"

class ray
{
private:
    vec3* o;
    vec3* d;

public:
    ray(vec3* origin, vec3* direction);
    ~ray();
    vec3* origin() {return o;}
    vec3* direction() {return d;}
    vec3* getVec3(double t);
};

ray::ray(vec3* origin, vec3* direction)
{
    o = origin;
    d = direction;
}

vec3* ray::getVec3(double t) {
    return vec3::add(o, d->mul(t));
}

ray::~ray()
{
}
