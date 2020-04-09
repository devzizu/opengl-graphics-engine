
#ifndef ENGINE_VBO_H
#define ENGINE_VBO_H

#include "model-info.h"

void initVBOModel(MODEL_INFO *model);

void initVBOGroup(Group *g);

void initVBOs (vector<Group>* scene_groups);

#endif