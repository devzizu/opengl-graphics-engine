
/*--------------------------------------------------------------------------------------------------------------------*/
//Required libraries

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
    #include <IL/il.h>
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
#include <textures.h>
#include <VBO.h>
#include <lights.h>
#include <sstream>

/*--------------------------------------------------------------------------------------------------------------------*/
//1) Global Variables

string WINDOW_TITLE = "Phase_4@CG_2020 | ? fps";
int frame = 0, fps = 0, timebase = 0;

/*--------------------------------------------------------------------------------------------------------------------*/

//Group structures
vector<Group> *sceneGroups;
//Light sources structure
vector<LightSource> *sceneLights;

/*--------------------------------------------------------------------------------------------------------------------*/
//2) Camera movements

//Macros for the camera movements
#define CAM_RIGHT 6
#define CAM_LEFT -6
#define CAM_FORWARD 6
#define CAM_BACKWARD -6
#define CAM_VERTICAL_OFF 6

//Macros for camera angles offset
#define ALPHA_OFFSET 0.08f
#define BETA_OFFSET 0.08f

//Camera alpha, beta and radius
float alpha =-172.8f, beta = 0.0f, radius = 10.0f;

//Camera position in global space
float camX = 0.0f, camY = 0.0f, camZ = 800.0f;
//Camera look at point
float LookX = 0, LookY = 0, LookZ = 799.0f;

//Camera up vector
float v_up[3] = { 0.0f, 1.0f, 0.0f };
//Vector r: move sideways
float v_r[3] = {0.0f, 0.0f, 0.0f};
//Vector r: move sideways
float v_look_direction[3] = {0.0f, 0.0f, 0.0f};

/*--------------------------------------------------------------------------------------------------------------------*/
//Change the screen size, set the viewport, ...

int VIEWPORT_SET = 0;
bool ENABLE_MODEL_AXIS = false;

/*--------------------------------------------------------------------------------------------------------------------*/

void drawString(char *string)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( 0, w, 0, h, -1, 1 );

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable( GL_DEPTH_TEST );

    glDisable( GL_LIGHTING );
    glColor3f(0, 1, 0);

    int x = 20, y = 20;
    glRasterPos2i(x, y);
    void *font = GLUT_BITMAP_HELVETICA_12;
    for (char* c=string; *c != '\0'; c++)
    {

        if (*c == '\n')
        {
            y+=20;
            glRasterPos2i(x, y);
        }

        glutBitmapCharacter(font, *c);
    }

    if (!sceneLights->empty())
        glEnable( GL_LIGHTING );

    glEnable (GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void processRunningInformation() {

    std::stringstream ss;

    ss << " (Enable/Disable axis: 'q', Reset Camera: 'r', Polygon mode: 'l' -> line, 'f' -> fill)" << endl;
    ss << "Camera lookat   : x = " << LookX << ", y = " << LookY << ", z = " << LookZ << ", alpha = " << alpha << "º" << endl;
    ss << "Camera position : x = " << camX << ", y = " << camY << ", z = " << camZ << endl;
    ss << "Engine Model Simulation" << endl;

    drawString((char*) ss.str().c_str());
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

    //Normal viewport
    if (VIEWPORT_SET == 0) {

        // Set the viewport to be the entire window
        glViewport(0, 0, w, h);

    } else if (VIEWPORT_SET == 1) {

        // Small square view
        glViewport(w/2+20, h/2+20, w/2 - 20, h/2 - 20);

    }

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,10000.0f);

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
        string newTitle = "Phase_4@CG_2020 | " + to_string(fps) + " fps";
        glutSetWindowTitle(newTitle.c_str());
    }
}

