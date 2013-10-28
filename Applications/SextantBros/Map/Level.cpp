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
//	for (int x = 0; x < 80; x++) {
//		for (int y = 0; y < 25; y++) {
//			this->tab[x][y].init(x, y);
//			this->tab[x][y].setEcran(this->ecran);
//		}
//	}
//	this->size = 80;
//
//	// S
//	this->tab[2][15].setCaseBord();
//	this->tab[3][15].setCaseBord();
//	this->tab[4][15].setCaseBord();
//	this->tab[6][15].setCaseBord();
//	this->tab[2][16].setCaseBord();
//	this->tab[4][16].setCaseBord();
//	this->tab[6][16].setCaseBord();
//	this->tab[2][17].setCaseBord();
//	this->tab[4][17].setCaseBord();
//	this->tab[5][17].setCaseBord();
//	this->tab[6][17].setCaseBord();
//
//	// U
//	this->tab[2][19].setCaseBord();
//	this->tab[3][19].setCaseBord();
//	this->tab[4][19].setCaseBord();
//	this->tab[5][19].setCaseBord();
//	this->tab[6][19].setCaseBord();
//	this->tab[6][20].setCaseBord();
//	this->tab[2][21].setCaseBord();
//	this->tab[3][21].setCaseBord();
//	this->tab[4][21].setCaseBord();
//	this->tab[5][21].setCaseBord();
//	this->tab[6][21].setCaseBord();
//
//	// P
//	this->tab[2][23].setCaseBord();
//	this->tab[3][23].setCaseBord();
//	this->tab[4][23].setCaseBord();
//	this->tab[5][23].setCaseBord();
//	this->tab[6][23].setCaseBord();
//	this->tab[2][24].setCaseBord();
//	this->tab[4][24].setCaseBord();
//	this->tab[2][25].setCaseBord();
//	this->tab[3][25].setCaseBord();
//	this->tab[4][25].setCaseBord();
//
//	// E
//	this->tab[2][27].setCaseBord();
//	this->tab[3][27].setCaseBord();
//	this->tab[4][27].setCaseBord();
//	this->tab[5][27].setCaseBord();
//	this->tab[6][27].setCaseBord();
//	this->tab[2][28].setCaseBord();
//	this->tab[4][28].setCaseBord();
//	this->tab[6][28].setCaseBord();
//	this->tab[2][29].setCaseBord();
//	this->tab[6][29].setCaseBord();
//
//	//R
//	this->tab[2][31].setCaseBord();
//	this->tab[3][31].setCaseBord();
//	this->tab[4][31].setCaseBord();
//	this->tab[5][31].setCaseBord();
//	this->tab[6][31].setCaseBord();
//	this->tab[2][32].setCaseBord();
//	this->tab[4][32].setCaseBord();
//	this->tab[5][32].setCaseBord();
//	this->tab[2][33].setCaseBord();
//	this->tab[3][33].setCaseBord();
//	this->tab[4][33].setCaseBord();
//	this->tab[6][33].setCaseBord();
//
//	// S
//	this->tab[2][40].setCaseBord();
//	this->tab[3][40].setCaseBord();
//	this->tab[4][40].setCaseBord();
//	this->tab[6][40].setCaseBord();
//	this->tab[2][41].setCaseBord();
//	this->tab[4][41].setCaseBord();
//	this->tab[6][41].setCaseBord();
//	this->tab[2][42].setCaseBord();
//	this->tab[4][42].setCaseBord();
//	this->tab[5][42].setCaseBord();
//	this->tab[6][42].setCaseBord();
//
//	// E
//	this->tab[2][44].setCaseBord();
//	this->tab[3][44].setCaseBord();
//	this->tab[4][44].setCaseBord();
//	this->tab[5][44].setCaseBord();
//	this->tab[6][44].setCaseBord();
//	this->tab[2][45].setCaseBord();
//	this->tab[4][45].setCaseBord();
//	this->tab[6][45].setCaseBord();
//	this->tab[2][46].setCaseBord();
//	this->tab[6][46].setCaseBord();
//
//	// X
//	this->tab[2][48].setCaseBord();
//	this->tab[6][48].setCaseBord();
//	this->tab[3][49].setCaseBord();
//	this->tab[4][49].setCaseBord();
//	this->tab[5][49].setCaseBord();
//	this->tab[2][50].setCaseBord();
//	this->tab[6][50].setCaseBord();
//
//	// T
//	this->tab[2][52].setCaseBord();
//	this->tab[2][53].setCaseBord();
//	this->tab[3][53].setCaseBord();
//	this->tab[4][53].setCaseBord();
//	this->tab[5][53].setCaseBord();
//	this->tab[6][53].setCaseBord();
//	this->tab[2][54].setCaseBord();
//
//	// A
//	this->tab[2][56].setCaseBord();
//	this->tab[3][56].setCaseBord();
//	this->tab[4][56].setCaseBord();
//	this->tab[5][56].setCaseBord();
//	this->tab[6][56].setCaseBord();
//	this->tab[2][57].setCaseBord();
//	this->tab[4][57].setCaseBord();
//	this->tab[2][58].setCaseBord();
//	this->tab[3][58].setCaseBord();
//	this->tab[4][58].setCaseBord();
//	this->tab[5][58].setCaseBord();
//	this->tab[6][58].setCaseBord();
//
//	// N
//	this->tab[2][60].setCaseBord();
//	this->tab[3][60].setCaseBord();
//	this->tab[4][60].setCaseBord();
//	this->tab[5][60].setCaseBord();
//	this->tab[6][60].setCaseBord();
//	this->tab[3][61].setCaseBord();
//	this->tab[4][62].setCaseBord();
//	this->tab[5][62].setCaseBord();
//	this->tab[2][63].setCaseBord();
//	this->tab[3][63].setCaseBord();
//	this->tab[4][63].setCaseBord();
//	this->tab[5][63].setCaseBord();
//	this->tab[6][63].setCaseBord();
//
//	// T
//	this->tab[2][65].setCaseBord();
//	this->tab[2][66].setCaseBord();
//	this->tab[3][66].setCaseBord();
//	this->tab[4][66].setCaseBord();
//	this->tab[5][66].setCaseBord();
//	this->tab[6][66].setCaseBord();
//	this->tab[2][67].setCaseBord();
//
//	// <-
//	this->tab[12][5].setCaseBord();
//	this->tab[11][6].setCaseBord();
//	this->tab[12][6].setCaseBord();
//	this->tab[13][6].setCaseBord();
//	this->tab[10][7].setCaseBord();
//	this->tab[12][7].setCaseBord();
//	this->tab[14][7].setCaseBord();
//	this->tab[12][8].setCaseBord();
//	this->tab[12][9].setCaseBord();
//	this->tab[12][10].setCaseBord();
//	this->tab[12][11].setCaseBord();
//
//	// Q
//	this->tab[11][14].setCaseBord();
//	this->tab[12][14].setCaseBord();
//	this->tab[13][14].setCaseBord();
//	this->tab[10][15].setCaseBord();
//	this->tab[14][15].setCaseBord();
//	this->tab[10][16].setCaseBord();
//	this->tab[14][16].setCaseBord();
//	this->tab[11][17].setCaseBord();
//	this->tab[12][17].setCaseBord();
//	this->tab[13][17].setCaseBord();
//	this->tab[14][17].setCaseBord();
//	this->tab[14][18].setCaseBord();
//
//	// ->
//	this->tab[19][5].setCaseBord();
//	this->tab[19][6].setCaseBord();
//	this->tab[19][7].setCaseBord();
//	this->tab[19][8].setCaseBord();
//	this->tab[19][9].setCaseBord();
//	this->tab[18][10].setCaseBord();
//	this->tab[19][10].setCaseBord();
//	this->tab[20][10].setCaseBord();
//	this->tab[17][9].setCaseBord();
//	this->tab[19][11].setCaseBord();
//	this->tab[21][9].setCaseBord();
//
//	// D
//	this->tab[17][14].setCaseBord();
//	this->tab[18][14].setCaseBord();
//	this->tab[19][14].setCaseBord();
//	this->tab[20][14].setCaseBord();
//	this->tab[21][14].setCaseBord();
//	this->tab[17][15].setCaseBord();
//	this->tab[21][15].setCaseBord();
//	this->tab[17][16].setCaseBord();
//	this->tab[21][16].setCaseBord();
//	this->tab[18][17].setCaseBord();
//	this->tab[19][17].setCaseBord();
//	this->tab[20][17].setCaseBord();
//
//	// / \
//	//  |
//	this->tab[10][70].setCaseBord();
//	this->tab[11][69].setCaseBord();
//	this->tab[9][71].setCaseBord();
//	this->tab[10][71].setCaseBord();
//	this->tab[11][71].setCaseBord();
//	this->tab[12][71].setCaseBord();
//	this->tab[13][71].setCaseBord();
//	this->tab[14][71].setCaseBord();
//	this->tab[10][72].setCaseBord();
//	this->tab[11][73].setCaseBord();
//
//	//Z
//	this->tab[16][68].setCaseBord();
//	this->tab[21][68].setCaseBord();
//	this->tab[16][69].setCaseBord();
//	this->tab[20][69].setCaseBord();
//	this->tab[21][69].setCaseBord();
//	this->tab[16][70].setCaseBord();
//	this->tab[19][70].setCaseBord();
//	this->tab[21][70].setCaseBord();
//	this->tab[16][71].setCaseBord();
//	this->tab[18][71].setCaseBord();
//	this->tab[21][71].setCaseBord();
//	this->tab[16][72].setCaseBord();
//	this->tab[17][72].setCaseBord();
//	this->tab[21][72].setCaseBord();
//	this->tab[16][73].setCaseBord();
//	this->tab[21][73].setCaseBord();
//
//	// S
//	this->tab[14][28].setCaseBord();
//	this->tab[15][28].setCaseBord();
//	this->tab[16][28].setCaseBord();
//	this->tab[18][28].setCaseBord();
//	this->tab[14][29].setCaseBord();
//	this->tab[16][29].setCaseBord();
//	this->tab[18][29].setCaseBord();
//	this->tab[14][30].setCaseBord();
//	this->tab[16][30].setCaseBord();
//	this->tab[18][30].setCaseBord();
//	this->tab[14][31].setCaseBord();
//	this->tab[16][31].setCaseBord();
//	this->tab[17][31].setCaseBord();
//	this->tab[18][31].setCaseBord();
//
//	// T
//	this->tab[14][34].setCaseBord();
//	this->tab[14][35].setCaseBord();
//	this->tab[14][36].setCaseBord();
//	this->tab[15][36].setCaseBord();
//	this->tab[16][36].setCaseBord();
//	this->tab[17][36].setCaseBord();
//	this->tab[18][36].setCaseBord();
//	this->tab[14][37].setCaseBord();
//	this->tab[14][38].setCaseBord();
//
//	// A
//	this->tab[14][41].setCaseBord();
//	this->tab[15][41].setCaseBord();
//	this->tab[16][41].setCaseBord();
//	this->tab[17][41].setCaseBord();
//	this->tab[18][41].setCaseBord();
//	this->tab[14][42].setCaseBord();
//	this->tab[16][42].setCaseBord();
//	this->tab[14][43].setCaseBord();
//	this->tab[16][43].setCaseBord();
//	this->tab[14][44].setCaseBord();
//	this->tab[15][44].setCaseBord();
//	this->tab[16][44].setCaseBord();
//	this->tab[17][44].setCaseBord();
//	this->tab[18][44].setCaseBord();
//
//	// R
//	this->tab[14][47].setCaseBord();
//	this->tab[15][47].setCaseBord();
//	this->tab[16][47].setCaseBord();
//	this->tab[17][47].setCaseBord();
//	this->tab[18][47].setCaseBord();
//	this->tab[14][48].setCaseBord();
//	this->tab[16][48].setCaseBord();
//	this->tab[14][49].setCaseBord();
//	this->tab[16][49].setCaseBord();
//	this->tab[17][49].setCaseBord();
//	this->tab[14][50].setCaseBord();
//	this->tab[15][50].setCaseBord();
//	this->tab[16][50].setCaseBord();
//	this->tab[18][50].setCaseBord();
//
//	// T
//	this->tab[14][53].setCaseBord();
//	this->tab[14][54].setCaseBord();
//	this->tab[14][55].setCaseBord();
//	this->tab[15][55].setCaseBord();
//	this->tab[16][55].setCaseBord();
//	this->tab[17][55].setCaseBord();
//	this->tab[18][55].setCaseBord();
//	this->tab[14][56].setCaseBord();
//	this->tab[14][57].setCaseBord();
}

void Level::level1() {

}
