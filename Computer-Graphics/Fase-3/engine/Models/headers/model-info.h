
#ifndef ENGINE_MODEL_INFO_H
#define ENGINE_MODEL_INFO_H

#include <iostream>
#include <vector>
#include <stack>

#include <GL/glew.h>

using namespace std;

/*--------------------------------------------------------------------------------------------------------------------*/

class POINT_3D {

    public:
        POINT_3D(float x, float y, float z);

    public:
            float x;
            float y;
            float z;
};

/*
 * Stores information about a model.
 * Its file name and the vector of vertices.
 * */
class MODEL_INFO {

    public:
        string name;
        bool indexedModel;
        vector<float>* vertices;
        vector<GLuint>* indexes;
        GLuint verticesBuffer[1];
        GLuint indexesBuffer[1];

    public:
        MODEL_INFO(const string &name, bool isIndexed);
        vector<float> *getVertices() const;
        const string &getName() const;
};

/*--------------------------------------------------------------------------------------------------------------------*/
/*
 * Transformation class containing the
 * fundamental attributes for Rotation,
 * Translation and Scaling.
 * */
class Transformation {
    public:
        //Constructor for Rotate
        Transformation(const string &description, float x, float y, float z, float angle);
        //Constructor for Translate and Scale
        Transformation(const string &description, float x, float y, float z);

        //For time based Translations
        Transformation(const string &description, float time);
        //For time based Rotations
        Transformation(const string &description, float x, float y, float z, float angle, float time);

        void addTransformationPoint(POINT_3D *newPoint);

        //transformation name
        string description;
        //x, y and z values
        float x, y, z;
        //angle of rotation in degrees
        float angle;
        float time;

        float* startY;

        vector<POINT_3D>* transformationPoints;
};

/*
 * Call Rotation, Translation and scale as a Transformation type
 * */
typedef class Transformation Rotation, Translation, Scale;

/*--------------------------------------------------------------------------------------------------------------------*/
/*
 * A group of elements to compose.
 * Models and other groups will be affected by the
 * transformations in order.
 */
class Group {
public:
    Group();

public:
    //List of models: inside <models> tag
    vector<MODEL_INFO>* models;
    //List of models: inside <group> tag
    vector<Group>* groups;

    //Sequence of transformations
    vector<Transformation>* transformations;
};

/*--------------------------------------------------------------------------------------------------------------------*/
/*
 * Debug function to cout a group
 */
void displayGroup(Group group);

#endif