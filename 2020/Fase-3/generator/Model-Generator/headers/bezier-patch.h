
#ifndef GENERATOR_BEZIER_PATCH_H
#define GENERATOR_BEZIER_PATCH_H

int load_bezier_patch (string path_to_model, vector<struct POINT_3D>* control_points, vector<int>* patch_indices);

int generate_bezier_model(string outfile_path, vector<int>* patch_indices, vector<POINT_3D>* control_points, int tessellationLevel);

#endif
