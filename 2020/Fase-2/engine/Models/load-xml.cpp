
#include <iostream>
#include <fstream>
#include <vector>

#include <model-info.h>

#include "../tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

/*--------------------------------------------------------------------------------------------------------------------*/
//Global constants (folder and file locations)

//XML default file path
#define XML_CONFIG_FILES_PATH "../../examples/XML-Examples/"

//MODELS default path
#define MODEL_3D_PATH "../../examples/Model-Read-Tests/"

/*--------------------------------------------------------------------------------------------------------------------*/
//Read model file and store the vertices in the vertices vector from MODEL_INFO

int load_model_vertices(MODEL_INFO *model) {

    //Model path appended to default folder location for models
    string path_to_model = MODEL_3D_PATH + model -> getName();

    ifstream file_stream (path_to_model);

    if (!file_stream.is_open()) {
        cout << "Could not read from " << path_to_model << "!" << endl;
        return -1;
    }

    try {

        //to store the line
        string line;

        //get the number of vertices
        //-- used just for debugging purposes
        getline(file_stream, line);

        //3 fields of each line in model file
        //the 3 coordinates x, y and z
        float x, y, z;

        //while not EOF
        while (getline(file_stream, line)) {

            //Parse line float vertices
            sscanf(line.c_str(), "%f %f %f", &x, &y, &z);

            auto p = new POINT_3D(x,y,z);
            model -> addPoint(*p);
        }

        file_stream.close();

    //catch wtv error we got
    } catch (...) {
        file_stream.close();
        cout << "Error parsing 3D model file in: " << path_to_model << "..." << endl;
        return -1;
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the models (<models>)

static void processModelsTag(XMLElement *models_ptr, Group *group) {

    XMLElement* model_ptr = models_ptr -> FirstChildElement("model");

    for (; model_ptr != NULL; model_ptr = model_ptr -> NextSiblingElement("model")) {

        string model_file_name = string(model_ptr -> Attribute("file"));

        auto vertices = new vector<POINT_3D>;
        auto model = new MODEL_INFO(model_file_name, *vertices);

        load_model_vertices(model);

        group -> models -> push_back(*model);
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the translations (<translation X=? Y=? Z=?>)

static void processTranslationTag(XMLElement *translation_ptr, Group *group) {

    float x = 0.0f, y = 0.0f, z = 0.0f;

    translation_ptr -> QueryAttribute("X", &x);
    translation_ptr -> QueryAttribute("Y", &y);
    translation_ptr -> QueryAttribute("Z", &z);

    //Create new translation
    Transformation *t = new Translation("Translation", x, y, z);

    group -> transformations -> push_back(*t);
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the rotations (<rotation X=? ?Y=? ?Z=?>)
//X, Y and Z attributes are optional

static void processRotationTag(XMLElement *rotation_ptr, Group *group) {

    float angle = 0.0f, x = 0.0f, y = 0.0f, z = 0.0f;

    rotation_ptr -> QueryAttribute("angle", &angle);
    rotation_ptr -> QueryAttribute("axisX", &x);
    rotation_ptr -> QueryAttribute("axisY", &y);
    rotation_ptr -> QueryAttribute("axisZ", &z);

    //Create new rotation
    Transformation *t = new Rotation("Rotation", x, y, z, angle);

    group -> transformations -> push_back(*t);
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the scale (<translation X=? Y=? Z=?>)

static void processScaleTag(XMLElement *scale_ptr, Group *group) {

    //default scale
    float x = 1.0f, y = 1.0f, z = 1.0f;

    scale_ptr -> QueryAttribute("X", &x);
    scale_ptr -> QueryAttribute("Y", &y);
    scale_ptr -> QueryAttribute("Z", &z);

    Transformation *t = new Scale("Scale", x, y, z);

    group -> transformations -> push_back(*t);
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the group tag (<group>)

static void processGroupTag(XMLElement *group_tag_ptr, Group *group) {

    XMLElement* element = group_tag_ptr -> FirstChildElement(nullptr);

    while (element != nullptr) {

        string element_name = element -> Name();

        //Translate tag found
        if (element_name == "translate")
            { processTranslationTag(element, group); }

        //Rotate tag found
        if (element_name == "rotate")
            { processRotationTag(element, group); }

        //Scale tag found
        else if (element_name == "scale")
            { processScaleTag(element, group); }

        //Models tag found
        else if (element_name == "models")
            { processModelsTag(element, group); }

        //Group child tag found
        else if (element_name == "group")
            {
                //New child group
                auto childGroup = new Group;

                //process the group and store in childGroup addr
                processGroupTag(element, childGroup);

                //Add group to the groups vector of the current group
                group -> groups -> push_back(*childGroup);
            }

        /*--------------------------------------------------------*/

        element = element -> NextSiblingElement(nullptr);
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the xml file and load all structures and classes

vector<Group>* load_xml_config(string xml_config_filename) {

    /*--------------------------------------------------------------*/

    //XML config file name
    string file_path = XML_CONFIG_FILES_PATH + xml_config_filename;
    cout << endl << "> Reading from " << file_path << "..." << endl;

    //Load document file
    XMLDocument xml_config_doc;
    XMLError eResult = xml_config_doc.LoadFile(file_path.c_str());

    //Error loading file?
    if (eResult != XML_SUCCESS)
        return {};

    /*--------------------------------------------------------------*/

    //Root scene ptr
    XMLElement* rootScene = xml_config_doc.FirstChildElement("scene");

    //There's no root scene, return
    if (rootScene == nullptr)
        return {};

    /*--------------------------------------------------------------*/

    //Scene tags can only contain group child tags
    XMLElement* group_tag_ptr = rootScene -> FirstChildElement("group");

    //Vector ptr containing all the groups of the scene
    auto groups_vector = new vector<Group>;

    //Navigate through the root scene tag and search for group tags ONLY
    while (group_tag_ptr) {

        //Create new group that will be processed in processGroupTag(...)
        auto newGroup = new Group();

        //Process the group tag
        processGroupTag(group_tag_ptr, newGroup);

        //Insert new group in groups vector
        groups_vector -> push_back(*newGroup);

        //Get next group tag ptr
        group_tag_ptr = group_tag_ptr -> NextSiblingElement("group");
    }

    return groups_vector;
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Debug purpose

/* This is used to display all the groups information in the scene tag on the stdout

cout << "\n\nDisplaying group information: \n\n";

for (auto groupIter = groups_vector->begin(); groupIter != groups_vector->end(); ++groupIter) {

displayGroup(*groupIter);
}
*/