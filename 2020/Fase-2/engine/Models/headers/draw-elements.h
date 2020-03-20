
#ifndef ENGINE_DRAW_ELEMENTS_H
#define ENGINE_DRAW_ELEMENTS_H

#include "model-info.h"

/*
 * Draws the axis in the screen
 * */
void drawAxis();

/*
 * Draws a group of elements in the screen
 * @param g a Group class with elements to draw: models, groups and transformations
 * */
void drawGroupElements(Group g);

#endif //ENGINE_DRAW_ELEMENTS_H
