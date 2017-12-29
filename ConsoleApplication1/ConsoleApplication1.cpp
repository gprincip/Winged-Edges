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
	glOrtho(-7.0, 7.0, -7.0, 7.0, -7.0, 7.0);
	/*gluPerspective(40.0, 500.0 / 500.0, -13, 13);
	gluLookAt(0, 0, 12.9, 0, 0, 12, 0, 1, 0);*/
	glMatrixMode(GL_MODELVIEW);
}

void winReshape(GLint w, GLint h)
{

	mash->obrisiPodatke();

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

void crtajMash2() {

	float r, g, b;

	for (int i = 0; i < mash->lica.size(); i++) {

		r = ((float)rand() / RAND_MAX);
		g = ((float)rand() / RAND_MAX);
		b = ((float)rand() / RAND_MAX);

		Ivica *iv = mash->lica[i]->e;

		glColor3f(r, g, b);
		glPointSize(10);

		glBegin(GL_TRIANGLES);
		int s = 0;
		do {
			glVertex3f(iv->v->x, iv->v->y, iv->v->z);

			iv = iv->sled;
			s++;
		} while (iv != mash->lica[i]->e);

		//cout << s << endl;

		glEnd();


	}
}

void test(float *temeA, float *temeB, float *temeC, float *temeD) {

	Ivica *e1 = mash->ivice[0];

	//***************************************************
	Cvor *c1 = e1->v;
	Cvor *c2 = e1->sled->v;
	Cvor *c3 = e1->sled->sled->v;
	Cvor *c4 = e1->eSym->sled->sled->v;

	glColor3f(1, 0, 0);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);

	glVertex3f(e1->v->x, e1->v->y, e1->v->z);
	glVertex3f(e1->sled->v->x, e1->sled->v->y, e1->sled->v->z);
	/*glVertex3f(e1->sled->sled->v->x, e1->sled->sled->v->y, e1->sled->sled->v->z);
	glVertex3f(e1->sled->sled->sled->v->x, e1->sled->sled->sled->v->y, e1->sled->sled->sled->v->z);*/

	glEnd();
	//glFlush();

	glColor3f(1, 0, 0);
	glPointSize(100);
	glBegin(GL_POINTS);

	glVertex3f(c1->x, c1->y, c1->z);
	glVertex3f(c2->x, c2->y, c2->z);
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

	glVertex3f(c->x, c->y, c->z);

	glEnd();
	glFlush();

	mash->cvorovi.push_back(c);
	mash->ivice.push_back(en);
	mash->ivice.push_back(enSym);

}


void brojIvicaULicima() {

	for (int i = 0; i < mash->lica.size(); i++) {
		int br = 0;
		Ivica *temp = mash->lica[i]->e;
		do {
			br++;
			temp = temp->sled;
		} while (temp != mash->lica[i]->e);
		cout << "Broj ivica: " << br << endl;
	}

}

void nacrtajIviceLica(Lice *l) {
	Ivica *i = l->e;
	glLineWidth(5);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(i->v->x, i->v->y, i->v->z);
	do {
		i = i->sled;
		glVertex3f(i->v->x, i->v->y, i->v->z);
	} while (i != l->e);

	glEnd();
	glFlush();
}

