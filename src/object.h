#include "vec3.h"
#include "ray.h"

class object
{
private:
public:
    object();
    ~object();
    bool intersect(ray* r);
};

object::object()
{
}

object::~object()
{
}

bool object::intersect(ray* r) {
    return false;
}
