#pragma once
#include"Ivica.h"

void Ivica::dodaj(Ivica *ivica) {
	mash->ivice.push_back(ivica);
}

void Ivica::dodajLice(Lice *lice) {
	mash->lica.push_back(lice);
}