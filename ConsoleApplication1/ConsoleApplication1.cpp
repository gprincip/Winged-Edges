// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#define _USE_MATH_DEFINES

#include "stdafx.h"
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include "GL\glut.h"
#include<string>

#include "Mash.h"
#include "Cvor.h"
#include "Ivica.h"

#include<math.h>
#include<vector>

using namespace std;

float width = 500.0;
float height = 500.0;

Mesh *mesh = new Mesh;

bool rotirajSvetlo = false;
int rotacijaSvetla = 0.0;

bool rotiraj = false;
int rot = 0;

int brojSubdivizija = 1; //za f-ju tetraedar

int brojIvica(Lice *l) {

	Ivica *i = l->e;
	int br = 0;
	do {
		br++;
		i = i->sled;
	} while (i != l->e);
	return br;
}

void podesiSimetricneIvice() {
	int b = 0;
	int brIvica = mesh->ivice.size();
	for (int i = 0; i < mesh->ivice.size(); i++) {
		b++;
		if (b % 100 == 0) cout << "Podesavanje simetricnih ivica. Zavrseno " << b << " od " << brIvica << endl;
		Cvor *c1 = mesh->ivice[i]->v;
		Cvor *c2 = mesh->ivice[i]->sled->v;

		for (int j = 0; j < mesh->ivice.size(); j++) {

			if (mesh->ivice[j]->v == c2 && mesh->ivice[j]->sled->v == c1) {
				mesh->ivice[i]->eSym = mesh->ivice[j];
				break;
			}
		}
	}
}

void podesiOrjentaciju(Lice *l) {

	//ovo nije sigurno
	//ako je skalarni prozvod vektora normale trougla i neke tacke na trouglu > 0, onda je normala usmerena ka trouglu
	//ako je normala usmerena ka trouglu, lice je levo od ivice

	Ivica *i = l->e;

	float skalarniProjzvod = l->vektorNormale[0] * i->v->x + l->vektorNormale[1] * i->v->y + l->vektorNormale[2] * i->v->z;

	if (skalarniProjzvod < 0) {

		Ivica *e1 = l->e;
		Ivica *e2 = e1->sled;
		Ivica *e3 = e2->sled;

		e1->sled = e1->preth;
		e2->sled = e2->preth;
		e3->sled = e3->preth;

		e1->preth = e1->sled->sled;
		e2->preth = e2->sled->sled;
		e3->preth = e3->sled->sled;

		float u[3] = { i->sled->v->x - i->v->x , i->sled->v->y - i->v->y , i->sled->v->z - i->v->z };
		float v[3] = { i->sled->sled->v->x - i->v->x , i->sled->sled->v->y - i->v->y , i->sled->sled->v->z - i->v->z };

		l->vektorNormale[0] = (u[1] * v[2]) - (u[2] * v[1]);
		l->vektorNormale[1] = (u[2] * v[0]) - (u[0] * v[2]);
		l->vektorNormale[2] = (u[0] * v[1]) - (u[1] * v[0]);

		float norma = sqrt(pow(l->vektorNormale[0], 2) + pow(l->vektorNormale[1], 2) + pow(l->vektorNormale[2], 2));

		l->vektorNormale[0] /= norma;
		l->vektorNormale[1] /= norma;
		l->vektorNormale[2] /= norma;
	}
}

