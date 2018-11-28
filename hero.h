#ifndef _HERO_H_
#define _HERO_H_

#include "perso.h"

class hero:public perso
{
	private:
		int nb_vie;
		char * nom;
	public:
		hero():perso() {nb_vie=VIE;nom=NULL;}
		hero(const hero & h):perso(h) {nb_vie=h.nb_vie;nom=h.nom;}
		~hero();

		int & get_vie() {return nb_vie;}
		char * get_nom() {return nom;}
		void set_nom(char * str) {nom=_strdup(str);}

		void avance(int);
		void recule(int);
		void baisser(frame *);
		void attack1(frame *);
		void attack2(frame *);
		void atk_boule(frame *);
		void atk_kame(frame *);
};





#endif