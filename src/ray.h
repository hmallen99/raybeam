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
};

ray::ray(vec3* origin, vec3* direction)
{
    o = origin;
    d = direction;
}

ray::~ray()
{
}
