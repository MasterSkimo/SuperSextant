#include "PlateauSextantBros.h"

/**
 * Constructeur du plateau
 */
PlateauSextantBros::PlateauSextantBros(EcranV *e, ClavierV *c, HorlogeBros *h) {
	this->ecran = e;
	this->clavier = c;
	this->horloge = h;
	this->score = 0;
	this->pieces = 0;
	this->vie = 3;
	this->niveauTermine = false;
	this->numLvl = 0;
	this->mario.setBas(23);
	this->mario.setHaut(23);
	this->mario.setY(5);
}

/**
 * appelle la bonne fonction de déplacement selon la touche pressée
 */
void PlateauSextantBros::bougerMario(char fleche) {

	switch (fleche) {
	case 'q':
		bougerDroite(false);
		break;
	case 'd':
		bougerGauche(false);
		break;
	case 'z':
		sauter();
		break;
	}
}

/**
 * Déplacement à droite de Mario
 */
void PlateauSextantBros::bougerDroite(bool saut) {

	//Gestion de la fin du niveau (type de bloc CHATEAU ou DRAPEAU capté sur ou sous Mario)
	int etatHaut =
			this->tabLevel[this->mario.getHaut()][this->mario.getY() + 1].getEtat();
	int etatBas =
			this->tabLevel[this->mario.getBas()][this->mario.getY() + 1].getEtat();

	if (etatHaut == DRAPEAU || etatHaut == CHATEAU || etatBas == DRAPEAU
			|| etatBas == CHATEAU) {
		niveauTermine = true;
		return;
	}

	//sinon, le déplacement est autorisé si on n'entre pas en collision avec le bloc de droite (ie. si le bloc en question est de type FOND ou PIECE)
	if ((etatHaut == FOND || etatHaut == PIECE)
			&& (etatBas == FOND || etatBas == PIECE)) {

		// Incrémentation nb pièces si ramassage d'une pièce
		if (etatHaut == PIECE)
			this->incrementerPiece();
		if (etatBas == PIECE)
			this->incrementerPiece();

		// On réinitialise les blocs que Mario couvrait
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseFond();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseFond();

		// On change les blocs ou Mario va avec le type Mario
		this->mario.setY(this->mario.getY() + 1);
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();

		//on rafraichit l'affichage
		this->rafraichir(true);
	}
	if (!saut) {
		this->tomber();
	}
}

/**
 * Déplacement à gauche de Mario
 */
void PlateauSextantBros::bougerGauche(bool saut) {

	//Gestion de la fin du niveau (type de bloc CHATEAU ou DRAPEAU capté sur ou sous Mario)
	int etatHaut =
			this->tabLevel[this->mario.getHaut()][this->mario.getY() - 1].getEtat();
	int etatBas =
			this->tabLevel[this->mario.getBas()][this->mario.getY() - 1].getEtat();

	if (etatHaut == DRAPEAU || etatHaut == CHATEAU || etatBas == DRAPEAU
			|| etatBas == CHATEAU) {
		niveauTermine = true;
		return;
	}

	//sinon, le déplacement est autorisé si on n'entre pas en collision avec le bloc de droite (ie. si le bloc en question est de type FOND ou PIECE)
	if ((etatHaut == FOND || etatHaut == PIECE)
			&& (etatBas == FOND || etatBas == PIECE)) {

		// Incrémentation nb pièces si ramassage d'une pièce
		if (etatHaut == PIECE)
			this->incrementerPiece();
		if (etatBas == PIECE)
			this->incrementerPiece();

		// On réinitialise les blocs que Mario couvrait
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseFond();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseFond();

		// On change les blocs ou Mario va avec le type Mario
		this->mario.setY(this->mario.getY() - 1);
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();

		//on rafraichit l'affichage
		this->rafraichir(true);
	}
	if (!saut) {
		this->tomber();
	}
}

/**
 * Gestion du saut de Mario (4 cases)
 */
void PlateauSextantBros::sauter() {
	//hauteur mario
	int i = 0;

	//Gestion fin de niveau
	int etatCaseBas = this->tabLevel[this->mario.getBas() + 1][this->mario.getY()].getEtat();

	if (etatCaseBas == DRAPEAU || etatCaseBas == CHATEAU) {
		niveauTermine = true;
		return;
	}

	//Monter
	if (etatCaseBas != FOND && etatCaseBas != PIECE && etatCaseBas != TROU) {
		while (i < 4) {
			Case* CaseHaut = &(this->tabLevel[this->mario.getHaut() - 1][this->mario.getY()]);

			if (CaseHaut->getEtat() == FOND || CaseHaut->getEtat() == PIECE) {
				if (CaseHaut->getEtat() == PIECE)
					this->incrementerPiece();
				//Efface Mario de son ancienne position
				this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseFond();
				this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseFond();
				//incrémente les positions de mario
				this->mario.setHaut(this->mario.getHaut() - 1);
				this->mario.setBas(this->mario.getBas() - 1);
				//modifie les blocs a la nouvelle position du Mario avec le bon type
				this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();
				this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();
				//rafraichissement de l'affichage
				this->rafraichir(true);

				//Gestion du déplacement G/D pendant le saut
				char c = clavier->getChar();

				switch (c) {
				case 'q':
					this->bougerGauche(true);
					break;
				case 'd':
					this->bougerDroite(true);
					break;

				}
			} else {
				//on entre en collision avec un bloc
				i = 5;
				if (CaseHaut->getEtat() == BOITEPIECE
						|| CaseHaut->getEtat() == BOITECHAMPI)
					casserBoite(CaseHaut);
			}
			i++;
		}
	}

	//Descendre
	this->tomber();

}

/**
 * Modifie l'affichage des blocs cassables (blocs de type BOITEPIECE ou BOITECHAMPI)
 */
