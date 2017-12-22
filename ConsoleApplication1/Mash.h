#pragma once

#include<vector>

class Cvor;
class Ivica;
class Lice;

class Mash{
public:
	std::vector<Cvor*> cvorovi;
	std::vector<Cvor*> noviCvorovi;
	std::vector<Ivica*> ivice;
	std::vector<Lice*> lica;

	void obrisiPodatke() {

		cvorovi.erase(cvorovi.begin(), cvorovi.end());
		noviCvorovi.erase(noviCvorovi.begin(), noviCvorovi.end());
		ivice.erase(ivice.begin(), ivice.end());
		lica.erase(lica.begin(), lica.end());


	}

};