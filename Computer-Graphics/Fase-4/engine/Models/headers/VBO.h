
#ifndef ENGINE_VBO_H
#define ENGINE_VBO_H

#include "model-info.h"

/*
 * Initializes all VBOs for a model
 * @param model the model
 * */
void initVBOModel(MODEL_INFO *model);

/*
 * Initializes VBOs for a group
 * @param g the group
 * */
void initVBOGroup(Group *g);

/*
 * Initializes VBOs to all scene groups
 * @param scene_groups scene groups vector
 * */
void initVBOs (vector<Group>* scene_groups);

#endif