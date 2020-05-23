
//----------------------------------------------------------------------------------------------------------------------

#include <model-info.h>

#include <IL/il.h>

//----------------------------------------------------------------------------------------------------------------------

#define TEXTURES_PATH "../../examples/Textures/"

//----------------------------------------------------------------------------------------------------------------------

void initModelTexture(MODEL_INFO *model) {

    //init DevIL
    ilInit();

    //Set texture origin in lower left side
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    //Image id, width and height
    unsigned int IMG_ID, IMG_WDT, IMG_HGT;
    unsigned char* DATA;

    //Generates 1 image name/id
    ilGenImages(1, &IMG_ID);
    ilBindImage(IMG_ID);

    string text_path = TEXTURES_PATH + model -> textureFile;
    const char* textureFile = text_path.c_str();

    ilLoadImage((ILstring) textureFile);
    IMG_WDT = ilGetInteger(IL_IMAGE_WIDTH);
    IMG_HGT = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    DATA = ilGetData();

    //Generates 1 texture for the gpu
    glGenTextures(1, &model -> glutTextureID);

    glBindTexture(GL_TEXTURE_2D, model -> glutTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //upload image data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, IMG_WDT, IMG_HGT, 0, GL_RGBA, GL_UNSIGNED_BYTE, DATA);

    //Maybe temporary
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void initGroupTextures(Group *g) {

    auto models = g -> models;

    for (auto modelIt = models->begin(); modelIt != models -> end(); ++modelIt) {

        if (modelIt->settings[0]) {

            //model has texture defined
            if (modelIt->settings[1])
                initModelTexture(modelIt.base());

        } else {

           //not set for models without indexes
        }
    }

    auto groupsVector = g -> groups;

    for (auto groupIter = groupsVector->begin(); groupIter != groupsVector -> end(); ++groupIter) {

        initGroupTextures(groupIter.base());
    }
}

void initTextures(vector<Group>* scene_groups) {

    cout << "[3] Loading Textures.... " << endl;

    for (auto iter = scene_groups->begin(); iter != scene_groups->end(); ++iter) {

        initGroupTextures(iter.base());
    }
}