void displayRunningInformation() {

    cout << "[4] Everything was loaded: " << endl;

    cout << "\tVendor   : " << glGetString(GL_VENDOR) << endl;
    cout << "\tRenderer : " << glGetString(GL_RENDERER) << endl;
    cout << "\tVersion  : " << glGetString(GL_VERSION) << endl;

    cout << "[4.1] Useful Keys:" << endl;

    cout << "\tl   : " << "glPolygonMode(GL_FRONT, GL_LINE) " << endl;
    cout << "\tf   : " << "glPolygonMode(GL_FRONT, GL_FILL) " << endl;
    cout << "\tARR_UP, ARR_DW, ARR_LEFT, ARR_RIGHT : Move the camera around a sphere." << endl;
    cout << "\tW, A, S, D : Forward, Backward, Left and Right motion." << endl;
    cout << "\tR : reset camera position to (0,0,0)." << endl;
    cout << "\tQ : Enable/Disable model axis." << endl;
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
    //Load lights in the scene
    for (auto it = sceneLights->begin(); it < sceneLights->end(); it++) {

        //Default glLight parameters/values
        //https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glLight.xml

        glClearColor(0, 0, 0, 0);

        GLenum lightIndex = GL_LIGHT0 + it -> lightEnumNumber;

        //light pos = {x,y,z,w}, case w = 0 -> vector, case w = 1 -> point
        glLightfv(lightIndex, GL_POSITION, it -> point);

        glLightfv(lightIndex, GL_SPECULAR, it -> specularComponent);
        glLightfv(lightIndex, GL_AMBIENT, it -> ambientComponent);
        glLightfv(lightIndex, GL_DIFFUSE, it -> diffuseComponent);
        //glLightf(lightIndex, GL_SHININESS, 2);

        if (it -> lightType == "SPOT") {

            glLightfv(lightIndex, GL_SPOT_DIRECTION, it -> SpotDirection);
            glLightf(lightIndex, GL_SPOT_EXPONENT, it -> SpotExponent);
            glLightf(lightIndex, GL_SPOT_CUTOFF, it -> SpotCutoff);
        }
    }

    /*----------------------------------------------------------------------------------------------------------------*/
    //Load the scene based on the structures

    //TMP: Fill every model white
    //glColor3f(1.0f, 1.0f, 1.0f);

    //::2::Iterate through all the scene groups
    for (auto iter = sceneGroups->begin(); iter != sceneGroups->end(); ++iter) {

        //Draw a single group and its child
        drawGroupElements(*iter, sceneLights->empty(), ENABLE_MODEL_AXIS);
    }

    /*----------------------------------------------------------------------------------------------------------------*/

    // Updates window information about frames/second
    processFPS();

    processRunningInformation();

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
        case 'q':

            if (ENABLE_MODEL_AXIS)
                ENABLE_MODEL_AXIS = false;
            else ENABLE_MODEL_AXIS = true;

            break;

        case 'r':

            camX = 0;
            camY = 0;
            camZ = 0;

            break;

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

void initClientState() {

    //Enables vertex arrays when calling glDrawArrays or glDrawElements
    glEnableClientState(GL_VERTEX_ARRAY);
    //Enables vertex normals arrays
    glEnableClientState(GL_NORMAL_ARRAY);
    //Enables texture coordinate arrays for rendering
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

}

int load_graphics(pair<vector<Group>*, vector<LightSource>*> scene, int argc, char** argv) {

    //------------------------------------------------------------------------------------------------------------------

    /*
     * Note: here argc and argv are inherit from the main() function
     *       where this was called
     * */

    //------------------------------------------------------------------------------------------------------------------
    //Setting up global variables

    //Loaded groups from the xml file
    sceneGroups = scene.first;
    //Loaded lights from the xml file
    sceneLights = scene.second;

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

    //Enable all client states
    initClientState();

    //Enables 2D textures
    glEnable(GL_TEXTURE_2D);

    //------------------------------------------------------------------------------------------------------------------
    // Initialization of VBOs, Textures, DevIl, ...

    initLights(scene);
    initVBOs(sceneGroups);
    initTextures(sceneGroups);

    //------------------------------------------------------------------------------------------------------------------

    //Sets the screen size to fullscreen
    glutFullScreen();

    //Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    //Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    glShadeModel(GL_SMOOTH);
    //OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glEnable(GL_COLOR_MATERIAL);

    //glEnable(GL_NORMALIZE);
    glEnable(GL_RESCALE_NORMAL);

    spherical2Cartesian();

    //Shows available keys, gpu information, ...
    displayRunningInformation();

    //------------------------------------------------------------------------------------------------------------------

    //GLUT's main cycle
    glutMainLoop();
}