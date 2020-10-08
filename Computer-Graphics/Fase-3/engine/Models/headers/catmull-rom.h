
#ifndef ENGINE_CATMULL_ROM_H
#define ENGINE_CATMULL_ROM_H

#include "model-info.h"

void getGlobalCatmullRomPoint(vector<POINT_3D>* points, float gt, float *pos, float *deriv);
void normalize(float *a);
void cross(float *a, float *b, float *res);
void buildRotMatrix(float *x, float *y, float *z, float *m);
void renderCatmullRomCurve(vector<POINT_3D>* points);

#endif