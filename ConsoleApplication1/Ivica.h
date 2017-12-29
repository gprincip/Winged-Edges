#pragma once
#include"Cvor.h"
#include"Lice.h"
#include"Ivica.h"

using namespace std;
#include<iostream>

class Ivica {
public:
	Cvor *v;
	Lice *l;
	Ivica *eSym;
	Ivica *preth;
	Ivica *sled;
	Mash *mash;
	bool podeljena;

	float xpom, ypom, zpom;

	Ivica(Cvor *v = NULL, Lice *l = NULL, Ivica *eSym = NULL, Ivica *preth = NULL, Ivica *sled = NULL, Mash *mash = NULL) {
		this->v = v;
		this->l = l;
		this->eSym = eSym;
		this->preth = preth;
		this->sled = sled;
		this->mash = mash;
		podeljena = false;
		xpom = ypom = zpom = 0.0;
	}

	void dodaj(Ivica *ivica);

	void dodajLice(Lice *lice);

	void deli() {

		Cvor *c = new Cvor(NULL); //treba da bude od en
		xpom = sled->v->x;
		ypom = sled->v->y;
		zpom = sled->v->z;

		eSym->xpom = eSym->sled->v->x;
		eSym->ypom = eSym->sled->v->y;
		eSym->zpom = eSym->sled->v->z;

		Ivica *en = new Ivica(c, l, eSym, this, sled, mash);
		Ivica *enSym = new Ivica(c, eSym->l, this, eSym, eSym->sled, mash);

		c->e = en;

		this->sled = en;
		eSym->sled = enSym;
		this->eSym = enSym;
		eSym->eSym = en;

		en->sled->preth = en;
		enSym->sled->preth = enSym;

		//Koordinate cvora
		//zapamti stare vrednosti

		/*c->x += this->v->x * (3.0 / 8.0); cout << "x1: " << this->v->x << "   ";
		c->x += sled->sled->v->x * (3.0 / 8.0); cout << "x2: " << sled->sled->v->x << "   ";
		c->x += preth->v->x * (1.0 / 8.0); cout << "x3: " << preth->v->x << "   ";
		c->x += eSym->preth->preth->v->x * (1.0 / 8.0); cout << "x4: " << eSym->preth->preth->v->x << "   ";
		cout << endl;

		c->y += this->v->y * (3.0 / 8.0);
		c->y += sled->sled->v->y * (3.0 / 8.0);
		c->y += preth->v->y * (1.0 / 8.0);
		c->y += eSym->preth->preth->v->y * (1.0 / 8.0);

		c->z += this->v->z * (3.0 / 8.0);
		c->z += sled->sled->v->z * (3.0 / 8.0);
		c->z += preth->v->z * (1.0 / 8.0);
		c->z += eSym->preth->preth->v->z * (1.0 / 8.0);*/

		mash->noviCvorovi.push_back(c);

		mash->cvorovi.push_back(c);
		mash->ivice.push_back(en);
		mash->ivice.push_back(enSym);

	}


};