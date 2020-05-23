
#ifndef ENGINE_LOAD_XML_H
#define ENGINE_LOAD_XML_H

#include "lights.h"

/*
 * Carrega o ficheiro de configuração xml num objeto com o nome
 * de todos os modelos.
 * @param caminho para o ficheiro xml
 * */
pair<vector<Group>*, vector<LightSource>*> load_xml_config(std::string xml_config_filename);

#endif
