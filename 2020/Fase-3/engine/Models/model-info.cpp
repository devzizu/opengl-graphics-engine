
#include "model-info.h"

/*--------------------------------------------------------------------------------------------------------------------*/
/* MODEL_INFO methods */

//Get vertices vector ptr
vector<float> *MODEL_INFO::getVertices() const {
    return vertices;
}

//Get model name
const string &MODEL_INFO::getName() const {
    return name;
}

//MODEL_INFO constructor
MODEL_INFO::MODEL_INFO(const string &name, vector<float> *vertices) : name(name), vertices(vertices) {}

/*--------------------------------------------------------------------------------------------------------------------*/
/* Groups and geometric transformations methods */

//For Rotation constructor
Transformation::Transformation(const string &description, float x, float y, float z, float angle) : description(
        description), x(x), y(y), z(z), angle(angle) {}

//Other constructors
Transformation::Transformation(const string &description, float x, float y, float z) : description(description), x(x),
                                                                                       y(y), z(z) {}

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