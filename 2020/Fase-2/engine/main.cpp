
#include <iostream>

#include "Models/headers/model-info.h"
#include "Models/headers/load-xml.h"
#include "Models/headers/load-graphics.h"

#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

#define xml_config_file "ex-config-2.xml"

int main(int argc, char** argv)
{
    system("clear");

    cout << endl << "»»» Engine starting..." << endl;
    cout << endl << "[...] Reading configuration file: " << xml_config_file << endl;

    //Loading xml file
    vector<Group>* scene_groups = load_xml_config(xml_config_file);

    // Could not read any group from a scene tag
    // inside the xml configuration file
    if (scene_groups->empty()) {

        cout << endl << "[X] Could not load any group from " << xml_config_file << " (check the syntax!);" << endl;

        //end program because an error was detected while parsing
        return 0;
    }

    //At this point the structures were loaded successfully
    //Graphic engine initialized:
    cout  << "[...] Initializing graphics engine with the structures... " << endl;

    load_graphics(scene_groups, argc, argv);

    return 0;
}
