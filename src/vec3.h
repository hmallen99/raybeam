#pragma once
#include <math.h>
#include <memory>

class vec3 {
    private:
        double x;
        double y;
        double z;
    
    public:
        vec3();
        vec3(double xc, double yc, double zc) {
            x = xc;
            y = yc;
            z = zc;
        }

        double getx() {return x;}
        double gety() {return y;}
        double getz() {return z;}

        static std::shared_ptr<vec3> add(std::shared_ptr<vec3> a, std::shared_ptr<vec3> b);
        static std::shared_ptr<vec3> sub(std::shared_ptr<vec3> a, std::shared_ptr<vec3> b);
        static std::shared_ptr<vec3> cross(std::shared_ptr<vec3> a, std::shared_ptr<vec3> b);
        static double dot(std::shared_ptr<vec3> a, std::shared_ptr<vec3> b);

        std::shared_ptr<vec3> add(std::shared_ptr<vec3> b);
        std::shared_ptr<vec3> sub(std::shared_ptr<vec3> b);
        std::shared_ptr<vec3> mul(double c);
        std::shared_ptr<vec3> mul(std::shared_ptr<vec3> b);
        std::shared_ptr<vec3> div(double c);
        std::shared_ptr<vec3> normalize();
        double l2norm();
        
        static std::shared_ptr<vec3> randomVec();

        vec3 operator-();
    
};

vec3::vec3() {
    x = 0;
    y = 0;
    z = 0;
}

std::shared_ptr<vec3>vec3::add(std::shared_ptr<vec3> a, std::shared_ptr<vec3> b) {
    return std::make_shared<vec3>(a->getx() + b->getx(), a->gety() + b-> gety(), a->getz() + b->getz());
}

std::shared_ptr<vec3> vec3::sub(std::shared_ptr<vec3> a, std::shared_ptr<vec3> b) {
    return std::make_shared<vec3>(a->getx() - b->getx(), a->gety() - b-> gety(), a->getz() - b->getz());
}

std::shared_ptr<vec3> vec3::cross(std::shared_ptr<vec3> a, std::shared_ptr<vec3> b) {
    double i = (a->gety() * b->getz()) - (a->getz() * b->gety());
    double j = (a->getz() * b->getx()) - (a->getx() * b->getz());
    double k = (a->getx() * b->gety()) - (a->gety() * b->getx());
    return std::make_shared<vec3>(i, j, k);
}

double vec3::dot(std::shared_ptr<vec3> a, std::shared_ptr<vec3> b) {
    return a->getx()* b->getx() + a->gety()*b->gety() + a->getz()*b->getz();
}

std::shared_ptr<vec3> vec3::add(std::shared_ptr<vec3> b) {
    return std::make_shared<vec3>(x + b->getx(), y + b->gety(), z + b->getz());
}

std::shared_ptr<vec3> vec3::sub(std::shared_ptr<vec3> b) {
    return std::make_shared<vec3>(x - b->getx(), y - b->gety(), z - b->getz());
}

std::shared_ptr<vec3> vec3::mul(double c) {
    return std::make_shared<vec3>(x * c, y * c, z * c);
}

std::shared_ptr<vec3> vec3::mul(std::shared_ptr<vec3> b) {
    return std::make_shared<vec3>(x * b->getx(), y * b->gety(), z * b->getz());
}


std::shared_ptr<vec3> vec3::div(double c) {
    return std::make_shared<vec3>(x / c, y / c, z / c);
}



double vec3::l2norm() {
    return sqrt(x*x + y*y + z*z);
}


vec3 vec3::operator-() {
    return vec3(-x, -y, -z);
}

std::shared_ptr<vec3> vec3::randomVec() {
    double x = double(rand()) / double(RAND_MAX);
    double y = double(rand()) / double(RAND_MAX);
    double z = double(rand()) / double(RAND_MAX);
    return vec3::sub(std::make_shared<vec3>(x * 2, y * 2, z * 2), std::make_shared<vec3>(1, 1, 1));
}

std::shared_ptr<vec3> vec3::normalize() {
    return this->div(this->l2norm());
}
