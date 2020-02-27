
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

void generate_box (double x, double y, double z, int divisions, string file_name) {

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