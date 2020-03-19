
#include <iostream>

#include "Model-Generator/model-generator.h"

using namespace std;

#define GENERATED_FILES "../../examples/Model-Read-Tests/"

string arg_cmd (int argc, char* argv[]) {
    string cmd = "";
    for (int i = 0; i < argc; i++) {
        cmd += argv[i];
        cmd += " ";
    }
    return cmd;
}

void cat_command_options (string invalid_cmd) {

    cout << "Invalid command: " << invalid_cmd << endl << endl;
    cout << "Command options: " << endl << endl;
    cout << "plane   : generator plane <dim> <outfile>" << endl;
    cout << "box     : generator box <X> <Y> <Z> <outfile>" << endl;
    cout << "box-div : generator box <X> <Y> <Z> <divisions> <outfile>" << endl;
    cout << "sphere  : generator sphere <radius> <slices> <stacks> <outfile>" << endl;
    cout << "cone    : generator cone <bot-radius> <height> <slices> <stacks> <outfile>" << endl;
}

void cat_end_program() {
    cout << endl << "Program finished..." << endl << endl;
}

int main(int argc, char* argv[]) {

    //------------------------------------------------------------------------------------------------------------------

    //Clear the console
    system("clear");

    cout << endl << "Generator starting..." << endl << endl;

    //------------------------------------------------------------------------------------------------------------------
    //Insufficient arguments

    if (argc <= 1) {
        cat_command_options(arg_cmd(argc, argv));
        cat_end_program();

        return 0;
    }

    //------------------------------------------------------------------------------------------------------------------

    string selected_model = argv[1];

    if (selected_model == "plane") {
    //generator plane <dim> <outfile>

        try {

            double dim = stod(argv[2]);

            string output_file = argv[3];

            cout << "[status] Generating vertices for: " << endl;

            cout << "\t-> Model       : " << selected_model << "," << endl;
            cout << "\t-> Properties  : " << endl;
            cout << "\t\t / Side-Dimension = " << dim << "." << endl;
            cout << "\t-> Output file : " << "Model-Vertices-Files/" + output_file << endl;

            generate_plane_3d(dim, GENERATED_FILES + output_file);

            cout << "[status] All vertices were generated... " << endl << endl;

        } catch (...) {
            cat_command_options(arg_cmd(argc, argv)); cat_end_program();
            return 0;
        }

    } else if (selected_model == "box") {

        try {

            double X = stod(argv[2]), Y = stod(argv[3]), Z = stod(argv[4]);

            if (argc == 6) { //without dimensions
            //generator box <X> <Y> <Z> <outfile>

                string output_file = argv[5];

                cout << "[status] Generating vertices for: " << endl;

                cout << "\t-> Model       : " << selected_model << "," << endl;
                cout << "\t-> Properties  : " << endl;
                cout << "\t\t / X = " << X << "," << endl;
                cout << "\t\t / Y = " << Y << "," << endl;
                cout << "\t\t / Z = " << Z << "," << endl;
                cout << "\t-> Output file : " << "Model-Vertices-Files/" + output_file << endl;

                generate_box_3d(X, Y, Z, 0, GENERATED_FILES + output_file);

                cout << "[status] All vertices were generated... " << endl << endl;

            } else if (argc == 7) { //with dimensions
            //generator box <X> <Y> <Z> <divisions> <outfile>

                int divisions = stod(argv[5]);
                string output_file = argv[6];

                cout << "[status] Generating vertices for: " << endl << endl;

                cout << "\t-> Model       : " << selected_model << "," << endl;
                cout << "\t-> Properties  : " << endl;
                cout << "\t\t / X   = " << X << "," << endl;
                cout << "\t\t / Y   = " << Y << "," << endl;
                cout << "\t\t / Z   = " << Z << "," << endl;
                cout << "\t\t / Div = " << divisions << "," << endl;
                cout << "\t-> Output file : " << "Model-Vertices-Files/" + output_file << endl;

                generate_box_3d(X, Y, Z, divisions, GENERATED_FILES + output_file);

                cout << "[status] All vertices were generated... " << endl << endl;
            }

        } catch (...) { cat_command_options(arg_cmd(argc, argv)); cat_end_program(); return 0; }

    } else if (selected_model == "sphere") {
    //generator sphere <radius> <slices> <stacks> <outfile>

        try {

            double radius = stod(argv[2]);
            int slices = stod(argv[3]), stacks = stod(argv[4]);
            string output_file = argv[5];

            cout << "[status] Generating vertices for: " << endl;

            cout << "\t-> Model       : " << selected_model << "," << endl;
            cout << "\t-> Properties  : " << endl;
            cout << "\t\t / Radius   = " << radius << "," << endl;
            cout << "\t\t / Slices   = " << slices << "," << endl;
            cout << "\t\t / Stacks   = " << stacks << "," << endl;
            cout << "\t-> Output file : " << "Model-Vertices-Files/" + output_file << endl;

            generate_sphere_3d (radius, slices, stacks, GENERATED_FILES + output_file);

            cout << "[status] All vertices were generated... " << endl << endl;

        } catch (...) { cat_command_options(arg_cmd(argc, argv)); cat_end_program(); return 0; }

    } else if (selected_model == "cone") {
    //generator cone <bot-radius> <height> <slices> <stacks> <outfile>

        try {

            double radius = stod(argv[2]), height = stod(argv[3]);
            int slices = stod(argv[4]), stacks = stod(argv[5]);
            string output_file = argv[6];

            cout << "[status] Generating vertices for: " << endl;

            cout << "\t-> Model       : " << selected_model << "," << endl;
            cout << "\t-> Properties  : " << endl;
            cout << "\t\t / Radius   = " << radius << "," << endl;
            cout << "\t\t / Height   = " << height << "," << endl;
            cout << "\t\t / Slices   = " << slices << "," << endl;
            cout << "\t\t / Stacks   = " << stacks << "," << endl;
            cout << "\t-> Output file : " << GENERATED_FILES + output_file << endl;

            generate_cone_3d(radius, height, slices, stacks, GENERATED_FILES + output_file);

            cout << "[status] All vertices were generated... " << endl << endl;

        } catch (...) { cat_command_options(arg_cmd(argc, argv)); cat_end_program(); return 0; }

    } else {

        cat_command_options(arg_cmd(argc, argv));
    }

    cat_end_program();

    return 0;
}
