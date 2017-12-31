#pragma once
#include<vector>
#include"Mash.h"
#include"Ivica.h"
class Cvor;

class Lice {
public:
	Ivica *e;
	Mesh *mash;
	float r, g, b;
	float *vektorNormale; //[0] - x , [1] - y , [2] - z
	Lice(Ivica *e = NULL, Mesh *mesh = NULL) {
		this->e = e;
		this->mash = mesh;
		r = ((float)rand() / RAND_MAX);
		g = ((float)rand() / RAND_MAX);
		b = ((float)rand() / RAND_MAX);
		vektorNormale = new float[3];
		vektorNormale[0] = vektorNormale[1] = vektorNormale[2] = 0;
	}

	std::vector<Cvor*> sviCvorovi();

	void deli();

	void izracunajVektorNormale();
};