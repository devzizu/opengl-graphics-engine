

#include "model-info.h"

void initIndexedVBOModel(MODEL_INFO *model) {

    vector<float> vert_ptr = *model -> getVertices();
    vector<GLuint> ind_ptr = *model -> indexes;

    vector<float> text_ptr;
    if (model->settings[1])
        text_ptr = *model -> getTextureCoordinates();

    int arraySize = (*model -> vertices).size() * sizeof(float);

    //Vertices
    glGenBuffers(1, model->verticesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, model -> verticesBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, arraySize, &(*model -> getVertices())[0], GL_STATIC_DRAW);

    int indexArraySize = model -> indexes -> size() * sizeof(GLuint);

    //Indexes
    glGenBuffers(1, model->indexesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model -> indexesBuffer[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexArraySize, &(*model -> indexes)[0], GL_STATIC_DRAW);

    int vertexNormalArraySize = model -> vertexNormals -> size() * sizeof(float);

    //Normals
    glGenBuffers(1, model->normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, model -> normalsBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexNormalArraySize, &(*model -> getVertexNormals())[0], GL_STATIC_DRAW);

    //Textures
    if (model->settings[1]) { //has textures

        int textureArraySize = model -> texturesCoord -> size() * sizeof(float);

        glGenBuffers(1, model -> textureBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, model -> textureBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, textureArraySize, &(*model -> getTextureCoordinates())[0], GL_STATIC_DRAW);
    }
}

void initVBOModel(MODEL_INFO *model) {

    vector<float> vert_ptr = *model -> getVertices();

    int arraySize = vert_ptr.size() * sizeof(float);

    float *vertexArray = &vert_ptr[0];

    glGenBuffers(1, model->verticesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, model -> verticesBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, arraySize, vertexArray, GL_STATIC_DRAW);
}

void initVBOGroup(Group *g) {

    auto models = g -> models;

    for (auto modelIt = models->begin(); modelIt != models -> end(); ++modelIt) {

        if (modelIt->settings[0])
            initIndexedVBOModel(modelIt.base());
        else
            initVBOModel(modelIt.base());
    }

    auto groupsVector = g -> groups;

    for (auto groupIter = groupsVector->begin(); groupIter != groupsVector -> end(); ++groupIter) {

        initVBOGroup(groupIter.base());

    }
}

void initVBOs (vector<Group>* scene_groups) {

    cout << "[2] Initializing VBOs.... " << endl;

    for (auto iter = scene_groups->begin(); iter != scene_groups->end(); ++iter) {

        initVBOGroup(iter.base());
    }
}