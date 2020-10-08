#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <cctype>

#include <model-info.h>
#include <draw-elements.h>

/*--------------------------------------------------------------------------------------------------------------------*/
//1) Global Variables

//Group structures
vector<Group> *sceneGroups;

/*--------------------------------------------------------------------------------------------------------------------*/
//2) Camera movements

//Translations
float alfa = 0.0f,
      beta = 0.0f,
      radius = 30.0f;

float camX, camY, camZ;

float pos_x = -15.0f,
      pos_y = 0.0f,
      pos_z = 0.0f;

float rotation = 0.0f;

/*--------------------------------------------------------------------------------------------------------------------*/
//Change the screen size, set the viewport, ...

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

/*--------------------------------------------------------------------------------------------------------------------*/
//Render scene function

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);


    /*----------------------------------------------------------------------------------------------------------------*/
    //Load the scene based on the structures

    //TMP: Move models in the XZ plane
    glTranslatef(pos_x, pos_y, pos_z);

    //::1::Draw the axis
    glPushMatrix();
    drawAxis();
    glPopMatrix();

    //TMP: Fill every model white
    glColor3f(1.0f, 1.0f, 1.0f);

    //::2::Iterate through all the scene groups
    for (auto iter = sceneGroups->begin(); iter != sceneGroups->end(); ++iter) {

        //Draw a single group and its childs
        drawGroupElements(*iter);
    }

    /*----------------------------------------------------------------------------------------------------------------*/

    // End of frame
    glutSwapBuffers();
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Convert spherical to cartesian

void spherical2Cartesian() {

    camX = radius * cos(beta) * sin(alfa);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alfa);
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process normal keys

void processKeys(unsigned char c, int xx, int yy) {

    switch(tolower(c))
    {
        case 'w':
            pos_z+=0.1f;
            break;
        case 'a':
            pos_x+=0.1f;
            break;
        case 's':
            pos_z-=0.1f;
            break;
        case 'd':
            pos_x-=0.1f;
            break;
        case 'f':
            glPolygonMode(GL_FRONT, GL_FILL);
            break;
        case 'l':
            glPolygonMode(GL_FRONT, GL_LINE);
            break;
    }

    glutPostRedisplay();
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process special keys

void processSpecialKeys(int key, int xx, int yy)
{
    switch (key)
    {
        case GLUT_KEY_F1:
            glPolygonMode(GL_FRONT, GL_FILL);
            break;

        case GLUT_KEY_F2:
            glPolygonMode(GL_FRONT, GL_LINE);
            break;

        case GLUT_KEY_RIGHT:
            alfa -= 0.1; break;

        case GLUT_KEY_LEFT:
            alfa += 0.1; break;

        case GLUT_KEY_UP:
            beta += 0.1f;
            if (beta > 1.5f)
                beta = 1.5f;
            break;

        case GLUT_KEY_DOWN:
            beta -= 0.1f;
            if (beta < -1.5f)
                beta = -1.5f;
            break;

        case GLUT_KEY_PAGE_DOWN: radius -= 0.1f;
            if (radius < 0.1f)
                radius = 0.1f;
            break;

        case GLUT_KEY_PAGE_UP: radius += 0.1f; break;
    }

    spherical2Cartesian();

    glutPostRedisplay();
}


int load_graphics(vector<Group>* scene_groups, int argc, char** argv) {

    //Note: here argc and argv are inherit from the main() function
    //      where this wall called

    //Assign global variable scene_groups with the loaded groups vector
    sceneGroups = scene_groups;

    //init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Phase_2@CG_2020");

    //Sets the screen size to fullscreen
    glutFullScreen();

    //Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    //Callback registration for keyboard processing
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processKeys);

    //OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //Set the polygon display mode
    glPolygonMode(GL_FRONT, GL_FILL);

    //...
    spherical2Cartesian();

    //GLUT's main cycle
    glutMainLoop();
}