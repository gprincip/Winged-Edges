#pragma once

#include<vector>

class Cvor;
class Ivica;
class Lice;

class Mesh{
public:
	std::vector<Cvor*> cvorovi;
	std::vector<Cvor*> noviCvorovi;
	std::vector<Ivica*> ivice;
	std::vector<Lice*> lica;
};