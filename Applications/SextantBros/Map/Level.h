/*
 * Level.h
 *
 *  Created on: 24 oct. 2013
 *      Author: Matthieu Gutierrez
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "Case.h"

class Level {
	int size;
public:
	Case tab[80][25];
	Level();
	void generer(int numlvl);
	void introduction();
	void level1();
	int getSize();
};

#endif /* LEVEL_H_ */
