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
		
		horizontal = vec3(4.0, 0.0, 0.0);
		vertical = vec3(0.0, 2.0, 0.0);
		origin = o;
		lower_left_corner = origin.add(vec3(-2.0, -1.0, -1.0));
	}

	camera(vec3 from, vec3 to) {
		origin  = from;
		vec3 vup = vec3(0, 1, 0);
		double height = 2.0;
		double width = 4.0;
		vec3 w = vec3::sub(from, to).normalize();
		vec3 u = vec3::cross(vup, w).normalize();
		vec3 v = vec3::cross(w, u);
		horizontal = u.mul(width);
		vertical = v.mul(height);
		lower_left_corner = origin.sub(horizontal.div(2.0)).sub(vertical.div(2.0)).sub(w);

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