void ucitajObj(const char *triangleMeshImeFajla, const char *indeksiImeFajla) {

	ifstream triangleMeshStream;
	triangleMeshStream.open(triangleMeshImeFajla);
	string linija;

	if (triangleMeshStream.is_open()) {
		while (getline(triangleMeshStream, linija)) {

			int i = 2;
			string x, y, z;
			x = y = z = "";

			//ucitavanje iksa
			while (true) {
				if (linija[i] == ' ') break;
				x += linija[i++];
			}
			i++;
			//uvitavanje ipsilona
			while (true) {
				if (linija[i] == ' ') break;
				y += linija[i++];

			}
			i++;
			//ucitavanje zeda
			while (true) {
				//if (linija[i] == ' ') break;
				if (i == linija.length()) break;
				z += linija[i++];
			}

			mesh->cvorovi.push_back(new Cvor(stof(x), stof(y), stof(z)));

		}
		triangleMeshStream.close();
	}
	else {
		cout << "Greska pri otvaranju fajla" << endl;
	}

	ifstream indeksi;
	indeksi.open(indeksiImeFajla);

	if (indeksi.is_open()) {
		while (getline(indeksi, linija)) {


			int i = 2;
			string ind1, ind2, ind3;

			//ucitavanje prvog indeksa
			while (true) {
				if (linija[i] == '/') break;
				ind1 += linija[i++];
			}
			i++;

			while (true) {
				if (linija[i++] == ' ') break;
			}
			
			//*******************************************

			//ucitavanje drugog indeksa
			while (true) {
				if (linija[i] == '/') break;
				ind2 += linija[i++];
			}
			i++;

			while (true) {
				if (linija[i++] == ' ') break;
			}
		

			//*******************************************

			//ucitavanje treceg indeksa
			while (true) {
				if (linija[i] == '/') break;
				ind3 += linija[i++];
			}

			Cvor *c1 = mesh->cvorovi[stoi(ind1)-1];
			Cvor *c2 = mesh->cvorovi[stoi(ind2)-1];
			Cvor *c3 = mesh->cvorovi[stoi(ind3)-1];

			Ivica *e1 = new Ivica(c1, NULL, NULL, NULL, NULL, mesh);
			Ivica *e2 = new Ivica(c2, NULL, NULL, e1, NULL, mesh);
			Ivica *e3 = new Ivica(c3, NULL, NULL, e2, e1, mesh);
			c1->e = e1;
			c2->e = e2;
			c3->e = e3;

			mesh->ivice.push_back(e1);
			mesh->ivice.push_back(e2);
			mesh->ivice.push_back(e3);

			e1->sled = e2;
			e1->preth = e3;

			e2->sled = e3;

			Lice *l = new Lice(e1, mesh);
			mesh->lica.push_back(l);
			e1->l = l;
			e2->l = l;
			e3->l = l;

		}
		indeksi.close();
	}
	else {
		cout << "Greska pri otvaranju indeksa" << endl;
	}

	//podesi normale i proveri da li svaka ivica pamti lice sa leve strane
	for (int i = 0; i < mesh->lica.size(); i++) {
		mesh->lica[i]->izracunajVektorNormale();
		//podesiOrjentaciju(mesh->lica[i]);
	}

	for (int i = 0; i < mesh->cvorovi.size(); i++) {
		mesh->cvorovi[i]->izracunajVektorNormale();
	}

	podesiSimetricneIvice();

}

void ucitajMesh(const char* triangleMeshImeFajla, const char* indeksiImeFajla) {

	ifstream triangleMeshStream;
	triangleMeshStream.open(triangleMeshImeFajla);
	string linija;

	if (triangleMeshStream.is_open()) {
		while (getline(triangleMeshStream, linija)) {

			int i = 0;
			string x, y, z;
			x = y = z = "";

			//ucitavanje iksa
			while (true) {
				if (linija[i] == ' ') break;
				x += linija[i++];
			}
			i++;
			//uvitavanje ipsilona
			while (true) {
				if (linija[i] == ' ') break;
				y += linija[i++];

			}
			i++;
			//ucitavanje zeda
			while (true) {
				if (linija[i] == ' ') break;
				z += linija[i++];
			}


			mesh->cvorovi.push_back(new Cvor(stof(x), stof(y), stof(z)));

		}
		triangleMeshStream.close();
	}
	else {
		cout << "Greska pri otvaranju fajla" << endl;
	}

	ifstream indeksi;
	indeksi.open(indeksiImeFajla);

	if (indeksi.is_open()) {
		while (getline(indeksi, linija)) {

			int i = 2;
			string ind1, ind2, ind3;

			//ucitavanje prvog indeksa
			while (true) {
				if (linija[i] == ' ') break;
				ind1 += linija[i++];
			}
			i++;

			//ucitavanje drugog indeksa
			while (true) {
				if (linija[i] == ' ') break;
				ind2 += linija[i++];
			}
			i++;

			//ucitavanje treceg indeksa
			while (true) {
				if (linija[i] == ' ') break;
				ind3 += linija[i++];
			}

			Cvor *c1 = mesh->cvorovi[stoi(ind1)];
			Cvor *c2 = mesh->cvorovi[stoi(ind2)];
			Cvor *c3 = mesh->cvorovi[stoi(ind3)];

			Ivica *e1 = new Ivica(c1, NULL, NULL, NULL, NULL, mesh);
			Ivica *e2 = new Ivica(c2, NULL, NULL, e1, NULL, mesh);
			Ivica *e3 = new Ivica(c3, NULL, NULL, e2, e1, mesh);
			c1->e = e1;
			c2->e = e2;
			c3->e = e3;

			mesh->ivice.push_back(e1);
			mesh->ivice.push_back(e2);
			mesh->ivice.push_back(e3);

			e1->sled = e2;
			e1->preth = e3;

			e2->sled = e3;

			Lice *l = new Lice(e1, mesh);
			mesh->lica.push_back(l);
			e1->l = l;
			e2->l = l;
			e3->l = l;

		}
		indeksi.close();
	}
	else {
		cout << "Greska pri otvaranju fajla" << endl;
	}

	//podesi normale i proveri da li svaka ivica pamti lice sa leve strane
	for (int i = 0; i < mesh->lica.size(); i++) {
		mesh->lica[i]->izracunajVektorNormale();
		//podesiOrjentaciju(mesh->lica[i]);
	}

	for (int i = 0; i < mesh->cvorovi.size(); i++) {
		mesh->cvorovi[i]->izracunajVektorNormale();
	}

	podesiSimetricneIvice();

}