int deljenje = 0;

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

	//test(temeA , temeB , temeC , temeD); 

	int k = 0;
	while (k < 1) {
		k++;

		vector<Ivica*> ivice = mash->ivice;
		vector<Cvor*> cvorovi = mash->cvorovi; //stari cvorovi

		for (int i = 0; i < ivice.size(); i++) {
			if (!ivice[i]->podeljena) {
				ivice[i]->podeljena = true;
				ivice[i]->eSym->podeljena = true;
				ivice[i]->deli();
			}
		}

		for (int i = 0; i < mash->noviCvorovi.size(); i++) {
			podesiKoordinateCvora(mash->noviCvorovi[i]);
		}

		mash->noviCvorovi.erase(mash->noviCvorovi.begin(), mash->noviCvorovi.end());

		for (int i = 0; i < cvorovi.size(); i++) {
			cvorovi[i]->azurirajCvorove();
		}

		vector<Lice*> lica = mash->lica;
		for (int i = 0; i < lica.size(); i++) {
			lica[i]->deli();
		}

		for (int i = 0; i < mash->ivice.size(); i++) {
			mash->ivice[i]->podeljena = false;
		}
		//brojIvicaULicima();
	}

	/*deljenje = 6;

	Lice *l = mash->lica[deljenje];
	Ivica *i = l->e;
	vector<Ivica*> iv;

	do {
		iv.push_back(i);
		i = i->sled;
	} while (i != l->e);

	for (int i = 0; i < iv.size(); i++)
		iv[i]->deli();

	podesiKoordinateCvora(i->sled->v);
	podesiKoordinateCvora(i->sled->sled->sled->v);
	podesiKoordinateCvora(i->sled->sled->sled->sled->sled->v);

	i->v->azurirajCvorove();
	i->sled->sled->v->azurirajCvorove();
	i->sled->sled->sled->sled->v->azurirajCvorove();

	l->deli();*/


}


//****************Test trouglovi*****************