void PlateauSextantBros::casserBoite(Case *laCase) {
	//BOITEPIECE -> incrémente le nb de pièces par 10
	if (laCase->getEtat() == BOITEPIECE) {
		this->incrementerPiece(10);
	}

	//BOITECHAMPI -> mario grandit
	else if (laCase->getEtat() == BOITECHAMPI && !this->mario.getSuper()) {
		this->mario.grandir();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();
	}
	else {
		this->score+= 500;
		this->initBandeau();
	}

	//Modification type de blocs
	laCase->setCaseBord();
	if (this->tabLevel[this->mario.getHaut() - 1][this->mario.getY() - 1].getEtat() == BOITEPIECE
	|| this->tabLevel[this->mario.getHaut() - 1][this->mario.getY() - 1].getEtat() == BOITECHAMPI)
		this->tabLevel[this->mario.getHaut() - 1][this->mario.getY() - 1].setCaseBord();
	else
		this->tabLevel[this->mario.getHaut() - 1][this->mario.getY() + 1].setCaseBord();

	//rafraichissement de l'affichage
	this->rafraichir(true);
}

/**
 * Gestion de la chute de Mario (lors d'un saut ou absence de sol)
 */
void PlateauSextantBros::tomber() {
	int etatCaseBas = this->tabLevel[this->mario.getBas() + 1][this->mario.getY()].getEtat();

	//fin de niveau
	if (etatCaseBas == DRAPEAU || etatCaseBas == CHATEAU) {
		niveauTermine = true;
		return;
	}

	switch (this->tabLevel[this->mario.getBas() + 1][this->mario.getY()].getEtat()) {
		case PIECE:
			//bloc PIECE -> incrémente le nb de pièces
			this->incrementerPiece();
		case FOND:
			//bloc FOND -> Mario descend d'un bloc
			this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseFond();
			this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseFond();
			this->mario.setHaut(this->mario.getHaut() + 1);
			this->mario.setBas(this->mario.getBas() + 1);
			this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();
			this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();
			this->rafraichir(true);

			break;

		case TROU:
			//Bord de l'écran en bas == perte d'une vie de mario puis retour au début du niveau
			this->perdreVie();
			break;
		default:
			break;

	}
}

/**
 * Affichage de la page d'intro du jeu (nom + commandes sont affichés)
 */