int indeksCvoraUMeshu(Cvor *c) {

	for (int i = 0; i < mesh->cvorovi.size(); i++) {
		if (mesh->cvorovi[i] == c) {
			return i;
		}
	}
	return INT_MAX;
}

void upisiObj(const char *imeFajlaCvorovi, const char *imeFajlaIndeksi) {
	ofstream cvorovi;
	cvorovi.open(imeFajlaCvorovi);

	for (int i = 0; i < mesh->cvorovi.size(); i++) {
		cvorovi <<"v "<< mesh->cvorovi[i]->x << " " << mesh->cvorovi[i]->y << " " << mesh->cvorovi[i]->z << " ";
		if (i != mesh->cvorovi.size() - 1) cvorovi << endl;
	}

	cvorovi.close();

	ofstream indeksi;
	indeksi.open(imeFajlaIndeksi);

	for (int i = 0; i < mesh->lica.size(); i++) {
		indeksi << "f ";

		Ivica *e = mesh->lica[i]->e;

		do {
			int ind = indeksCvoraUMeshu(e->v);
			if (ind != INT_MAX) indeksi<< ind+1 << "/0/0"<< " ";
			else {
				cout << "Greska prilikom upisivanja u mesh" << endl;
				return;
			}
			e = e->sled;
		} while (e != mesh->lica[i]->e);

		if (i != mesh->lica.size() - 1) indeksi << endl;
	}

	indeksi.close();

}

void upisiMesh(const char *imeFajlaCvorovi, const char *imeFajlaIndeksi) {

	ofstream cvorovi;
	cvorovi.open(imeFajlaCvorovi);

	for (int i = 0; i < mesh->cvorovi.size(); i++) {
		cvorovi << mesh->cvorovi[i]->x << " " << mesh->cvorovi[i]->y << " " << mesh->cvorovi[i]->z << " ";
		if (i != mesh->cvorovi.size() - 1) cvorovi << endl;
	}

	cvorovi.close();

	ofstream indeksi;
	indeksi.open(imeFajlaIndeksi);

	for (int i = 0; i < mesh->lica.size(); i++) {
		indeksi << "3 ";

		Ivica *e = mesh->lica[i]->e;

		do {
			int ind = indeksCvoraUMeshu(e->v);
			if (ind != INT_MAX) indeksi << ind << " ";
			else {
				cout << "Greska prilikom upisivanja u mesh" << endl;
				return;
			}
			e = e->sled;
		} while (e != mesh->lica[i]->e);

		if (i != mesh->lica.size() - 1) indeksi << endl;
	}

	indeksi.close();
}

