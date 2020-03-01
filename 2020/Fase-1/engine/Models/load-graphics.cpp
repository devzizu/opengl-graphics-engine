#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <cctype>

#include <model-info.h>

//Global variables

//Models
vector<MODEL_INFO> models_list;
//Translations
float pos_x = 0.0f,
      pos_y = 0.0f,
      pos_z = 0.0f;

float rotation = 0.0f;

void drawAxis() {

    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f( 5.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();
}

void draw_model(MODEL_INFO* model) {

    glBegin(GL_TRIANGLES);

    float red = 1.0f;
    float green = 0.0f;
    float blue = 0.0f;

    vector<POINT_3D> vertices = model->getVertices();
    for(auto it = vertices.begin(); it != vertices.end(); it++) {
        glColor3f(red, green, blue);
        glVertex3f(it->getX(), it->getY(), it->getZ());
        if(red == 1.0f) {
            red = 0.0f;
            green = 1.0f;
        }
        else if(green == 1.0f) {
            green = 0.0f;
            blue = 1.0f;
        }
        else if(blue = 1.0f) {
            red = 1.0f;
            blue = 0.0f;
        }

    }

    glEnd();
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(10.0f,12.0f,5.0f,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    drawAxis();

    glTranslatef(pos_x, pos_y, pos_z);
    glRotatef(rotation, 0, 0, 1.0f);

    for(auto it = models_list.begin(); it != models_list.end(); ++it) {

        draw_model(it.base());
    }

    // End of frame
    glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {

    switch(tolower(c)) {

        case 'f':
            glPolygonMode(GL_FRONT, GL_FILL);
            break;
        case 'l':
            glPolygonMode(GL_FRONT, GL_LINE);
            break;
        case 'w':
            pos_x-=0.1f;
            break;
        case 'a':
            pos_z+=0.1f;
            break;
        case 's':
            pos_x+=0.1f;
            break;
        case 'd':
            pos_z-=0.1f;
            break;
        case 'r':
            rotation+=0.5;
            break;
    }

    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

}

int load_graphics(vector<MODEL_INFO> models, int argc, char** argv) {

    //load models pointer to global variable
    models_list = models;
    //default values
    // int argc; char* argv[0];

    //init GLUT and the window
    glutInit(&argc, argv);
    cout << "lol" << endl;
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Phase_1@CG_2020");

    //Sets the screen size to fullscreen
    glutFullScreen();

    //Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    //Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    //OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glPolygonMode(GL_FRONT, GL_LINE);

    //GLUT's main cycle
    glutMainLoop();
}