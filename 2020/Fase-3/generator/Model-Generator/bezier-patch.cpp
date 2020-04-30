
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>

#include "headers/model-info.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------

//Bezier surface formula in matrix form
float M_BEZIER[4][4] = { { -1,  3, -3, 1 },
                         {  3, -6,  3, 0 },
                         { -3,  3,  0, 0 },
                         {  1,  0,  0, 0 } };

//----------------------------------------------------------------------------------------------------------------------

void multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

//----------------------------------------------------------------------------------------------------------------------

int load_bezier_patch(string path_to_patch, vector<struct POINT_3D>* control_points, vector<int>* patch_indices) {

    ifstream file_stream(path_to_patch);

    if (!file_stream.is_open()) {
        cout  << "[status] Could not read from " << path_to_patch << "!" << endl;
        return -1;
    }

    try {

        //--------------------------------------------------------------------------------------------------------------

        string line, delimiter = ",";

        int nr_patches = 0;
        int nr_controlPoints = 0;

        //line equal to 1 since line 0 has nr_patches
        int line_number = 1;

        //--------------------------------------------------------------------------------------------------------------

        getline(file_stream, line);
        nr_patches = stoi(line);

        //--------------------------------------------------------------------------------------------------------------

        while (getline(file_stream, line)) {

            //Get bezier patches reading as much lines as the
            //number indicated in the first line
            if (line_number <= nr_patches) {

                auto start = 0U;
                auto end = line.find(',');

                while (end != string::npos) {

                    patch_indices -> push_back(stoi(line.substr(start, end - start)));

                    start = end + delimiter.length();
                    end = line.find(delimiter, start);
                }

                patch_indices -> push_back(stoi(line.substr(start, end - start)));

                line_number++;

            } else {

                line_number++;

                if (line_number == 2 + nr_patches) {

                    nr_controlPoints = stoi(line);
                }

                if ((line_number > (2 + nr_patches)) &&
                    (line_number <= (line_number + nr_controlPoints))) {

                    float x, y, z;
                    sscanf(line.c_str(), " %f, %f, %f", &x, &y, &z);

                    POINT_3D* pt = new POINT_3D(x, y, z);

                    control_points -> push_back(*pt);
                }
            }

        }

        file_stream.close();

    } catch (...) {

        file_stream.close();
        cout << "Error parsing 3D model file in: " << path_to_patch << "..." << endl;
        return -1;
    }
}

//----------------------------------------------------------------------------------------------------------------------

void getVerticesInPatch(int patchNr, vector<int>* indices, vector<POINT_3D>* points, float* PijX, float* PijY, float* PijZ) {

    for (int i = 0; i < 16; i++) {

        PijX[i] = points->at(indices->at(i + patchNr * 16)).x;
        PijY[i] = points->at(indices->at(i + patchNr * 16)).y;
        PijZ[i] = points->at(indices->at(i + patchNr * 16)).z;
    }

}

//----------------------------------------------------------------------------------------------------------------------

