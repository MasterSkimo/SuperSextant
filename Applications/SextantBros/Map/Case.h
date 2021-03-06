#ifndef CASE_H
#define CASE_H

/**
 * @file Case.h
 * @class Case
 * @brief Une case de la grille de jeu.
 */


#include <drivers/EcranV.h>
#include "../config.h"

class Case {
	/**
	 * écran pour l'affichage de la case
	 */
	EcranV* ecran;
	/**
	 * coordonnzes de la case dans la grille.
	 */
    int x, y ;
    /**
     * Etat de la case. Permet de savoir si la case est un trou, un mur, une raquette ou une balle.
     */

    int etatold;
    /**
     * Couleur du premier plan de la case.
     */
    Couleur couleurPr();
    /**
     * Couleur de l'arrière plan de la case.
     */
    Couleur couleurAr();
    /**
     * Caractère de la case.
     */
    char Caractere();

#define FOND 				0
#define BORD				10
#define TROU				20
#define GUMBA				30
#define MARIO				40
#define PORTAIL				50
#define TUBE				60
#define BOITECHAMPI			70
#define BOITEPIECE			80
#define PIECE				90
#define CHATEAU				100
#define DRAPEAU				110

public:
    int etat;
	//Setters
	void setEcran(EcranV* e);
	void setCaseFond();
	void setCaseBord();
    void setCaseTrou();
    void setCaseGumba();
    void setCaseMario();
    void setCasePortail();
    void setCaseTube();
    void setCaseBoiteChampi();
    void setCaseBoitePiece();
    void setCasePiece();
    void setCaseChateau();
    void setCaseDrapeau();
    //Getters
    EcranV* getEcran();
    int getEtat();

    /**
     * définit la case x,y comme une case vide.
     */
    void init(int x, int y);

    /**
     * Affiche la case.
     */
    void paint(int posX, int posY);


    void occupe();
    void libere();
    int Etat();
    int EtatOld();

};
#endif
