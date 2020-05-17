#include "vec3.h"
#include "ray.h"

class object
{
private:
public:
    object();
    ~object();
    bool intersect(ray* r, vec3* pHit, vec3* nHit);
};

object::object()
{
}

object::~object()
{
}

bool intersect(ray* r, vec3* pHit, vec3* nHit) {
    return false;
}
