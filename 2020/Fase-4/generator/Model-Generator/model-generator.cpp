
#include <fstream>
#include <cmath>
#include <vector>
#include "headers/model-info.h"

using namespace std;

void generate_plane_3d (double size, string file_name) {

    ofstream outfile(file_name);

    int nr_of_vertices = 6;

    outfile << nr_of_vertices << endl;

    //First triangle
    outfile << size/2 << " " << 0 << " " << -size/2 << endl;
    outfile << -size/2 << " " << 0 << " " << size/2 << endl;
    outfile << size/2 << " " << 0 << " " << size/2 << endl;
    //Second triangle
    outfile << size/2 << " " << 0 << " " << -size/2 << endl;
    outfile << -size/2 << " " << 0 << " " << -size/2 << endl;
    outfile << -size/2 << " " << 0 << " " << size/2 << endl;

    outfile.close();
}

void generate_box_3d (double x, double y, double z, int divisions, string file_name) {

    ofstream outfile(file_name);

    int nr_of_vertices = 6 * 6 * pow((1+divisions), 2);

    outfile << nr_of_vertices << endl;

    int iterations = pow((divisions+1), 2);

    //Bottom rectangles (Plane XZ, Y = 0)
    for (int go_up = 0; go_up < (divisions + 1); go_up++) {

        for (int go_right = 0; go_right < (divisions + 1);go_right++) {

            //----------------------------------------------------------------

            /* PLANO Z max */

            //First triangle
            outfile << (x/(divisions+1)) * (go_right + 1) << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << z << endl;
            outfile << (x/(divisions+1)) * go_right << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << z << endl;
            outfile << (x/(divisions+1)) * go_right << " "
                    << (y/(divisions+1)) * go_up << " "
                    << z << endl;

            //Second triangle
            outfile << (x/(divisions+1)) * (go_right + 1) << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << z << endl;
            outfile << (x/(divisions+1)) * go_right << " "
                    << (y/(divisions+1)) * go_up << " "
                    << z << endl;
            outfile << (x/(divisions+1)) * (go_right + 1) << " "
                    << (y/(divisions+1)) * go_up << " "
                    << z << endl;

            /* PLANO Z = 0 */

            //First triangle
            outfile << (x/(divisions+1)) * go_right << " "
                    << (y/(divisions+1)) * go_up << " "
                    << 0 << endl;
            outfile << (x/(divisions+1)) * go_right << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << 0 << endl;
            outfile << (x/(divisions+1)) * (go_right + 1) << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << 0 << endl;

            //Second triangle
            outfile << (x/(divisions+1)) * go_right << " "
                    << (y/(divisions+1)) * go_up << " "
                    << 0 << endl;
            outfile << (x/(divisions+1)) * (go_right + 1) << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << 0 << endl;
            outfile << (x/(divisions+1)) * (go_right + 1) << " "
                    << (y/(divisions+1)) * go_up << " "
                    << 0 << endl;

            //----------------------------------------------------------------

            /* PLANO X max */

            //First triangle
            outfile << x << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;
            outfile << x << " "
                    << (y/(divisions+1)) * go_up << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;
            outfile << x << " "
                    << (y/(divisions+1)) * go_up << " "
                    << (z/(divisions+1)) * go_right << endl;

            //Second triangle
            outfile << x << " "
                    << (y/(divisions+1)) * go_up << " "
                    << (z/(divisions+1)) * go_right << endl;
            outfile << x << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << (z/(divisions+1)) * go_right << endl;
            outfile << x << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;

            /* PLANO X = 0 */

            //First triangle
            outfile << 0 << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;
            outfile << 0 << " "
                    << (y/(divisions+1)) * go_up << " "
                    << (z/(divisions+1)) * go_right << endl;
            outfile << 0 << " "
                    << (y/(divisions+1)) * go_up << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;

            //Second triangle
            outfile << 0 << " "
                    << (y/(divisions+1)) * go_up << " "
                    << (z/(divisions+1)) * go_right << endl;
            outfile << 0 << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;
            outfile << 0 << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << (z/(divisions+1)) * go_right << endl;

            //----------------------------------------------------------------

            /* PLANO Y max */

            //First triangle
            outfile << (x/(divisions+1)) * go_up << " "
                    << y << " "
                    << (z/(divisions+1)) * go_right << endl;
            outfile << (x/(divisions+1)) * go_up<< " "
                    << y << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;
            outfile << (x/(divisions+1)) * (go_up + 1) << " "
                    << y << " "
                    << (z/(divisions+1)) * go_right << endl;

            //Second triangle
            outfile << (x/(divisions+1)) * go_up << " "
                    << y << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;
            outfile << (x/(divisions+1)) * (go_up + 1) << " "
                    << y << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;
            outfile << (x/(divisions+1)) * (go_up + 1) << " "
                    << y << " "
                    << (z/(divisions+1)) * go_right << endl;

            /* PLANO Y = 0 */

            //First triangle
            outfile << (x/(divisions+1)) * go_up << " "
                    << 0 << " "
                    << (z/(divisions+1)) * go_right << endl;
            outfile << (x/(divisions+1)) * (go_up + 1) << " "
                    << 0 << " "
                    << (z/(divisions+1)) * go_right << endl;
            outfile << (x/(divisions+1)) * go_up<< " "
                    << 0 << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;

            //Second triangle
            outfile << (x/(divisions+1)) * (go_up + 1) << " "
                    << 0 << " "
                    << (z/(divisions+1)) * go_right << endl;
            outfile << (x/(divisions+1)) * (go_up + 1) << " "
                    << 0 << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;
            outfile << (x/(divisions+1)) * go_up << " "
                    << 0 << " "
                    << (z/(divisions+1)) * (go_right + 1) << endl;
        }
    }

    outfile.close();
}

