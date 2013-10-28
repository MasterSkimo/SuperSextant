/*
 * Mario.cpp
 *
 *  Created on: 24 oct. 2013
 *      Author: Gwenaël
 */

#include <Applications/SextantBros/Personnage/Mario.h>

Mario::Mario() {
	this->haut = 15;
	this->bas = 14;
	this->y = 40;
}

void Mario::setHaut(int x) {
	this->haut = x;
}

int Mario::getHaut(){
	return this->haut;
}

void Mario::setBas(int x){
	this->bas = x;
}

int Mario::getBas(){
	return this->bas;
}

void Mario::setY(int x){
	this->y = x;
}

int Mario::getY(){
	return this->y;
}


//void Mario::sauter() {
//	int i,j = 0;
//
//	while(i < 4){
//		if(this->plateauSextantBros->tab[x][y-1].etat == FOND){
//			sauterMonter();
//			i,j ++;
//		}
//		else
//			i = 5;
//	}
//	while (sauterDescendre());
//}
//
//void Mario::sauterMonter(){
//	this->plateauSextantBros->tab[x][y].setCaseFond();
//	this->x--;
//	this->plateauSextantBros->tab[x][y].setCaseMario();
//}
//
//bool Mario::sauterDescendre(){
//	switch (this->plateauSextantBros->tab[x][y+1].etat){
//	case FOND :
//		DescendreMario();
//		return true;
//	case TROU :
//		DescendreMario();
//		//this->plateauSextantBros->PerdreVie();
//		return false;
//	case GUMBA :
//		DescendreMario();
//		return false;
//	case PORTAIL :
//		return false;
//	case PIECE :
//		// FOnctionPIECE
//		DescendreMario();
//		return true;
//	default :
//		return false;
//	}
//}
//
//void Mario::DescendreMario(){
//	this->plateauSextantBros->tab[x][y].setCaseFond();
//	this->x++;
//	this->plateauSextantBros->tab[x][y].setCaseMario();
//}
//
//// Direction True = DROITE / False = Gauche
//void Mario::bouger(bool direction) {
//	if (direction){
//		this->plateauSextantBros->tab[x][y].setCaseFond();
//		this->y ++;
//		this->plateauSextantBros->tab[x][y].setCaseMario();
//
//	}
//	else {
//		this->plateauSextantBros->tab[x][y].setCaseFond();
//		this->y --;
//		this->plateauSextantBros->tab[x][y].setCaseMario();
//	}
//}
//
//void Mario::run() {
//
//}
//
