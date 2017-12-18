// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#define _USE_MATH_DEFINES

#include "stdafx.h"
#include<stdlib.h>
#include<iostream>
#include "GL\glut.h"

#include "Mash.h"
#include "Cvor.h"
#include "Ivica.h"

#include<math.h>
#include<vector>

using namespace std;

int width = 500;
int height = 500;

Mash *mash = new Mash;

static void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-7.0, 7.0, -7.0, 7.0, -7, 7.0);
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
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}


void crtajMash() {

	float r, g, b;

	for (int i = 0; i < mash->lica.size(); i++) {

		r = ((float)rand() / RAND_MAX);
		g = ((float)rand() / RAND_MAX);
		b = ((float)rand() / RAND_MAX);

		vector<Cvor*> cvorovi = mash->lica[i]->sviCvorovi();

		glColor3f(r, g, b);
		glPointSize(10);
		glBegin(GL_TRIANGLES); //bilo je triangles, sad crta tacke

		for (int j = 0; j < cvorovi.size(); j++) {
			glVertex3f(cvorovi[j]->x, cvorovi[j]->y, cvorovi[j]->z);
			//cout << cvorovi[j]->x << "," << cvorovi[j]->y<<"," << cvorovi[j]->z << endl;
		}
		glEnd();


	}

	glFlush();
}

void test(float *temeA , float *temeB , float *temeC , float *temeD) {

	Ivica *e1 = mash->ivice[0];

	//***************************************************
	Cvor *c1 = e1->v;
	Cvor *c2 = e1->sled->v;
	Cvor *c3 = e1->sled->sled->v;
	Cvor *c4 = e1->eSym->sled->sled->v;

	/*glColor3f(1, 0, 0);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);

	glVertex3f(e1->v->x, e1->v->y, e1->v->z);
	glVertex3f(e1->sled->v->x, e1->sled->v->y, e1->sled->v->z);
	glVertex3f(e1->sled->sled->v->x, e1->sled->sled->v->y, e1->sled->sled->v->z);
	glVertex3f(e1->sled->sled->sled->v->x, e1->sled->sled->sled->v->y, e1->sled->sled->sled->v->z);

	glEnd();
	glFlush();*/

	glColor3f(1, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);

	glVertex3f(c1->x , c1->y , c1->z);
	glVertex3f(c2->x, c2->y, c2->z+0.001);
	glVertex3f(c3->x, c3->y, c3->z);
	glVertex3f(c4->x, c4->y, c4->z);

	glEnd();
	glFlush();

	//***************************************************

	Cvor *c = new Cvor(NULL);
	Ivica *en = new Ivica(c, e1->l, NULL, e1, e1->sled, mash);
	Ivica *enSym = new Ivica(c, e1->eSym->l, e1, e1->eSym, e1->eSym->sled, mash);

	c->e = en;

	e1->sled = en;
	e1->eSym = enSym;

	e1->eSym->sled = enSym;
	enSym->eSym = e1;

	en->sled->preth = en;
	enSym->sled->preth = enSym;

	cout << "x1: " << c1->x << "   ";
	cout << "x2: " << c2->x << "   ";
	cout << "x3: " << c3->x << "   ";
	cout << "x4: " << c4->x << "   ";
	cout << endl;

	c->x += c1->x * (3.0 / 8.0); 
	c->x += c2->x * (3.0 / 8.0);
	c->x += c3->x * (1.0 / 8.0);
	c->x += c4->x * (1.0 / 8.0); 
	

	c->y += c1->y * (3.0 / 8.0);
	c->y += c2->y * (3.0 / 8.0);
	c->y += c3->y * (1.0 / 8.0);
	c->y += c4->y * (1.0 / 8.0);

	c->z += c1->z * (3.0 / 8.0);
	c->z += c2->z * (3.0 / 8.0);
	c->z += c3->z * (1.0 / 8.0);
	c->z += c4->z * (1.0 / 8.0);

	glColor3f(0, 1, 0);
	glPointSize(10);
	glBegin(GL_POINTS);

	glVertex3f(c->x, c->y, c->z+1);


	glEnd();
	glFlush();

	mash->cvorovi.push_back(c);
	mash->ivice.push_back(en);
	mash->ivice.push_back(enSym);

}

