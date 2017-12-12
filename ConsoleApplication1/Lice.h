#pragma once
#include<vector>
#include"Mash.h"
#include"Ivica.h"
class Cvor;

class Lice {
public:
	Ivica *e;
	Mash *mash;
	bool podeljeno;

	Lice(Ivica *e = NULL, Mash *mash = NULL) {
		this->e = e;
		this->mash = mash;
		podeljeno = false;
	}

	std::vector<Cvor*> sviCvorovi();

	void dodaj(Ivica *ivica) {
		mash->ivice.push_back(ivica);
	}

	void dodajLice(Lice *lice) {
		mash->lica.push_back(lice);
	}

	void deli();
};