#include"Cvor.h"
#include"Ivica.h"
#include"Lice.h"
#include<vector>
#include<math.h>

# define M_PI           3.14159265358979323846

//podeli ivice, apdejtuj cvorove, podeli lica, nadji normale

std::vector<Lice*> Cvor::svaLica(Cvor *c){

	Ivica *temp = c->e;
	std::vector<Lice*> ret;

	while (temp != c->e){

		ret.push_back(temp->l);
		temp = temp->preth->eSym;
	}
return ret;
}

void Cvor::azurirajCvorove(){

	int k = brojSusednihCvorova;

	float omega = 1.0 / k * (5.0 / 8.0 - pow((3.0 / 8.0 + 1.0 / 4.0 * cos(2.0 * M_PI) / k), 2));

	this->x = (1 - omega*k) *this->x + omega * sumax;
	this->y = (1 - omega*k) *this->y + omega * sumay;
	this->z = (1 - omega*k) *this->z + omega * sumaz;
}

void Cvor::izracunajSumuSusednihCvorova() {

	Ivica *i = this->e;
	int j = 0;
	do {
		j++;
		sumax += i->sled->v->x;
		sumay += i->sled->v->y;
		sumaz += i->sled->v->z;
		i = i->preth->eSym;
		brojSusednihCvorova++;
		if (j > 6) break;
	} while (i != this->e && i != NULL); //Probaj da napravis da i nikad ne bude null
}

void Cvor::izracunajVektorNormale() {

	Ivica *e = this->e;

	float sumax = 0.0;
	float sumay = 0.0;
	float sumaz = 0.0;

	int brLica = 0;
	int j = 0;
	do {
		if (e == NULL) break;
		j++;
		sumax += e->l->vektorNormale[0];
		sumay += e->l->vektorNormale[1];
		sumaz += e->l->vektorNormale[2];
		e = e->preth->eSym;
		brLica++;
		if (j > 6) break;
	} while (e != this->e && e != NULL);

	this->vektorNormale[0] = sumax / brLica;
	this->vektorNormale[1] = sumay / brLica;
	this->vektorNormale[2] = sumaz / brLica;

	//normalizacija

	float norma = sqrt(pow(vektorNormale[0], 2) + pow(vektorNormale[1], 2) + pow(vektorNormale[2], 2));

	vektorNormale[0] /= norma;
	vektorNormale[1] /= norma;
	vektorNormale[2] /= norma;
}