void PlateauSextantBros::introduction() {
	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			tabIntro[x][y].init(x, y);
			this->tabIntro[x][y].setEcran(this->ecran);
		}
	}

	// S
	this->tabIntro[2][15].setCaseBord();
	this->tabIntro[3][15].setCaseBord();
	this->tabIntro[4][15].setCaseBord();
	this->tabIntro[6][15].setCaseBord();
	this->tabIntro[2][16].setCaseBord();
	this->tabIntro[4][16].setCaseBord();
	this->tabIntro[6][16].setCaseBord();
	this->tabIntro[2][17].setCaseBord();
	this->tabIntro[4][17].setCaseBord();
	this->tabIntro[5][17].setCaseBord();
	this->tabIntro[6][17].setCaseBord();

	// U
	this->tabIntro[2][19].setCaseBord();
	this->tabIntro[3][19].setCaseBord();
	this->tabIntro[4][19].setCaseBord();
	this->tabIntro[5][19].setCaseBord();
	this->tabIntro[6][19].setCaseBord();
	this->tabIntro[6][20].setCaseBord();
	this->tabIntro[2][21].setCaseBord();
	this->tabIntro[3][21].setCaseBord();
	this->tabIntro[4][21].setCaseBord();
	this->tabIntro[5][21].setCaseBord();
	this->tabIntro[6][21].setCaseBord();

	// P
	this->tabIntro[2][23].setCaseBord();
	this->tabIntro[3][23].setCaseBord();
	this->tabIntro[4][23].setCaseBord();
	this->tabIntro[5][23].setCaseBord();
	this->tabIntro[6][23].setCaseBord();
	this->tabIntro[2][24].setCaseBord();
	this->tabIntro[4][24].setCaseBord();
	this->tabIntro[2][25].setCaseBord();
	this->tabIntro[3][25].setCaseBord();
	this->tabIntro[4][25].setCaseBord();

	// E
	this->tabIntro[2][27].setCaseBord();
	this->tabIntro[3][27].setCaseBord();
	this->tabIntro[4][27].setCaseBord();
	this->tabIntro[5][27].setCaseBord();
	this->tabIntro[6][27].setCaseBord();
	this->tabIntro[2][28].setCaseBord();
	this->tabIntro[4][28].setCaseBord();
	this->tabIntro[6][28].setCaseBord();
	this->tabIntro[2][29].setCaseBord();
	this->tabIntro[6][29].setCaseBord();

	//R
	this->tabIntro[2][31].setCaseBord();
	this->tabIntro[3][31].setCaseBord();
	this->tabIntro[4][31].setCaseBord();
	this->tabIntro[5][31].setCaseBord();
	this->tabIntro[6][31].setCaseBord();
	this->tabIntro[2][32].setCaseBord();
	this->tabIntro[4][32].setCaseBord();
	this->tabIntro[5][32].setCaseBord();
	this->tabIntro[2][33].setCaseBord();
	this->tabIntro[3][33].setCaseBord();
	this->tabIntro[4][33].setCaseBord();
	this->tabIntro[6][33].setCaseBord();

	// S
	this->tabIntro[2][40].setCaseBord();
	this->tabIntro[3][40].setCaseBord();
	this->tabIntro[4][40].setCaseBord();
	this->tabIntro[6][40].setCaseBord();
	this->tabIntro[2][41].setCaseBord();
	this->tabIntro[4][41].setCaseBord();
	this->tabIntro[6][41].setCaseBord();
	this->tabIntro[2][42].setCaseBord();
	this->tabIntro[4][42].setCaseBord();
	this->tabIntro[5][42].setCaseBord();
	this->tabIntro[6][42].setCaseBord();

	// E
	this->tabIntro[2][44].setCaseBord();
	this->tabIntro[3][44].setCaseBord();
	this->tabIntro[4][44].setCaseBord();
	this->tabIntro[5][44].setCaseBord();
	this->tabIntro[6][44].setCaseBord();
	this->tabIntro[2][45].setCaseBord();
	this->tabIntro[4][45].setCaseBord();
	this->tabIntro[6][45].setCaseBord();
	this->tabIntro[2][46].setCaseBord();
	this->tabIntro[6][46].setCaseBord();

	// X
	this->tabIntro[2][48].setCaseBord();
	this->tabIntro[6][48].setCaseBord();
	this->tabIntro[3][49].setCaseBord();
	this->tabIntro[4][49].setCaseBord();
	this->tabIntro[5][49].setCaseBord();
	this->tabIntro[2][50].setCaseBord();
	this->tabIntro[6][50].setCaseBord();

	// T
	this->tabIntro[2][52].setCaseBord();
	this->tabIntro[2][53].setCaseBord();
	this->tabIntro[3][53].setCaseBord();
	this->tabIntro[4][53].setCaseBord();
	this->tabIntro[5][53].setCaseBord();
	this->tabIntro[6][53].setCaseBord();
	this->tabIntro[2][54].setCaseBord();

	// A
	this->tabIntro[2][56].setCaseBord();
	this->tabIntro[3][56].setCaseBord();
	this->tabIntro[4][56].setCaseBord();
	this->tabIntro[5][56].setCaseBord();
	this->tabIntro[6][56].setCaseBord();
	this->tabIntro[2][57].setCaseBord();
	this->tabIntro[4][57].setCaseBord();
	this->tabIntro[2][58].setCaseBord();
	this->tabIntro[3][58].setCaseBord();
	this->tabIntro[4][58].setCaseBord();
	this->tabIntro[5][58].setCaseBord();
	this->tabIntro[6][58].setCaseBord();

	// N
	this->tabIntro[2][60].setCaseBord();
	this->tabIntro[3][60].setCaseBord();
	this->tabIntro[4][60].setCaseBord();
	this->tabIntro[5][60].setCaseBord();
	this->tabIntro[6][60].setCaseBord();
	this->tabIntro[3][61].setCaseBord();
	this->tabIntro[4][62].setCaseBord();
	this->tabIntro[5][62].setCaseBord();
	this->tabIntro[2][63].setCaseBord();
	this->tabIntro[3][63].setCaseBord();
	this->tabIntro[4][63].setCaseBord();
	this->tabIntro[5][63].setCaseBord();
	this->tabIntro[6][63].setCaseBord();

	// T
	this->tabIntro[2][65].setCaseBord();
	this->tabIntro[2][66].setCaseBord();
	this->tabIntro[3][66].setCaseBord();
	this->tabIntro[4][66].setCaseBord();
	this->tabIntro[5][66].setCaseBord();
	this->tabIntro[6][66].setCaseBord();
	this->tabIntro[2][67].setCaseBord();

	// <-
	this->tabIntro[12][5].setCaseBord();
	this->tabIntro[11][6].setCaseBord();
	this->tabIntro[12][6].setCaseBord();
	this->tabIntro[13][6].setCaseBord();
	this->tabIntro[10][7].setCaseBord();
	this->tabIntro[12][7].setCaseBord();
	this->tabIntro[14][7].setCaseBord();
	this->tabIntro[12][8].setCaseBord();
	this->tabIntro[12][9].setCaseBord();
	this->tabIntro[12][10].setCaseBord();
	this->tabIntro[12][11].setCaseBord();

	// Q
	this->tabIntro[11][14].setCaseBord();
	this->tabIntro[12][14].setCaseBord();
	this->tabIntro[13][14].setCaseBord();
	this->tabIntro[10][15].setCaseBord();
	this->tabIntro[14][15].setCaseBord();
	this->tabIntro[10][16].setCaseBord();
	this->tabIntro[14][16].setCaseBord();
	this->tabIntro[11][17].setCaseBord();
	this->tabIntro[12][17].setCaseBord();
	this->tabIntro[13][17].setCaseBord();
	this->tabIntro[14][17].setCaseBord();
	this->tabIntro[14][18].setCaseBord();

	// ->
	this->tabIntro[19][5].setCaseBord();
	this->tabIntro[19][6].setCaseBord();
	this->tabIntro[19][7].setCaseBord();
	this->tabIntro[19][8].setCaseBord();
	this->tabIntro[19][9].setCaseBord();
	this->tabIntro[18][10].setCaseBord();
	this->tabIntro[19][10].setCaseBord();
	this->tabIntro[20][10].setCaseBord();
	this->tabIntro[17][9].setCaseBord();
	this->tabIntro[19][11].setCaseBord();
	this->tabIntro[21][9].setCaseBord();

	// D
	this->tabIntro[17][14].setCaseBord();
	this->tabIntro[18][14].setCaseBord();
	this->tabIntro[19][14].setCaseBord();
	this->tabIntro[20][14].setCaseBord();
	this->tabIntro[21][14].setCaseBord();
	this->tabIntro[17][15].setCaseBord();
	this->tabIntro[21][15].setCaseBord();
	this->tabIntro[17][16].setCaseBord();
	this->tabIntro[21][16].setCaseBord();
	this->tabIntro[18][17].setCaseBord();
	this->tabIntro[19][17].setCaseBord();
	this->tabIntro[20][17].setCaseBord();

	// / \
	//  |
	this->tabIntro[10][70].setCaseBord();
	this->tabIntro[11][69].setCaseBord();
	this->tabIntro[9][71].setCaseBord();
	this->tabIntro[10][71].setCaseBord();
	this->tabIntro[11][71].setCaseBord();
	this->tabIntro[12][71].setCaseBord();
	this->tabIntro[13][71].setCaseBord();
	this->tabIntro[14][71].setCaseBord();
	this->tabIntro[10][72].setCaseBord();
	this->tabIntro[11][73].setCaseBord();

	//Z
	this->tabIntro[16][68].setCaseBord();
	this->tabIntro[21][68].setCaseBord();
	this->tabIntro[16][69].setCaseBord();
	this->tabIntro[20][69].setCaseBord();
	this->tabIntro[21][69].setCaseBord();
	this->tabIntro[16][70].setCaseBord();
	this->tabIntro[19][70].setCaseBord();
	this->tabIntro[21][70].setCaseBord();
	this->tabIntro[16][71].setCaseBord();
	this->tabIntro[18][71].setCaseBord();
	this->tabIntro[21][71].setCaseBord();
	this->tabIntro[16][72].setCaseBord();
	this->tabIntro[17][72].setCaseBord();
	this->tabIntro[21][72].setCaseBord();
	this->tabIntro[16][73].setCaseBord();
	this->tabIntro[21][73].setCaseBord();

	// S
	this->tabIntro[14][28].setCaseBord();
	this->tabIntro[15][28].setCaseBord();
	this->tabIntro[16][28].setCaseBord();
	this->tabIntro[18][28].setCaseBord();
	this->tabIntro[14][29].setCaseBord();
	this->tabIntro[16][29].setCaseBord();
	this->tabIntro[18][29].setCaseBord();
	this->tabIntro[14][30].setCaseBord();
	this->tabIntro[16][30].setCaseBord();
	this->tabIntro[18][30].setCaseBord();
	this->tabIntro[14][31].setCaseBord();
	this->tabIntro[16][31].setCaseBord();
	this->tabIntro[17][31].setCaseBord();
	this->tabIntro[18][31].setCaseBord();

	// T
	this->tabIntro[14][34].setCaseBord();
	this->tabIntro[14][35].setCaseBord();
	this->tabIntro[14][36].setCaseBord();
	this->tabIntro[15][36].setCaseBord();
	this->tabIntro[16][36].setCaseBord();
	this->tabIntro[17][36].setCaseBord();
	this->tabIntro[18][36].setCaseBord();
	this->tabIntro[14][37].setCaseBord();
	this->tabIntro[14][38].setCaseBord();

	// A
	this->tabIntro[14][41].setCaseBord();
	this->tabIntro[15][41].setCaseBord();
	this->tabIntro[16][41].setCaseBord();
	this->tabIntro[17][41].setCaseBord();
	this->tabIntro[18][41].setCaseBord();
	this->tabIntro[14][42].setCaseBord();
	this->tabIntro[16][42].setCaseBord();
	this->tabIntro[14][43].setCaseBord();
	this->tabIntro[16][43].setCaseBord();
	this->tabIntro[14][44].setCaseBord();
	this->tabIntro[15][44].setCaseBord();
	this->tabIntro[16][44].setCaseBord();
	this->tabIntro[17][44].setCaseBord();
	this->tabIntro[18][44].setCaseBord();

	// R
	this->tabIntro[14][47].setCaseBord();
	this->tabIntro[15][47].setCaseBord();
	this->tabIntro[16][47].setCaseBord();
	this->tabIntro[17][47].setCaseBord();
	this->tabIntro[18][47].setCaseBord();
	this->tabIntro[14][48].setCaseBord();
	this->tabIntro[16][48].setCaseBord();
	this->tabIntro[14][49].setCaseBord();
	this->tabIntro[16][49].setCaseBord();
	this->tabIntro[17][49].setCaseBord();
	this->tabIntro[14][50].setCaseBord();
	this->tabIntro[15][50].setCaseBord();
	this->tabIntro[16][50].setCaseBord();
	this->tabIntro[18][50].setCaseBord();

	// T
	this->tabIntro[14][53].setCaseBord();
	this->tabIntro[14][54].setCaseBord();
	this->tabIntro[14][55].setCaseBord();
	this->tabIntro[15][55].setCaseBord();
	this->tabIntro[16][55].setCaseBord();
	this->tabIntro[17][55].setCaseBord();
	this->tabIntro[18][55].setCaseBord();
	this->tabIntro[14][56].setCaseBord();
	this->tabIntro[14][57].setCaseBord();

	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			this->tab[x][y] = &(this->tabIntro[x][y]);
			this->tab[x][y]->paint(x, y);
		}
	}
}

