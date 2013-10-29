#include <Applications/SextantBros/Personnage/Gumpa.h>

Gumpa::Gumpa(int inf, int sup, int posX, PlateauSextantBros* tableau, HorlogeBros * h) {
	// TODO Auto-generated constructor stub
	borneInf = inf;
	borneSup = sup;
	positionX = posX;
	positionY = borneInf;
	direction = -1;
	isAlive = true;
	plateauBros = tableau;
	horloge = h;
}

void Gumpa::bouger() {
	// Gestion de la direction
	if (positionY < borneInf || positionY > borneSup)
		changerDirection();

	// Si Collision
	if (this->plateauBros->tabLevel[positionX][positionY + direction].getEtat() == MARIO) {
		this->plateauBros->tabLevel[positionX][positionY].setCaseFond();
		this->isAlive = false;
		this->plateauBros->perdreRetrecir();
	}
	//Fake Mario tuage de goomba
	else if (this->plateauBros->tabLevel[positionX-1][positionY].getEtat() == MARIO){
		this->plateauBros->tabLevel[positionX][positionY].setCaseFond();
		this->plateauBros->score+=500;
		this->isAlive = false;
	}
	// Sinon déplacement
	else {
		this->plateauBros->tabLevel[positionX][positionY].setCaseFond();
		positionY += direction;
		this->plateauBros->tabLevel[positionX][positionY].setCaseGumba();
	}
	this->plateauBros->rafraichir(false);
	horloge->tempoGumba();
}

void Gumpa::changerDirection() {
	direction = direction * (-1);
}

void Gumpa::detruire() {
	isAlive = false;
}
void Gumpa::run() {
	while (isAlive && !this->plateauBros->niveauTermine) {
		bouger();
	}
}
