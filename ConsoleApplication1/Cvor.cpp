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

	Ivica *temp = this->e;
	std::vector<Cvor*> cvorovi;

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

	float k = cvorovi.size();
	float omega = 1.0 / k * (5.0 / 8.0 - pow((3.0 / 8.0 + 1.0 / 4.0 * cos(2.0 * M_PI) / k), 2));

	float beta = 3.0 / (8 * cvorovi.size());

	/*this->x = beta * (sumax)+(1 - cvorovi.size() * beta) * this->x;
	this->y = beta * (sumay)+(1 - cvorovi.size() * beta) * this->y;
	this->z = beta * (sumaz)+(1 - cvorovi.size() * beta) * this->z;*/

	this->x = (1 - omega*k) *this->x + omega * sumax;
	this->y = (1 - omega*k) *this->y + omega * sumay;
	this->z = (1 - omega*k) *this->z + omega * sumaz;
	
}