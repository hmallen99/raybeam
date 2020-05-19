#pragma once
#include "vec3.h"
#include "ray.h"

class camera {
public:
	camera() {
		lower_left_corner = std::make_shared<vec3>(-2.0, -1.0, -1.0);
		horizontal = std::make_shared<vec3>(4.0, 0.0, 0.0);
		vertical = std::make_shared<vec3>(0.0, 2.0, 0.0);
		origin = std::make_shared<vec3>(0.0, 0.0, 0.0);
	}
    camera(std::shared_ptr<vec3> o) {
		lower_left_corner = std::make_shared<vec3>(-2.0, -1.0, -1.0);
		horizontal = std::make_shared<vec3>(4.0, 0.0, 0.0);
		vertical = std::make_shared<vec3>(0.0, 2.0, 0.0);
		origin = std::move(o);
	}

	ray* getRay(float u, float v) { return new ray(origin, lower_left_corner->add(horizontal->mul(u))->add(vertical->mul(v))->sub(origin)); }

	std::shared_ptr<vec3> origin;
	std::shared_ptr<vec3>  lower_left_corner;
	std::shared_ptr<vec3>  horizontal;
	std::shared_ptr<vec3>  vertical;

    //TODO: void moveTo(vec3()) -> move origin and lower left corner in parallel
    //TODO: void rotate(double radians?) -> move lower_left_corner
};