void generate_cone_indexed (double radius, double height, int slices, int stacks, string file_name) {

    ofstream outfile(file_name);

    int nr_of_vertices = 1 + (slices+1) * (stacks + 1);
    int nr_indices = 3 * slices + 6 * stacks * slices;
    int nr_textureCoords = nr_indices;

    outfile << nr_of_vertices << "," << nr_indices << "," << nr_textureCoords << endl;

    double alpha = 0.0, alpha_offset = 2 * M_PI / slices;
    double curr_x, curr_y, curr_z, new_radius;
    double stack_height = height / stacks;

    //Texture coordinates vector
    auto *textureCoordinates = new vector<POINT_3D>();

    for (int st = 0; st <= stacks; st++) {

        new_radius = radius - st * (radius / stacks);

        if (st == 0) {

            curr_x = 0.0f;
            curr_y = 0.0f;
            curr_z = 0.0f;

            //write vertex to output file
            outfile << curr_x << " " << curr_y << " " << curr_z << endl;
        }

        for (int sl = 0; sl <= slices; sl++) {

            alpha = sl * alpha_offset;

            curr_x = new_radius * sin(alpha);
            curr_y = st * stack_height;
            curr_z = new_radius * cos(alpha);

            //write vertex to output file
            outfile << curr_x << " " << curr_y << " " << curr_z << endl;

            textureCoordinates -> push_back(*new POINT_3D(
                    (sl / (float) slices),
                    (st / (float) stacks),
                    0.0f
            ));
        }
    }

    int A, B, C, D;

    //write indexes
    for (int st = 0; st < stacks; st++) {

        for (int sl = 0; sl < slices; sl++) {

            if (st == 0) {

                //Considering a triangle ABC
                //       B
                //      /|
                //    /  |
                //  /    |
                // C_____D

                B = 0;
                D = sl  +1;
                C = D + 1;

                //Draw: BCD
                outfile << B << endl << C << endl << D << endl;
            }

            //Considering a square ABCD
            // C_____D
            // |\    |
            // |  \  |
            // |    \|
            // A_____B

            A = st * (slices + 1) + sl + 1;
            B = A + 1;
            C = (st + 1) * (slices + 1) + sl + 1;
            D = C + 1;

            //Draw: ACB
            outfile << B << endl << C << endl << A << endl;

            //Draw: BCD
            outfile << D << endl << C << endl << B << endl;
        }
    }

    //write the texture coordinates to the output file
    for (auto it = textureCoordinates -> begin(); it < textureCoordinates->end(); it++) {

        outfile << it->x << " " << it->y << endl;
    }

    outfile.close();
}


