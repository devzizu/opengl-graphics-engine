
#include <iostream>

#include "Models/headers/model-info.h"
#include "Models/headers/load-xml.h"
#include "Models/headers/load-graphics.h"

#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

#define xml_config_file "ex-config-1.xml"

int main(int argc, char** argv)
{
    system("clear");

    cout << endl << "Engine starting..." << endl;
    cout << endl << "Reading configuration file: " << xml_config_file << endl;

    //Loading xml file
    vector<MODEL_INFO> models_list = load_xml_config(xml_config_file);

    //Error handling
    if (models_list.empty()) {
        cout << endl << "Error reading " << xml_config_file << ";" << endl;
        return 0;
    }

    //load opengl
    cout << endl << "Loading models to data structures..." << endl << endl;

    for(auto it = models_list.begin(); it != models_list.end(); ++it) {

        load_model(it.base());
    }

    load_graphics(models_list, argc, argv);

    return 0;
}
