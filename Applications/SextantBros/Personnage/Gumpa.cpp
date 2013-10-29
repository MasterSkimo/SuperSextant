#include <Applications/SextantBros/Personnage/Gumpa.h>

Gumpa::Gumpa(int inf, int sup, int posX, PlateauSextantBros* tableau) {
	// TODO Auto-generated constructor stub
	borneInf = inf;
	borneSup = sup;
	positionX = posX;
	positionY = borneInf;
	direction = 1;
	isAlive = true;
	plateauBros = tableau;
}

void Gumpa::bouger() {
	// Gestion de la direction
	if (positionY <= borneInf || positionY >= borneSup)
		changerDirection();

	// Gestion du déplacement
	this->plateauBros->tabLevel[positionX][positionY].setCaseFond();
	positionY += direction;
	this->plateauBros->tabLevel[positionX][positionY].setCaseGumba();
	this->plateauBros->rafraichir();
}


void Gumpa::changerDirection() {
	direction = direction *(-1);
}

void Gumpa::detruire(){
	isAlive = false;
}
void Gumpa::run() {
	while(isAlive){
		bouger();
	}
}
