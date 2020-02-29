
#include <iostream>
#include <fstream>
#include <vector>
#include <model-info.h>

#include "../tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//XML default file path
#define XML_CONFIG_FILES_PATH "../../examples/XML-Examples/"

//MODELS default path
#define MODEL_3D_PATH "../../examples/Model-Read-Tests/"


vector<MODEL_INFO> load_xml_config(string xml_config_filename) {

    string file_path = XML_CONFIG_FILES_PATH + xml_config_filename;
    cout << endl << "Reading from " << file_path << "..." << endl;

    //Load document file
    XMLDocument xml_config_doc;
    XMLError eResult = xml_config_doc.LoadFile(file_path.c_str());

    //Error loading file?
    if (eResult != XML_SUCCESS)
        return {};

    //Error loading first scene element?
    XMLElement* rootScene = xml_config_doc.FirstChildElement("scene");

    if (rootScene == nullptr)
        return {};

    vector<MODEL_INFO> models;

    while (rootScene) {

        //Read all model elements

        XMLElement* model_ptr = rootScene->FirstChildElement("model");

        for (; model_ptr != NULL;
               model_ptr = model_ptr -> NextSiblingElement("model")) {

            string model_file = string(model_ptr -> Attribute("file"));
            //cout << "> Got file model = " << model_file << ";" << endl;

            MODEL_INFO* m = new MODEL_INFO(model_file);
            models.push_back(*m);
        }

        //End of reading models

        rootScene = rootScene -> NextSiblingElement("scene");
        if (rootScene != nullptr) { return {}; }
    }

    if (models.size() == 0) return {};

    return models;
}

int load_model(MODEL_INFO *model) {

    string path_to_model = MODEL_3D_PATH + model->getName();
    cout << "Reading from " << path_to_model << endl;

    ifstream filestream (path_to_model);

    if (!filestream.is_open()) {
        return -1;
    }

    string line;

    try {

        //get the number of vertices
        getline(filestream, line);

        int total = stoi(line);
        model->setTotalVertices(stoi(line));

        float x, y, z;
        while (getline(filestream, line)) {

            sscanf(line.c_str(), "%f %f %f", &x, &y, &z);

            auto p = new POINT_3D(x,y,z);
            model->addPoint(*p);
        }

        filestream.close();

    } catch (...) {

        filestream.close();

        cout << "error parsing 3d model" << endl;

        return -1;
    }

    //for(auto it = (model->getVertices()).begin(); it != model->getVertices().end(); ++it) {

    //    cout << it.base()->getX() << " " << it.base()->getY() << " " << it.base()->getZ() << endl;
    //}

 }

