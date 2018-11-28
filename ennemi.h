#ifndef _ENNEMI_H_
#define _ENNEMI_H_

#include "perso.h"
#include "decor_obj.h"
#include "bg.h"
#include "hero.h"

class ennemi:public perso
{
	private:
		int num_plate;
		int inf,sup;
		SDL_mutex * mut;
		int delay;
		int vitesse;
	public:
		ennemi():perso() {num_plate=-1;inf=0;sup=0;};
		ennemi(const ennemi & e):perso(e) {num_plate=e.num_plate;};
		virtual ~ennemi();

		int & get_plate() {return num_plate;};
		int & get_inf() {return inf;};
		int & get_sup() {return sup;};
		int & get_del() {return delay;};
		int & get_vit() {return vitesse;};
		SDL_mutex * & get_mut() {return mut;};

		void avance(int);
		void recule(int);

		void droite();
		void gauche();

		void tombe(stage<sprite> *);

};

#endif