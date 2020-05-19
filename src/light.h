#pragma once
#include "vec3.h"

class light {
    private:
        std::shared_ptr<vec3> origin;
        std::shared_ptr<vec3> color;
        double brightness;
    public:
        light() {
            origin = std::make_shared<vec3>();
            brightness = 1.0;
            color = std::make_shared<vec3>(1, 1, 1);
        }

        light(std::shared_ptr<vec3> o, double b) {
            brightness = b;
            origin = std::move(o);
            color = std::make_shared<vec3>(1, 1, 1);
        }

        std::shared_ptr<vec3> getColor() {return color;}
};