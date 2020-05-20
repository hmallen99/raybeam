#pragma once
#include "vec3.h"
#include "ray.h"

class camera {
public:
	camera() {
		lower_left_corner = vec3(-2.0, -1.0, -1.0);
		horizontal = vec3(4.0, 0.0, 0.0);
		vertical = vec3(0.0, 2.0, 0.0);
		origin = vec3(0.0, 0.0, 0.0);
	}
    camera(vec3 o) {
		lower_left_corner = vec3(-2.0, -1.0, -1.0);
		horizontal = vec3(4.0, 0.0, 0.0);
		vertical = vec3(0.0, 2.0, 0.0);
		origin = o;
	}

	ray* getRay(float u, float v) {
		vec3 direction = lower_left_corner.add(horizontal.mul(u)).add(vertical.mul(v)).sub(origin);
		return new ray(origin, direction); 
		
	}

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

    //TODO: void moveTo(vec3()) -> move origin and lower left corner in parallel
    //TODO: void rotate(double radians?) -> move lower_left_corner
};