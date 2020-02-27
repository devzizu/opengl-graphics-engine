
#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

void generate_plane_3d (int size, string file_name) {

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

void generate_box (int x, int y, int z, int divisions, string file_name) {

    ofstream outfile(file_name);

    int nr_of_vertices = 6 * 6 * pow((1+divisions), 2);

    outfile << nr_of_vertices << endl;

    int iterations = pow((divisions+1), 2);

    //Bottom rectangles (Plane XZ, Y = 0)
    for (int go_up = 0; go_up < (divisions + 1); go_up++) {

        for (int go_right = 0; go_right < (divisions + 1);go_right++) {

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
        }
    }

    for (int go_up = 0; go_up < (divisions + 1); go_up++) {

        for (int go_right = 0; go_right < (divisions + 1);go_right++) {

            //First triangle
            outfile << (x/(divisions+1)) * (go_right + 1) << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << 0 << endl;
            outfile << (x/(divisions+1)) * go_right << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << 0 << endl;
            outfile << (x/(divisions+1)) * go_right << " "
                    << (y/(divisions+1)) * go_up << " "
                    << 0 << endl;

            //Second triangle
            outfile << (x/(divisions+1)) * (go_right + 1) << " "
                    << (y/(divisions+1)) * (go_up + 1) << " "
                    << 0 << endl;
            outfile << (x/(divisions+1)) * go_right << " "
                    << (y/(divisions+1)) * go_up << " "
                    << 0 << endl;
            outfile << (x/(divisions+1)) * (go_right + 1) << " "
                    << (y/(divisions+1)) * go_up << " "
                    << 0 << endl;
        }
    }

    outfile.close();
}

int main(int argc, char* argv[]) {

    string xml_generated_files_path = "../XML-Examples/";

    //generate_plane_3d(4, xml_generated_files_path + "plane.3d");
    generate_box(8, 2, 3, 20, xml_generated_files_path + "box.3d");

    return 0;
}
