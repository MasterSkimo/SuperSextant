/*
 * PlateauSextantBros.h
 *
 *  Created on: 24 oct. 2013
 *      Author: Matthieu Gutierrez
 */

#ifndef PLATEAUSEXTANTBROS_H_
#define PLATEAUSEXTANTBROS_H_

#include "Level.h"
#include "Case.h"
#include "../Personnage/Mario.h"
#include <drivers/ClavierV.h>

class PlateauSextantBros {
public :
	int numLvl;
	Mario mario;
	bool niveauTermine;
	EcranV *ecran;
	ClavierV *clavier;
	int score;
	int vie;
	int timer;
	Case* tab[HAUTEUR][LARGEUR];
	Case tabLevel[HAUTEUR][300];
	Case tabIntro[HAUTEUR][LARGEUR];
	void genererTube(int posX, int posY, int h);
	void genererBoite(int posX, int posY, bool champi);
	void genererEscalier(int posX, int posY, int h, bool reverse);
	void genererLigne(int posX, int posY, int t);
	void genererColonne(int posX, int posY, int t);

	// Constructeur
	PlateauSextantBros(EcranV *, ClavierV *);

	// Mario
	void initMario();
	void bougerMario(char fleche);
	void bougerDroite(bool saut);
	void bougerGauche(bool saut);
	void sauter();
	void tomber();
	void introduction();
	void level();
	void rafraichir();
};



#endif /* PLATEAUSEXTANTBROS_H_ */
