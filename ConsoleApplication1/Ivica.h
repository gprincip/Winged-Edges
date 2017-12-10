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

		Cvor *c = new Cvor(this); //treba da bude od en
		Ivica *en = new Ivica(c, l, eSym, this, sled);
		Ivica *enSym = new Ivica(c, eSym->l, this, eSym, eSym->sled);

		c->e = en;

		this->sled = en;
		this->eSym = enSym;

		eSym->sled = enSym;
		eSym->eSym = en;

		podeljena = true;

		//Koordinate cvora
		c->x += this->v->x * (3 / 8);
		c->x += sled->v->x * (3 / 8);
		c->x += preth->v->x * (1 / 8);
		c->x += eSym->preth->v->x * (1 / 8);

		c->y += this->v->x * (3 / 8);
		c->y += sled->v->x * (3 / 8);
		c->y += preth->v->x * (1 / 8);
		c->y += eSym->preth->v->x * (1 / 8);

		c->z += this->v->x * (3 / 8);
		c->z += sled->v->x * (3 / 8);
		c->z += preth->v->x * (1 / 8);
		c->z += eSym->preth->v->x * (1 / 8);
		
		mash->cvorovi.push_back(c);
		mash->ivice.push_back(en);
		mash->ivice.push_back(enSym);

	}

};