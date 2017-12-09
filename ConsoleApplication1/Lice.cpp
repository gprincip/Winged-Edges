#pragma once
#include"Lice.h"
#include"Cvor.h"
#include"Ivica.h"
#include<vector>

std::vector<Cvor*> Lice::sviCvorovi(Lice *l){

	std::vector<Cvor*> ret;

	Ivica *temp = l->e;
	
	while (temp != l->e){
		ret.push_back(temp->v);
		temp = temp->sled;
	}

return ret;
}


//ovo treba u cvor
void Lice::azurirajCvorove(){

	std::vector<Cvor*> susedniCvorovi = sviCvorovi(this); 

	float sumax = 0;
	float sumay = 0;
	float sumaz = 0;

	for (int i = 0; i < susedniCvorovi.size(); i++){

		sumax += susedniCvorovi[i]->x;
		sumay += susedniCvorovi[i]->y;
		sumaz += susedniCvorovi[i]->z;

	}

	float beta = 3.0 / (8 * susedniCvorovi.size());

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

			Ivica *en1 = new Ivica(v2, e->l, NULL /*treba da se stavi en2*/, e1, e4);
			Ivica *en2 = new Ivica(v4, NULL/*novo lice*/, en1, e3, e2);

			en1->eSym = en2;

			Lice *lnovo = new Lice(en2);

			en2->l = lnovo;

			e2->preth = en2;
			e3->sled = en2;
			e3->l = lnovo;
			e2->l = lnovo;

			e1->sled = en1;

			e4->preth = en1;
			this->e = en1;
		}
}