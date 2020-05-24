#ifndef PROJETO_CG_MODEL_GENERATOR_H
#define PROJETO_CG_MODEL_GENERATOR_H

using namespace std;

/*
 * Obsolete (Phase 1)
 * */
void generate_plane_3d (double size, string file_name);

/*
 * Generates an indexed plane file.
 * @param size side dimension
 * @param file_name output file name (stored in examples/Models.3d)
 * */
void generate_plane_indexed (double size, string file_name);

/*
 * Obsolete (Phase 1)
 */
void generate_box_3d (double x, double y, double z, int divisions, string file_name);

/*
 * Generates an indexed box width divisions file.
 * @param x x dimension
 * @param y y dimension
 * @param z z dimension
 * @param divisions number of divisions for each side
 * @param file_name output file name (stored in examples/Models.3d)
 * */
void generate_box_indexed (double x, double y, double z, int divisions, string file_name);

/*
 * Obsolete (Phase 1)
 */
void generate_cone_3d (double radius, double height, int slices, int stacks, string file_name);

/*
 * Generates an indexed cone file.
 * @param radius bottom cone radius
 * @param height cone height
 * @param slices number of side slices
 * @param stacks number of stacks
 * @param file_name output file name (stored in examples/Models.3d)
 * */
void generate_cone_indexed (double radius, double height, int slices, int stacks, string file_name);

/*
 * Obsolete (Phase 1)
 */
void generate_sphere_3d (double radius, double slices, int stacks, string file_name);

/*
 * Generates an indexed sphere file.
 * @param radius sphere radius
 * @param slices number of side slices
 * @param stacks number of stacks
 * @param file_name output file name (stored in examples/Models.3d)
 * */
void generate_sphere_indexed (double radius, int slices, int stacks, string file_name);

#endif
