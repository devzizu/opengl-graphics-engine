#ifndef PROJETO_CG_MODEL_GENERATOR_H
#define PROJETO_CG_MODEL_GENERATOR_H

using namespace std;

void generate_plane_3d (double size, string file_name);
void generate_box_3d (double x, double y, double z, int divisions, string file_name);
void generate_cone_3d (double radius, double height, int slices, int stacks, string file_name);
void generate_sphere_3d (double radius, double slices, int stacks, string file_name);

#endif
