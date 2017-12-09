// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#define _USE_MATH_DEFINES

#include "stdafx.h"
#include<stdlib.h>
#include "GL\glut.h"

#include "Mash.h"
#include "Cvor.h"
#include "Ivica.h"

#include<math.h>
#include<vector>

int width = 500;
int height = 500;

Mash *mash = new Mash;

static void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-7.0, 7.0, -7.0, 7.0, -7.0, 7.0);          // set viewing volume to 7 X 7 X 7
	glMatrixMode(GL_MODELVIEW);
}

void winReshape(GLint w, GLint h)
{

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, -7, 7);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void trougao(float *a, float *b, float *c) {

	Cvor *cvorA = new Cvor(a[0], a[1], a[2]);
	Cvor *cvorB = new Cvor(a[0], a[1], a[2]);
	Cvor *cvorC = new Cvor(a[0], a[1], a[2]);

	Lice *lice = new Lice(NULL, mash);

	mash->cvorovi.push_back(cvorA);
	mash->cvorovi.push_back(cvorB);
	mash->cvorovi.push_back(cvorC);
	


	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void tetraedar(float *a, float *b, float *c, float *d) {


	glColor3f(1.0, 0.0, 0.0);
	trougao(a, b, c);
	glColor3f(0.0, 1.0, 0.0);
	trougao(a, b, d);
	glColor3f(0.0, 0.0, 1.0);
	trougao(a, d, c);
	glColor3f(0.0, 0.0, 0.0);
	trougao(b, c, d);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	GLfloat a[3] = { 0.0, 4.0, 0.0 },
		b[3] = { 0.0, 0.0, -7.0 },
		c[3] = { 4.0, 7.0, 6.0 },
		d[3] = { -6.0, 6.0, -4.0 };
	glBegin(GL_TRIANGLES);

	tetraedar(a, b, c, d);

	glEnd();
	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);   // use GLUT_DEPTH if HSR is being used
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("subdivizija");
	glutDisplayFunc(display);
	//glutReshapeFunc(winReshape);
	myInit();
	glEnable(GL_DEPTH_TEST);                                    // enable Hidden Surface Removal Algorithm
	glutMainLoop();
	return 0;
}