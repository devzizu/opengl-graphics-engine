
#ifndef ENGINE_LOAD_XML_H
#define ENGINE_LOAD_XML_H

#include "lights.h"

/*
 * Loads our xml configuration file.
 * @param xml file path
 * */
pair<vector<Group>*, vector<LightSource>*> load_xml_config(std::string xml_config_filename);

#endif
