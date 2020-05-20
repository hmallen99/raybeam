#pragma once
#include "vec3.h"

class light {
    private:
        vec3* origin;
        vec3* color;
        double brightness;
    public:
        light() {
            origin = new vec3();
            brightness = 1.0;
            color = new vec3(1, 1, 1);
        }

        light(vec3* o, double b) {
            brightness = b;
            origin = o;
            color = new vec3(1, 1, 1);
        }

        ~light() {
            delete origin;
            delete color;
        }

        vec3* getColor() {return color;}
};