/**
 * Initialisation du niveau = placement des différents blocs et Gumpa
 */
void PlateauSextantBros::level() {
	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < 300; y++) {
			this->tabLevel[x][y].init(x, y);
			this->tabLevel[x][y].setEcran(this->ecran);
		}
	}

	// Sol
	int x = 24;
	for (int y = 0; y < 300; y++) {
		this->tabLevel[x][y].setCaseBord();
	}

	/* TUBES */
	// 1
	this->genererTube(0, 23, 7);
	//2
	this->genererTube(30, 23, 2);
	//3
	this->genererTube(36, 23, 3);
	//4
	this->genererTube(42, 23, 4);
	//5
	this->genererTube(125, 23, 3);
	//6
	this->genererTube(131, 23, 2);
	//7
	this->genererTube(136, 23, 4);
	//8
	this->genererTube(211, 23, 9);
	//9
	this->genererTube(216, 23, 7);
	//10
	this->genererTube(221, 23, 5);
	//11
	this->genererTube(226, 23, 3);
	//12
	this->genererTube(244, 23, 3);
	//13
	this->genererTube(249, 23, 5);
	//14
	this->genererTube(254, 23, 7);

	/* Boite  */
	//1
	this->genererBoite(12, 20, true);
	//2
	this->genererBoite(18, 20, false);
	//3
	this->genererBoite(52, 11, false);
	//4
	this->genererBoite(108, 12, false);
	//5
	this->genererBoite(109, 21, true);
	//6
	this->genererBoite(113, 21, false);
	//7
	this->genererBoite(117, 21, false);
	//8
	this->genererBoite(174, 10, true);

	// Escalier
	this->genererEscalier(77, 23, 6, false);

	this->genererEscalier(86, 23, 6, true);

	this->genererEscalier(202, 23, 7, false);

	this->genererEscalier(236, 23, 4, false);

	this->genererEscalier(261, 23, 9, false);

	this->genererEscalier(272, 12, 4, false);

	this->genererLigne(23, 268, 6, BORD);
	this->genererLigne(22, 268, 6, BORD);
	this->genererLigne(21, 268, 6, BORD);
	this->genererLigne(20, 268, 6, BORD);
	this->genererLigne(19, 268, 6, BORD);
	this->genererLigne(18, 268, 6, BORD);
	this->genererLigne(17, 268, 6, BORD);
	this->genererLigne(16, 268, 6, BORD);
	this->genererLigne(15, 268, 6, BORD);

	// Ligne
	this->genererLigne(18, 48, 4, BORD);
	this->genererLigne(18, 54, 4, BORD);
	this->genererLigne(14, 51, 4, BORD);
	this->genererLigne(20, 92, 5, BORD);
	this->genererLigne(18, 98, 5, BORD);
	this->genererLigne(16, 104, 5, BORD);
	this->genererLigne(21, 162, 5, BORD);
	this->genererLigne(21, 171, 5, BORD);
	this->genererLigne(21, 180, 5, BORD);
	this->genererLigne(17, 166, 6, BORD);
	this->genererLigne(17, 175, 6, BORD);
	this->genererLigne(13, 170, 6, BORD);

	// Trou
	this->genererLigne(24, 83, 2, TROU);
	this->genererLigne(24, 164, 21, TROU);
	this->genererLigne(24, 209, 1, TROU);
	this->genererLigne(24, 240, 3, TROU);
	this->genererLigne(24, 246, 2, TROU);
	this->genererLigne(24, 251, 2, TROU);
	this->genererLigne(24, 256, 2, TROU);

	// Pi��ces
	this->tabLevel[22][14].setCasePiece();
	this->tabLevel[22][16].setCasePiece();
	this->tabLevel[22][18].setCasePiece();
	this->tabLevel[20][28].setCasePiece();
	this->tabLevel[20][31].setCasePiece();
	this->tabLevel[19][34].setCasePiece();
	this->tabLevel[17][39].setCasePiece();
	this->tabLevel[17][42].setCasePiece();
	this->tabLevel[16][46].setCasePiece();
	this->tabLevel[16][49].setCasePiece();
	this->tabLevel[16][52].setCasePiece();
	this->tabLevel[16][55].setCasePiece();
	this->tabLevel[22][63].setCasePiece();
	this->tabLevel[22][65].setCasePiece();
	this->tabLevel[22][67].setCasePiece();
	this->tabLevel[22][69].setCasePiece();
	this->tabLevel[22][71].setCasePiece();
	this->tabLevel[18][123].setCasePiece();
	this->tabLevel[18][126].setCasePiece();
	this->tabLevel[21][128].setCasePiece();
	this->tabLevel[20][130].setCasePiece();
	this->tabLevel[18][133].setCasePiece();
	this->tabLevel[17][136].setCasePiece();
	this->tabLevel[19][162].setCasePiece();
	this->tabLevel[19][164].setCasePiece();
	this->tabLevel[19][166].setCasePiece();
	this->tabLevel[19][171].setCasePiece();
	this->tabLevel[19][173].setCasePiece();
	this->tabLevel[19][175].setCasePiece();
	this->tabLevel[19][180].setCasePiece();
	this->tabLevel[19][182].setCasePiece();
	this->tabLevel[19][184].setCasePiece();
	this->tabLevel[15][166].setCasePiece();
	this->tabLevel[15][168].setCasePiece();
	this->tabLevel[15][170].setCasePiece();
	this->tabLevel[15][175].setCasePiece();
	this->tabLevel[15][177].setCasePiece();
	this->tabLevel[15][179].setCasePiece();
	this->tabLevel[13][210].setCasePiece();
	this->tabLevel[13][213].setCasePiece();
	this->tabLevel[15][215].setCasePiece();
	this->tabLevel[15][218].setCasePiece();
	this->tabLevel[17][220].setCasePiece();
	this->tabLevel[17][223].setCasePiece();
	this->tabLevel[19][225].setCasePiece();
	this->tabLevel[19][228].setCasePiece();
	this->tabLevel[19][243].setCasePiece();
	this->tabLevel[19][246].setCasePiece();
	this->tabLevel[17][248].setCasePiece();
	this->tabLevel[17][251].setCasePiece();
	this->tabLevel[15][253].setCasePiece();
	this->tabLevel[15][256].setCasePiece();
	this->tabLevel[13][269].setCasePiece();
	this->tabLevel[13][271].setCasePiece();
	this->tabLevel[13][273].setCasePiece();

	//Fin de niveau : Drapeau
	this->tabLevel[23][280].setCaseChateau();
	this->tabLevel[22][280].setCaseChateau();
	this->tabLevel[21][280].setCaseChateau();
	this->tabLevel[20][280].setCaseChateau();
	this->tabLevel[19][280].setCaseChateau();
	this->tabLevel[18][280].setCaseChateau();
	this->tabLevel[17][280].setCaseChateau();
	this->tabLevel[16][280].setCaseChateau();
	this->tabLevel[15][280].setCaseChateau();
	this->tabLevel[14][280].setCaseChateau();
	this->tabLevel[13][280].setCaseChateau();
	this->tabLevel[12][280].setCaseChateau();
	this->tabLevel[11][280].setCaseChateau();
	this->tabLevel[10][280].setCaseChateau();
	this->tabLevel[9][280].setCaseChateau();
	this->tabLevel[8][280].setCaseChateau();
	this->tabLevel[7][280].setCaseChateau();
	this->tabLevel[6][280].setCaseChateau();
	this->tabLevel[6][281].setCaseDrapeau();
	this->tabLevel[6][282].setCaseDrapeau();
	this->tabLevel[7][281].setCaseDrapeau();
	this->tabLevel[7][282].setCaseDrapeau();
	this->tabLevel[7][283].setCaseDrapeau();
	this->tabLevel[7][284].setCaseDrapeau();
	this->tabLevel[8][281].setCaseDrapeau();
	this->tabLevel[8][282].setCaseDrapeau();
	this->tabLevel[8][283].setCaseDrapeau();
	this->tabLevel[8][284].setCaseDrapeau();
	this->tabLevel[8][285].setCaseDrapeau();
	this->tabLevel[8][286].setCaseDrapeau();
	this->tabLevel[9][281].setCaseDrapeau();
	this->tabLevel[9][282].setCaseDrapeau();
	this->tabLevel[9][283].setCaseDrapeau();
	this->tabLevel[9][284].setCaseDrapeau();
	this->tabLevel[10][282].setCaseDrapeau();
	this->tabLevel[10][281].setCaseDrapeau();

	//Fin de niveau : Chateau
	this->tabLevel[23][284].setCaseChateau();
	this->tabLevel[22][284].setCaseChateau();
	this->tabLevel[21][284].setCaseChateau();
	this->tabLevel[20][284].setCaseChateau();
	this->tabLevel[19][284].setCaseChateau();
	this->tabLevel[18][284].setCaseChateau();
	this->tabLevel[17][284].setCaseChateau();

	this->tabLevel[17][284].setCaseChateau();
	this->tabLevel[17][285].setCaseChateau();
	this->tabLevel[17][286].setCaseChateau();
	this->tabLevel[17][287].setCaseChateau();
	this->tabLevel[17][288].setCaseChateau();
	this->tabLevel[17][289].setCaseChateau();
	this->tabLevel[17][290].setCaseChateau();
	this->tabLevel[17][291].setCaseChateau();
	this->tabLevel[17][292].setCaseChateau();
	this->tabLevel[17][293].setCaseChateau();
	this->tabLevel[17][294].setCaseChateau();
	this->tabLevel[17][295].setCaseChateau();
	this->tabLevel[17][296].setCaseChateau();

	this->tabLevel[23][296].setCaseChateau();
	this->tabLevel[22][296].setCaseChateau();
	this->tabLevel[21][296].setCaseChateau();
	this->tabLevel[20][296].setCaseChateau();
	this->tabLevel[19][296].setCaseChateau();
	this->tabLevel[18][296].setCaseChateau();
	this->tabLevel[17][296].setCaseChateau();

	this->tabLevel[16][285].setCaseChateau();
	this->tabLevel[16][286].setCaseChateau();
	this->tabLevel[15][287].setCaseChateau();
	this->tabLevel[15][288].setCaseChateau();
	this->tabLevel[14][289].setCaseChateau();
	this->tabLevel[14][290].setCaseChateau();
	this->tabLevel[14][291].setCaseChateau();
	this->tabLevel[15][292].setCaseChateau();
	this->tabLevel[15][293].setCaseChateau();
	this->tabLevel[16][294].setCaseChateau();
	this->tabLevel[16][295].setCaseChateau();

	// Bandeau Haut
	for (int y = 0; y < 300; y++) {
		this->tabLevel[0][y].setCaseBord();
	}
	this->initBandeau();

	//Mario
	this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();
	this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();

	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			this->tab[x][y] = &(this->tabLevel[x][y]);
		}
	}
}

