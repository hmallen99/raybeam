#pragma once
#include "vec3.h"
#include "ray.h"

class camera {
public:
	camera() {
		lower_left_corner = new vec3(-2.0, -1.0, -1.0);
		horizontal = new vec3(4.0, 0.0, 0.0);
		vertical = new vec3(0.0, 2.0, 0.0);
		origin = new vec3(0.0, 0.0, 0.0);
	}
    camera(vec3* o) {
		lower_left_corner = new vec3(-2.0, -1.0, -1.0);
		horizontal = new vec3(4.0, 0.0, 0.0);
		vertical = new vec3(0.0, 2.0, 0.0);
		origin = o;
	}

	~camera() {
		delete origin;
		delete lower_left_corner;
		delete horizontal;
		delete vertical;
	}

	ray* getRay(float u, float v) {
		vec3* hor = horizontal->mul(u);
		vec3* vert = vertical->mul(v);
		vec3* vh = vert->add(hor);
		delete hor;
		delete vert;
		vec3* pos = lower_left_corner->add(vh);
		delete vh;
		vec3* direction = pos->sub(origin);
		delete pos;
		vec3* copyOrigin = new vec3(origin->getx(), origin->gety(), origin->getz()); 
		return new ray(copyOrigin, direction); 
		
	}

	vec3* origin;
	vec3*  lower_left_corner;
	vec3*  horizontal;
	vec3*  vertical;

    //TODO: void moveTo(vec3()) -> move origin and lower left corner in parallel
    //TODO: void rotate(double radians?) -> move lower_left_corner
};