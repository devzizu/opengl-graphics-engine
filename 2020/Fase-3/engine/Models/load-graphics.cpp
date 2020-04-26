
/*--------------------------------------------------------------------------------------------------------------------*/
//Required libraries

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
#endif

/*--------------------------------------------------------------------------------------------------------------------*/
//Main imports

#define _USE_MATH_DEFINES
#include <math.h>
#include <cctype>

/*--------------------------------------------------------------------------------------------------------------------*/
//Custom imports

#include <model-info.h>
#include <draw-elements.h>
#include "VBO.h"

/*--------------------------------------------------------------------------------------------------------------------*/
//1) Global Variables

string WINDOW_TITLE = "Phase_3@CG_2020 | ? fps";
int frame = 0, fps = 0, timebase = 0;


/*--------------------------------------------------------------------------------------------------------------------*/

//Group structures
vector<Group> *sceneGroups;

/*--------------------------------------------------------------------------------------------------------------------*/
//2) Camera movements

//Translations
float alfa = 0.0f,
      beta = 0.0f,
      radius = 30.0f;

//float camX, camY, camZ;
float camX = -5.0f, camY = 0.0f, camZ = 0.0f;

float pos_x = 100.0f,
      pos_y = 0.0f,
      pos_z = 100.0f;

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
//Display useful information

void processFPS () {
    frame++;
    int time=glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        fps = frame*1000.0/(time-timebase);
        timebase = time;
        frame = 0;
        string newTitle = "Phase_3@CG_2020 | " + to_string(fps) + " fps";
        glutSetWindowTitle(newTitle.c_str());
    }
}

void displayRunningInformation() {

    cout << "[3] Everything was loaded: " << endl;

    cout << "\tVendor   : " << glGetString(GL_VENDOR) << endl;
    cout << "\tRenderer : " << glGetString(GL_RENDERER) << endl;
    cout << "\tVersion  : " << glGetString(GL_VERSION) << endl;

    cout << "[4] Useful Keys:" << endl;

    cout << "\tl   : " << "glPolygonMode(GL_FRONT, GL_LINE) " << endl;
    cout << "\tf   : " << "glPolygonMode(GL_FRONT, GL_FILL) " << endl;
    cout << "\tARROW_UP, ARROW_DW, ARROW_LEFT, ARROW_RIGHT : Move the camera." << endl;
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
    //glTranslatef(pos_x, pos_y, pos_z);

    //::1::Draw the axis
    glPushMatrix();
        drawAxis(50.0f, 50.0f, 50.0f);
    glPopMatrix();

    //TMP: Fill every model white
    glColor3f(1.0f, 1.0f, 1.0f);

    //::2::Iterate through all the scene groups
    for (auto iter = sceneGroups->begin(); iter != sceneGroups->end(); ++iter) {

        //Draw a single group and its child
        drawGroupElements(*iter);
    }

    /*----------------------------------------------------------------------------------------------------------------*/

    processFPS();

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

        case GLUT_KEY_PAGE_DOWN: radius -= 0.5f;
            if (radius < 0.1f)
                radius = 0.1f;
            break;

        case GLUT_KEY_PAGE_UP: radius += 0.5f; break;
    }

    spherical2Cartesian();

    glutPostRedisplay();
}

int load_graphics(vector<Group>* scene_groups, int argc, char** argv) {

    //------------------------------------------------------------------------------------------------------------------

    /*
     * Note: here argc and argv are inherit from the main() function
     *       where this was called
     * */

    //------------------------------------------------------------------------------------------------------------------
    //Setting up global variables

    //Loaded groups from the xml file
    sceneGroups = scene_groups;

    //------------------------------------------------------------------------------------------------------------------
    //Glut, Glew and VBOs Initialization

    //init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow(WINDOW_TITLE.c_str());

    //------------------------------------------------------------------------------------------------------------------

    #ifndef __APPLE__
        glewInit();
    #endif

    //------------------------------------------------------------------------------------------------------------------
    // VBOs Initialization

    //Enables vertex arrays when calling glDrawArrays or glDrawElements
    glEnableClientState(GL_VERTEX_ARRAY);

    initVBOs(sceneGroups);

    //------------------------------------------------------------------------------------------------------------------

    //Sets the screen size to fullscreen
    //glutFullScreen();

    //Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    //Callback registration for keyboard processing
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processKeys);

    //OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    spherical2Cartesian();


    displayRunningInformation();

    //------------------------------------------------------------------------------------------------------------------

    //GLUT's main cycle
    glutMainLoop();
}