/**
 * affichage de la map
 */
void PlateauSextantBros::rafraichir(bool tout) {
	if (this->horloge->getTemps() <= 0)
		this->perdreVie();
	else {
		if (this->mario.getY() > 40 && this->mario.getY() < 261) {
			int deb = -41;
			for (int x = 1; x < HAUTEUR; x++) {
				for (int y = 0; y < LARGEUR; y++) {
					this->tab[x][y] = &(this->tabLevel[x][this->mario.getY()
							+ deb]);
					deb++;
				}
				deb = -41;
			}
		}

		for (int x = 1; x < HAUTEUR; x++) {
			for (int y = 0; y < LARGEUR; y++) {
				this->tab[x][y]->paint(x, y);
			}
		}
	}
}

void PlateauSextantBros::genererTube(int posX, int posY, int h) {
	for (int y = posY; y >= (posY - h); y--) {
		if (y == (posY - h)) {
			this->tabLevel[y][posX - 1].setCaseTube();
			this->tabLevel[y][posX + 2].setCaseTube();
		}
		this->tabLevel[y][posX].setCaseTube();
		this->tabLevel[y][posX + 1].setCaseTube();
	}
}

void PlateauSextantBros::genererBoite(int posX, int posY, bool champi) {
	if (champi) {
		this->tabLevel[posY][posX].setCaseBoiteChampi();
		this->tabLevel[posY][posX + 1].setCaseBoiteChampi();
	} else {
		this->tabLevel[posY][posX].setCaseBoitePiece();
		this->tabLevel[posY][posX + 1].setCaseBoitePiece();
	}
}

