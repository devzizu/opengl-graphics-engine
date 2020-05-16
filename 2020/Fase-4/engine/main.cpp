
#include <iostream>

#include "Models/headers/model-info.h"
#include "Models/headers/load-xml.h"
#include "Models/headers/load-graphics.h"

#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

#define default_xml_config_file "default-config.xml"
#define XML_CONFIG_FILES_PATH "../../examples/XML-Examples/"

void cat_commands () {

    cout << endl << "[...] Available commands: " << endl;
    cout << "1) No arguments, uses the default xml config file: " << default_xml_config_file << ";" << endl;
    cout << "» ./engine" << endl;
    cout << "2) Pass xml config file as the first argument;" << endl;
    cout << "» ./engine file_name.xml" << endl;
    cout << endl << "[-] All xml files should be stored in " << XML_CONFIG_FILES_PATH << " !" << endl;
}

int main(int argc, char** argv)
{
    system("clear");

    /* 1) Check if there's any config name passed as an argument */

    string xml_file_name;

    //An argument was passed to the program
    if (argc == 2) {

        //Get first argument as the filename
        xml_file_name = argv[1];

    } else if (argc == 1) {

        //Get first argument as the filename
        xml_file_name = default_xml_config_file;

    } else {

        //Invalid command

        cat_commands();
        return 0;
    }

    /* 2) Execute the xml file */

    cout << endl << "»»» Engine starting..." << endl;
    cout << endl << "[...] Reading configuration file: " << xml_file_name << endl;

    vector<Group>* scene_groups;

    try {

        //Loading xml file
        scene_groups = load_xml_config(xml_file_name);

    } catch (string msg) {

        cout << endl << "[X] Parse error, check the xml config file syntax!" << endl;
        cout << "\n> Message: \"" << msg << "\"" << endl;

        cout << endl << "[X] Engine exited with code -1." << endl;

        return 0;
    }

    // Could not read any group from a scene tag
    // inside the xml configuration file
    if (scene_groups == nullptr || scene_groups->empty()) {

        cout << endl << "[X] Could not load any group from " << xml_file_name << " (or the file doesn't exist in the default path " << XML_CONFIG_FILES_PATH << " !);" << endl;

        //end program because an error was detected while parsing
        return 0;
    }

    //At this point the structures were loaded successfully
    //Graphic engine initialized:
    cout  << endl << "[1] Initializing graphics engine with the structures... " << endl;

    load_graphics(scene_groups, argc, argv);

    return 0;
}
