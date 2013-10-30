/*
 * SextantBros.h
 *
 *  Created on: 25 oct. 2013
 *      Author: Matthieu Gutierrez
 */

#ifndef SEXTANTBROS_H_
#define SEXTANTBROS_H_

#include <drivers/ClavierV.h>

#include "Map/PlateauSextantBros.h"
#include "Horloge/HorlogeBros.h"

#include "config.h"
#include <sextant/Activite/Threads.h>
#include "Personnage/Gumpa.h"

class SextantBros : public Threads {
	PlateauSextantBros *plateau;
	ClavierV *clavier;
	EcranV *ecran;
	HorlogeBros *horloge;
	Gumpa *tabGumpa[6];
	int scoreVie, scoreTemps, scoreDrapeau, scoreBonus;
public:
	SextantBros();
	SextantBros(EcranV *e, ClavierV *c, PlateauSextantBros *p );
	virtual ~SextantBros();
	void run();
	void launch();
	void calculPoint();
};

#endif /* SEXTANTBROS_H_ */