void PlateauSextantBros::genererEscalier(int posX, int posY, int h,
		bool reverse) {
	int p = h;
	if (reverse) {
		for (int y = posY; y >= (posY - h); y--) {
			for (int x = posX; x < posX + p; x++) {
				this->tabLevel[y][x].setCaseBord();
			}
			p--;
		}

	} else {
		for (int y = posY; y >= (posY - h); y--) {
			for (int x = posX; x < posX + p; x++) {
				this->tabLevel[y][x].setCaseBord();
			}
			posX++;
			p--;
		}
	}
}

void PlateauSextantBros::genererLigne(int posX, int posY, int t, int type) {
	for (int y = posY; y <= posY + t; y++) {
		switch (type) {
		case BORD:
			this->tabLevel[posX][y].setCaseBord();
			break;
		case TROU:
			this->tabLevel[posX][y].setCaseTrou();
			break;
		}

	}
}

void PlateauSextantBros::incrementerPiece() {
	this->score += 10;
	this->pieces++;
	if (this->pieces >= 100) {
		this->pieces -= 100;
		this->vie++;
	}
	this->initBandeau();
}

void PlateauSextantBros::incrementerPiece(int nbPieces) {
	this->score += nbPieces * 10;
	this->pieces += nbPieces;

	if (this->pieces >= 100) {
		this->pieces -= 100;
		this->vie++;
	}
	this->initBandeau();
}

void PlateauSextantBros::initBandeau() {
	this->ecran->afficherMot(0, 0, "Score : ", BLANC);
	this->ecran->afficherBase(this->score, 10, BLANC);
	this->ecran->afficherMot(0, 20, "Vie : ", BLANC);
	this->ecran->afficherBase(this->vie, 10, BLANC);
	this->ecran->afficherMot(0, 30, "Pieces : ", BLANC);
	this->ecran->afficherBase(this->pieces, 10, BLANC);
	this->ecran->afficherMot(0, 44, "Temps : ", BLANC);
	this->ecran->afficherBase(this->horloge->getTemps(), 10, BLANC);
}

void PlateauSextantBros::perdreVie() {
	this->vie--;
	if (this->vie <= 0)
		this->niveauTermine = true;
	else {
		this->mario.setBas(23);
		this->mario.setHaut(23);
		this->mario.setY(5);
		this->horloge->setTemps(300);
		this->level();
		this->rafraichir(true);
	}
}

/**
 * initialise les blocs pour la page de partie perdue
 */
