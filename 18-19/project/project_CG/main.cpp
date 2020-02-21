#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include "alien.h"

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
float a=0.1f,b=0.5f,radius=10.0f;
float x = 0.1f,ca=0.1f,cb=0.9f;

void draw(const char *pFilename)
{
	char *vert[MAX];
	readFileToStruct(pFilename,vert);
	int i,pin = 0;
	float end = strtof(vert[pin++], NULL);

	for(i=0;i < end ;i++)
	{
		float a1,a2,a3,a4,a5,a6,a7,a8,a9;
		a1 = strtof(vert[pin],NULL);
		pin++;
		a2 = strtof(vert[pin],NULL);
		pin++;
		a3 = strtof(vert[pin],NULL);
		pin++;
		a4 = strtof(vert[pin],NULL);
		pin++;
		a5 = strtof(vert[pin],NULL);
		pin++;
		a6 = strtof(vert[pin],NULL);
		pin++;
		a7 = strtof(vert[pin],NULL);
		pin++;
		a8 = strtof(vert[pin],NULL);
		pin++;
		a9 = strtof(vert[pin],NULL);
		pin++;
		glBegin(GL_TRIANGLES);
			glVertex3f(a1,a2,a3);
			glVertex3f(a4,a5,a6);
			glVertex3f(a7,a8,a9);
			//glVertex3f(vert[pin++],vert[pin++],vert[pin++]);
			//glVertex3f(vert[pin++],vert[pin++],vert[pin++]);
			//glVertex3f(vert[pin++],vert[pin++],vert[pin++]);
		glEnd();
		i +=3;
		if(ca >= 1)//colors
			x = -x;
		if(ca <= 0)
			x = -x;
		ca += x;
		cb -=x;
	}
}

void translateGroup(char* str)
{
	if (strcmp(str,"n"))
	{
		float x = strtof(strtok(str,"/"),NULL);
		float y = strtof(strtok(NULL,"/"),NULL);
		float z = strtof(strtok(NULL,"/"),NULL);
		glTranslatef(x,y,z);
	}
}

void rotateGroup (char* str)
{
	if (strcmp(str,"n"))
	{
		float d = strtof(strtok(str,"/"),NULL);//degree
		float x = strtof(strtok(NULL,"/"),NULL);
		float y = strtof(strtok(NULL,"/"),NULL);
		float z = strtof(strtok(NULL,"/"),NULL);
		glRotatef(d,x,y,z);
	}
}

void drawGroup(Group group)
{
	glPushMatrix();
	float x,y,z;
	switch (group.index)
	{
		case 0:
			printf("(not R) && (not T)\n");
			break;
		case 1:
		{
			printf("R && (not T)\n");
			rotateGroup(group.rotation);
			break;
		}
		case 2:
		{
			printf("R && T\n");
			rotateGroup(group.rotation);
			translateGroup(group.translation);
			break;
		}
		case 3:
		{
			printf("T && (not R)\n");
			translateGroup(group.translation);
			break;
		}
		case 4:
		{
			printf("T && R\n");
			translateGroup(group.translation);
			rotateGroup(group.rotation);
			break;
		}
	}

		//glScalef(10,10,10);
	int i = 0;
	while (group.file[i] != NULL)
	{
		draw(group.file[i]);
		i++;
	}
	printf("all set\n");
	glPopMatrix();
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(radius*sin(a)*cos(b),radius*sin(b),radius*cos(a)*cos(b),
		      0.0f,0.0f,0.0f,
			  0.0f,1.0f,0.0f);

	char *file[1000];
	int i = 0;
	Group* solarSystem = getTexturesName("models/shapes.xml");

	//glPolygonMode(GL_FRONT,GL_LINE);
	glPushMatrix();

	while(solarSystem != NULL)
	{
		drawGroup(*solarSystem);
		solarSystem = solarSystem -> next;
	}
	glPopMatrix();
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy)
{
	// put code to process regular keys in here
	switch (c)
	{
		case 'a':
			a=a-0.001f;
			break;
		case 'd':
			a=a+0.001f;
			break;
		case 'w':
			b=b+0.001f;
			break;
		case 's':
			b=b-0.001f;
			break;
		case '.':
			radius -= 1.0f;
			if (radius < 1.0f)
				radius = 1.0f;
			break;
		case '-':
			radius += 1.0f;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {

}

using namespace std;
int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(400,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Engine");

// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable ( GL_COLOR_MATERIAL ) ;
	glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
