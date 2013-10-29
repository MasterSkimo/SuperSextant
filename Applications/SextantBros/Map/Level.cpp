/*
 * Level.cpp
 *
 *  Created on: 24 oct. 2013
 *      Author: Matthieu Gutierrez
 */

#include "Level.h"

Level::Level() {

}

void Level::generer(int numLvl) {
	switch (numLvl) {
	case 0:
		introduction();
		break;
	case 1:
		level1();
		break;
	default:
		break;
	}
}

int Level::getSize(){
	return this->size;
}

void Level::introduction() {

}
void Level::level1() {

}