void PlateauSextantBros::perdu() {
	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			tabIntro[x][y].init(x, y);
			this->tabIntro[x][y].setEcran(this->ecran);
		}
	}

	// P
	this->tabIntro[11][47].setCaseBord();
	this->tabIntro[12][47].setCaseBord();
	this->tabIntro[13][47].setCaseBord();
	this->tabIntro[14][47].setCaseBord();
	this->tabIntro[15][47].setCaseBord();
	this->tabIntro[11][48].setCaseBord();
	this->tabIntro[13][48].setCaseBord();
	this->tabIntro[11][49].setCaseBord();
	this->tabIntro[13][49].setCaseBord();
	this->tabIntro[11][50].setCaseBord();
	this->tabIntro[12][50].setCaseBord();
	this->tabIntro[13][50].setCaseBord();

	//E
	this->tabIntro[11][52].setCaseBord();
	this->tabIntro[12][52].setCaseBord();
	this->tabIntro[13][52].setCaseBord();
	this->tabIntro[14][52].setCaseBord();
	this->tabIntro[15][52].setCaseBord();
	this->tabIntro[11][53].setCaseBord();
	this->tabIntro[13][53].setCaseBord();
	this->tabIntro[15][53].setCaseBord();
	this->tabIntro[11][54].setCaseBord();
	this->tabIntro[13][54].setCaseBord();
	this->tabIntro[15][54].setCaseBord();
	this->tabIntro[11][55].setCaseBord();
	this->tabIntro[15][55].setCaseBord();

	// R
	this->tabIntro[11][57].setCaseBord();
	this->tabIntro[12][57].setCaseBord();
	this->tabIntro[13][57].setCaseBord();
	this->tabIntro[14][57].setCaseBord();
	this->tabIntro[15][57].setCaseBord();
	this->tabIntro[11][58].setCaseBord();
	this->tabIntro[13][58].setCaseBord();
	this->tabIntro[11][59].setCaseBord();
	this->tabIntro[13][59].setCaseBord();
	this->tabIntro[11][60].setCaseBord();
	this->tabIntro[13][60].setCaseBord();
	this->tabIntro[14][60].setCaseBord();
	this->tabIntro[11][61].setCaseBord();
	this->tabIntro[12][61].setCaseBord();
	this->tabIntro[13][61].setCaseBord();
	this->tabIntro[15][61].setCaseBord();

	// D
	this->tabIntro[11][63].setCaseBord();
	this->tabIntro[12][63].setCaseBord();
	this->tabIntro[13][63].setCaseBord();
	this->tabIntro[14][63].setCaseBord();
	this->tabIntro[15][63].setCaseBord();
	this->tabIntro[11][64].setCaseBord();
	this->tabIntro[15][64].setCaseBord();
	this->tabIntro[11][65].setCaseBord();
	this->tabIntro[15][65].setCaseBord();
	this->tabIntro[11][66].setCaseBord();
	this->tabIntro[15][66].setCaseBord();
	this->tabIntro[12][67].setCaseBord();
	this->tabIntro[13][67].setCaseBord();
	this->tabIntro[14][67].setCaseBord();

	// U
	this->tabIntro[11][69].setCaseBord();
	this->tabIntro[12][69].setCaseBord();
	this->tabIntro[13][69].setCaseBord();
	this->tabIntro[14][69].setCaseBord();
	this->tabIntro[15][69].setCaseBord();
	this->tabIntro[15][70].setCaseBord();
	this->tabIntro[15][71].setCaseBord();
	this->tabIntro[11][72].setCaseBord();
	this->tabIntro[12][72].setCaseBord();
	this->tabIntro[13][72].setCaseBord();
	this->tabIntro[14][72].setCaseBord();
	this->tabIntro[15][72].setCaseBord();

	// !
	this->tabIntro[11][75].setCaseBord();
	this->tabIntro[12][75].setCaseBord();
	this->tabIntro[13][75].setCaseBord();
	this->tabIntro[15][75].setCaseBord();

	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			this->tab[x][y] = &(this->tabIntro[x][y]);
			this->tab[x][y]->paint(x, y);
		}
	}

	this->marioAscii();
}

/**
 * initialise les blocs pour la page de partie gagnée
 */
void PlateauSextantBros::victory(int scoreDrapeau,int scoreVie,int scoreTemps, int scoreBonus) {
	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			tabIntro[x][y].init(x, y);
			this->tabIntro[x][y].setEcran(this->ecran);
		}
	}

	// B
	this->tabIntro[6][47].setCaseBord();
	this->tabIntro[7][47].setCaseBord();
	this->tabIntro[8][47].setCaseBord();
	this->tabIntro[9][47].setCaseBord();
	this->tabIntro[10][47].setCaseBord();
	this->tabIntro[6][48].setCaseBord();
	this->tabIntro[8][48].setCaseBord();
	this->tabIntro[10][48].setCaseBord();
	this->tabIntro[6][49].setCaseBord();
	this->tabIntro[7][49].setCaseBord();
	this->tabIntro[8][49].setCaseBord();
	this->tabIntro[10][49].setCaseBord();
	this->tabIntro[8][50].setCaseBord();
	this->tabIntro[9][50].setCaseBord();
	this->tabIntro[10][50].setCaseBord();

	// R
	this->tabIntro[6][52].setCaseBord();
	this->tabIntro[7][52].setCaseBord();
	this->tabIntro[8][52].setCaseBord();
	this->tabIntro[9][52].setCaseBord();
	this->tabIntro[10][52].setCaseBord();
	this->tabIntro[6][53].setCaseBord();
	this->tabIntro[8][53].setCaseBord();
	this->tabIntro[6][54].setCaseBord();
	this->tabIntro[8][54].setCaseBord();
	this->tabIntro[6][55].setCaseBord();
	this->tabIntro[8][55].setCaseBord();
	this->tabIntro[9][55].setCaseBord();
	this->tabIntro[6][56].setCaseBord();
	this->tabIntro[7][56].setCaseBord();
	this->tabIntro[8][56].setCaseBord();
	this->tabIntro[10][56].setCaseBord();

	// A
	this->tabIntro[6][58].setCaseBord();
	this->tabIntro[7][58].setCaseBord();
	this->tabIntro[8][58].setCaseBord();
	this->tabIntro[9][58].setCaseBord();
	this->tabIntro[10][58].setCaseBord();
	this->tabIntro[6][59].setCaseBord();
	this->tabIntro[8][59].setCaseBord();
	this->tabIntro[6][60].setCaseBord();
	this->tabIntro[8][60].setCaseBord();
	this->tabIntro[6][61].setCaseBord();
	this->tabIntro[7][61].setCaseBord();
	this->tabIntro[8][61].setCaseBord();
	this->tabIntro[9][61].setCaseBord();
	this->tabIntro[10][61].setCaseBord();

	// V
	this->tabIntro[6][63].setCaseBord();
	this->tabIntro[7][63].setCaseBord();
	this->tabIntro[8][64].setCaseBord();
	this->tabIntro[9][64].setCaseBord();
	this->tabIntro[10][65].setCaseBord();
	this->tabIntro[8][66].setCaseBord();
	this->tabIntro[9][66].setCaseBord();
	this->tabIntro[6][67].setCaseBord();
	this->tabIntro[7][67].setCaseBord();

	// O
	this->tabIntro[6][69].setCaseBord();
	this->tabIntro[7][69].setCaseBord();
	this->tabIntro[8][69].setCaseBord();
	this->tabIntro[9][69].setCaseBord();
	this->tabIntro[10][69].setCaseBord();
	this->tabIntro[6][70].setCaseBord();
	this->tabIntro[10][70].setCaseBord();
	this->tabIntro[6][71].setCaseBord();
	this->tabIntro[10][71].setCaseBord();
	this->tabIntro[6][72].setCaseBord();
	this->tabIntro[7][72].setCaseBord();
	this->tabIntro[8][72].setCaseBord();
	this->tabIntro[9][72].setCaseBord();
	this->tabIntro[10][72].setCaseBord();

	// !
	this->tabIntro[6][75].setCaseBord();
	this->tabIntro[7][75].setCaseBord();
	this->tabIntro[8][75].setCaseBord();
	this->tabIntro[10][75].setCaseBord();



	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			this->tab[x][y] = &(this->tabIntro[x][y]);
			this->tab[x][y]->paint(x, y);
		}
	}



	// score :
	this->ecran->ecrireMot(16,47,"SCORE", GRIS_LEGER, NOIR);
	this->ecran->afficherChiffre(16,53,this->score);

	this->ecran->ecrireMot(18,47,"BONUS", GRIS_LEGER, NOIR);
	this->ecran->afficherChiffre(18,53,scoreDrapeau);
	this->ecran->ecrireMot(18,57,"+", GRIS_LEGER, NOIR);
	this->ecran->afficherChiffre(18,59,scoreVie);
	this->ecran->ecrireMot(18,64,"+", GRIS_LEGER, NOIR);
	this->ecran->afficherChiffre(18,66,scoreTemps);
	this->ecran->ecrireMot(18,71,"=", GRIS_LEGER, NOIR);
	this->ecran->afficherChiffre(18,73,scoreBonus);

	this->score += scoreBonus;
	this->ecran->ecrireMot(20,47,"SCORE FINAL", GRIS_LEGER, NOIR);
	this->ecran->afficherChiffre(20,60,this->score);

	this->marioAscii();

}

