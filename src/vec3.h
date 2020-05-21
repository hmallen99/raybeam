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

        static vec3 add(vec3 a, vec3 b);
        static vec3 sub(vec3 a, vec3 b);
        static vec3 cross(vec3 a, vec3 b);
        static double dot(vec3 a, vec3 b);

        vec3 add(vec3 b);
        vec3 sub(vec3 b);
        vec3 mul(double c);
        vec3 mul(vec3 b);
        vec3 div(double c);
        vec3 normalize();
        double l2norm();
        vec3 operator+(vec3 b);
        vec3 operator-(vec3 b);
        vec3 operator*(double c);
        vec3 operator/(double c);
        double dot(vec3 b);
        
        static vec3 randomVec();

        vec3 operator-();
    
};

vec3::vec3() {
    x = 0;
    y = 0;
    z = 0;
}

vec3 vec3::add(vec3 a, vec3 b) {
    return vec3(a.getx() + b.getx(), a.gety() + b. gety(), a.getz() + b.getz());
}

vec3 vec3::sub(vec3 a, vec3 b) {
    return vec3(a.getx() - b.getx(), a.gety() - b. gety(), a.getz() - b.getz());
}

vec3 vec3::cross(vec3 a, vec3 b) {
    double i = (a.gety() * b.getz()) - (a.getz() * b.gety());
    double j = (a.getz() * b.getx()) - (a.getx() * b.getz());
    double k = (a.getx() * b.gety()) - (a.gety() * b.getx());
    return vec3(i, j, k);
}

double vec3::dot(vec3 a, vec3 b) {
    return a.getx() * b.getx() + a.gety() * b.gety() + a.getz() * b.getz();
}

vec3 vec3::add(vec3 b) {
    return vec3(x + b.getx(), y + b.gety(), z + b.getz());
}

vec3 vec3::sub(vec3 b) {
    return vec3(x - b.getx(), y - b.gety(), z - b.getz());
}

vec3 vec3::mul(double c) {
    return vec3(x * c, y * c, z * c);
}

vec3 vec3::mul(vec3 b) {
    return vec3(x * b.getx(), y * b.gety(), z * b.getz());
}


vec3 vec3::div(double c) {
    return vec3(x / c, y / c, z / c);
}



double vec3::l2norm() {
    return sqrt(x*x + y*y + z*z);
}


vec3 vec3::operator-() {
    return vec3(-x, -y, -z);
}

vec3 vec3::randomVec() {
    double x = double(rand()) / double(RAND_MAX);
    double y = double(rand()) / double(RAND_MAX);
    double z = double(rand()) / double(RAND_MAX);
    vec3 r = vec3(x * 2, y * 2, z * 2);
    vec3 s = vec3(1, 1, 1);
    vec3 retVec = vec3::sub(r, s);
    return retVec;
}

vec3 vec3::normalize() {
    double norm = l2norm();
    return vec3(x / norm, y/ norm, z/norm);
}

vec3 vec3::operator+(vec3 b) {
    return vec3(x + b.getx(), y + b.gety(), z + b.getz());
}

vec3 vec3::operator-(vec3 b) {
    return vec3(x - b.getx(), y - b.gety(), z - b.getz());
}

vec3 vec3::operator*(double c) {
    return vec3(x * c, y * c, z * c);
}

vec3 vec3::operator/(double c) {
    return vec3(x / c, y / c, z / c);
}

double vec3::dot(vec3 b) {
    return x * b.getx() + y * b.gety() + z * b.getz();
}