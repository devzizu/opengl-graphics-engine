
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
#include <catmull-rom.h>
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

//Macros for the camera movements
#define CAM_RIGHT 5
#define CAM_LEFT -5
#define CAM_FORWARD 5
#define CAM_BACKWARD -5
#define CAM_VERTICAL_OFF 5

//Macros for camera angles offset
#define ALPHA_OFFSET 0.08f
#define BETA_OFFSET 0.08f

//Camera alpha, beta and radius
float alpha = 0.0f, beta = 0.0f, radius = 10.0f;

//Camera position in global space
float camX = 0.0f, camY = 0.0f, camZ = -80.0f;
//Camera look at point
float LookX = 0, LookY = 0, LookZ = 0;

//Camera up vector
float v_up[3] = { 0.0f, 1.0f, 0.0f };
//Vector r: move sideways
float v_r[3] = {0.0f, 0.0f, 0.0f};
//Vector r: move sideways
float v_look_direction[3] = {0.0f, 0.0f, 0.0f};

/*--------------------------------------------------------------------------------------------------------------------*/
//Change the screen size, set the viewport, ...

int VIEWPORT_SET = 0;

/*--------------------------------------------------------------------------------------------------------------------*/

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

    //Normal viewport
    if (VIEWPORT_SET == 0) {

        // Set the viewport to be the entire window
        glViewport(0, 0, w, h);


    } else if (VIEWPORT_SET == 1) {

        // Small square view
        glViewport(w/2+20, h/2+20, w/2 - 20, h/2 - 20);

    }

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,100000.0f);

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
    cout << "\tARR_UP, ARR_DW, ARR_LEFT, ARR_RIGHT : Move the camera around a sphere." << endl;
    cout << "\tW, A, S, D : Forward, Backward, Left and Right motion." << endl;
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Render scene function

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*----------------------------------------------------------------------------------------------------------------*/

    //Control camera look position
    LookX = camX + sin(alpha);
    LookY = camY + sin(beta);
    LookZ = camZ + cos(alpha);

    // set the camera
    glLoadIdentity();

    gluLookAt( camX,  camY,  camZ,
              LookX, LookY, LookZ,
              0.0f,1.0f,0.0f);

    /*----------------------------------------------------------------------------------------------------------------*/
    //Load the scene based on the structures

    //TMP: Move models in the XZ plane
    //glTranslatef(pos_x, pos_y, pos_z);

    //::1::Draw the axis
    glPushMatrix();
        //drawAxis(50.0f, 50.0f, 50.0f);
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

    LookX = radius * cos(beta) * sin(alpha);
    LookY = radius * sin(beta);
    LookZ = radius * cos(beta) * cos(alpha);
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

        case 'n':

            VIEWPORT_SET = 0;

            break;

        case 'm':

            VIEWPORT_SET = 1;

            break;

        case ' ':

            camY+=CAM_VERTICAL_OFF;

            break;

        case '2':

            camY-=CAM_VERTICAL_OFF;

            break;

        case 'w': //forward movement

            //----------------------------------------------------------------------------------------------------------

            //look direction vector
            //d = L - P = (Lx - Px, 0, Lz - Pz)
            v_look_direction[0] = LookX - camX;
            v_look_direction[1] = LookY - camY;
            v_look_direction[2] = LookZ - camZ;

            normalize(v_look_direction);

            //update camera position adding look direction vector
            //P' = P + k * direction
            camX = camX + CAM_FORWARD * v_look_direction[0];
            camY = camY + CAM_FORWARD * v_look_direction[1];
            camZ = camZ + CAM_FORWARD * v_look_direction[2];

            //Update looking point
            //L' = L + k * direction
            LookX = LookX + CAM_FORWARD * v_look_direction[0];
            LookY = LookY + CAM_FORWARD * v_look_direction[1];
            LookZ = LookZ + CAM_FORWARD * v_look_direction[2];

            //----------------------------------------------------------------------------------------------------------

            break;

        case 's': //backward movement

            //----------------------------------------------------------------------------------------------------------

            //look direction vector
            //d = L - P = (Lx - Px, 0, Lz - Pz)
            v_look_direction[0] = LookX - camX;
            v_look_direction[1] = LookY - camY;
            v_look_direction[2] = LookZ - camZ;

            normalize(v_look_direction);

            //update camera position adding look direction vector
            //P' = P + k * direction
            camX = camX + CAM_BACKWARD * v_look_direction[0];
            camY = camY + CAM_BACKWARD * v_look_direction[1];
            camZ = camZ + CAM_BACKWARD * v_look_direction[2];

            //Update looking point
            //L' = L + k * direction
            LookX = LookX + CAM_BACKWARD * v_look_direction[0];
            LookY = LookY + CAM_BACKWARD * v_look_direction[1];
            LookZ = LookZ + CAM_BACKWARD * v_look_direction[2];

            //----------------------------------------------------------------------------------------------------------

            break;

        case 'a':

            //----------------------------------------------------------------------------------------------------------

            v_look_direction[0] = LookX - camX;
            v_look_direction[1] = LookY - camY;
            v_look_direction[2] = LookZ - camZ;

            normalize(v_look_direction);

            //r = d x up
            cross(v_look_direction, v_up, v_r);

            //P' = P + k * direction
            camX = camX + CAM_LEFT * v_r[0];
            camY = camY + CAM_LEFT * v_r[1];
            camZ = camZ + CAM_LEFT * v_r[2];

            //L' = L + k * direction
            LookX = LookX + CAM_LEFT * v_r[0];
            LookY = LookY + CAM_LEFT * v_r[1];
            LookZ = LookZ + CAM_LEFT * v_r[2];

            //----------------------------------------------------------------------------------------------------------

            break;

        case 'd':

            //----------------------------------------------------------------------------------------------------------

            v_look_direction[0] = LookX - camX;
            v_look_direction[1] = LookY - camY;
            v_look_direction[2] = LookZ - camZ;

            normalize(v_look_direction);

            //r = d x up
            cross(v_look_direction, v_up, v_r);

            //P' = P + k * direction
            camX = camX + CAM_RIGHT * v_r[0];
            camY = camY + CAM_RIGHT * v_r[1];
            camZ = camZ + CAM_RIGHT * v_r[2];

            //L' = L + k * direction
            LookX = LookX + CAM_RIGHT * v_r[0];
            LookY = LookY + CAM_RIGHT * v_r[1];
            LookZ = LookZ + CAM_RIGHT * v_r[2];

            //----------------------------------------------------------------------------------------------------------

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
        case GLUT_KEY_RIGHT:
            alpha -= ALPHA_OFFSET; break;

        case GLUT_KEY_LEFT:
            alpha += ALPHA_OFFSET; break;

        case GLUT_KEY_UP :
            beta += BETA_OFFSET;
            if (beta > 1.5f)
                beta = 1.5f;
            break;

        case GLUT_KEY_DOWN:
            beta -= BETA_OFFSET;
            if (beta < -1.5f)
                beta = -1.5f;
            break;
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
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    //OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    spherical2Cartesian();

    displayRunningInformation();

    //------------------------------------------------------------------------------------------------------------------

    //GLUT's main cycle
    glutMainLoop();
}