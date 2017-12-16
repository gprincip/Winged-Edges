#pragma once
#include"Cvor.h"
#include"Lice.h"
#include"Ivica.h"

class Ivica {
public:
	Cvor *v;
	Lice *l;
	Ivica *eSym;
	Ivica *preth;
	Ivica *sled;
	Mash *mash;
	bool podeljena;

	Ivica(Cvor *v = NULL, Lice *l = NULL, Ivica *eSym = NULL, Ivica *preth = NULL, Ivica *sled = NULL, Mash *mash = NULL) {
		this->v = v;
		this->l = l;
		this->eSym = eSym;
		this->preth = preth;
		this->sled = sled;
		this->mash = mash;
		podeljena = false;
	}

	void dodaj(Ivica *ivica);

	void dodajLice(Lice *lice);

	void deli() {

		Cvor *c = new Cvor(NULL); //treba da bude od en
		Ivica *en = new Ivica(c, l, eSym, this, sled, mash);
		Ivica *enSym = new Ivica(c, eSym->l, this, eSym, eSym->sled, mash);

		c->e = en;

		this->sled = en;
		this->eSym = enSym;

		eSym->sled = enSym;
		eSym->eSym = en;

		en->sled->preth = en;
		enSym->sled->preth = enSym;

		podeljena = true;

		//Koordinate cvora
		//zapamti stare vrednosti
		c->xpom = c->x;
		c->ypom = c->y;
		c->zpom = c->z;

		c->x += this->v->x * (3.0 / 8.0);
		c->x += sled->sled->v->x * (3.0 / 8.0);
		c->x += preth->preth->v->x * (1.0 / 8.0);
		c->x += eSym->preth->preth->preth->v->x * (1.0 / 8.0);

		c->y += this->v->y * (3.0 / 8.0);
		c->y += sled->sled->v->y * (3.0 / 8.0);
		c->y += preth->preth->v->y * (1.0 / 8.0);
		c->y += eSym->preth->preth->preth->v->y * (1.0 / 8.0);

		c->z += this->v->z * (3.0 / 8.0);
		c->z += sled->sled->v->z * (3.0 / 8.0);
		c->z += preth->preth->v->z * (1.0 / 8.0);
		c->z += eSym->preth->preth->preth->v->z * (1.0 / 8.0);
		
		mash->cvorovi.push_back(c);
		mash->ivice.push_back(en);
		mash->ivice.push_back(enSym);

	}

};