static void myInit()
{
	//ucitajMesh("torus.txt", "torusIndeksi.txt");
	ucitajObj("motorObj.txt", "motorObjIndeksi.txt");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void winReshape(GLint w, GLint h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*gluPerspective(40.0, (float)w / (float)h, 2.0, -2.0); //torus, piramida
	gluLookAt(0, 0, 4, 0, 0, -2, 0, 1, 0);*/

	/*gluPerspective(40.0, (float)w / (float)h, 2.0, -2.0); //tetraedar, treba da se odkomentarise podesiOrjentaciju
	gluLookAt(0, 0, 10, 0, 0, -2, 0, 1, 0);*/

	/*gluPerspective(40.0, (float)w / (float)h, 0.7, -0.7); //svecnjak, zmaj
	gluLookAt(0, 0, 1, 0, 0, -2, 0, 1, 0);*/

	/*gluPerspective(40.0, (float)w / (float)h, 35.0, -35.0); //stopalo
	gluLookAt(0, 0, 40, 0, 0, -2, 0, 1, 0);*/

	gluPerspective(40.0, (float)w / (float)h, 130.0, -130.0); // motor
	gluLookAt(0, 0, 400, 0, 0, -2, 0, 1, 0);

	//glOrtho(-7, 7, -7, 7, -7, 7);
	//glOrtho(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void podesiKoordinateCvora(Cvor *c) {

	if (c->e->eSym != NULL) {
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
	else {
		Cvor *levo = c->e->preth->v;
		Cvor *desno = c->e->sled->v;

		c->x += levo->x * 0.5;
		c->x += desno->x * 0.5;

		c->y += levo->y * 0.5;
		c->y += desno->y * 0.5;

		c->z += levo->z * 0.5;
		c->z += desno->z * 0.5;
	}
}

void nacrtajIvicu(Ivica *i) {

	glLineWidth(5);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);

	glVertex3f(i->v->x, i->v->y, i->v->z);
	glVertex3f(i->sled->v->x, i->sled->v->y, i->sled->v->z);

	glEnd();
}

void crtajMesh() {
	int br = 0;
	for (int i = 0; i < mesh->lica.size(); i++) {
		Ivica *iv = mesh->lica[i]->e;
		glColor3f(mesh->lica[i]->r, mesh->lica[i]->g, mesh->lica[i]->b);

		glBegin(GL_TRIANGLES);
		glNormal3fv(mesh->lica[i]->vektorNormale);

		do {
			glNormal3fv(iv->v->vektorNormale);
			glVertex3f(iv->v->x, iv->v->y, iv->v->z);
			iv = iv->sled;
		} while (iv != mesh->lica[i]->e);
		glEnd();
	}
}

void tetraedar(float *temeA, float *temeB, float *temeC, float *temeD) {

	Cvor *v1 = new Cvor(temeA[0], temeA[1], temeA[2]);
	Cvor *v2 = new Cvor(temeB[0], temeB[1], temeB[2]);
	Cvor *v3 = new Cvor(temeC[0], temeC[1], temeC[2]);
	Cvor *v4 = new Cvor(temeD[0], temeD[1], temeD[2]);

	Lice *f1 = new Lice(NULL, mesh);
	Lice *f2 = new Lice(NULL, mesh);
	Lice *f3 = new Lice(NULL, mesh);
	Lice *f4 = new Lice(NULL, mesh);

	//f3
	Ivica *a = new Ivica(v1, f3, NULL, NULL, NULL, mesh);
	Ivica *b = new Ivica(v2, f3, NULL, a, NULL, mesh);
	Ivica *c = new Ivica(v3, f3, NULL, b, a, mesh);

	//f2
	Ivica *dSym = new Ivica(v4, f2, NULL, NULL, NULL, mesh);
	Ivica *bSym = new Ivica(v3, f2, b, dSym, NULL, mesh);
	Ivica *fSym = new Ivica(v2, f2, NULL, bSym, dSym, mesh);

	//f4
	Ivica *d = new Ivica(v3, f4, dSym, NULL, NULL, mesh);
	Ivica *e = new Ivica(v4, f4, NULL, d, NULL, mesh);
	Ivica *cSym = new Ivica(v1, f4, c, e, d, mesh);

	//f1
	Ivica *f = new Ivica(v4, f1, fSym, NULL, NULL, mesh);
	Ivica *aSym = new Ivica(v2, f1, a, f, NULL, mesh);
	Ivica *eSym = new Ivica(v1, f1, e, aSym, f, mesh);

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

	mesh->cvorovi.push_back(v1);
	mesh->cvorovi.push_back(v2);
	mesh->cvorovi.push_back(v3);
	mesh->cvorovi.push_back(v4);

	mesh->ivice.push_back(a);
	mesh->ivice.push_back(b);
	mesh->ivice.push_back(c);
	mesh->ivice.push_back(d);
	mesh->ivice.push_back(e);
	mesh->ivice.push_back(f);
	mesh->ivice.push_back(aSym);
	mesh->ivice.push_back(bSym);
	mesh->ivice.push_back(cSym);
	mesh->ivice.push_back(dSym);
	mesh->ivice.push_back(eSym);
	mesh->ivice.push_back(fSym);

	mesh->lica.push_back(f1);
	mesh->lica.push_back(f2);
	mesh->lica.push_back(f3);
	mesh->lica.push_back(f4);

	for (int i = 0; i < mesh->lica.size(); i++) {
		mesh->lica[i]->izracunajVektorNormale();
	}

	for (int i = 0; i < mesh->cvorovi.size(); i++) {
		mesh->cvorovi[i]->izracunajVektorNormale();
	}

	//Subdivizija

	int k = 0;
	while (k < brojSubdivizija) {
		k++;

		//zapamti podatke pre subdivizije
		vector<Ivica*> ivice = mesh->ivice;
		vector<Cvor*> cvorovi = mesh->cvorovi;
		vector<Lice*> lica = mesh->lica;

		//podeli ivice
		for (int i = 0; i < ivice.size(); i++) {
			if (!ivice[i]->podeljena) {
				ivice[i]->podeljena = true;
				ivice[i]->eSym->podeljena = true;
				ivice[i]->deli();
			}
		}

		//podesi koordinate novih cvorova
		for (int i = 0; i < mesh->noviCvorovi.size(); i++) {
			podesiKoordinateCvora(mesh->noviCvorovi[i]);
		}

		//isprazni vektor sa novim cvorovima
		mesh->noviCvorovi.erase(mesh->noviCvorovi.begin(), mesh->noviCvorovi.end());

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
		for (int i = 0; i < mesh->lica.size(); i++) {
			mesh->lica[i]->izracunajVektorNormale();
		}

		//-,,- cvorova
		for (int i = 0; i < mesh->cvorovi.size(); i++) {
			mesh->cvorovi[i]->izracunajVektorNormale();
		}

		//oznaci sve ivice kao nepodeljene
		for (int i = 0; i < mesh->ivice.size(); i++) {
			mesh->ivice[i]->podeljena = false;
		}
	}
}

void subdivizija(int brojIteracija) {
	int k = 0;

	while (k < brojIteracija) {
		k++;

		//zapamti podatke pre subdivizije
		vector<Ivica*> ivice = mesh->ivice;
		vector<Cvor*> cvorovi = mesh->cvorovi;
		vector<Lice*> lica = mesh->lica;

		//izracunaj sumu susednih cvorova pre subdivizije
		for (int i = 0; i < cvorovi.size(); i++) {
			cvorovi[i]->izracunajSumuSusednihCvorova();
		}

		//podeli ivice
		for (int i = 0; i < ivice.size(); i++) {
			if (!ivice[i]->podeljena) {
				ivice[i]->podeljena = true;
				if (ivice[i]->eSym != NULL) ivice[i]->eSym->podeljena = true;
				ivice[i]->deli();
			}
		}

		//podesi koordinate novih cvorova
		for (int i = 0; i < mesh->noviCvorovi.size(); i++) {
			podesiKoordinateCvora(mesh->noviCvorovi[i]);
		}

		//isprazni vektor sa novim cvorovima
		mesh->noviCvorovi.erase(mesh->noviCvorovi.begin(), mesh->noviCvorovi.end());

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
		for (int i = 0; i < mesh->lica.size(); i++) {
			mesh->lica[i]->izracunajVektorNormale();
		}

		//-,,- cvorova
		for (int i = 0; i < mesh->cvorovi.size(); i++) {
			mesh->cvorovi[i]->izracunajVektorNormale();
		}

		//oznaci sve ivice kao nepodeljene
		for (int i = 0; i < mesh->ivice.size(); i++) {
			mesh->ivice[i]->podeljena = false;
		}
	}
}


void update(int value) {

	if (rotiraj) rot = (rot + 1) % 360;

	if (rotirajSvetlo) rotacijaSvetla = (rotacijaSvetla + 2) % 360;

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glRotated(rotacijaSvetla, 1, 0, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0.0, 0.0, 150.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light1_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { 0.0, 0.0, -150.0, 1.0 };
	GLfloat spot_direction[] = { 0.0, 0.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.15);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 100.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	glLoadIdentity();

	glRotated(rot, 0, 1, 0);
	glRotated(30, 1, 0, 0);

	float temeA[3] = { -6.0, -6.0, 0.0 };
	float temeB[3] = { -2.0, 0.0 , 0.0 };
	float temeC[3] = { 2.0 , -6.0 , 0.0 };

	crtajMesh();

	glFlush();
}

void onMouseClick(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (rotiraj) rotiraj = false;
		else rotiraj = true;
	}

}

void keybordFunc(unsigned char key, int x, int y) {

	if (key == 's') {
		if (rotirajSvetlo) rotirajSvetlo = false;
		else rotirajSvetlo = true;
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

	//tetraedar(a, b, c, d);

	glutDisplayFunc(display);
	glutReshapeFunc(winReshape);
	glutTimerFunc(100, update, 0);
	glutMouseFunc(onMouseClick);
	glutKeyboardFunc(keybordFunc);
	myInit();
	subdivizija(1);
	//upisiMesh("testCvorovi.txt", "testIndeksi.txt");
	//upisiObj("objCvorovi.txt", "objIndeksi.txt");
	glEnable(GL_DEPTH_TEST);                                    // enable Hidden Surface Removal Algorithm
	glutMainLoop();
	return 0;
}