/*
 * Gumpa.h
 *
 *  Created on: 24 oct. 2013
 *      Author: Gwenaël
 */

#ifndef GUMPA_H_
#define GUMPA_H_

#include <sextant/Activite/Threads.h>
#include "../Map/PlateauSextantBros.h"

class Gumpa : public Threads{
	PlateauSextantBros *plateauBros;

	int borneInf, borneSup, positionX, positionY, direction;
	bool isAlive;
public:
	Gumpa();
	Gumpa(int inf, int sup, int positionX, PlateauSextantBros *);

	void bouger();
	void changerDirection();
	void run();
	void detruire();
};

#endif /* GUMPA_H_ */
