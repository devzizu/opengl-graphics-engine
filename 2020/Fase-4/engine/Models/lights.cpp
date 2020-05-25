
#include <lights.h>
#include <iostream>
#include <model-info.h>

using namespace std;

LightSource::LightSource() {

    this -> lightType = "POINT";

    //filling with default values first
    //captured from: https://www.glprogramming.com/red/chapter05.html
    for (int i = 0; i < 4; i++) {

        if (i < 3) {

            this -> ambientComponent[i] = 0.0f;
        }

        this -> diffuseComponent[i] = 1.0f;
        this -> specularComponent[i] = 1.0f;
    }

    this -> point[0] = 0.0f;
    this -> point[1] = 0.0f;
    this -> point[2] = 0.0f;
    this -> point[3] = 1.0f;

    this -> ambientComponent[3] = 1.0f;

    this -> SpotCutoff = 180.0f;
    this -> SpotExponent = 0.0f;
    this -> SpotDirection[0] = 0.0f;
    this -> SpotDirection[1] = 0.0f;
    this -> SpotDirection[2] = -1.0f;
}

void printArrayComponent(float* array, int tam) {

    for (int i = 0; i < tam; i++) {

        if (i == tam - 1) {

            cout << array[i] << endl;
            break;
        }

        cout << array[i] << " | ";

    }
}

void printLightSource(LightSource* ls) {

    cout << "......................................" << endl;
    cout << "Light type: " << ls ->lightType << endl;
    cout << "Light number: " << ls ->lightEnumNumber << endl;
    cout << "Point: " << endl;
    printArrayComponent(ls ->point, 4);
    cout << "Diffuse: " << endl;
    printArrayComponent(ls ->diffuseComponent, 4);
    cout << "Specular: " << endl;
    printArrayComponent(ls ->specularComponent, 4);
    cout << "Ambient: " << endl;
    printArrayComponent(ls ->ambientComponent, 4);
    cout << "Spot direction: " << endl;
    printArrayComponent(ls ->SpotDirection, 3);
    cout << "Spot Exponent: " << ls ->SpotExponent << endl;
    cout << "Spot cutoff: " << ls ->SpotCutoff << endl;
    cout << "......................................" << endl;
}

void initLights(pair<vector<Group>*, vector<LightSource>*> scene) {

    //Enable lights
    if (!scene.second->empty()) {
        glEnable(GL_LIGHTING); //turn on lighting
        for (auto it = scene.second->begin(); it < scene.second->end(); it++) {
            glEnable(GL_LIGHT0 + it->lightEnumNumber); //turn on the light source
        }
    }

}