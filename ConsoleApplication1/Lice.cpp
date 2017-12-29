#pragma once
#include"Lice.h"
#include"Cvor.h"
#include"Ivica.h"
#include<vector>

std::vector<Cvor*> Lice::sviCvorovi(){

	std::vector<Cvor*> ret;

	Ivica *temp = this->e;
	
	do{
		ret.push_back(temp->v);
		temp = temp->sled;
	} while (temp != this->e);

return ret;
}


void Lice::deli() {
	int k = 0;
		while (true) {
			k++;
			Ivica *e1 = e;
			Ivica *e2 = e1->sled;
			Ivica *e3 = e2->sled;
			Ivica *e4 = e3->sled;

			if (e1 == e4) break;

			Cvor *v1 = e1->v;
			Cvor *v2 = e2->v;
			Cvor *v3 = e3->v;
			Cvor *v4 = e4->v;

			Ivica *en1 = new Ivica(v2, e->l, NULL /*treba da se stavi en2*/, e1, e4, mash);
			Ivica *en2 = new Ivica(v4, NULL/*novo lice*/, en1, e3, e2, mash);

			en1->eSym = en2;

			Lice *lnovo = new Lice(en2, mash);

			en2->l = lnovo;

			e2->preth = en2;
			e3->sled = en2;
			e3->l = lnovo;
			e2->l = lnovo;

			e1->sled = en1;

			e4->preth = en1;

			mash->ivice.push_back(en1);
			mash->ivice.push_back(en2);
			mash->lica.push_back(lnovo);

			this->e = en1;
			podeljeno = true;

		}
		cout << k << endl;
}