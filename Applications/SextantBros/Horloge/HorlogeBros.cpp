/*
 * HorlogeBros.cpp
 *
 *  Created on: 28 oct. 2013
 *      Author: Matthieu Gutierrez
 */

#include "HorlogeBros.h"

HorlogeBros::HorlogeBros() {

}

HorlogeBros::HorlogeBros(EcranV *e) {
	this->ecran = e;
	this->timer = new Timer();
	this->fin = false;
	this->temps = 300;

}

HorlogeBros::~HorlogeBros() {
	// TODO Auto-generated destructor stub
}

void HorlogeBros::run() {
	int t1 = this->timer->getSecondes();
	int t2 = this->timer->getSecondes();
	while (!fin) {
		while (t2 != (t1 + 1)) {
			t2 = this->timer->getSecondes();
		}
		t1 = t2;
		this->temps--;
		if (!fin) {
			this->ecran->setLigne(0);
			this->ecran->setColonne(52);
			this->ecran->afficherBase(temps, 10, BLANC);
		}
	}
}

int HorlogeBros::getTemps() {
	return this->temps;
}

void HorlogeBros::setTemps(int temps) {
	this->temps = temps;
}

void HorlogeBros::tempoGumba() {
	int t1 = this->timer->getDsecondes();
	int t2 = this->timer->getDsecondes();
	while (t2 < (t1 + 1)) {
		t2 = this->timer->getDsecondes();
	}
}

void HorlogeBros::wait(int sec) {
	int t1 = this->timer->getSecondes();
	int t2 = this->timer->getSecondes();
	while (t2 < (t1 + sec)) {
		t2 = this->timer->getSecondes();
	}
}

void HorlogeBros::setFin(bool fin) {
	this->fin = fin;
}
