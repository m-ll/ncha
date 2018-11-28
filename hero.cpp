#include "hero.h"

hero::~hero()
{
	get_img()=NULL;
	get_f()=NULL;
	delete [] nom;
	nom=NULL;
}

void hero::avance(int march)
{
	extern int enlair2;
	extern int bord;

	if(get_xs()<=640-get_wt()-bord)
		get_xs()=get_xs()+march;
	if(!enlair2)
	{
		if(march==COURIR) get_step()++;
		next_frame();
		SDL_Delay(TPS_MARCHE);
	}
	else SDL_Delay(TPS_SAUT);
}

void hero::recule(int march)
{
	extern int enlair2;
	extern int bord;

	if(get_xs()>=bord)
		get_xs()=get_xs()-march;
	if(!enlair2)
	{
		if(march==COURIR) get_step()++;
		next_frame();
		SDL_Delay(TPS_MARCHE);
	}
	else SDL_Delay(TPS_SAUT);
}

void hero::baisser(frame * f)
{
	set_f(f);
	get_step()=1;
	next_frame();
}

void hero::attack1(frame * f)
{
	set_f(f);
	get_step()=1;
	next_frame();
}

void hero::attack2(frame * f)
{
	set_f(f);
	get_step()=1;
	next_frame();
}

void hero::atk_boule(frame * f)
{
	set_f(f);
	get_step()=1;
	next_frame();
}

void hero::atk_kame(frame * f)
{
	int nb=0;

	set_f(f);
	get_step()=1;
	for(int i=0;i<f->get_nbf();i++)
		if(nb<f->get_prio(i)) nb=f->get_prio(i);
	next_frame();
	drawscene();
	for(int j=1;j<nb;j++)
	{
		SDL_Delay(TPS_CONCENTRATION_KAME);
		next_frame();
		drawscene();
	}
}

