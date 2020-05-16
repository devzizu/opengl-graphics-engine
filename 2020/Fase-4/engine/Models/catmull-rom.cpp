
#define _USE_MATH_DEFINES
#include <math.h>
#include <model-info.h>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

using namespace std;

void buildRotMatrix(float *x, float *y, float *z, float *m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

float length(float *v) {

    float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    return res;

}

void multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

    //----------------------------------------------------------------------------------------------------

    // catmull-rom matrix

    float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
                         { 1.0f, -2.5f,  2.0f, -0.5f},
                         {-0.5f,  0.0f,  0.5f,  0.0f},
                         { 0.0f,  1.0f,  0.0f,  0.0f}};


    //----------------------------------------------------------------------------------------------------

    float T[4]  = { t*t*t, t*t, t, 1 };
    float TD[4] = { 3*t*t, 2*t, 1, 0 };

    //----------------------------------------------------------------------------------------------------

    // Compute A = M * P

    float P[3][4] = { { p0[0], p1[0], p2[0], p3[0] },
                      { p0[1], p1[1], p2[1], p3[1] },
                      { p0[2], p1[2], p2[2], p3[2] }
    };


    float A[3][4];

    multMatrixVector(*m, P[0], A[0]);
    multMatrixVector(*m, P[1], A[1]);
    multMatrixVector(*m, P[2], A[2]);

    //----------------------------------------------------------------------------------------------------

    // Compute pos = T * A

    for (int i = 0; i < 4; i++) {

        pos[0] += T[i] * A[0][i];
        pos[1] += T[i] * A[1][i];
        pos[2] += T[i] * A[2][i];
    }

    //----------------------------------------------------------------------------------------------------

    // compute deriv = T' * A

    for (int i = 0; i < 4; i++) {

        deriv[0] += TD[i] * A[0][i];
        deriv[1] += TD[i] * A[1][i];
        deriv[2] += TD[i] * A[2][i];
    }

}

void getGlobalCatmullRomPoint(vector<POINT_3D>* points, float gt, float *pos, float *deriv) {

    int POINT_COUNT = points -> size();

    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
    indices[1] = (indices[0]+1)%POINT_COUNT;
    indices[2] = (indices[1]+1)%POINT_COUNT;
    indices[3] = (indices[2]+1)%POINT_COUNT;

    //stores the base points for the curve
    float p[4][3];

    for (int i = 0; i < 4; i++) {

        p[i][0] = points -> at(indices[i]).x;
        p[i][1] = points -> at(indices[i]).y;
        p[i][2] = points -> at(indices[i]).z;
    }

    getCatmullRomPoint(t, p[0], p[1], p[2], p[3], pos, deriv);
}

void renderCatmullRomCurve(vector<POINT_3D>* points) {

    //cout << "Inicio" << endl;

    //----------------------------------------------------------

    // draw curve using line segments with GL_LINE_LOOP

    glBegin(GL_POINTS);

    for (int i = 0; i < 200; i++) {

        float pos[3] = { 0.0, 0.0, 0.0 };
        float deriv[3] = { 0.0, 0.0, 0.0 };
        float gt = i / 200.0f;

        getGlobalCatmullRomPoint(points, gt, (float*)pos, (float*)deriv);

        glVertex3f(pos[0], pos[1], pos[2]);
    }

    glEnd();

    //----------------------------------------------------------

    //cout << "Fim..." << endl;
}