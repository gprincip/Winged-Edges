#pragma once
#include<vector>

class Lice;
class Ivica;

class Cvor{

public:
	Ivica *e;

	float x, y, z;

	float sumax, sumay, sumaz;

	int brojSuseda;

	Cvor(Ivica *e = NULL){
		this->e = e;
	}

	Cvor(float x, float y, float z){
		sumax = sumay = sumaz = 0.0;
		this->x = x; 
		this->y = y;
		this->z = z;
		brojSuseda = 0;
	}

	std::vector<Lice*> svaLica(Cvor *c);

	void azurirajCvorove();

	void izracunajSumuSusednihCvorova();
};