POINT_3D* getBezierPoint(float u, float v, float *PijX, float *PijY, float *PijZ, float *resultCoords) {

    /*
     *  B(u, v) = SUM[3]_j=0 ( SUM[3]_i=0 ( B_i(u) * P_ij * B_j(v) ) )
     *
     *  Simplified:
     *  B(u, v) = [u^3 u^2 u 1] * M_BEZIER * Pij * M_BEZIER^T * [v^3 v^2 v 1]^T
    */

    float v_vector[4] = { (v * v * v), (v * v), v, 1 };

    //------------------------------------------------------------------------------------------------------------------

    /*
     * M_BEZIER (transpose) * v
     *
     * 1) m_t means M_BEZIER transpose
     * 2) M_BEZIER is symmetric M_transpose == M_BEZIER
     * 3) M_t * v = M * v => (4x4) * (4x1) = (4x1) => Mv_res
     * */

    float M_v[4];
    multMatrixVector(*M_BEZIER, v_vector, M_v);

    //------------------------------------------------------------------------------------------------------------------

    /*
     * Pij(x,y,z) * (M_BEZIER (transpose) * v)
     * */

    float Pxyz_M_v[3][4];
    multMatrixVector(PijX, M_v, Pxyz_M_v[0]);
    multMatrixVector(PijY, M_v, Pxyz_M_v[1]);
    multMatrixVector(PijZ, M_v, Pxyz_M_v[2]);

    //------------------------------------------------------------------------------------------------------------------

    /*
     * M_BEZIER * [Pij(x,y,z) * (M_BEZIER (transpose) * v)]
     * */

    float M_Pxyz_M_v[3][4];
    multMatrixVector(*M_BEZIER, Pxyz_M_v[0], M_Pxyz_M_v[0]);
    multMatrixVector(*M_BEZIER, Pxyz_M_v[1], M_Pxyz_M_v[1]);
    multMatrixVector(*M_BEZIER, Pxyz_M_v[2], M_Pxyz_M_v[2]);

    /*
     * u * {M_BEZIER * [Pij(x,y,z) * (M_BEZIER (transpose) * v)]}
     * */

    float u_vector[4] = { (u * u * u), (u * u), u, 1 };

    resultCoords[0] = 0.0f; resultCoords[1] = 0.0f; resultCoords[2] = 0.0f;

    for (int i = 0; i < 4; i++) {

        resultCoords[0] += u_vector[i] * M_Pxyz_M_v[0][i];
        resultCoords[1] += u_vector[i] * M_Pxyz_M_v[1][i];
        resultCoords[2] += u_vector[i] * M_Pxyz_M_v[2][i];
    }

    return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------

int generate_bezier_model(string outfile_path, vector<int>* patch_indices, vector<POINT_3D>* control_points, int tessellationLevel) {

    ofstream outfile(outfile_path);

    int nr_controlPoints = control_points -> size();
    int nr_indices = patch_indices -> size();
    int nr_patchs  = (nr_indices) / 16;

    cout << "\t-> Other properties (after parsing):" << endl;
    cout << "\t\t/ Control points     = " << nr_controlPoints << endl;
    cout << "\t\t/ Patchs (16 points) = " << nr_patchs << endl;
    cout << "\t\t/ Total indexes      = " << nr_indices << endl << endl;

    //Store here the vertices of each patch
    float Pij_X[16];
    float Pij_Y[16];
    float Pij_Z[16];

    //Current calculated point
    float bezierResultantPoint[3] = { 0.0f, 0.0f, 0.0f };

    //For divisions (tessellation)
    float t_u, t_v;

    //------------------------------------------------------------------------------------------------------------------
    //Process vertices

    //Run through all the patches having 16 vertices / patch
    for (int indice_in_patch = 0; indice_in_patch < nr_indices; indice_in_patch+=16) {

        int patch = indice_in_patch / 16;

        getVerticesInPatch(patch, patch_indices, control_points, Pij_X, Pij_Y, Pij_Z);

        for (int v = 0; v <= tessellationLevel; v++) {

            for (int u = 0; u <= tessellationLevel; u++) {

                t_u = ((float) u / (float) tessellationLevel);
                t_v = ((float) v / (float) tessellationLevel);

                getBezierPoint(t_u, t_v,
                               Pij_X, Pij_Y, Pij_Z,
                               bezierResultantPoint);

                outfile << bezierResultantPoint[0] << " "
                        << bezierResultantPoint[1] << " "
                        << bezierResultantPoint[2] << endl;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------
    //Process indices

    int nr_vertices_in_patch = pow(tessellationLevel + 1, 2);
    int iA, iB, iC, iD, patch, iOffset;

    for (int indice_in_patch = 0; indice_in_patch < nr_indices; indice_in_patch+=16) {

        for (int v = 0; v < tessellationLevel; v++) {

            for (int u = 0; u < tessellationLevel; u++) {

                    //Considering a square ABCD
                    // A_____B
                    // |    /|
                    // |  /  |
                    // |/    |
                    // C_____D
                    //Draw: ACB and then BCD

                    patch = indice_in_patch / 16;

                    iOffset = patch * nr_vertices_in_patch;

                    iA = iOffset + u + ((tessellationLevel+1) * v);
                    iB = iA + 1;
                    iC = iOffset + u + (tessellationLevel+1) * (v + 1);
                    iD = iC + 1;

                    outfile << iA << endl << iC << endl << iB << endl;
                    outfile << iB << endl << iC<< endl << iD << endl;
            }
        }
    }


    outfile.close();

    return 0;
}