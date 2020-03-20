
#ifndef ENGINE_MODEL_INFO_H
#define ENGINE_MODEL_INFO_H

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*--------------------------------------------------------------------------------------------------------------------*/
/*
 * Stores a point representation in 3D.
 * */
class POINT_3D {

    public:
        float x; float y; float z;

        POINT_3D(float x, float y, float z);

        float getX() const;

        float getY() const;

        float getZ() const;
};

/*--------------------------------------------------------------------------------------------------------------------*/

/*
 * Stores information about a model.
 * Its file name and the vector of vertices.
 * */
class MODEL_INFO {

    public:
        string name;
        vector<POINT_3D> vertices;

    public:
        MODEL_INFO(const string &name, const vector<POINT_3D> &vertices);

        const vector<POINT_3D> &getVertices() const;
            const string &getName() const;

        void addPoint(POINT_3D point3D);
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

public:
        //transformation name
        string description;
        //x, y and z values
        float x, y, z;
        //angle of rotation in degrees
        float angle;
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