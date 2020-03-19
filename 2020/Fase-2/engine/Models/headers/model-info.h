
#ifndef ENGINE_MODEL_INFO_H
#define ENGINE_MODEL_INFO_H

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*--------------------------------------------------------------------------------------------------------------------*/

class POINT_3D {

    public:
        float x; float y; float z;

        POINT_3D(float x, float y, float z);

        float getX() const;

        float getY() const;

        float getZ() const;
};

/*--------------------------------------------------------------------------------------------------------------------*/

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

class Transformation {
public:
    Transformation(const string &description, float x, float y, float z, float angle);

    Transformation(const string &description, float x, float y, float z);

public:
        string description;
        float x, y, z;
        float angle;
};

//Call Rotation, Translation and scale as a Transformation type
typedef class Transformation Rotation, Translation, Scale;

/*--------------------------------------------------------------------------------------------------------------------*/
/*
 *
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