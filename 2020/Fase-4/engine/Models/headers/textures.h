
#ifndef ENGINE_TEXTURES_H
#define ENGINE_TEXTURES_H

#include "model-info.h"

/*
 * Initializes textures specified in the models of the
 * different groups, loading image data, texture ID,...
 * */
void initTextures(vector<Group>* scene_groups);

/*
 * Initializes textures specified in the models of the
 * different groups, loading image data, texture ID,...  for sky
 * */
int initModelTextureSky(string texture);

#endif //ENGINE_TEXTURES_H
