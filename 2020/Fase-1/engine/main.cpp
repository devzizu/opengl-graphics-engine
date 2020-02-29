
#include <iostream>

#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//XML default file path
#define XML_CONFIG_FILES_PATH "../XML-Examples/"

int load_xml_config(string xml_config_filename) {

    string file_path = XML_CONFIG_FILES_PATH + xml_config_filename;
    cout << endl << "Reading from " << file_path << "..." << endl;

    //Load document file
    XMLDocument xml_config_doc;
    XMLError eResult = xml_config_doc.LoadFile(file_path.c_str());

    //Read all models
    XMLElement* scene = xml_config_doc.FirstChildElement("scene");
    for (XMLElement* model_ptr = scene -> FirstChildElement("model");
         model_ptr != NULL;
         model_ptr = model_ptr -> NextSiblingElement()
         ) {

        string model_file = string(model_ptr -> Attribute("file"));
        cout << endl << "Got file model = " << model_file << ";";
    }

    cout << endl;

    return eResult;
}

int main() {

    system("clear");
    cout << endl << "Engine starting..." << endl;

    string xml_file = "ex-config-1.xml";
    int loaded = load_xml_config(xml_file);

    if (loaded != XML_SUCCESS) {

        cout << endl << "Error reading " + xml_file + ";" << endl;
        return 0;
    }

    return 0;
}
