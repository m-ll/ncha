#include "thread.h"

thread::~thread()
{
	for(int i=0;i<nb_th;i++)
	{
		SDL_KillThread(th_tab[i]);
		th_tab[i]=NULL;
	}
	delete[] th_tab;
	th_tab=NULL;
	nb_th=0;
}

void thread::init_th(int nb)
{
	nb_th=nb;
	th_tab=new SDL_Thread * [nb_th];
	for(int j=0;j<nb_th;j++)
		th_tab[j]=NULL;
}

void thread::run_th(int (*fn)(void *),stage<sprite> * s,int plusieurs)
{
	if(nb_th<0) erreur("pb avec le nb de thread");
	else if(nb_th>0)
		if(plusieurs==0)
		{
			SDL_KillThread(th_tab[0]);
			th_tab[0]=NULL;
			th_tab[0]=SDL_CreateThread(fn,s);
		}
		else
		{
			for(int i=0;i<nb_th;i++)
			{
				SDL_KillThread(th_tab[i]);
				th_tab[i]=NULL;
				th_tab[i]=SDL_CreateThread(fn,s->get_stage(i));
			}
		}
}

void thread::run_th(int (*fn)(void *),sprite * s)
{
	if(nb_th!=1) erreur("le nb de thread doit etre de 1");
	SDL_KillThread(th_tab[0]);
	th_tab[0]=NULL;
	th_tab[0]=SDL_CreateThread(fn,s);
}

void thread::run_th(int (*fn)(void *),sprite ** s)
{
	if(nb_th!=1) erreur("le nb de thread doit etre de 1");
	SDL_KillThread(th_tab[0]);
	th_tab[0]=NULL;
	th_tab[0]=SDL_CreateThread(fn,s);
}


void thread::supp_th(int nb)
{
	if(nb>=nb_th||nb<-1) erreur("pb indice de destruction de thread");

	if(nb==-1)
		for(int i=0;i<nb_th;i++)
		{
			SDL_KillThread(th_tab[i]);
			th_tab[i]=NULL;
		}
	else
	{
		SDL_KillThread(th_tab[nb]);
		th_tab[nb]=NULL;
	}
}

