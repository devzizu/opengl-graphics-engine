#include "alien.h"
using namespace std;

int alien(int x)
{
  return x;
}

void readFile(const char* pFilename)//print all vertices from .3d
{
  FILE* fp = fopen(pFilename, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  char* line = NULL;
  size_t len = 0;
  while ((getline(&line, &len, fp)) != -1) {
      // using printf() in all tests for consistency
      printf("%s", line);
  }
  fclose(fp);

  if (line)
    free(line);

}

void readFromStruct(float *vert)//print all vertices from array
{
  int i = 0;
  while(*vert != (-0.01f))
  {
    if( i++ == 0)
      printf("%.2f\n",*(vert++));
    else
      printf("%.2f %.2f %.2f\n",*(vert++),*(vert++),*(vert++));
  }
}

void readFileToStruct(const char* pFilename,char *vert[])//puts all vertices from .3d in an array
{
  FILE* fp = fopen(pFilename, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  char* line = NULL;
  size_t len = 0;
  int x = 0;
  char *buff = (char*) malloc(sizeof(char)*256);

  while ((getline(&line, &len, fp)) != -1)
  {
    if( x==0)
      vert[x++] = strdup(strtok(line," "));
    else
    {
      vert[x++] = strdup(strtok(line," "));
      vert[x++] = strdup(strtok(NULL," "));
      vert[x++] = strdup(strtok(NULL," "));
    }
  }
  vert[x] = NULL;
  fclose(fp);

  //

  if (line)
    free(line);

}
Group* getTexturesName(const char* pFilename)
{

	TiXmlDocument doc( pFilename );
	bool loadOkay = doc.LoadFile();

  TiXmlHandle docHandle( &doc );

  TiXmlElement* child = docHandle.FirstChild( "scene" ).FirstChild( "group" ).ToElement();
  string aux;
  Group* solarSystem = NULL;
  int solarSystemPositionn = 0;
  int i,groupIndex;

  for( child; child; child=child->NextSiblingElement())
  {
    i = 0,groupIndex = 0;
    char *file[100];
    string model;
    std::ostringstream strRotate;
    std::ostringstream strTranslate;
    //model = child->Attribute( "file");
    TiXmlElement* state = child;
    if (state->FirstChild("rotate") != NULL)
    {
      TiXmlElement* rotate = child->FirstChild("rotate")->ToElement();
      strRotate << (rotate->Attribute( "angle" )) << "/" <<  strdup(rotate->Attribute( "axisX" ))
                << "/" << strdup(rotate->Attribute( "axisY" )) << "/" << strdup(rotate->Attribute( "axisZ" )) <<"/";
      //printf("%s",strRotate.str());
      if (!strcmp(rotate->Attribute( "order" ),"0"))
        groupIndex = 1;
      else
        groupIndex = 3;
    }
    else
    {
      strRotate << "n";
    }
    if (state->FirstChild("translate") != NULL)
    {
      TiXmlElement* translate = child->FirstChild("translate")->ToElement();
      strTranslate << translate->Attribute( "X" ) << "/" << translate->Attribute( "Y" ) << "/"
                   << translate->Attribute( "Z" ) << "/";

      if (groupIndex == 1)
        groupIndex = 2;
      else if (groupIndex == 3)
        groupIndex = 4;
      else
        groupIndex = 3;
      //printf("hello%s",strTranslate.str());
    }
    else
    {
      strTranslate << "n";
    }
    if (state->FirstChild("scale") != NULL)
    {
      TiXmlElement* translate = child->FirstChild("scale")->ToElement();
      strTranslate << translate->Attribute( "X" ) << "/" << translate->Attribute( "Y" ) << "/"
                   << translate->Attribute( "Z" ) << "/";
      //printf("hello%s",strTranslate.str());
    }
    else
    {
      strTranslate << "n";
    }

    if (state->FirstChild("models") != NULL)
    {
      TiXmlElement* models = child->FirstChild("models")->FirstChild("model")->ToElement();
      while (models)
      {
        model = models->Attribute("file");
        //printf("%s\n",model.c_str());
        file[i++] = strdup(model.c_str());
        models = models->NextSiblingElement();
      }
    }
    file[i] = NULL;
    solarSystem = createGroup(solarSystem,groupIndex,strRotate.str().c_str(),strTranslate.str().c_str(),file);
    //printf("%d\n",solarSystem -> index);
    //cout << model;
  }
  return solarSystem;
}

void insertTexturesName(const char* pFilename,const char* textureName)
{
  TiXmlDocument doc( pFilename );
  bool loadOkay = doc.LoadFile();
  int x = 1;
  TiXmlHandle docHandle( &doc );

  TiXmlElement* child = docHandle.FirstChild( "scene" ).FirstChild( "model" ).ToElement();

  for( child; child; child=child->NextSiblingElement() )
  {
    if (strcmp(textureName,child->Attribute( "file")) == 0)
    {
      x = 0;
      break;
    }
  }
  if(x)
  {
    TiXmlElement* root = doc.FirstChildElement("scene");

    TiXmlElement* element1 = new TiXmlElement("model");
    root->LinkEndChild(element1);
    element1->SetAttribute("file", textureName);

    doc.SaveFile("models/shapes.xml");
  }
}

Group* createGroup(Group* group,int value,const char* rotate,const char* translate,char **fname)
{
  if ( group == NULL)
  {
    group = (struct group*) malloc(sizeof(struct group));
    (*group).index = value;
    //0 -> (not R) && (not T)
    //1 -> R && (not T)
    //2 -> R && T
    //3 -> T && (not R)
    //4 -> T && R

    (*group).rotation = strdup(rotate);
    (*group).translation = strdup(translate);
    int i = 0;
    while (fname[i])
    {
      ((*group).file)[i] = (char*) malloc(sizeof(char)*100);
      strcpy(((*group).file)[i],strdup(fname[i]));
      i++;
    }
    (*group).file[i] = NULL;
    (group) -> next = NULL;
    return group;
  }
  else
  {
    Group* aux;
    aux = (struct group*) malloc(sizeof(struct group));
    (*aux).index = value;
    //0 -> (not R) && (not T)
    //1 -> R && (not T)
    //2 -> R && T
    //3 -> (not R) && T
    (*aux).rotation = strdup(rotate);
    (*aux).translation = strdup(translate);
    int i = 0;
    while (fname[i])
    {
      ((*aux).file)[i] = (char*) malloc(sizeof(char)*100);
      strcpy(((*aux).file)[i],strdup(fname[i]));
      i++;
    }
    (*aux).file[i] = NULL;
    (aux) -> next = group;
    return aux;
  }
}

int getGroupRotation()
{
  int result;
  return result;
}
int getGroupTranslation()
{
  int result;
  return result;
}
int getGroupScale()
{
  int result;
  return result;
}
