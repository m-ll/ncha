///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

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

