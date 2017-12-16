#include"Cvor.h"
#include"Ivica.h"
#include"Lice.h"
#include<vector>

std::vector<Lice*> Cvor::svaLica(Cvor *c){

	Ivica *temp = c->e;
	std::vector<Lice*> ret;

	while (temp != c->e){

		ret.push_back(temp->l);
		temp = temp->preth->eSym;

	}

return ret;

}
//podeli ivice, apdejtuj cvorove, podeli lica, nadji normale

void Cvor::azurirajCvorove(){

	Ivica *temp = this->e;
	std::vector<Cvor*> cvorovi;

	//beskonacna petlja
	do{
		cvorovi.push_back(temp->sled->sled->v);
		temp = temp->preth->eSym;
	} while (temp != this->e);

	float sumax = 0;
	float sumay = 0;
	float sumaz = 0;

	for (int i = 0; i < cvorovi.size(); i++){

		sumax += cvorovi[i]->x;
		sumay += cvorovi[i]->y;
		sumaz += cvorovi[i]->z;

	}

	float beta = 3.0 / (8 * cvorovi.size());

	this->x = beta * (sumax)+(1 - cvorovi.size() * beta) * this->x;
	this->y = beta * (sumay)+(1 - cvorovi.size() * beta) * this->y;
	this->z = beta * (sumaz)+(1 - cvorovi.size() * beta) * this->z;

}