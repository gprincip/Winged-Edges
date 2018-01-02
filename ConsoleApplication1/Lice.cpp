#pragma once
#include"Lice.h"
#include"Cvor.h"
#include"Ivica.h"
#include<vector>

std::vector<Cvor*> Lice::sviCvorovi(){

	std::vector<Cvor*> ret;

	Ivica *temp = this->e;
	
	do{
		ret.push_back(temp->v);
		temp = temp->sled;
	} while (temp != this->e);

return ret;
}


void Lice::deli() {

		while (true) {

			Ivica *e1 = e;
			Ivica *e2 = e1->sled;
			Ivica *e3 = e2->sled;
			Ivica *e4 = e3->sled;

			if (e1 == e4) break;

			Cvor *v1 = e1->v;
			Cvor *v2 = e2->v;
			Cvor *v3 = e3->v;
			Cvor *v4 = e4->v;

			Ivica *en1 = new Ivica(v2, e->l, NULL, e1, e4, mash);
			Ivica *en2 = new Ivica(v4, NULL, en1, e3, e2, mash);

			en1->eSym = en2;

			Lice *lnovo = new Lice(en2, mash);

			en2->l = lnovo;

			e2->preth = en2;
			e3->sled = en2;
			e3->l = lnovo;
			e2->l = lnovo;

			e1->sled = en1;

			e4->preth = en1;

			mash->ivice.push_back(en1);
			mash->ivice.push_back(en2);
			mash->lica.push_back(lnovo);

			this->e = en1;
		}
}

void Lice::izracunajVektorNormale() {
	Ivica *i = this->e;

	float u[3] = { i->sled->v->x - i->v->x , i->sled->v->y - i->v->y , i->sled->v->z - i->v->z };
	float v[3] = { i->sled->sled->v->x - i->v->x , i->sled->sled->v->y - i->v->y , i->sled->sled->v->z - i->v->z };

	vektorNormale[0] = (u[1] * v[2]) - (u[2] * v[1]);
	vektorNormale[1] = (u[2] * v[0]) - (u[0] * v[2]);
	vektorNormale[2] = (u[0] * v[1]) - (u[1] * v[0]);

	//normalizacija

	float norma = sqrt(pow(vektorNormale[0], 2) + pow(vektorNormale[1], 2) + pow(vektorNormale[2], 2));

	vektorNormale[0] /= norma;
	vektorNormale[1] /= norma;
	vektorNormale[2] /= norma;

	//provera da li svaka ivica pamti lice sa leve strane

	Cvor *c1 = e->v;
	Cvor *c2 = e->sled->v;
	Cvor *c3 = e->sled->sled->v;

	float n[3]; //[0] - x, [1] - y, [2] - z
	n[0] = (c2->y - c1->y)*(c3->z - c1->z) - (c2->z - c1->z)*(c3->y - c1->y);
	n[1] = (c2->z - c1->z)*(c3->x - c1->x) - (c2->x - c1->x)*(c3->z - c1->z);
	n[2] = (c2->x - c1->x)*(c3->y - c1->y) - (c2->y - c1->y)*(c3->x - c1->x);

	float smer = n[0] * vektorNormale[0] + n[1] * vektorNormale[1] + n[2] * vektorNormale[2];

	if (smer < 0) {
		Ivica *e1 = e;
		Ivica *e2 = e1->sled;
		Ivica *e3 = e2->sled;

		e1->sled = e1->preth;
		e2->sled = e2->preth;
		e3->sled = e3->preth;

		e1->preth = e1->sled->sled;
		e2->preth = e2->sled->sled;
		e3->preth = e3->sled->sled;
	}


}