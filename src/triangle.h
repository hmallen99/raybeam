#pragma once
#include "object.h"

class triangle : public object {
    private:
        std::shared_ptr<vec3> p1;
        std::shared_ptr<vec3> p2;
        std::shared_ptr<vec3> p3;
        std::shared_ptr<vec3> normal;
    public:
        triangle(std::shared_ptr<vec3> point1, std::shared_ptr<vec3> point2, std::shared_ptr<vec3> point3) {
            p1 = std::move(point1);
            p2 = std::move(point2);
            p3 = std::move(point3);
            setMaterial(new lambertian(std::make_shared<vec3>(1, 1, 1)));
        }

        triangle(std::shared_ptr<vec3> point1, std::shared_ptr<vec3> point2, std::shared_ptr<vec3> point3, material* m) {
            p1 = std::move(point1);
            p2 = std::move(point2);
            p3 = std::move(point3);
            setMaterial(m);
        }
        virtual bool intersect(ray* r, std::shared_ptr<vec3> &pHit, std::shared_ptr<vec3> &nHit);
};

// source: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool triangle::intersect(ray* r, std::shared_ptr<vec3> &pHit, std::shared_ptr<vec3> &nHit) {
    const float eps = 0.00000001;
    std::shared_ptr<vec3> edge1 = vec3::sub(p2, p1);
    std::shared_ptr<vec3> edge2 = vec3::sub(p3, p1);
    normal = vec3::cross(edge1, edge2);
    std::shared_ptr<vec3> h = vec3::cross(r->direction(), edge2);
    
    double a = vec3::dot(edge1, h);
    if (a > eps && a < eps) {
        return false;
    }
    double f = 1.0 / a;
    std::shared_ptr<vec3> s = vec3::sub(r->origin(), p1);
    double u = f * vec3::dot(s, h);

    if (u < 0.0 || u > 1.0) {
        return false;
    }
    std::shared_ptr<vec3> q = vec3::cross(s, edge1);
    double v = f * vec3::dot(r->direction(), q);

    if(v < 0.0 || u + v > 1.0) {
        return false;
    }

    nHit = std::move(normal);
    double t = f * vec3::dot(edge2, q);
    if (t < eps && t > -eps) {
        return false;
    }
    pHit = r->getVec3(t);
    return true;
}