
#include <fstream>
#include <cmath>
#include <vector>
#include <iostream>
#include "headers/model-info.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------

void generate_plane_3d (double size, string file_name) {

    ofstream outfile(file_name);

    int nr_of_vertices = 4;

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

void generate_plane_indexed (double size, string file_name) {

    ofstream outfile(file_name);

    int nr_of_vertices = 4;
    int nr_indexes = 6;
    int nr_textCoords = nr_of_vertices;
    auto *textureCoordinates = new vector<POINT_3D>();

    outfile << nr_of_vertices << "," << nr_indexes << "," << nr_textCoords << "," << nr_of_vertices << endl;

    //Square: A---B (centred in (0,0,0))
    //        | / |
    //        C---D

    //Write vertexes-------------------------------------------

    //A
    outfile << size/2 << " " << 0 << " " << size/2 << endl;
    textureCoordinates -> push_back(*new POINT_3D(0.0f, 0.0f, 0.0f));
    //B
    outfile << -size/2 << " " << 0 << " " << -size/2 << endl;
    textureCoordinates -> push_back(*new POINT_3D(1.0f, 1.0f, 0.0f));
    //C
    outfile << -size/2 << " " << 0 << " " << size/2 << endl;
    textureCoordinates -> push_back(*new POINT_3D(1.0f, 0.0f, 0.0f));
    //D
    outfile << size/2 << " " << 0 << " " << -size/2 << endl;
    textureCoordinates -> push_back(*new POINT_3D(0.0f, 1.0f, 0.0f));

    //Write indexes--------------------------------------------

    //1st triangle: ABC
    outfile << 0 << endl << 1 << endl << 2 << endl;
    //2st triangle: BAD
    outfile << 1 << endl << 0 << endl << 3 << endl;

    //Write texture coordinates---------------------------------

    for (auto it = textureCoordinates -> begin(); it < textureCoordinates->end(); it++)
        outfile << -it->x << " " << it->y << endl;

    //Normal for plane vertexes
    auto *normal = new POINT_3D(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < 4; i++)
        outfile << normal->x << " " << normal->y << " " << normal->z << endl;

    outfile.close();
}

//----------------------------------------------------------------------------------------------------------------------

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

void generate_box_indexed (double x, double y, double z, int divisions, string file_name) {

    ofstream outfile(file_name);

    int off = pow((divisions + 2), 2);
    int nr_of_vertices = 6 * pow((divisions + 2), 2);
    int nr_indices = 6 * 6 * pow((divisions + 1), 2);
    int nr_textureCoords = nr_of_vertices;

    outfile << nr_of_vertices << "," << nr_indices << "," << nr_textureCoords << "," << nr_of_vertices << endl;

    auto *X0 = new vector<POINT_3D>();
    auto *Xmax = new vector<POINT_3D>();
    auto *Y0 = new vector<POINT_3D>();
    auto *Ymax = new vector<POINT_3D>();
    auto *Z0 = new vector<POINT_3D>();
    auto *Zmax = new vector<POINT_3D>();

    //Texture coordinates vector
    auto *textureCoordinates = new vector<POINT_3D>();

    //Generate vertexes
    for (int go_up = 0; go_up <= (divisions + 1); go_up++) {

        for (int go_right = 0; go_right <= (divisions + 1); go_right++) {

            // Plane X = 0
            X0->push_back(*new POINT_3D(
                0.0f,
                (y / (divisions + 1)) * (go_up),
                (z / (divisions + 1)) * (go_right)
            ));

            // Plane X = max
            Xmax->push_back(*new POINT_3D(
                    x,
                    (y / (divisions + 1)) * (go_up),
                    (z / (divisions + 1)) * (go_right)
            ));

            // Plane Y = 0
            Y0->push_back(*new POINT_3D(
                    (x / (divisions + 1)) * (go_up),
                    0.0f,
                    (z / (divisions + 1)) * (go_right)
            ));

            // Plane Y = max
            Ymax->push_back(*new POINT_3D(
                    (x / (divisions + 1)) * (go_up),
                    y,
                    (z / (divisions + 1)) * (go_right)
            ));

            // Plane Z = 0
            Z0->push_back(*new POINT_3D(
                    (x / (divisions + 1)) * (go_right),
                    (y / (divisions + 1)) * (go_up),
                    0
            ));

            // Plane Z = max
            Zmax->push_back(*new POINT_3D(
                    (x / (divisions + 1)) * (go_right),
                    (y / (divisions + 1)) * (go_up),
                    z
            ));

            textureCoordinates -> push_back(*new POINT_3D(
                    (float) -go_up / ((float) divisions + 1),
                    (float) -go_right / ((float) divisions + 1),
                    0.0f
            ));
        }
    }

    for (auto it = X0->begin(); it < X0->end(); it++)
        outfile << it->x << " " << it->y << " " << it->z << endl;
    for (auto it = Xmax->begin(); it < Xmax->end(); it++)
        outfile << it->x << " " << it->y << " " << it->z << endl;
    for (auto it = Y0->begin(); it < Y0->end(); it++)
        outfile << it->x << " " << it->y << " " << it->z << endl;
    for (auto it = Ymax->begin(); it < Ymax->end(); it++)
        outfile << it->x << " " << it->y << " " << it->z << endl;
    for (auto it = Z0->begin(); it < Z0->end(); it++)
        outfile << it->x << " " << it->y << " " << it->z << endl;
    for (auto it = Zmax->begin(); it < Zmax->end(); it++)
        outfile << it->x << " " << it->y << " " << it->z << endl;

    int iA, iB, iC, iD;
    //Generate indexes
    for (int go_up = 0; go_up <= divisions; go_up++) {

        for (int go_right = 0; go_right <= divisions; go_right++) {

            iA = (go_up + 1) * (divisions+2) + (go_right + 1);
            iB = (go_up + 1) * (divisions+2) + go_right;
            iC = (go_up) * (divisions+2) + go_right + 1;
            iD = (go_up) * (divisions+2) + go_right;

            //x = 0
            outfile << iA << endl << iB << endl << iD << endl;
            outfile << iC << endl << iA << endl << iD << endl;

            //x = max
            outfile << iD + off << endl << iB + off << endl << iA + off << endl;
            outfile << iA + off << endl << iC + off << endl << iD + off << endl;

            //y = 0
            outfile << iD + off*2 << endl << iB + off*2 << endl << iA + off*2 << endl;
            outfile << iA + off*2 << endl << iC + off*2 << endl << iD + off*2 << endl;

            //y = max
            outfile << iA + off*3 << endl << iB + off*3 << endl << iD + off*3 << endl;
            outfile << iC + off*3 << endl << iA + off*3 << endl << iD + off*3 << endl;

            //Z = 0
            outfile << iD + off*4 << endl << iB + off*4 << endl << iA + off*4 << endl;
            outfile << iA + off*4 << endl << iC + off*4 << endl << iD + off*4 << endl;

            //Z = max
            outfile << iA + off*5 << endl << iB + off*5 << endl << iD + off*5 << endl;
            outfile << iC + off*5 << endl << iA + off*5 << endl << iD + off*5 << endl;
        }
    }

    //write the texture coordinates to the output file
    for (int i = 0; i < 6; i++)
        for (auto it = textureCoordinates -> begin(); it < textureCoordinates->end(); it++)
            outfile << it->x << " " << it->y << endl;

    //Normals for X = 0 (plano YZ)
    for (int i = 0; i < nr_of_vertices/6; i++)
        outfile << -1.0f << " " << 0.0f << " " << 0.0f << endl;
    //Normals for X = max (plano YZ)
    for (int i = 0; i < nr_of_vertices/6; i++)
        outfile << +1.0f << " " << 0.0f << " " << 0.0f << endl;
    //Normals for Y = 0 (plano XZ)
    for (int i = 0; i < nr_of_vertices/6; i++)
        outfile << 0.0f << " " << -1.0f << " " << 0.0f << endl;
    //Normals for Y = max (plano XZ)
    for (int i = 0; i < nr_of_vertices/6; i++)
        outfile << 0.0f << " " << 1.0f << " " << 0.0f << endl;
    //Normals for Z = 0 (plano YX)
    for (int i = 0; i < nr_of_vertices/6; i++)
        outfile << 0.0f << " " << 0.0f << " " << -1.0f << endl;
    //Normals for Z = max (plano YX)
    for (int i = 0; i < nr_of_vertices/6; i++)
        outfile << 0.0f << " " << 0.0f << " " << +1.0f << endl;

    outfile.close();
}

//----------------------------------------------------------------------------------------------------------------------

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

void generate_cone_indexed (double radius, double height, int slices, int stacks, string file_name) {

    ofstream outfile(file_name);

    int nr_of_vertices = 2*(slices+1) + (slices+1) * (stacks + 1);
    int nr_indices = 3 * slices + 6 * stacks * slices;
    int nr_textureCoords = nr_of_vertices;

    outfile << nr_of_vertices << "," << nr_indices << "," << nr_textureCoords << "," << nr_of_vertices << endl;

    double alpha = 0.0, alpha_offset = 2 * M_PI / slices;
    double curr_x, curr_y, curr_z, new_radius;
    double stack_height = height / stacks;

    //Texture coordinates vector
    auto *textureCoordinates = new vector<POINT_3D>();

    //Normals for each vector
    auto *normalVector = new vector<POINT_3D>();

    float beta;
    for (int st = 0; st <= stacks; st++) {

        new_radius = radius - st * (radius / stacks);

        if (st == 0) {

            for (int sl = 0; sl <= slices; sl++) {

                //-------------------------------------------------------------------
                //write center

                outfile << 0.0f << " " << 0.0f << " " << 0.0f << endl;

                textureCoordinates -> push_back(*new POINT_3D(
                        0.5,
                        0.5,
                        0.0f
                ));

                normalVector -> push_back(*new POINT_3D(
                        0.0f,
                        -1.0f,
                        0.0f
                ));

                //-------------------------------------------------------------------

                alpha = sl * alpha_offset;

                curr_x = new_radius * sin(alpha);
                curr_y = st * stack_height;
                curr_z = new_radius * cos(alpha);

                //write vertex to output file
                outfile << curr_x << " " << curr_y << " " << curr_z << endl;

                textureCoordinates -> push_back(*new POINT_3D(
                        0.5f * sin(alpha) + 0.5f,
                        0.5f * cos(alpha) + 0.5f,
                        0.0f
                ));

                normalVector -> push_back(*new POINT_3D(
                        0.0f,
                        -1.0f,
                        0.0f
                ));
            }
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

            beta = atan(radius / height);

            normalVector -> push_back(*new POINT_3D(
                    cos(beta) * sin(alpha),
                    sin(beta),
                    cos(beta) * cos(alpha)
            ));
        }
    }

    int A, B, C, D, offset = 2*(slices+1);

    //write indexes
    for (int st = 0; st < stacks; st++) {

        if (st == 0) {

            for (int sl = 0; sl < slices; sl++) {

                //Considering a triangle ABC
                //       B
                //      /|
                //    /  |
                //  /    |
                // D_____C

                B = 0;
                D = 1 + sl * 2;
                C = D + 2;

                //Draw: BCD
                outfile << B << endl << C << endl << D << endl;
            }
        }

        for (int sl = 0; sl < slices; sl++) {

            //Considering a square ABCD
            // C_____D
            // |\    |
            // |  \  |
            // |    \|
            // A_____B

            A = offset + st * (slices + 1) + sl ;
            B = A + 1;
            C = offset + (st + 1) * (slices + 1) + sl ;
            D = C + 1;

            //Draw: ACB
            outfile << B << endl << C << endl << A << endl;

            //Draw: BCD
            outfile << D << endl << C << endl << B << endl;
        }
    }

    //write the texture coordinates to the output file
    for (auto it = textureCoordinates -> begin(); it < textureCoordinates->end(); it++)
        outfile << it->x << " " << it->y << endl;

    //write the texture coordinates to the output file
    for (auto it = normalVector -> begin(); it < normalVector->end(); it++)
        outfile << it->x << " " << it->y << " " << it->z << endl;

    outfile.close();
}

//----------------------------------------------------------------------------------------------------------------------

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


void generate_sphere_indexed (double radius, int slices, int stacks, string file_name) {

    //create file for the sphere model
    ofstream outfile(file_name);

    int nr_of_vertices = (stacks + 1) * (slices + 1);
    int nr_indices = 6 * stacks * slices;
    int nr_texture_coord = nr_of_vertices;
    outfile << nr_of_vertices << "," << nr_indices << "," << nr_texture_coord << "," << nr_of_vertices << endl;

    double alpha = 0.0, alpha_offset = 2 * M_PI / slices;
    double beta = 0.0, beta_offset = M_PI / stacks;
    double curr_x, curr_y, curr_z, new_radius = radius;

    //------------------------------------------------------------------------------------------------------------------
    //To store normals and texture coordinates

    //Texture coordinates vector
    auto *textureCoordinates = new vector<POINT_3D>();

    //Normals for each vector
    auto *normalVector = new vector<POINT_3D>();

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
                    1.0f - (st / (float) stacks),
                    0.0f
            ));

            normalVector -> push_back(*new POINT_3D(
                     curr_x/radius,
                     curr_y/radius,
                     curr_z/radius
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
    for (auto it = textureCoordinates -> begin(); it < textureCoordinates->end(); it++)
        outfile << it->x << " " << it->y << endl;

    //write the texture coordinates to the output file
    for (auto it = normalVector -> begin(); it < normalVector->end(); it++)
        outfile << it->x << " " << it->y << " " << it->z << endl;

    outfile.close();
}

//----------------------------------------------------------------------------------------------------------------------
