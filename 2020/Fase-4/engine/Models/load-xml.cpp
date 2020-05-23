
#include <iostream>
#include <fstream>
#include <vector>

#include <model-info.h>
#include <lights.h>

#include "../tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

/*--------------------------------------------------------------------------------------------------------------------*/
//Global constants (folder and file locations)

//XML default file path
#define XML_CONFIG_FILES_PATH "../../examples/XML-Examples/"

//MODELS default path
#define MODEL_3D_PATH "../../examples/Models.3d/"

/*--------------------------------------------------------------------------------------------------------------------*/
//Read model file and store the vertices in the vertices vector from MODEL_INFO

int load_standard_model_vertices(MODEL_INFO *model) {

    //Model path appended to default folder location for models
    string path_to_model = MODEL_3D_PATH + model -> getName();

    ifstream file_stream (path_to_model);

    if (!file_stream.is_open()) {
        throw string("Could not read from " + path_to_model + "!");
    }

    //Get model array of vertices pointer
    vector<float>* modelVertices = model -> getVertices();

    try {

        //to store the line
        string line;

        //get the number of vertices
        //-- used just for debugging purposes
        getline(file_stream, line);

        //3 fields of each line in model file
        //the 3 coordinates x, y and z
        float x, y, z;

        //while not EOF
        while (getline(file_stream, line)) {

            //Parse line float vertices
            sscanf(line.c_str(), "%f %f %f", &x, &y, &z);

            modelVertices->push_back(x);
            modelVertices->push_back(y);
            modelVertices->push_back(z);
        }

        file_stream.close();

    //catch wtv error we got
    } catch (...) {
        file_stream.close();
        cout << "Error parsing 3D model file in: " << path_to_model << "..." << endl;
        return -1;
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Read model file and store the vertices and indexes vectors from MODEL_INFO
//This type of models can eventually have texture coordinates and normals

int load_indexed_model(MODEL_INFO *model) {

    //Model path appended to default folder location for models
    string path_to_model = MODEL_3D_PATH + model -> getName();

    ifstream file_stream (path_to_model);

    if (!file_stream.is_open()) {
        throw string("Could not read from " + path_to_model + "!");
    }

    //Get model array of vertices pointer
    vector<float>* modelVertices      = model -> getVertices();
    vector<GLuint>* indexes = model -> indexes;
    vector<float>* modelTextureCoords;
    modelTextureCoords = model -> getTextureCoordinates();
    vector<float>* vertexNormals = model -> getVertexNormals();

    //0: vertices
    //1: indexes
    int parsing = 0, floatsRead = 0;
    try {

        //to store the line
        string line;

        //read first line containing nr of vert, indexes, texture Coord...
        getline(file_stream, line);
        int nr_vert = 0, nr_indexes = 0, nr_textCoord = 0, nr_normals = 0;
        sscanf(line.c_str(), "%d,%d,%d,%d", &nr_vert, &nr_indexes, &nr_textCoord, &nr_normals);

        //3 fields of each line in model file
        //the 3 coordinates x, y and z
        float x, y, z;
        float t_x, t_y;
        int index;
        int read_indexes = 0, read_texturecoords = 0, read_normals = 0;

        //while not EOF
        while (getline(file_stream, line)) {


            //parsing vertices
            if (parsing == 0) {

                floatsRead = sscanf(line.c_str(), "%f %f %f", &x, &y, &z);

                if (floatsRead != 3) {

                    index = (GLuint) x;
                    read_indexes++;
                    parsing = 1;
                    continue;
                }

                modelVertices->push_back(x);
                modelVertices->push_back(y);
                modelVertices->push_back(z);

                //parsing indexes
            } else if (parsing == 1) {

                indexes->push_back(index);

                sscanf(line.c_str(), "%d", &index);

                read_indexes++;

                if (read_indexes == nr_indexes) {
                    parsing = 2; //parsing texture coordinates now
                    read_texturecoords = 0;
                    indexes->push_back(index);
                }

            } else if(parsing == 2) {

                sscanf(line.c_str(), "%f %f", &t_x, &t_y);

                modelTextureCoords->push_back(t_x);
                modelTextureCoords->push_back(t_y);
                read_texturecoords++;

               if (read_texturecoords > nr_textCoord) {

                   parsing = 3;

                   sscanf(line.c_str(), "%f %f %f", &x, &y, &z);

                   vertexNormals -> push_back(x);
                   vertexNormals -> push_back(y);
                   vertexNormals -> push_back(z);

                   read_normals++;
               }

            } else if (parsing == 3) {


                sscanf(line.c_str(), "%f %f %f", &x, &y, &z);

                vertexNormals -> push_back(x);
                vertexNormals -> push_back(y);
                vertexNormals -> push_back(z);

                read_normals++;

                if (read_normals > nr_normals) break;
            }
        }

        file_stream.close();

        //catch wtv error we got
    } catch (...) {

        file_stream.close();
        cout << "Error parsing 3D model file in: " << path_to_model << "..." << endl;

        return -1;
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the models (<models>)

static void processModelsTag(XMLElement *models_ptr, Group *group) {

    XMLElement* model_ptr = models_ptr -> FirstChildElement("model");

    for (; model_ptr != NULL; model_ptr = model_ptr -> NextSiblingElement("model")) {

        //--------------------------------------------------------------------------------------------------------------

        //file name
        auto file_model = model_ptr -> Attribute("file");

        if (!file_model)
            throw string("No 'file' attributes found for model ?");

        string model_file_name = string(file_model);

        //textures
        auto file_texture = model_ptr -> Attribute("texture");

        string model_texture;
        if (file_texture) {

            model_texture = string(file_texture);
        }

        //--------------------------------------------------------------------------------------------------------------

        if (model_file_name.substr(model_file_name.find_last_of(".") + 1) == "indexed") {

            auto model = new MODEL_INFO(model_file_name, true, file_texture != nullptr);

            if (file_texture) {
                model -> settings[1] = true;
                model->textureFile = model_texture;
            }

            load_indexed_model(model);

            //----------------------------------------------------------------------------------------------------------
            // Parse colours (if any)

            //has setted colour components
            model -> settings[2] = true;

            model_ptr -> QueryAttribute("diffR", &model->diffuseComponent[0]);
            model_ptr -> QueryAttribute("diffG", &model->diffuseComponent[1]);
            model_ptr -> QueryAttribute("diffB", &model->diffuseComponent[2]);

            model_ptr -> QueryAttribute("specR", &model->specularComponent[0]);
            model_ptr -> QueryAttribute("specG", &model->specularComponent[1]);
            model_ptr -> QueryAttribute("specB", &model->specularComponent[2]);

            model_ptr -> QueryAttribute("ambiR", &model->ambientComponent[0]);
            model_ptr -> QueryAttribute("ambiG", &model->ambientComponent[1]);
            model_ptr -> QueryAttribute("ambiB", &model->ambientComponent[2]);

            model_ptr -> QueryAttribute("emisR", &model->emissiveComponent[0]);
            model_ptr -> QueryAttribute("emisG", &model->emissiveComponent[1]);
            model_ptr -> QueryAttribute("emisB", &model->emissiveComponent[2]);

            //----------------------------------------------------------------------------------------------------------

            group -> models -> push_back(*model);

        } else {

            auto model = new MODEL_INFO(model_file_name, false, false);

            load_standard_model_vertices(model);

            group -> models -> push_back(*model);
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the translations

/*
 * Translation can have 2 types:
 * Standard   : <translate X="..." Y="..." Z="..."/>
 * Time based : <translate time="...">
 *                  <point X="..." Y="..." Z="..." />
 *                  ....
 *                  <point X="..." Y="..." Z="..." />
 */

static void processTranslationTag(XMLElement *translation_ptr, Group *group) {

    float time = 0.0f;
    XMLError queryTimeExists = translation_ptr -> QueryAttribute("time", &time);

    //Standard translation
    if (queryTimeExists == XML_NO_ATTRIBUTE) {

        float x = 0.0f, y = 0.0f, z = 0.0f;

        translation_ptr -> QueryAttribute("X", &x);
        translation_ptr -> QueryAttribute("Y", &y);
        translation_ptr -> QueryAttribute("Z", &z);

        //Create new translation
        Transformation *t = new Translation("Translation", x, y, z);

        group -> transformations -> push_back(*t);

    //Catmull-Rom transformation
    } else {

        Transformation *t = new Translation("Translation_TimeBased", time);

        XMLElement* translationPoint = translation_ptr->FirstChildElement(nullptr);

        int nr_points = 0;
        while (translationPoint) {

            float x, y, z;

            translationPoint -> QueryAttribute("X", &x);
            translationPoint -> QueryAttribute("Y", &y);
            translationPoint -> QueryAttribute("Z", &z);

            t -> addTransformationPoint(new POINT_3D(x, y, z));

            translationPoint = translationPoint -> NextSiblingElement("point");

            nr_points++;
        }

        //minimum number of points is 4
        if (nr_points >= 4) {

            group -> transformations -> push_back(*t);

        } else {

            //process error
            throw string("The minimum number of points is 4 in dynamic translations!");
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the rotations

/*
 * Rotation can have 2 types:
 * Standard   : <rotate axisX="..." axisY="..." axisZ="..." angle="..."/>
 * Time based : <rotate time="...">
 *              (in this case time to perform a full 360 degrees rotation)
 */

static void processRotationTag(XMLElement *rotation_ptr, Group *group) {

    float time = 0.0f;
    XMLError queryTimeExists = rotation_ptr -> QueryAttribute("time", &time);

    float angle = 0.0f, x = 0.0f, y = 0.0f, z = 0.0f;

    rotation_ptr -> QueryAttribute("angle", &angle);
    rotation_ptr -> QueryAttribute("axisX", &x);
    rotation_ptr -> QueryAttribute("axisY", &y);
    rotation_ptr -> QueryAttribute("axisZ", &z);

    //Standard translation
    if (queryTimeExists == XML_NO_ATTRIBUTE) {

        //Create new rotation
        Transformation *t = new Rotation("Rotation", x, y, z, angle);

        group -> transformations -> push_back(*t);

    } else {

        Transformation *t = new Rotation("Rotation_TimeBased", x, y, z, angle, time);

        group -> transformations -> push_back(*t);
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the scale (<translation X=? Y=? Z=?>)

static void processScaleTag(XMLElement *scale_ptr, Group *group) {

    //default scale
    float x = 1.0f, y = 1.0f, z = 1.0f;

    scale_ptr -> QueryAttribute("X", &x);
    scale_ptr -> QueryAttribute("Y", &y);
    scale_ptr -> QueryAttribute("Z", &z);

    Transformation *t = new Scale("Scale", x, y, z);

    group -> transformations -> push_back(*t);
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the lights

static vector<LightSource>* processLightsTag(XMLElement *lights_ptr) {

    auto *vectorLights = new vector<LightSource>();

    XMLElement* lightSourceElement = lights_ptr -> FirstChildElement("light");

    int lightOffset = 0;
    //Process a list of light sources
    while (lightSourceElement) {

        auto hasTypeString = lightSourceElement -> Attribute("type");

        string lightType;
        if (hasTypeString) {

            lightType = string(hasTypeString);

            auto* lightSource = new LightSource();

            lightSourceElement -> QueryAttribute("diffR",&lightSource->diffuseComponent[0]);
            lightSourceElement -> QueryAttribute("diffG",&lightSource->diffuseComponent[1]);
            lightSourceElement -> QueryAttribute("diffB",&lightSource->diffuseComponent[2]);

            lightSourceElement -> QueryAttribute("specR", &lightSource->specularComponent[0]);
            lightSourceElement -> QueryAttribute("specG", &lightSource->specularComponent[1]);
            lightSourceElement -> QueryAttribute("specB", &lightSource->specularComponent[2]);

            lightSourceElement -> QueryAttribute("ambiR", &lightSource->ambientComponent[0]);
            lightSourceElement -> QueryAttribute("ambiG", &lightSource->ambientComponent[1]);
            lightSourceElement -> QueryAttribute("ambiB", &lightSource->ambientComponent[2]);

            lightSourceElement -> QueryAttribute("posX",&lightSource->point[0]);
            lightSourceElement -> QueryAttribute("posY",&lightSource->point[1]);
            lightSourceElement -> QueryAttribute("posZ",&lightSource->point[2]);

            if (lightType == "POINT") {

                lightSource -> lightType = "POINT";

                lightSource -> point[3] = 1.0f;

            } else if (lightType == "DIRECTIONAL") {

                lightSource -> lightType = "DIRECTIONAL";

                lightSource -> point[3] = 0.0f;

            } else if (lightType == "SPOT") {

                lightSource -> lightType = "SPOT";

                lightSourceElement -> QueryAttribute("cutoff",&lightSource->SpotCutoff);
                lightSourceElement -> QueryAttribute("exponent",&lightSource->SpotExponent);

                lightSourceElement -> QueryAttribute("dirX",&(lightSource->SpotDirection[0]));
                lightSourceElement -> QueryAttribute("dirY",&(lightSource->SpotDirection[1]));
                lightSourceElement -> QueryAttribute("dirZ",&(lightSource->SpotDirection[2]));
            }

            //printLightSource(lightSource);

            lightSource -> lightEnumNumber = lightOffset;

            vectorLights -> push_back(*lightSource);

            lightOffset+=1;

        } else
            throw string("A light source type may be defined in the lights scope!");

        lightSourceElement = lightSourceElement -> NextSiblingElement("light");
    }

    return vectorLights;
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the group tag (<group>)

static void processGroupTag(XMLElement *group_tag_ptr, Group *group) {

    XMLElement* element = group_tag_ptr -> FirstChildElement(nullptr);

    int tr = 0, rt = 0, scl = 0;

    while (element != nullptr) {

        string element_name = element -> Name();

        //Translate tag found
        if (element_name == "translate")
            { processTranslationTag(element, group); tr++; }

        //Rotate tag found
        if (element_name == "rotate")
            { processRotationTag(element, group); rt++; }

        //Scale tag found
        else if (element_name == "scale")
            { processScaleTag(element, group); scl++; }

        //Models tag found
        else if (element_name == "models")
            { processModelsTag(element, group); }

        //Group child tag found
        else if (element_name == "group")
            {
                //New child group
                auto childGroup = new Group;

                //process the group and store in childGroup addr
                processGroupTag(element, childGroup);

                //Add group to the groups vector of the current group
                group -> groups -> push_back(*childGroup);
            }

        /*--------------------------------------------------------*/

        element = element -> NextSiblingElement(nullptr);
    }

    if (scl > 1 || tr > 1 || rt > 1) {
        throw string("Multiple transformations of the same type on the same Group!");
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
//Process the xml file and load all structures and classes

pair<vector<Group>*, vector<LightSource>*> load_xml_config(string xml_config_filename) {

    /*--------------------------------------------------------------*/

    //XML config file name
    string file_path = XML_CONFIG_FILES_PATH + xml_config_filename;
    cout << endl << "»»» Reading from " << file_path << "..." << endl;

    //Load document file
    XMLDocument xml_config_doc;
    XMLError eResult = xml_config_doc.LoadFile(file_path.c_str());

    //Error loading file?
    if (eResult != XML_SUCCESS)
        return {};

    /*--------------------------------------------------------------*/

    //Root scene ptr
    XMLElement* rootScene = xml_config_doc.FirstChildElement("scene");

    //There's no root scene, return
    if (rootScene == nullptr)
        return {};

    /*--------------------------------------------------------------*/
    //Process light sources from xml

    XMLElement* lightsElement = rootScene -> FirstChildElement("lights");

    auto* lights = new vector<LightSource>();

    if (lightsElement != NULL) {

        lights = processLightsTag(lightsElement);
    }

    /*--------------------------------------------------------------*/

    //Scene tags can only contain group child tags or light sources
    XMLElement* group_tag_ptr = rootScene -> FirstChildElement("group");

    //Vector ptr containing all the groups of the scene
    auto groups_vector = new vector<Group>;

    //Navigate through the root scene tag and search for group tags ONLY
    while (group_tag_ptr) {

        //Create new group that will be processed in processGroupTag(...)
        auto newGroup = new Group();

            //Process the group tag
            processGroupTag(group_tag_ptr, newGroup);

        //Insert new group in groups vector
        groups_vector -> push_back(*newGroup);

        //Get next group tag ptr
        group_tag_ptr = group_tag_ptr -> NextSiblingElement("group");
    }

    return make_pair(groups_vector, lights);
}
