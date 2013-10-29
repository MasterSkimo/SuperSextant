/*
 * Gumpa.h
 *
 *  Created on: 24 oct. 2013
 *      Author: Gwena�l
 */

#ifndef GUMPA_H_
#define GUMPA_H_

#include <sextant/Activite/Threads.h>
#include "../Map/PlateauSextantBros.h"
#include "../Horloge/HorlogeBros.h"

class Gumpa : public Threads{
	PlateauSextantBros *plateauBros;

	int borneInf, borneSup, positionX, positionY, direction;
	bool isAlive;
	HorlogeBros *horloge;
public:
	Gumpa();
	Gumpa(int inf, int sup, int positionX, PlateauSextantBros *, HorlogeBros *);

	void bouger();
	void changerDirection();
	void run();
	void detruire();
};

#endif /* GUMPA_H_ */
