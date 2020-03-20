#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <model-info.h>

#endif

/*--------------------------------------------------------------------------------------------------------------------*/
//Draw the axis on the screen

void drawAxis() {

    glBegin(GL_LINES);

    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-20.0f, 0.0f, 0.0f);
    glVertex3f( 80.0f, 0.0f, 0.0f);

    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -20.0f, 0.0f);
    glVertex3f(0.0f, 20.0f, 0.0f);

    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -20.0f);
    glVertex3f(0.0f, 0.0f, 20.0f);
    glEnd();
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Draw a MODEL_INFO vertices from the loaded model

void drawModelVertices(MODEL_INFO model) {

    //For coloring the models
    //float red = 1.0f, green = 0.0f, blue = 0.0f;

    //Get models vertices and assign to a pointer
    vector<POINT_3D> vertices = model.getVertices();

    //Draw using triangles
    glBegin(GL_TRIANGLES);

    for(auto it = vertices.begin(); it != vertices.end(); it++) {

        //Apply color to the models
        //glColor3f(red, green, blue);

        glVertex3f(it -> getX(),
                   it -> getY(),
                   it -> getZ());

        /*

        if(red == 1.0f) {
            red = 0.0f; green = 1.0f;
        }
        else if(green == 1.0f) {
            green = 0.0f; blue = 1.0f;
        }
        else if(blue = 1.0f) {
            red = 1.0f; blue = 0.0f;
        }

         */
    }

    glEnd();
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Draw group

void drawGroupElements(Group g) {

    //From source: pushes the current matrix stack down by one
    glPushMatrix();

    /*-------------------------------------------------------------*/

    //::1:: Apply group transformations
    vector<Transformation> *transformations = g.transformations;

    for (auto it = transformations -> begin(); it != transformations -> end(); ++it) {

        if (it -> description == "Translation") {
            glTranslatef(it->x, it->y, it->z);
        } else if (it -> description == "Rotation") {
            glRotatef(it->angle, it->x, it->y, it->z);
        } else if (it -> description == "Scale") {
            glScalef(it->x, it->y, it->z);
        }
    }

    //::2:: Load group models
    vector<MODEL_INFO> *models = g.models;

    for (auto it = models -> begin(); it != models -> end(); ++it) {

        drawModelVertices(*it);
    }

    //::3:: Load child groups
    vector<Group> *groups = g.groups;

    for (auto it = groups -> begin(); it != groups -> end(); ++it) {

        drawGroupElements(*it);
    }

    /*-------------------------------------------------------------*/

    //From source: pops the current matrix stack,
    //             replacing the current matrix
    //             with the one below it on the stack.
    glPopMatrix();
}