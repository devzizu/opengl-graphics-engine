
#ifndef ENGINE_DRAW_ELEMENTS_H
#define ENGINE_DRAW_ELEMENTS_H

#include "model-info.h"

/*
 * Draws the axis in the screen
 * give each axis length from origin
 * @param x axis X length
 * @param y axis Y length
 * @param z axis Z length
 * */
void drawAxis(float x, float y, float z);

/*
 * Draws a group of elements in the screen
 * @param g a Group class with elements to draw: models, groups and transformations
 * @param hasLighting false if lights should be enabled
 * @param ENABLE_MODEL_AXIS true if axis should be displayed
 * */
void drawGroupElements(Group g, bool hasLighting, bool ENABLE_MODEL_AXIS);

#endif //ENGINE_DRAW_ELEMENTS_H
