#ifndef MARIO_H_
#define MARIO_H_

class Mario{
	int haut, bas, y;

public:
	Mario();
	void setHaut(int x);
	void setBas(int x);
	void setY(int y);
	int getHaut();
	int getBas();
	int getY();
	bool getSuper();
	void grandir();
	void retrecir();
};

#endif /* MARIO_H_ */
