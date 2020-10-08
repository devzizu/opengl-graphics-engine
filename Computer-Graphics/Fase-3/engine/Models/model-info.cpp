
#include "model-info.h"

/*--------------------------------------------------------------------------------------------------------------------*/
/* POINT_3D methods and constructors */

POINT_3D::POINT_3D(float x, float y, float z) : x(x), y(y), z(z) {}

/*--------------------------------------------------------------------------------------------------------------------*/
/* MODEL_INFO methods and constructors */

//Get vertices vector ptr
vector<float> *MODEL_INFO::getVertices() const {
    return vertices;
}

//Get model name
const string &MODEL_INFO::getName() const {
    return name;
}

//MODEL_INFO constructor
MODEL_INFO::MODEL_INFO(const string &name, bool isIndexed) : name(name), indexedModel(isIndexed) {

    this->vertices = new vector<float>();

    if(isIndexed) {
        this->indexes = new vector<GLuint>();
    }

}

/*--------------------------------------------------------------------------------------------------------------------*/
/* Groups and geometric transformations methods */

//For Rotation constructor
Transformation::Transformation(const string &description, float x, float y, float z, float angle) : description(
        description), x(x), y(y), z(z), angle(angle) {}

//Other constructors
Transformation::Transformation(const string &description, float x, float y, float z) : description(description), x(x),
                                                                                       y(y), z(z) {}
//For time based translations
Transformation::Transformation(const string &description, float time) : description(description), time(time) {

    if (description == "Translation_TimeBased") {

        //Create a valid memory pointer for the points vector
        this->transformationPoints = new vector<POINT_3D>();

        this -> startY = (float*) malloc(sizeof(float)*3);

        this -> startY[0] = 0.0f;
        this -> startY[1] = 1.0f;
        this -> startY[2] = 0.0f;
    }
}

//Add a new transformation point
void Transformation::addTransformationPoint(POINT_3D *newPoint) {

    this->transformationPoints->push_back(*newPoint);
}

Transformation::Transformation(const string &description, float x, float y, float z, float angle, float time)
        : description(description), x(x), y(y), z(z), angle(angle), time(time) {}

//Group constructor
Group::Group() {
    this->models = new vector<MODEL_INFO>;
    this->groups = new vector<Group>;
    this->transformations = new vector<Transformation>;
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Debug function

void displayGroup(Group group) {

    cout << ">> Group: " << endl;

    auto tr = group.transformations;
    int nr_of_order = 1;
    for (auto trIt = tr->begin(); trIt != tr -> end(); ++trIt) {
        cout << "\t» Tranformation of order " << nr_of_order <<  ": " << trIt -> description << endl;

        if (trIt -> description == "Translation") {
            cout << "\t»»»» Values :: x = " << trIt -> x << " y = " << trIt -> y << " z = " << trIt -> z << endl;
        }

        if (trIt -> description == "Translation_TimeBased") {

            cout << "\t»»»» Values :: time = " << trIt -> time << "...points:" << endl;

            auto points = trIt -> transformationPoints;
            for (auto pointsItr = points->begin(); pointsItr != points->end(); pointsItr++) {

                auto point = pointsItr.base();

                cout << "\t\t»» Point :: x = " << point -> x << " y = " << point -> y << " z = " << point -> z << endl;
            }
        }

        if (trIt -> description == "Rotation") {
            cout << "\t»»»» Values :: x = " << trIt -> x << " y = " << trIt -> y << " z = " << trIt -> z << " angle = " << trIt -> angle << endl;
        }

        if (trIt -> description == "Scale") {
            cout << "\t»»»» Values :: x = " << trIt -> x << " y = " << trIt -> y << " z = " << trIt -> z << endl;
        }

        nr_of_order++;
    }

    auto models = group.models;
    for (auto modelIt = models->begin(); modelIt != models -> end(); ++modelIt) {
        cout << "\t» Model: " << modelIt -> getName() << endl;

        auto vertices = modelIt -> getVertices();
        int limit_print = 0;
        for (auto vertIt = vertices->begin(); limit_print < 3 && vertIt != vertices->end(); vertIt+=3) {

            cout << "\t\tVertex :: x = " << *vertIt.base() << " y = " << *(vertIt+1).base() << " z = " << *(vertIt+2).base() << ";" << endl;
            limit_print++;
        }
    }

    auto groupsVector = group.groups;
    for (auto groupIter = groupsVector->begin(); groupIter != groupsVector -> end(); ++groupIter) {

        displayGroup(*groupIter.base());
    }

    cout << "<< End Group... " << endl;

}
