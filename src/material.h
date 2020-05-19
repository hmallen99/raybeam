#pragma once
#include "vec3.h"

class material {
    private:
        vec3* color;
    public:
        material(vec3* rgb){
            color = rgb;
        }
        material() {
            color = new vec3();
        }
        vec3* getColor() {return color;}
};