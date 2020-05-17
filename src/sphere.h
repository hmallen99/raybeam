#include "object.h"

class sphere : object {
    private:
        vec3* origin;
        double radius;

    public:
        sphere(vec3* o, double r) {
            origin = o;
            radius = r;
        }
        ~sphere();

        bool intersect(ray* r, vec3* pHit, vec3* nHit);
};

bool sphere::intersect(ray* r, vec3* pHit, vec3* nHit) {
    return false;
}