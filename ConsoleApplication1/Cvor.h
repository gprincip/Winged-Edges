#pragma once
#include<vector>

class Lice;
class Ivica;

class Cvor{

public:
	Ivica *e;

	float x, y, z;

	float xpom, ypom, zpom;

	Cvor(Ivica *e = NULL){
		this->e = e;
	}

	Cvor(float x, float y, float z){
		this->x = xpom = x;
		this->y = ypom = y;
		this->z = zpom = z;
	}

	std::vector<Lice*> svaLica(Cvor *c);

	void azurirajCvorove();

};