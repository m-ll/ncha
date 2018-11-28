#ifndef _ALL_ENNEMI_H
#define _ALL_ENNEMI_H

#include "type.h"
#include "ennemi.h"
#include "thread.h"


class all_ennemi
{
	private:
		stage<ennemi> ** enn_all;
		SDL_mutex ** mut_all;
		thread ** th_all;
		int nb_all;
	public:
		all_ennemi() {enn_all=NULL;mut_all=NULL;th_all=NULL;nb_all=0;};
		all_ennemi(const all_ennemi & a);
		~all_ennemi();

		int & get_nball() {return nb_all;};
		SDL_mutex * & get_mutall(int);
		stage<ennemi> * & get_ennall(int);
		thread * & get_thall(int);
		
		void add(char *,frame *,int,int,int);

		void lancer_thread(int (*)(void *),int,int);

};





#endif