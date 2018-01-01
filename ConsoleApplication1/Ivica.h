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
	Mesh *mesh;
	bool podeljena;

	Ivica(Cvor *v = NULL, Lice *l = NULL, Ivica *eSym = NULL, Ivica *preth = NULL, Ivica *sled = NULL, Mesh *mesh = NULL) {
		this->v = v;
		this->l = l;
		this->eSym = eSym;
		this->preth = preth;
		this->sled = sled;
		this->mesh = mesh;
		podeljena = false;
	}

	void deli() {

		Cvor *c = new Cvor(NULL);

		if (eSym != NULL) { //ako nije granicna ivica

			Ivica *en = new Ivica(c, l, eSym, this, sled, mesh);
			Ivica *enSym = new Ivica(c, eSym->l, this, eSym, eSym->sled, mesh);

			c->e = en;

			this->sled = en;
			eSym->sled = enSym;
			this->eSym = enSym;
			en->eSym->eSym = en;

			en->sled->preth = en;
			enSym->sled->preth = enSym;

			mesh->noviCvorovi.push_back(c);

			mesh->cvorovi.push_back(c);
			mesh->ivice.push_back(en);
			mesh->ivice.push_back(enSym);

		}
		else { //ako je granicna

			Ivica *en = new Ivica(c, l, NULL, this, sled, mesh);

			c->e = en;
			this->sled = en;
			en->sled->preth = en;
			
			mesh->noviCvorovi.push_back(c);
			mesh->cvorovi.push_back(c);


		}
	}
};