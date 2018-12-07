///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#include "all_ennemi.h"


all_ennemi::all_ennemi(const all_ennemi & a)
{
	nb_all=a.nb_all;
	enn_all=a.enn_all;
	mut_all=a.mut_all;
	th_all=a.th_all;
}

all_ennemi::~all_ennemi()
{
	for(int i=0;i<nb_all;i++)
	{
		delete th_all[i];
		th_all[i]=NULL;
		delete enn_all[i];
		enn_all[i]=NULL;
		SDL_DestroyMutex(mut_all[i]);
		mut_all[i]=NULL;
	}
	delete [] enn_all;
	delete [] mut_all;
	delete [] th_all;
	enn_all=NULL;
	mut_all=NULL;
	th_all=NULL;
}

SDL_mutex * & all_ennemi::get_mutall(int i)
{
	if(i<0||i>=nb_all) erreur("indice avec all_ennemi et mutex");
	return mut_all[i];
}

stage<ennemi> * & all_ennemi::get_ennall(int i)
{
	if(i<0||i>=nb_all) erreur("indice avec all_ennemi et stage ennemi");
	return enn_all[i];
}

thread * & all_ennemi::get_thall(int i)
{
	if(i<0||i>=nb_all) erreur("indice avec all_ennemi et thread ennemi");
	return th_all[i];
}


void all_ennemi::add(char * dir,frame * f,int level,int delay,int pas)
{
	nb_all++;
	enn_all=(stage<ennemi> **)realloc(enn_all,nb_all*sizeof(stage<ennemi> *));
	mut_all=(SDL_mutex **)realloc(mut_all,nb_all*sizeof(SDL_mutex *));
	th_all=(thread **)realloc(th_all,nb_all*sizeof(thread *));

	enn_all[nb_all-1]=NULL;
	mut_all[nb_all-1]=NULL;
	th_all[nb_all-1]=NULL;

	enn_all[nb_all-1]=new stage<ennemi>;
	mut_all[nb_all-1]=SDL_CreateMutex();
	th_all[nb_all-1]=new thread;

	enn_all[nb_all-1]->init_pos_obj(dir,f,level);
	for(int i=0;i<enn_all[nb_all-1]->get_nbo();i++)
	{
		enn_all[nb_all-1]->get_stage(i)->get_del()=delay;
		enn_all[nb_all-1]->get_stage(i)->get_vit()=pas;
		enn_all[nb_all-1]->get_stage(i)->get_mut()=mut_all[nb_all-1];
	}

}


void all_ennemi::lancer_thread(int (*fn)(void *),int plus,int i)
{
	if(i<0||i>=nb_all) erreur("indice de lancement de thread %d",i);
	th_all[i]->init_th(enn_all[i]->get_nbo());
	th_all[i]->run_th(fn,(stage<sprite> *)enn_all[i],plus);
}