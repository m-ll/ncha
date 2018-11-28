#ifndef _THREAD_H_
#define _THREAD_H_

#include "type.h"
#include "sprite.h"

class thread
{
	private:
		SDL_Thread ** th_tab;
		int nb_th;
	public:
		thread() {th_tab=NULL;nb_th=0;};
		thread(const thread & a) {th_tab=a.th_tab;nb_th=a.nb_th;};
		~thread();

		SDL_Thread ** & get_tab() {return th_tab;};
		int & get_nbth() {return nb_th;};

		void init_th(int);

		void run_th(int (*)(void *),stage<sprite> *,int);
		void run_th(int (*)(void *),sprite *);
		void run_th(int (*)(void *),sprite **);
		void supp_th(int=-1);


};

#endif
