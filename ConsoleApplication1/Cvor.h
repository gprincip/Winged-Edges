#pragma once
#include<vector>

class Lice;
class Ivica;

class Cvor{

public:
	Ivica *e;

	float x, y, z;

	float sumax, sumay, sumaz;

	int brojSusednihCvorova;

	float *vektorNormale; //[0] - x , [1] - y , [2] - z

	Cvor(Ivica *e = NULL){
		this->e = e;
		vektorNormale = new float[3];
		vektorNormale[0] = vektorNormale[1] = vektorNormale[2] = 0;
	}

	Cvor(float x, float y, float z){
		sumax = sumay = sumaz = 0.0;
		this->x = x; 
		this->y = y;
		this->z = z;
		brojSusednihCvorova = 0;
		vektorNormale = new float[3];
		vektorNormale[0] = vektorNormale[1] = vektorNormale[2] = 0;
	}

	std::vector<Lice*> svaLica(Cvor *c);

	void azurirajCvorove();

	void izracunajSumuSusednihCvorova();

	void izracunajVektorNormale();
};