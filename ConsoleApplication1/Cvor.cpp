#include"Cvor.h"
#include"Ivica.h"
#include"Lice.h"
#include<vector>
#include<math.h>

# define M_PI           3.14159265358979323846

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

	int k = brojSuseda;

	float omega = 1.0 / k * (5.0 / 8.0 - pow((3.0 / 8.0 + 1.0 / 4.0 * cos(2.0 * M_PI) / k), 2));

	this->x = (1 - omega*k) *this->x + omega * sumax;
	this->y = (1 - omega*k) *this->y + omega * sumay;
	this->z = (1 - omega*k) *this->z + omega * sumaz;
	
}

void Cvor::izracunajSumuSusednihCvorova() {

	Ivica *i = this->e;

	do {
		sumax += i->sled->v->x;
		sumay += i->sled->v->y;
		sumaz += i->sled->v->z;
		i = i->preth->eSym;
		brojSuseda++;
	} while (i != this->e);

	cout << brojSuseda << endl;

}