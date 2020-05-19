#pragma once
#include "vec3.h"

class material {
    public:
        virtual std::shared_ptr<vec3> getColor() = 0;
        virtual ray* getOutRay(std::shared_ptr<vec3> origin, std::shared_ptr<vec3> normal) = 0;
};


class lambertian : public material {
    private:
        std::shared_ptr<vec3> color;
    public:
        lambertian(std::shared_ptr<vec3> rgb) {
            color = std::move(rgb);
        }
        ray* getOutRay(std::shared_ptr<vec3> origin, std::shared_ptr<vec3> normal) {
            return new ray(origin, normal->add(vec3::randomVec()));
        }
        std::shared_ptr<vec3> getColor() {return color;}
};