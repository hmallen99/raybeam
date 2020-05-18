
#include <iostream>
#include <fstream>
#include <vector>
#include "vec3.h"
#include "ray.h"
#include "object.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"

using namespace std;

int main () {
    ofstream out("pic.ppm", ios::binary);
    int nx = 800;
    int ny = 600;
    int ns = 10;
    out << "P3\n" << nx << " " << ny << "\n255\n";
    vector<object *> objList;
    //objList.push_back(new sphere(new vec3(0, -100.5, -1), 100));
    objList.push_back(new triangle(new vec3(-2, 0, -1), new vec3(0, -1, -1), new vec3(2, 0, -1)));
    camera* cam = new camera();
    vec3* pHit = new vec3();
    vec3* nHit = new vec3();
    ray* test = cam->getRay(0.5, 0.47);
    objList[0]->intersect(test, pHit, nHit);

    for (int j=ny-1; j>=0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray* r = cam->getRay(u, v);
            for (int o = 0; o < objList.size(); o++) {
                if (objList[o]->intersect(r, pHit, nHit)) {
                    out << 255 << " " << 255 << " " << 255 << "\n";
                }
                else {
                    out << 0 << " " << 0 << " " << 0 << "\n";
                }
            }
        }
    }
    out.close();
    return 0;
}