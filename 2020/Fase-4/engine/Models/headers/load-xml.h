
#ifndef ENGINE_LOAD_XML_H
#define ENGINE_LOAD_XML_H

/*
 * Carrega o ficheiro de configuração xml num objeto com o nome
 * de todos os modelos.
 * @param caminho para o ficheiro xml
 * */
vector<Group>* load_xml_config(std::string xml_config_filename);

#endif
