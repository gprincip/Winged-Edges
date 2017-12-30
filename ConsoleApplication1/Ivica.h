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
		eSym->sled = enSym;
		this->eSym = enSym;
		en->eSym->eSym = en;

		en->sled->preth = en;
		enSym->sled->preth = enSym;

		mash->noviCvorovi.push_back(c);

		mash->cvorovi.push_back(c);
		mash->ivice.push_back(en);
		mash->ivice.push_back(enSym);

	}


};