void generate_cone_3d (double radius, double height, int slices, int stacks, string file_name) {

    ofstream outfile(file_name);

    int nr_of_vertices = (slices * 3 * stacks) + (6 * slices * stacks);
    
    double alpha = 2*M_PI/slices;
    double stack_height = height/stacks;
    double stack_radius, next_radius;

    outfile << nr_of_vertices << endl;

    for(int j=0; j < stacks;j++) {

        stack_radius = radius - (j*radius/stacks);
        next_radius = radius - ((j+1)*radius/stacks);

        for(int i=0; i < slices;i++) {

            // Bottom of each stack
            outfile << 0.0 << " " << j*stack_height << " " << 0.0 << endl;
            outfile << stack_radius * sin(alpha*(i+1)) << " " << j*stack_height << " " << stack_radius * cos(alpha*(i+1)) <<  endl;
            outfile <<  stack_radius * sin(alpha*i) << " " << j*stack_height << " " << stack_radius * cos(alpha*i) << endl;

            // Sides of each stack

            //triangle 1
            outfile << stack_radius * sin(alpha*i) << " " <<  j*stack_height << " " <<  stack_radius * cos(alpha*i) << endl;
            outfile << next_radius * sin(alpha*(i+1)) << " " << (j+1)*stack_height << " " <<  next_radius * cos(alpha*(i+1)) << endl;
            outfile << next_radius * sin(alpha*i) << " " <<  (j+1)*stack_height << " " <<  next_radius * cos(alpha*i) << endl;

            //triangle 2
            outfile << stack_radius * sin(alpha*(i+1)) << " " <<  j*stack_height << " " <<  stack_radius * cos(alpha*(i+1))<< endl;
            outfile << next_radius * sin(alpha*(i+1)) << " " <<  (j+1)*stack_height << " " <<  next_radius * cos(alpha*(i+1))<< endl;
            outfile << stack_radius * sin(alpha*i) << " " <<  j*stack_height << " " <<  stack_radius * cos(alpha*i)<< endl;
        }
    }
    outfile.close();
}

void generate_sphere_indexed (double radius, int slices, int stacks, string file_name) {

    //create file for the sphere model
    ofstream outfile(file_name);

    int nr_of_vertices = (stacks + 1) * (slices + 1);
    int nr_indices = 6 * stacks * slices;
    int nr_texture_coord = nr_of_vertices;
    outfile << nr_of_vertices << "," << nr_indices << "," << nr_texture_coord << endl;

    double alpha = 0.0, alpha_offset = 2 * M_PI / slices;
    double beta = 0.0, beta_offset = M_PI / stacks;
    double curr_x, curr_y, curr_z, new_radius = radius;

    //------------------------------------------------------------------------------------------------------------------
    //To store normals and texture coordinates

    //Texture coordinates vector
    auto *textureCoordinates = new vector<POINT_3D>();

    //------------------------------------------------------------------------------------------------------------------

    //write vertices
    for (int st = 0; st <= stacks; st++) {

        //beta for the stacks PI/2 -> -PI/2
        beta = M_PI / 2 - st * beta_offset;

        //compute new radius
        new_radius = radius * cos(beta);

        for (int sl = 0; sl <= slices; sl++) {

            //alpha for the slices
            alpha = sl * alpha_offset;

            //calculate vertices
            curr_x = new_radius * sin(alpha);
            curr_y = radius * sin(beta);
            curr_z = new_radius * cos(alpha);

            //write vertex to output file
            outfile << curr_x << " " << curr_y << " " << curr_z << endl;

            textureCoordinates -> push_back(*new POINT_3D(
                    (sl / (float) slices),
                    -(st / (float) stacks),
                    0.0f
            ));
        }
    }

    int A, B, C, D;

    //write indexes
    for (int st = 0; st < stacks; st++) {

        for (int sl = 0; sl < slices; sl++) {

            //Considering a square ABCD
            // A_____B
            // |    /|
            // |  /  |
            // |/    |
            // C_____D

            A = st * (slices + 1) + sl;
            B = A + 1;
            C = (st + 1) * (slices + 1) + sl;
            D = C + 1;

            //Draw: ACB
            outfile << A << endl << C << endl << B << endl;

            //Draw: BCD
            outfile << B << endl << C << endl << D << endl;
        }
    }

    //write the texture coordinates to the output file
    for (auto it = textureCoordinates -> begin(); it < textureCoordinates->end(); it++) {

        outfile << it->x << " " << it->y << endl;
    }

    outfile.close();
}

