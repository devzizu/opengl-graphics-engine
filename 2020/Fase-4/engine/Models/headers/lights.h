
#ifndef ENGINE_LIGHTS_H
#define ENGINE_LIGHTS_H

#include <GL/glew.h>
#include <iostream>

using namespace std;

class LightSource {

public:
    LightSource();

public:

    string lightType;

    //Lights are defined in enums
    int lightEnumNumber;

    //light position (POINT (w=1) or DIRECTIONAL (w=0))
    float point[4];

    //light intensity RGBA colour
    float diffuseComponent[4];
    float specularComponent[4];
    float ambientComponent[4];

    //For Spotlights

    //direction of spotlight
    float SpotDirection[3];
    //spotlight exponent
    float SpotExponent;
    //spotlight exponent
    float SpotCutoff;
};

void printLightSource(LightSource* ls);
void printArrayComponent(float* array, int tam);

#endif //ENGINE_LIGHTS_H
