#include "Case.h"

/**
 * @file Case.cpp
 * Implémentation des méthodes de la classes Case.
 */

/**
 * Initialisation d'un bloc dans la map aux coordonnées xx et yy. Le bloc par défaut est un bloc de fond.
 */
void Case::init(int xx, int yy) {
	x = xx;
	y = yy;
	setCaseFond();
}
;

int Case::getEtat() {
	return etat;
}
;

void Case::setEcran(EcranV* e) {
	ecran = e;
}

EcranV* Case::getEcran() {
	return ecran;
}


/*
 * Changement d'état des blocs
 */
void Case::setCaseFond() {
	etat = FOND;
};

void Case::setCaseBord() {
	etat = BORD;
};

void Case::setCaseTrou() {
	etat = TROU;
};

void Case::setCaseGumba() {
	etat = GUMBA;
};

void Case::setCaseMario() {
	etat = MARIO;
};

void Case::setCasePortail() {
	etat = PORTAIL;
};

void Case::setCaseTube() {
	etat = TUBE;
};

void Case::setCaseBoiteChampi() {
	etat = BOITECHAMPI;
};

void Case::setCaseBoitePiece() {
	etat = BOITEPIECE;
};

void Case::setCasePiece() {
	etat = PIECE;
};

void Case::setCaseChateau() {
    etat = CHATEAU;
};

void Case::setCaseDrapeau() {
	etat = DRAPEAU;

};

/**
 * Afficher le bloc
 */
void Case::paint(int posX, int posY) {
	ecran->afficherCaractere(posX,posY, couleurPr(), couleurAr(), Caractere());
}
;

/**
 * retourne la couleur de premier plan d'un bloc en fonction de son type
 */
Couleur Case::couleurPr() {
	switch (etat) {
		case FOND:
			return GRIS_LEGER;
		case BORD:
			return NOIR;
		case TROU:
			return GRIS_LEGER;
		case GUMBA:
			return MARRON;
		case MARIO:
			return ROUGE;
		case PORTAIL:
			return CYAN;
		case TUBE:
			return VERT;
		case BOITECHAMPI:
			return MARRON;
		case BOITEPIECE :
			return MARRON;
		case PIECE:
			return JAUNE;
		case CHATEAU:
			return ROUGE;
		case DRAPEAU:
			return VERT;
		default:
			return GRIS_LEGER;
	}
}

/**
 * retourne la couleur d'arrière plan d'un bloc en fonction de son type
 */
Couleur Case::couleurAr() {
	switch (etat) {
		case FOND:
			return GRIS_LEGER;
		case BORD:
			return MARRON;
		case TROU:
			return GRIS_LEGER;
		case GUMBA:
			return GRIS_LEGER;
		case MARIO:
			return ROUGE;
		case PORTAIL:
			return CYAN;
		case TUBE:
			return VERT;
		case BOITECHAMPI:
			return MARRON;
		case BOITEPIECE :
			return MARRON;
		case PIECE:
			return GRIS_LEGER;
		case CHATEAU:
			return ROUGE;
		case DRAPEAU:
			return VERT;
		default:
			return GRIS_LEGER;
	}
}

/**
 * retourne le caractère à afficher dans un bloc selon son type
 */
char Case::Caractere() {
	switch (etat) {
	case FOND:
		return ' ';
	case GUMBA:
		return 2;
	case PIECE:
		return '0';
	default:
		return 219; //bloc vide
	}
}

void Case::libere() {
	etat = etatold;
}
;

int Case::EtatOld() {
	return etatold;
}
;

int Case::Etat() {
	return etat;
}
;

