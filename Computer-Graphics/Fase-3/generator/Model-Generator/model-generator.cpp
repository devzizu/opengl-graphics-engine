
#include <fstream>
#include <cmath>

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

            //Note: X = r * cos(b) * sin(a) | Y = r * sin(b) | Z = r * cos(b) * cos(a)

            //Top stacks of the sphere
            outfile << 0.0 << " "<< radius * sin(beta_top) << " "<< 0.0  << endl;
            outfile << radius * cos(beta_top) * sin(alpha * i) << " "<< radius * sin(beta_top) << " "<< radius * cos(beta_top) * cos(alpha*i)  <<  endl;
            outfile << radius * cos(beta_top) * sin(alpha*(i+1)) << " "<< radius * sin(beta_top) << " "<< radius * cos(beta_top) * cos(alpha*(i+1))  << endl;

            //Bottom stacks of the sphere
            outfile << 0.0 << " "<< radius * sin(beta_bottom) << " "<< 0.0  << endl;
            outfile << radius * cos(beta_bottom) * sin(alpha * i) << " "<< radius * sin(beta_bottom) << " "<< radius * cos(beta_bottom) * cos(alpha*i)  <<  endl;
            outfile << radius * cos(beta_bottom) * sin(alpha*(i+1)) << " "<< radius * sin(beta_bottom) << " "<< radius * cos(beta_bottom) * cos(alpha*(i+1))  << endl;

            // Sides of each stack

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
