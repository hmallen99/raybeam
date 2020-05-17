#include "object.h"

class triangle : object {
    private:
        vec3* p1;
        vec3* p2;
        vec3* p3;
        vec3* normal;
    public:
        triangle(vec3* point1, vec3* point2, vec3* point3, vec3* n) {
            p1 = point1;
            p2 = point2;
            p3 = point3;
            normal = n;
        }
        ~triangle();

        bool intersect(ray* r, vec3* pHit, vec3* nHit);
};

// source: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool triangle::intersect(ray* r, vec3* pHit, vec3* nHit) {
    vec3* edge1 = vec3::sub(p2, p1);
    vec3* edge2 = vec3::sub(p3, p1);
    vec3* h = vec3::cross(r->direction(), edge2);
    vec3* s = vec3::sub(r->origin, p1);
    double a = vec3::dot(edge1, h);
    double f = 1.0 / a;
    double u = f * vec3::dot(s, h);

    if (u < 0.0 || u > 1.0) {
        return false;
    }
    vec3* q = vec3::cross(s, edge1);
    double v = f * vec3::dot(r->direction(), q);

    if(v < 0.0 || u + v > 1.0) {
        return false;
    }

    nHit = normal;
    double t = f * vec3::dot(edge2, q);
    pHit = r->getVec3(t);
    return true;
}