void trouglovi() {

	Cvor *a = new Cvor(-2.0, -2.0, 0);
	Cvor *b = new Cvor(2.0, -2.0, 0);
	Cvor *c = new Cvor(0.0, 2.0, 0);
	Cvor *d = new Cvor(-4.0, 2.0, 0);
	Cvor *ve = new Cvor(4.0, 2.0, 0);
	Cvor *vf = new Cvor(0.0, -6.0, 0);

	Ivica *e1 = new Ivica(a, NULL, NULL, NULL, NULL, mash);
	Ivica *e2 = new Ivica(b, NULL, NULL, e1, NULL, mash);
	Ivica *e3 = new Ivica(c, NULL, NULL, e2, e1, mash);
	Ivica *e1Sym = new Ivica(b, NULL, e1, NULL, NULL, mash);
	Ivica *e2Sym = new Ivica(c, NULL, e2, NULL, NULL, mash);
	Ivica *e3Sym = new Ivica(a, NULL, e3, NULL, NULL, mash);
	Ivica *e4 = new Ivica(c, NULL, NULL, e3Sym, NULL, mash);
	Ivica *e5 = new Ivica(d, NULL, NULL, e4, e3Sym, mash);
	Ivica *e5Sym = new Ivica(a, NULL, e5, NULL, NULL, mash);
	Ivica *e4Sym = new Ivica(d, NULL, e4, NULL, NULL, mash);
	Ivica *e6 = new Ivica(ve, NULL, NULL, NULL, e2Sym, mash);
	Ivica *e7 = new Ivica(b, NULL, NULL, e2Sym, e6, mash);
	Ivica *e8 = new Ivica(vf, NULL, NULL, NULL, e1Sym, mash);
	Ivica *e9 = new Ivica(a, NULL, NULL, e1Sym, e8, mash);
	Ivica *e6Sym = new Ivica(c, NULL, e6, NULL, NULL, mash);
	Ivica *e7Sym = new Ivica(ve, NULL, e7, NULL, NULL, mash);
	Ivica *e8Sym = new Ivica(b, NULL, e8, NULL, NULL, mash);
	Ivica *e9Sym = new Ivica(vf, NULL, e9, NULL, NULL, mash);

	Lice *l1 = new Lice(e1, mash);
	Lice *l2 = new Lice(e3Sym, mash);
	Lice *l3 = new Lice(e7, mash);
	Lice *l4 = new Lice(e8, mash);

	e1->l = e2->l = e3->l = l1;
	e1->eSym = e1Sym;
	e2->eSym = e2Sym;
	e3->eSym = e3Sym;
	e4->eSym = e4Sym;
	e5->eSym = e5Sym;
	e6->eSym = e6Sym;
	e7->eSym = e7Sym;
	e8->eSym = e8Sym;
	e9->eSym = e9Sym;

	e6->l = e7->l = l3;
	e9->l = e8->l = l4;
	e6->preth = e7;
	e8->preth = e9;

	e1->sled = e2;
	e1->preth = e3;
	e2->sled = e3;

	e4->l = e5->l = e3Sym->l = l2;
	e3Sym->sled = e4;
	e3Sym->preth = e5;
	e4->sled = e5;

	e2Sym->l = l3;
	e1Sym->l = l4;

	e2Sym->sled = e7;
	e2Sym->preth = e6;
	e1Sym->sled = e9;
	e1Sym->preth = e8;

	vector<Ivica*> ivice; vector<Cvor*> cvorovi; vector<Lice*> lica;
	mash->ivice.push_back(e1);
	mash->ivice.push_back(e2);
	mash->ivice.push_back(e3);
	mash->ivice.push_back(e4);
	mash->ivice.push_back(e5);
	mash->ivice.push_back(e1Sym);
	mash->ivice.push_back(e2Sym);
	mash->ivice.push_back(e3Sym);
	mash->ivice.push_back(e4Sym);
	mash->ivice.push_back(e5Sym);
	mash->ivice.push_back(e6);
	mash->ivice.push_back(e7);
	mash->ivice.push_back(e8);
	mash->ivice.push_back(e9);
	mash->ivice.push_back(e6Sym);
	mash->ivice.push_back(e7Sym);
	mash->ivice.push_back(e8Sym);
	mash->ivice.push_back(e9Sym);

	mash->cvorovi.push_back(a);
	mash->cvorovi.push_back(b);
	mash->cvorovi.push_back(c);
	mash->cvorovi.push_back(d);
	mash->cvorovi.push_back(ve);
	mash->cvorovi.push_back(vf);

	mash->lica.push_back(l1);
	mash->lica.push_back(l2);
	mash->lica.push_back(l3);
	mash->lica.push_back(l4);

	/*

	//deljenje ivice;

	Cvor *c1 = e1->v;
	Cvor *c2 = e1->sled->sled->v;
	Cvor *c3 = e1->sled->v;
	Cvor *c4 = e1->preth->eSym->sled->sled->v;

	//crtanje tacaka na osnovu kojih se racunaju koordinate novog cvora
	glPointSize(3);
	glBegin(GL_POINTS);

	glVertex3f(c1->x, c1->y, c1->z);
	glVertex3f(c2->x, c2->y, c2->z);
	glVertex3f(c3->x, c3->y, c3->z);
	glVertex3f(c4->x, c4->y, c4->z);

	glEnd();

	Cvor *cn = new Cvor(NULL);
	Ivica *en = new Ivica(c, e1->l, NULL, e1, e1->sled, mash);
	Ivica *enSym = new Ivica(c, e1->eSym->l, e1, e1->eSym, e1->eSym->sled, mash);

	cn->e = en;

	e1->sled = en;
	e1->eSym = enSym;

	e1->eSym->sled = enSym;
	enSym->eSym = e1;

	en->sled->preth = en;
	enSym->sled->preth = enSym;

	cn->x += c1->x * (3.0 / 8.0);
	cn->x += c2->x * (3.0 / 8.0);
	cn->x += c3->x * (1.0 / 8.0);
	cn->x += c4->x * (1.0 / 8.0);

	cn->y += c1->y * (3.0 / 8.0);
	cn->y += c2->y * (3.0 / 8.0);
	cn->y += c3->y * (1.0 / 8.0);
	cn->y += c4->y * (1.0 / 8.0);

	cn->z += c1->z * (3.0 / 8.0);
	cn->z += c2->z * (3.0 / 8.0);
	cn->z += c3->z * (1.0 / 8.0);
	cn->z += c4->z * (1.0 / 8.0);

	//crtanje nove tacke

	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);

	glVertex3f(cn->x, cn->y, cn->z);

	glEnd();

	*/

	//deljenje
	int k = 0;
	while (k < 1) {
		k++;

		vector<Ivica*> ivice = mash->ivice;
		vector<Cvor*> cvorovi = mash->cvorovi; //stari cvorovi

		for (int i = 0; i < ivice.size(); i++) {
			if (!ivice[i]->podeljena) {
				ivice[i]->podeljena = true;
				ivice[i]->eSym->podeljena = true;
				ivice[i]->deli();
			}
		}

		for (int i = 0; i < mash->noviCvorovi.size(); i++) {
			podesiKoordinateCvora(mash->noviCvorovi[i]);
		}

		mash->noviCvorovi.erase(mash->noviCvorovi.begin(), mash->noviCvorovi.end());

		for (int i = 0; i < cvorovi.size(); i++) {
			cvorovi[i]->azurirajCvorove();
		}

		vector<Lice*> lica = mash->lica;
		for (int i = 0; i < lica.size(); i++) {
			lica[i]->deli();
		}

		for (int i = 0; i < mash->ivice.size(); i++) {
			mash->ivice[i]->podeljena = false;
		}
		//brojIvicaULicima();
	}

	
	//crtanje

	float r, g, bl;

	for (int i = 0; i < lica.size(); i++) {

		r = ((float)rand() / RAND_MAX);
		g = ((float)rand() / RAND_MAX);
		bl = ((float)rand() / RAND_MAX);

		Ivica *iv = lica[i]->e;

		glColor3f(r, g, bl);
		glPointSize(10);

		glBegin(GL_TRIANGLES);
		int s = 0;
		do {
			glVertex3f(iv->v->x, iv->v->y, iv->v->z);
			cout << iv->v->x << " , " << iv->v->y << " , " << iv->v->z << endl;
			iv = iv->sled;
			s++;
		} while (iv != lica[i]->e);

		//cout << s << endl;

		glEnd();
	}

}

