#ifndef ENGINE_LOAD_GRAPHICS_H
#define ENGINE_LOAD_GRAPHICS_H

/*
 * Carrega um conjunto de modelos dados como argumento em OpenGL
 * @param models vetor de modelos a carregar.
 * @param scene pair composed by the groups and lights that define our scene
 * @param argv argv da main principal
 * */
int load_graphics(pair<vector<Group>*, vector<LightSource>*> scene, int argc, char** argv);

#endif