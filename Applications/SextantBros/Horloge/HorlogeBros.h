#ifndef HORLOGEBROS_H_
#define HORLOGEBROS_H_

#include <sextant/Activite/Threads.h>
#include <drivers/timer.h>
extern int temps;
class HorlogeBros : public Threads {
	Timer *timer;
	EcranV *ecran;
	int temps;
	bool fin;

public:
	HorlogeBros();
	HorlogeBros(EcranV *);
	virtual ~HorlogeBros();
	void run();
	int getTemps();
	void setTemps(int temps);
	void tempoGumba();
	void setFin(bool);
	void wait(int sec);


};

#endif /* HORLOGEBROS_H_ */
