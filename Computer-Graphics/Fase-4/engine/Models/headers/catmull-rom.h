
#ifndef ENGINE_CATMULL_ROM_H
#define ENGINE_CATMULL_ROM_H

#include "model-info.h"

/*
 * Gets a generic catmull rom point given a set of control points
 * @param points vector of control points
 * @param gt offset in the curve
 * @param pos float array where the point gets stored
 * @para deriv float array where the derivative gets stored
 * */
void getGlobalCatmullRomPoint(vector<POINT_3D>* points, float gt, float *pos, float *deriv);

/*
 * Normalizes a generic 3 floats vector
 * @param a vector to normalize
 * */
void normalize(float *a);

/*
 * Applies cross product between 2 vectors
 * @param a first vector
 * @param b second vector
 * @param res result vector
 * */
void cross(float *a, float *b, float *res);

/*
 * Builds a rotation matrix for the 3 axis
 * @param x axis X
 * @param y axis Y
 * @param z axis Z
 * @param m resultant matrix
 * */
void buildRotMatrix(float *x, float *y, float *z, float *m);

/*
 * Draws a generic catmull rom curve given a set of control points
 * Uses GL_POINTS to draw the outline of the curve
 * */
void renderCatmullRomCurve(vector<POINT_3D>* points);

#endif