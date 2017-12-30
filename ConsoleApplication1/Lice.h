#pragma once
#include<vector>
#include"Mash.h"
#include"Ivica.h"
class Cvor;

class Lice {
public:
	Ivica *e;
	Mash *mash;
	float r, g, b;
	float *vektorNormale; //[0] - x , [1] - y , [2] - z
	Lice(Ivica *e = NULL, Mash *mash = NULL) {
		this->e = e;
		this->mash = mash;
		r = ((float)rand() / RAND_MAX);
		g = ((float)rand() / RAND_MAX);
		b = ((float)rand() / RAND_MAX);
		vektorNormale = new float[3];
		vektorNormale[0] = vektorNormale[1] = vektorNormale[2] = 0;
	}

	std::vector<Cvor*> sviCvorovi();

	void dodaj(Ivica *ivica) {
		mash->ivice.push_back(ivica);
	}

	void dodajLice(Lice *lice) {
		mash->lica.push_back(lice);
	}

	void deli();

	void izracunajVektorNormale();

	};