void generate_sphere_3d (double radius, double slices, int stacks, string file_name) {

    ofstream outfile(file_name);

    double alpha = 2*M_PI/slices;
    double beta_top = M_PI/2 + (M_PI / stacks), next_beta_top = M_PI/2 + (M_PI / stacks);
    double beta_bottom = -M_PI/2 - (M_PI / stacks), next_beta_bot = -M_PI/2 - (M_PI / stacks);

    int stack_iter = stacks / 2 + (stacks % 2 != 0);

    int nr_of_vertices = 3 * 6 * slices * (stack_iter + 1);
    outfile << nr_of_vertices << endl;

    for(int j=0; j < stack_iter + 1;j++) {

        beta_bottom += M_PI / stacks;
        beta_top -= M_PI / stacks;

        for(int i=0; i < slices;i++) {

            //----------------------------------------------------------------------------------------------------------
            // Draw each stack (optional)

            //Note: X = r * cos(b) * sin(a) | Y = r * sin(b) | Z = r * cos(b) * cos(a)

            //Top stacks of the sphere
            outfile << 0.0 << " "<< radius * sin(beta_top) << " "<< 0.0  << endl;
            outfile << radius * cos(beta_top) * sin(alpha * i) << " "<< radius * sin(beta_top) << " "<< radius * cos(beta_top) * cos(alpha*i)  <<  endl;
            outfile << radius * cos(beta_top) * sin(alpha*(i+1)) << " "<< radius * sin(beta_top) << " "<< radius * cos(beta_top) * cos(alpha*(i+1))  << endl;

            //Bottom stacks of the sphere
            outfile << 0.0 << " "<< radius * sin(beta_bottom) << " "<< 0.0  << endl;
            outfile << radius * cos(beta_bottom) * sin(alpha * i) << " "<< radius * sin(beta_bottom) << " "<< radius * cos(beta_bottom) * cos(alpha*i)  <<  endl;
            outfile << radius * cos(beta_bottom) * sin(alpha*(i+1)) << " "<< radius * sin(beta_bottom) << " "<< radius * cos(beta_bottom) * cos(alpha*(i+1))  << endl;

            //----------------------------------------------------------------------------------------------------------
            // Draw sides of each stack (top -> beta)


            //triangle 1 - top
            outfile << radius * cos(next_beta_top) * sin(alpha*i) << " "<<  radius * sin(next_beta_top) << " "<<  radius * cos(next_beta_top) * cos(alpha*i)  << endl;
            outfile  << radius * cos(beta_top) * sin(alpha*i) << " "<<  radius * sin(beta_top) << " "<<  radius * cos(beta_top) * cos(alpha*i)  << endl;
            outfile  << radius * cos(beta_top) * sin(alpha*(i+1)) << " "<<  radius * sin(beta_top) << " "<<  radius * cos(beta_top) * cos(alpha*(i+1))  << endl;

            //triangle 2 - top
            outfile << radius * cos(next_beta_top) * sin(alpha*i) << " "<<  radius * sin(next_beta_top) << " "<<  radius * cos(next_beta_top) * cos(alpha*i)  << endl;
            outfile << radius * cos(beta_top) * sin(alpha*(i+1)) << " "<<  radius * sin(beta_top) << " "<<  radius * cos(beta_top) * cos(alpha*(i+1))  << endl;
            outfile << radius * cos(next_beta_top) * sin(alpha*(i+1)) << " "<<  radius * sin(next_beta_top) << " "<<  radius * cos(next_beta_top) * cos(alpha*(i+1))  << endl;

            //triangle 1 - bottom
            outfile  << radius * cos(beta_bottom) * sin(alpha*i) << " "<<  radius * sin(beta_bottom) << " "<<  radius * cos(beta_bottom) * cos(alpha*i)  << endl;
            outfile << radius * cos(next_beta_bot) * sin(alpha*i) << " "<<  radius * sin(next_beta_bot) << " "<<  radius * cos(next_beta_bot) * cos(alpha*i)  << endl;
            outfile  << radius * cos(beta_bottom) * sin(alpha*(i+1)) << " "<<  radius * sin(beta_bottom) << " "<<  radius * cos(beta_bottom) * cos(alpha*(i+1))  << endl;

            //triangle 2 - bottom
            outfile << radius * cos(next_beta_bot) * sin(alpha*i) << " "<<  radius * sin(next_beta_bot) << " "<<  radius * cos(next_beta_bot) * cos(alpha*i)  << endl;
            outfile << radius * cos(next_beta_bot) * sin(alpha*(i+1)) << " "<<  radius * sin(next_beta_bot) << " "<<  radius * cos(next_beta_bot) * cos(alpha*(i+1))  << endl;
            outfile << radius * cos(beta_bottom) * sin(alpha*(i+1)) << " "<<  radius * sin(beta_bottom) << " "<<  radius * cos(beta_bottom) * cos(alpha*(i+1))  << endl;

        }

        next_beta_bot += M_PI / stacks;
        next_beta_top -= M_PI / stacks;

    }
    outfile.close();
}
