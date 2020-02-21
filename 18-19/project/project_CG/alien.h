#ifndef ALIEN_H_
#define ALIEN_H_
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <ostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <list>
#define MAX 1000000

typedef struct group
{
  int index;
  char* rotation;
  char* translation;
  char* scale;
  char* file[1000];
  struct group* next;
}Group;

int alien(int x);
void readFile(const char* pFilename);
void readFromStruct(float *vert);
void readFileToStruct(const char* pFilename,char *vert[]);
Group* getTexturesName(const char* pFilename);
void insertTexturesName(const char* pFilename,const char* textureName);
Group* createGroup(Group* group,int value,const char* rotate,const char* translate,char **fname);
int getGroupTranslation();
int getGroupScale();

#endif
/*
char *mystrcat(char s1[], char s2[])
{
  char *s0 = s1;
  int k=0;
  for(int i=0;s1[i];i++)
  {
    k +=1;
  }

  for(int i=0;s2[i];i++)
   {
     s1[k]= s2[i];
     k++;
   }

  s1[k] = '\0';
  return s0;
}*/
