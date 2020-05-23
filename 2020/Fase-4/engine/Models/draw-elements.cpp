
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
#endif

#include <model-info.h>
#include <catmull-rom.h>

/*--------------------------------------------------------------------------------------------------------------------*/
//...
void setMaterials(MODEL_INFO *model) {

    //if has color attributes
    if (model -> settings[2]) {

        glMaterialfv(GL_FRONT, GL_DIFFUSE, model -> diffuseComponent);
        glMaterialfv(GL_FRONT, GL_SPECULAR, model -> specularComponent);
        glMaterialfv(GL_FRONT, GL_EMISSION, model -> emissiveComponent);
        glMaterialfv(GL_FRONT, GL_AMBIENT, model -> ambientComponent);
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Draw the axis on the screen

void drawAxis(float x, float y, float z) {

    glBegin(GL_LINES);

    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0.0f, 0.0f);
    glVertex3f( x, 0.0f, 0.0f);

    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0, 0.0f);
    glVertex3f(0.0f, y, 0.0f);

    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0);
    glVertex3f(0.0f, 0.0f, z);
    glEnd();
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Draw a MODEL_INFO vertices from the loaded model

void drawModelVertices(MODEL_INFO model) {

    //For coloring the models
    //float red = 1.0f, green = 0.0f, blue = 0.0f;

    //Get models vertices and assign to a pointer
    vector<float>* vertices = model.getVertices();

    //Draw using triangles
    glBegin(GL_TRIANGLES);

    for(auto it = vertices->begin(); it != vertices->end(); it+=3) {

        //Apply color to the models
        //glColor3f(red, green, blue);

        glVertex3f(*(it).base(),
                   *(it+1).base(),
                   *(it+2).base());
    }

    glEnd();
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Draw model with VBOs

void drawModelVBO (MODEL_INFO model) {

    glBindBuffer(GL_ARRAY_BUFFER, model.verticesBuffer[0]);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);

    int count = model.vertices -> size() / 3;

    bool isTextured = model.settings[1];

    glBindBuffer(GL_ARRAY_BUFFER, model.normalsBuffer[0]);
    glNormalPointer(GL_FLOAT, 0, 0);

    if (model.settings[0]) { //if has indexes

        if (isTextured) {

            glBindBuffer(GL_ARRAY_BUFFER, model.textureBuffer[0]);
            glTexCoordPointer(2, GL_FLOAT, 0, 0);
            glBindTexture(GL_TEXTURE_2D, model.glutTextureID);
        }

        int indexArraySize = model.indexes -> size();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.indexesBuffer[0]);
        glDrawElements(GL_TRIANGLES, indexArraySize, GL_UNSIGNED_INT, nullptr);

        //temporary? clear color buffers
        glClearColor(0,0,0,0);

        if (model.settings[1]) glBindTexture(GL_TEXTURE_2D, 0);

    } else {

        glDrawArrays(GL_TRIANGLES, 0, count);
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Draw group

void drawGroupElements(Group g, bool hasLighting, bool ENABLE_MODEL_AXIS) {

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

        } else if (it -> description == "Translation_TimeBased") {


            float timeT = ((float) glutGet(GLUT_ELAPSED_TIME) / 1000) / (it -> time);

            float pos[3] = { 0.0, 0.0, 0.0 };
            float deriv[3] = { 0.0, 0.0, 0.0 };

            glDisable(GL_LIGHTING);

            glClearColor(0,0,0,0);
            glColor3f(0.5, 0.5, 0.5);

            renderCatmullRomCurve(it->transformationPoints);

            if (hasLighting)
                glEnable(GL_LIGHTING);

            getGlobalCatmullRomPoint(it->transformationPoints, timeT, (float*)pos, (float*)deriv);

            glTranslatef(pos[0], pos[1], pos[2]);

            float M[4][4];
            float Y[3], Z[3];

            cross(deriv, it -> startY, Z);
            cross(Z, deriv, it -> startY);

            normalize(deriv);
            normalize(it -> startY);
            normalize(Z);

            buildRotMatrix(deriv, it -> startY, Z, *M);

            glMultMatrixf(*M);

        } else if (it -> description == "Rotation_TimeBased") {

            float rotationAngle = (((float) glutGet(GLUT_ELAPSED_TIME) / 1000) * 360) / (it -> time);

            glRotatef(rotationAngle, it -> x, it -> y, it -> z);
        }
    }

    //::2:: Load group models
    vector<MODEL_INFO> *models = g.models;

    for (auto it = models -> begin(); it != models -> end(); ++it) {

        if (ENABLE_MODEL_AXIS) {

            //Axis around each model
            glPushMatrix();

            glDisable(GL_LIGHTING);

            glClearColor(0, 0, 0, 0);
            glColor3f(1, 1, 1);

            drawAxis(5.0f, 5.0f, 5.0f);

            if (!hasLighting) {

                glEnable(GL_LIGHTING);
            }

            glClearColor(0, 0, 0, 0);
            glColor3f(1, 1, 1);

            glPopMatrix();
        }

        if (!hasLighting) {

            glEnable(GL_LIGHTING);
        }

        glPushMatrix();

            //old: All models white
            //glColor3f(1,1,1);

            //Set model colour component
            setMaterials(it.base());

            //Phase 3
            drawModelVBO(*it);

        glPopMatrix();

        //Phase 1/2
        //drawModelVertices(*it);
    }

    //::3:: Load child groups
    vector<Group> *groups = g.groups;

    for (auto it = groups -> begin(); it != groups -> end(); ++it) {

        drawGroupElements(*it, hasLighting, ENABLE_MODEL_AXIS);
    }

    /*-------------------------------------------------------------*/

    //From source: pops the current matrix stack,
    //             replacing the current matrix
    //             with the one below it on the stack.
    glPopMatrix();
}
