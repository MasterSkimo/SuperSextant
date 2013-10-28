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

bool Mario::getSuper(){
	return (this->haut == this->bas -1);
}

void Mario::grandir(){
	this->bas ++;
}

void Mario::retrecir(){
	this->bas --;
}