//***********************************************

int rot = 0;
void update(int value) {

	rot = (rot + 1) % 360;

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslated(0, -1, 0);

	glRotated(rot, 0, 1, 0);
	//glRotated(30, 1, 0, 0);
	//glRotated(90, 0, 1, 0);

	float temeA[3] = { -6.0, -6.0, 0.0 };
	float temeB[3] = { -2.0, 0.0 , 0.0 };
	float temeC[3] = { 2.0 , -6.0 , 0.0 };

	crtajMash2();

	//trouglovi();

	//nacrtajIviceLica(mash->lica[deljenje]);

	Lice *l = mash->lica[1];
	Ivica *i = l->e;

	glLineWidth(5);
	glColor3f(1, 0, 0);

	//i = i->eSym->eSym;

	glBegin(GL_LINE_STRIP);

	glVertex3f(i->v->x, i->v->y, i->v->z);
	glVertex3f(i->preth->v->x, i->preth->v->y, i->preth->v->z);
	glVertex3f(i->preth->preth->v->x, i->preth->preth->v->y, i->preth->preth->v->z);
	glVertex3f(i->preth->preth->preth->v->x, i->preth->preth->preth->v->y, i->preth->preth->preth->v->z);


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

	GLfloat a[3] = { 0.0, 4.0, 0.0 },
		b[3] = { 0.0, 0.0, -7.0 },
		c[3] = { 4.0, 7.0, 6.0 },
		d[3] = { -6.0, 6.0, -4.0 };

	GLfloat a2[3] = { 0.0, 0.0, 0.0 },
		b2[3] = { 4.0, 0.0, 0.0 },
		c2[3] = { 2.0, 0.0, 0.1 },
		d2[3] = { 2.0, 4.0, 1.0 };

	GLfloat a3[3] = { -2.0, 2.0, -2.0 },
		b3[3] = { -2.0, -2.0, 2.0 },
		c3[3] = { 2.0, 2.0, 2.0 },
		d3[3] = { 2.0, -2.0, -2.0 };

	GLfloat a4[3] = { -2.0, 2.0, 0.0 },
		b4[3] = { -2.0, -2.0, 0.0 },
		c4[3] = { 2.0, 2.0, 0.0 },
		d4[3] = { 2.0, -2.0, 0.0 };

	//tetraedar(a4, b4, c4, d4);
	tetraedar(a3, b3, c3, d3);
	
	glutDisplayFunc(display);
	//glutReshapeFunc(winReshape);
	glutTimerFunc(100, update, 0);
	myInit();
	glEnable(GL_DEPTH_TEST);                                    // enable Hidden Surface Removal Algorithm
	glutMainLoop();
	return 0;
}