#pragma once
#include <stdlib.h>

class random {
    private:
        int seed;
    public:
        random(int s) {
            seed = s;
        }
        static double drand48() {
            return double(rand()) / double(RAND_MAX);
        }
};