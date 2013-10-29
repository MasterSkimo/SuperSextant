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
#include "../Horloge/HorlogeBros.h"
#include <drivers/ClavierV.h>

class PlateauSextantBros {
public :
	int numLvl;
	Mario mario;
	bool niveauTermine;
	EcranV *ecran;
	ClavierV *clavier;
	int score;
	int pieces;
	int vie;
	Case* tab[HAUTEUR][LARGEUR];
	Case tabLevel[HAUTEUR][300];
	Case tabIntro[HAUTEUR][LARGEUR];
	HorlogeBros *horloge;
	void genererTube(int posX, int posY, int h);
	void genererBoite(int posX, int posY, bool champi);
	void genererEscalier(int posX, int posY, int h, bool reverse);
	void genererLigne(int posX, int posY, int t, int type);
	void genererColonne(int posX, int posY, int t);

	// Constructeur
	PlateauSextantBros(EcranV *, ClavierV *, HorlogeBros *);

	// Bandeau Haut
	void initBandeau();

	// Mario
	void initMario();
	void bougerMario(char fleche);
	void bougerDroite(bool saut);
	void bougerGauche(bool saut);
	void sauter();
	void tomber();
	void introduction();
	void level();
	void gameOver();
	void marioAscii();
	void victory();
	void rafraichir(bool);
	void incrementerPiece();
	void incrementerPiece(int nbPieces);
	void perdreVie();
	void perdu();
	void casserBoite(Case *laCase);
};



#endif /* PLATEAUSEXTANTBROS_H_ */
