/*
 * SextantBros.cpp
 *
 *  Created on: 25 oct. 2013
 *      Author: Matthieu Gutierrez
 */

#include "SextantBros.h"

SextantBros::SextantBros() {
	// TODO Auto-generated constructor stub

}

SextantBros::SextantBros(EcranV *e, ClavierV *c, PlateauSextantBros *p) {
	this->ecran = e;
	this->clavier = c;
	this->plateau = p;
}

SextantBros::~SextantBros() {
	// TODO Auto-generated destructor stub
}

void SextantBros::launch() {
	this->horloge = new HorlogeBros(this->ecran);
	this->plateau = new PlateauSextantBros(this->ecran, this->clavier,
			this->horloge);
	this->tabGumpa[0] = new Gumpa(21, 29, 23, plateau, horloge);
	this->tabGumpa[1] = new Gumpa(50, 60, 23, plateau, horloge);
	this->tabGumpa[2] = new Gumpa(100, 110, 23, plateau, horloge);
	this->tabGumpa[3] = new Gumpa(140, 150, 23, plateau, horloge);
	this->tabGumpa[4] = new Gumpa(190, 200, 23, plateau, horloge);
	this->tabGumpa[5] = new Gumpa(230, 237, 23, plateau, horloge);
}

void SextantBros::run() {
	while (1) {
		ecran->effacerEcranV(NOIR);
		this->launch();

		// Introduction
		this->plateau->introduction();
		this->clavier->getChar();

		// Lancement du niveau
		this->plateau->level();
		this->horloge->start("Horloge");
		for (int x = 0; x < HAUTEUR; x++) {
			for (int y = 0; y < LARGEUR; y++) {
				this->plateau->tab[x][y]->paint(x, y);
			}
		}
		this->tabGumpa[0]->start("Gumpa0");
		this->tabGumpa[1]->start("Gumpa1");
		this->tabGumpa[2]->start("Gumpa2");
		this->tabGumpa[3]->start("Gumpa3");
		this->tabGumpa[4]->start("Gumpa4");
		this->tabGumpa[5]->start("Gumpa5");
		this->plateau->initBandeau();

		while (!this->plateau->niveauTermine) {
			char c = clavier->getChar();

			switch (c) {
			case 'q':
				this->plateau->bougerGauche(false);
				break;
			case 'd':
				this->plateau->bougerDroite(false);
				break;
			case 'z':
				this->plateau->sauter();
				break;
			}
		}
		this->horloge->setFin(true);
		if (this->plateau->niveauTermine && this->plateau->vie > 0) {
			this->plateau->victory();
		} else {
			this->plateau->perdu();
		}
		this->horloge->tempoGumba();
		char c = clavier->getChar();
	}
}