/**
 * mario affiché sur la page de fin de partie
 */
void PlateauSextantBros::marioAscii() {
//1
	this->ecran->afficherMot(5, 19, "/////////////", ROUGE);
//2
	this->ecran->afficherMot(6, 14, "//////////////////", ROUGE);
//3
	this->ecran->afficherMot(7, 12, "/////////////////", ROUGE);
	this->ecran->afficherMot(7, 29, "111", BLANC);
//4
	this->ecran->afficherMot(8, 10, "/////////////////", ROUGE);
	this->ecran->afficherMot(8, 27, "11111", BLANC);
//5
	this->ecran->afficherMot(9, 10, "//////////////////////////////", ROUGE);
//6
	this->ecran->afficherMot(10, 11, "/////////////////////////////", ROUGE);
//7
	this->ecran->afficherMot(11, 9, "$$$$$$$$$", MARRON);
	this->ecran->afficherMot(11, 18, "11111111111111111", BLANC);
//8
	this->ecran->afficherMot(12, 8, "$$$$", MARRON);
	this->ecran->afficherMot(12, 12, "1111", BLANC);
	this->ecran->afficherMot(12, 16, "$$$", MARRON);
	this->ecran->afficherMot(12, 19, "111111", BLANC);
	this->ecran->afficherMot(12, 25, "$$$", NOIR);
	this->ecran->afficherMot(12, 28, "111111111111", BLANC);
//9
	this->ecran->afficherMot(13, 7, "$$$$", MARRON);
	this->ecran->afficherMot(13, 11, "11111", BLANC);
	this->ecran->afficherMot(13, 16, "$$$$$", MARRON);
	this->ecran->afficherMot(13, 21, "11111111111111111111", BLANC);
//10
	this->ecran->afficherMot(14, 6, "$$$$$", MARRON);
	this->ecran->afficherMot(14, 11, "11111", BLANC);
	this->ecran->afficherMot(14, 16, "$$$$$", MARRON);
	this->ecran->afficherMot(14, 21, "11111111111111111111", BLANC);
//11
	this->ecran->afficherMot(15, 5, "$$$$$", MARRON);
	this->ecran->afficherMot(15, 10, "1111111", BLANC);
	this->ecran->afficherMot(15, 17, "$$$$", MARRON);
	this->ecran->afficherMot(15, 21, "11111111", BLANC);
	this->ecran->afficherMot(15, 29, "$$$$", MARRON);
	this->ecran->afficherMot(15, 33, "11111111", BLANC);
//12
	this->ecran->afficherMot(16, 5, "$$$$$$", MARRON);
	this->ecran->afficherMot(16, 11, "1111111111111", BLANC);
	this->ecran->afficherMot(16, 24, "$$$$$$$$$$$$$$$$", MARRON);
//13
	this->ecran->afficherMot(17, 5, "$$$$$$$$", MARRON);
	this->ecran->afficherMot(17, 13, "11111111111111", BLANC);
	this->ecran->afficherMot(17, 27, "$$$$$$$$$$$$$", MARRON);
//14
	this->ecran->afficherMot(18, 9, "$$$$$$", MARRON);
	this->ecran->afficherMot(18, 15, "11111111111111111111111", BLANC);
//15
	this->ecran->afficherMot(19, 11, "$$$$$", MARRON);
	this->ecran->afficherMot(19, 16, "1111111111111111111", BLANC);
//16
	this->ecran->afficherMot(20, 15, "111111111111111111", BLANC);

}

/**
 * retrecit la taille de Mario
 */
void PlateauSextantBros::perdreRetrecir() {
	if (this->mario.getSuper()) {
		this->tabLevel[mario.getHaut()][mario.getY()].setCaseFond();
		this->mario.retrecir();
		this->rafraichir(true);
	} else
		this->perdreVie();
}
