#include <math.h>

class vec3 {
    private:
        double x;
        double y;
        double z;

    public:
        vec3();
        ~vec3();
        vec3(double xc, double yc, double zc) {
            x = xc;
            y = yc;
            z = zc;
        }

        double getx() {return x;}
        double gety() {return y;}
        double getz() {return z;}

        static vec3* add(vec3* a, vec3* b);
        void add(vec3* b);
        void sub(vec3* b);
        void mul(double c);
        void div(double c);
        double l2norm();
        static double dot(vec3* a, vec3* b);

        vec3 operator-();
    
};

vec3::vec3() {
    x = 0;
    y = 0;
    z = 0;
}

vec3::~vec3() {

}

vec3* vec3::add(vec3* a, vec3* b) {
    return new vec3(a->getx() + b->getx(), a->gety() + b-> gety(), a->getz() + b->getz());
}

void vec3::add(vec3* b) {
    x = x + b->getx();
    y = y + b->gety();
    z = z + b->getz();
}

void vec3::sub(vec3* b) {
    x = x - b->getx();
    y = y - b->gety();
    z = z - b->getz();
}

void vec3::mul(double c) {
    x = x * c;
    y = y * c;
    z = z * c;
}

void vec3::div(double c) {
    x = x / c;
    y = y / c;
    z = z / c;
}

double vec3::dot(vec3* a, vec3* b) {
    return a->getx()* b->getx() + a->gety()*b->gety() + a->getz()*b->getz();
}

double vec3::l2norm() {
    return sqrt(x*x + y*y + z*z);
}


vec3 vec3::operator-() {
    return vec3(-x, -y, -z);
}