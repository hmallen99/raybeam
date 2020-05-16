#include <iostream>
#include <vector>
#include "vec3.h"

using namespace std;

int main () {
    vector<vec3*> vecList = vector<vec3*>();
    for (int i = 0; i < 3; i++) {
        vecList.push_back(new vec3(i, i+1, i+2));
    }
    vecList.push_back(vec3::add(vecList[0], vecList[1]));
    vecList[0]->add(vecList[1]);

    cout << vec3::dot(vecList[0], vecList[1]) << endl;
    for (int i = 0; i < 4; i++) {
        cout << vecList[i]->getx() << vecList[i]->gety() << vecList[i]->getz() << endl; 
    }
    return 0;
}