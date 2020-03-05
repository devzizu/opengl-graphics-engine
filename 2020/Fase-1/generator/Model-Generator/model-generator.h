#ifndef PROJETO_CG_MODEL_GENERATOR_H
#define PROJETO_CG_MODEL_GENERATOR_H

using namespace std;

/*
 * Gerar os vértices para um plano em 3D baseado em triângulos.
 * @param size dimensão lateral do plano
 * @param file_name ficheiro output
 */
void generate_plane_3d (double size, string file_name);

/*
 * Gerar os vértices para um caixa em 3D baseado em triângulos.
 * @param x dimensão da coordenada X
 * @param y dimensão da coordenada Y
 * @param z dimensão da coordenada Z
 * @param divisions número de divisioes da caixa
 * @param file_name ficheiro output
 */
void generate_box_3d (double x, double y, double z, int divisions, string file_name);

/*
 * Gerar os vértices para um cone em 3D baseado em triângulos.
 * @param radius raio
 * @param height altura
 * @param slices cortes da superfície de fora
 * @param stacks camadas
 * @param file_name ficheiro output
 */
void generate_cone_3d (double radius, double height, int slices, int stacks, string file_name);

/*
 * Gerar os vértices para uma esfera em 3D baseado em triângulos.
 * @param radius raio
 * @param slices cortes da superfície de fora
 * @param stacks camadas
 * @param file_name ficheiro output
 */
void generate_sphere_3d (double radius, double slices, int stacks, string file_name);

#endif
