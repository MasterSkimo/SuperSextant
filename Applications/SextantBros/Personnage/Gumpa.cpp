/*
 * Gumpa.cpp
 *
 *  Created on: 24 oct. 2013
 *      Author: Gwenaël
 */

#include <Applications/SextantBros/Personnage/Gumpa.h>

Gumpa::Gumpa(){

}

Gumpa::Gumpa(int inf, int sup, int pos) {
	// TODO Auto-generated constructor stub
	borneInf = inf;
	borneSup = sup;
	position = pos;
	direction = 1;

}

void Gumpa::bouger() {
	// Gestion de la direction
	if (position <= borneInf || position >= borneSup)
		changerDirection();

	// Gestion du déplacement
	position += direction;

}


void Gumpa::changerDirection() {
	direction = direction *(-1);
}

void Gumpa::detruire(){
	this->Exit();
	//~Gumpa();
}
void Gumpa::run() {
	while(1)
		bouger();
}


