
#ifndef ENGINE_LIGHTS_H
#define ENGINE_LIGHTS_H

#include <GL/glew.h>
#include <iostream>
#include <model-info.h>

using namespace std;

/*
 * Class that stores all the information about
 * a light source in this system. Lights could be SPOT,
 * DIRECTIONAL or POINT and the RGBA intensities may be
 * given as input.
 * Default OpenGL values are given to all colour components.
 * */
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

/*
 * Prints a light source class in stdout.
 * @param ls the LightSource class
 * */
void printLightSource(LightSource* ls);

/*
 * Generic array display function on stdout.
 * @param array the array
 * @param tam array length
 * */
void printArrayComponent(float* array, int tam);

/*
 * Loads lighting to opengl and enables all source lights
 * @param scene scene containing lights and groups
 * */
void initLights(pair<vector<Group>*, vector<LightSource>*> scene);

#endif //ENGINE_LIGHTS_H