void tetraedar(float *temeA, float *temeB, float *temeC, float *temeD) {

	Cvor *v1 = new Cvor(temeA[0], temeA[1], temeA[2]);
	Cvor *v2 = new Cvor(temeB[0], temeB[1], temeB[2]);
	Cvor *v3 = new Cvor(temeC[0], temeC[1], temeC[2]);
	Cvor *v4 = new Cvor(temeD[0], temeD[1], temeD[2]);

	Lice *f1 = new Lice(NULL, mash);
	Lice *f2 = new Lice(NULL, mash);
	Lice *f3 = new Lice(NULL, mash);
	Lice *f4 = new Lice(NULL, mash);

	//f3
	Ivica *a = new Ivica(v1, f3, NULL, NULL, NULL, mash);
	Ivica *b = new Ivica(v2, f3, NULL, a, NULL, mash);
	Ivica *c = new Ivica(v3, f3, NULL, b, a, mash);

	//f2
	Ivica *dSym = new Ivica(v4, f2, NULL, NULL, NULL, mash);
	Ivica *bSym = new Ivica(v3, f2, b, dSym, NULL, mash);
	Ivica *fSym = new Ivica(v2, f2, NULL, bSym, dSym, mash);

	//f4
	Ivica *d = new Ivica(v3, f4, dSym, NULL, NULL, mash);
	Ivica *e = new Ivica(v4, f4, NULL, d, NULL, mash);
	Ivica *cSym = new Ivica(v1, f4, c, e, d, mash);

	//f1
	Ivica *f = new Ivica(v4, f1, fSym, NULL, NULL, mash);
	Ivica *aSym = new Ivica(v2, f1, a, f, NULL, mash);
	Ivica *eSym = new Ivica(v1, f1, e, aSym, f, mash);

	//------------

	//cvorovi
	v1->e = a;
	v2->e = b;
	v3->e = c;
	v4->e = e;

	//f3	
	a->eSym = aSym;
	a->preth = c;
	a->sled = b;

	b->eSym = bSym;
	b->sled = c;

	c->eSym = cSym;
	//f2

	dSym->eSym = d;
	dSym->preth = fSym;
	dSym->sled = bSym;

	bSym->sled = fSym;

	fSym->eSym = f;

	//f4
	d->preth = cSym;
	d->sled = e;

	e->eSym = eSym;
	e->sled = cSym;

	//f1
	f->preth = eSym;
	f->sled = aSym;
	aSym->sled = eSym;


	//lica

	f1->e = f;
	f2->e = fSym;
	f3->e = a;
	f4->e = d;
	//------------

	mash->cvorovi.push_back(v1);
	mash->cvorovi.push_back(v2);
	mash->cvorovi.push_back(v3);
	mash->cvorovi.push_back(v4);

	mash->ivice.push_back(a);
	mash->ivice.push_back(b);
	mash->ivice.push_back(c);
	mash->ivice.push_back(d);
	mash->ivice.push_back(e);
	mash->ivice.push_back(f);
	mash->ivice.push_back(aSym);
	mash->ivice.push_back(bSym);
	mash->ivice.push_back(cSym);
	mash->ivice.push_back(dSym);
	mash->ivice.push_back(eSym);
	mash->ivice.push_back(fSym);

	mash->lica.push_back(f1);
	mash->lica.push_back(f2);
	mash->lica.push_back(f3);
	mash->lica.push_back(f4);

	test(temeA , temeB , temeC , temeD);

	int i = 0;
	while (i < 1) {
		i++;
		vector<Ivica*> ivice = mash->ivice;

		//for (int i = 0; i < ivice.size(); i++) {
		//	if (!ivice[i]->podeljena) {
		//		ivice[i]->podeljena = true;
		//		ivice[i]->eSym->podeljena = true;
		//		ivice[i]->deli();
		//	}
		//}


		///*for (int i = 0; i < mash->cvorovi.size(); i++) {
		//	mash->cvorovi[i]->azurirajCvorove();
		//}*/

		//vector<Lice*> lica = mash->lica;
		//for (int i = 0; i < lica.size(); i++) {
		//	lica[i]->deli();
		//}
	}
}



void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	GLfloat a[3] = { 0.0, 4.0, 0.0 },
		b[3] = { 0.0, 0.0, -7.0 },
		c[3] = { 4.0, 7.0, 6.0 },
		d[3] = { -6.0, 6.0, -4.0 };

	GLfloat a2[3] = { 0.0, 0.0, 0.0 },
		b2[3] = { 4.0, 0.0, 0.0 },
		c2[3] = { 2.0, 0.0, 0.1 },
		d2[3] = { 2.0, 4.0, 1.0 };

	tetraedar(a, b, c, d);

	float temeA[3] = { -6.0, -6.0, 0.0 };
	float temeB[3] = { -2.0, 0.0 , 0.0 };
	float temeC[3] = { 2.0 , -6.0 , 0.0 };

	//mockTrougao(temeA, temeB, temeC);

	crtajMash();

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