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
	this->plateau = new PlateauSextantBros(this->ecran, this->clavier, this->horloge);
}

void SextantBros::run() {
	ecran->effacerEcranV(NOIR);
	this->launch();

	// Introduction
	this->plateau->introduction();
	for (int i = 0; i < 2; i++) {
		ecran->effacerEcranV(NOIR);
		for (int x = 0; x < HAUTEUR; x++) {
			for (int y = 0; y < LARGEUR; y++) {
				this->plateau->tab[x][y]->paint(x, y);
			}
		}
	}
	this->clavier->getChar();

	// Lancement du niveau
	this->plateau->level();
	this->horloge->start("Horloge");
	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			this->plateau->tab[x][y]->paint(x, y);
		}
	}
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
	ecran->effacerEcranV(NOIR);
}

