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

float width = 500.0;
float height = 500.0;

Mash *mash = new Mash;

float rotacijaSvetla1 = 0.0;

int brojSubdivizija = 3;

static void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { -4.0, 0.0, -3, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light1_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { 4.0, 0.0, -3.0, 1.0 };
	GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

}

void winReshape(GLint w, GLint h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (float)w / (float)h, -7, 7);
	gluLookAt(0, 0, 10, 0, 0, -7, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void podesiKoordinateCvora(Cvor *c) {

	Cvor *levo = c->e->preth->v;
	Cvor *desno = c->e->sled->v;
	Cvor *gore = c->e->preth->preth->preth->v;
	Cvor *dole = c->e->eSym->preth->preth->v;

	c->x += levo->x * (3.0 / 8.0);
	c->x += desno->x * (3.0 / 8.0);
	c->x += gore->x * (1.0 / 8.0);
	c->x += dole->x * (1.0 / 8.0);

	c->y += levo->y * (3.0 / 8.0);
	c->y += desno->y * (3.0 / 8.0);
	c->y += gore->y * (1.0 / 8.0);
	c->y += dole->y * (1.0 / 8.0);

	c->z += levo->z * (3.0 / 8.0);
	c->z += desno->z * (3.0 / 8.0);
	c->z += gore->z * (1.0 / 8.0);
	c->z += dole->z * (1.0 / 8.0);
}

void nacrtajIvicu(Ivica *i) {

	glLineWidth(5);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);

	glVertex3f(i->v->x, i->v->y, i->v->z);
	glVertex3f(i->sled->v->x, i->sled->v->y, i->sled->v->z);

	glEnd();

}

void crtajMash() {

	for (int i = 0; i < mash->lica.size(); i++) {
		Ivica *iv = mash->lica[i]->e;
		glColor3f(mash->lica[i]->r, mash->lica[i]->g, mash->lica[i]->b);

		glBegin(GL_TRIANGLES);
		glNormal3fv(mash->lica[i]->vektorNormale);

		do {
			glNormal3fv(iv->v->vektorNormale);
			glVertex3f(iv->v->x, iv->v->y, iv->v->z);
			iv = iv->sled;
		} while (iv != mash->lica[i]->e);
		glEnd();
	}

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

	for (int i = 0; i < mash->lica.size(); i++) {
		mash->lica[i]->izracunajVektorNormale();
	}

	for (int i = 0; i < mash->cvorovi.size(); i++) {
		mash->cvorovi[i]->izracunajVektorNormale();
	}

	//Subdivizija

	int k = 0;
	while (k < brojSubdivizija) {
		k++;

		//zapamti podatke pre subdivizije
		vector<Ivica*> ivice = mash->ivice;
		vector<Cvor*> cvorovi = mash->cvorovi; 
		vector<Lice*> lica = mash->lica;

		//izracunaj sumu susednih cvorova pre subdivizije
		for (int i = 0; i < cvorovi.size(); i++) {
			cvorovi[i]->izracunajSumuSusednihCvorova();
		}

		//podeli ivice
		for (int i = 0; i < ivice.size(); i++) {
			if (!ivice[i]->podeljena) {
				ivice[i]->podeljena = true;
				ivice[i]->eSym->podeljena = true;
				ivice[i]->deli();
			}
		}

		//podesi koordinate novih cvorova
		for (int i = 0; i < mash->noviCvorovi.size(); i++) {
			podesiKoordinateCvora(mash->noviCvorovi[i]);
		}

		//isprazni vektor sa novim cvorovima
		mash->noviCvorovi.erase(mash->noviCvorovi.begin(), mash->noviCvorovi.end());

		//azuriraj stare cvorove i vrati sume susednih cvorova na nulu
		for (int i = 0; i < cvorovi.size(); i++) {
			cvorovi[i]->azurirajCvorove();
			cvorovi[i]->sumax = cvorovi[i]->sumay = cvorovi[i]->sumaz = cvorovi[i]->brojSusednihCvorova = 0.0;
		}

		//podeli lica
		for (int i = 0; i < lica.size(); i++) {
			lica[i]->deli();
		}

		//izracunaj vektor normale lica
		for (int i = 0; i < mash->lica.size(); i++) {
			mash->lica[i]->izracunajVektorNormale();
		}

		//-,,- cvorova
		for (int i = 0; i < mash->cvorovi.size(); i++) {
			mash->cvorovi[i]->izracunajVektorNormale();
		}

		//oznaci sve ivice kao nepodeljene
		for (int i = 0; i < mash->ivice.size(); i++) {
			mash->ivice[i]->podeljena = false;
		}


	}

}

bool rotiraj = true;
int rot = 0;

void update(int value) {

	if (rotiraj) rot = 1;
	else rot = 0;

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	glRotated(rot, 1, 0, 0);

	float temeA[3] = { -6.0, -6.0, 0.0 };
	float temeB[3] = { -2.0, 0.0 , 0.0 };
	float temeC[3] = { 2.0 , -6.0 , 0.0 };

	crtajMash();

	//glutSolidSphere(1, 5, 5);

	glFlush();
}

void onMouseClick(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (rotiraj) rotiraj = false;
		else rotiraj = true;
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);   // use GLUT_DEPTH if HSR is being used
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("subdivizija");

	GLfloat a[3] = { -2.0, 2.0, -2.0 },
		b[3] = { -2.0, -2.0, 2.0 },
		c[3] = { 2.0, 2.0, 2.0 },
		d[3] = { 2.0, -2.0, -2.0 };


	tetraedar(a, b, c, d);

	//duzine ivica
	
	/*
	for (int i = 0; i < mash->ivice.size(); i++) {

		cout << sqrt(pow(mash->ivice[i]->v->x - mash->ivice[i]->sled->v->x, 2) + pow(mash->ivice[i]->v->y - mash->ivice[i]->sled->v->y, 2) + pow(mash->ivice[i]->v->z - mash->ivice[i]->sled->v->z, 2)) << endl;

	}
	*/

	glutDisplayFunc(display);
	glutReshapeFunc(winReshape);
	glutTimerFunc(100, update, 0);
	glutMouseFunc(onMouseClick);
	myInit();
	glEnable(GL_DEPTH_TEST);                                    // enable Hidden Surface Removal Algorithm
	glutMainLoop();
	return 0;
}