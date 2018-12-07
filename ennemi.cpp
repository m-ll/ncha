///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#include "ennemi.h"

ennemi::~ennemi()
{
	get_img()=NULL;
	get_f()=NULL;
}

void ennemi::droite()
{
	extern stage<decor_obj> * sol;
	extern bg * backg;
	extern SDL_mutex * stop;
	

	next_frame();
	SDL_Delay(delay);

	for(;;)
	{
		if((sol->get_stage(get_plate())->get_xs()+
			sol->get_stage(get_plate())->get_wt()<0)||
			(sol->get_stage(get_plate())->get_xs()>640))
		{
			get_a()=0;
			SDL_Delay(delay);
		}
		else
		{
			get_a()=1;

			SDL_mutexP(stop);
			SDL_mutexV(stop);

			SDL_mutexP(get_mut());

			get_xs()+=vitesse;
			
			get_sup()=backg->get_wt()+backg->get_xs();
			if(get_xs()+get_wt()>get_sup())
			{
				get_xs()=get_sup()-
					get_wt();
				SDL_mutexV(get_mut());
				break;
			}
			int sd;
			for(sd=0;sd<sol->get_nbo();sd++)
			{
				if(collision_d(sol->get_stage(sd),0,0,0,0))
				{
					get_xs()=sol->get_stage(sd)->get_xs()-
						get_wt();
					break;
				}
			}
			if(sd<sol->get_nbo())
			{
				SDL_mutexV(get_mut());
				break;
			}

			get_sup()=sol->get_stage(get_plate())->get_xs()+sol->get_stage(get_plate())->get_wt();
			if(get_xs()+get_wt()>get_sup())
			{
				get_xs()=get_sup()-
					get_wt();
				SDL_mutexV(get_mut());
				break;
			}

			next_frame();

			SDL_mutexV(get_mut());

			drawscene();

			SDL_Delay(delay);
		}
	}
}

void ennemi::gauche()
{
	extern stage<decor_obj> * sol;
	extern bg * backg;
	extern SDL_mutex * stop;


	next_frame();
	SDL_Delay(delay);

	for(;;)
	{
		if((sol->get_stage(get_plate())->get_xs()+
			sol->get_stage(get_plate())->get_wt()<0)||
			(sol->get_stage(get_plate())->get_xs()>640))
		{
			get_a()=0;
			SDL_Delay(delay);
		}
		else
		{
			get_a()=1;

			SDL_mutexP(stop);
			SDL_mutexV(stop);

			SDL_mutexP(get_mut());

			get_xs()-=vitesse;

			if(get_xs()<backg->get_xs())
			{
				get_xs()=backg->get_xs();
				SDL_mutexV(get_mut());
				break;
			}
			int sg;
			for(sg=0;sg<sol->get_nbo();sg++)
			{
				if(collision_g(sol->get_stage(sg),0,0,0,0))
				{
					get_xs()=sol->get_stage(sg)->get_xs()+
						sol->get_stage(sg)->get_wt();
					break;
				}
			}
			if(sg<sol->get_nbo())
			{
				SDL_mutexV(get_mut());
				break;
			}
			
			get_inf()=sol->get_stage(get_plate())->get_xs();
			if(get_xs()<get_inf())
			{
				get_xs()=get_inf();
				SDL_mutexV(get_mut());
				break;
			}

			next_frame();

			SDL_mutexV(get_mut());

			drawscene();

			SDL_Delay(delay);
		}
	}
}


void ennemi::avance(int d)
{
	extern int bloque;
	extern int decal;

	SDL_mutexP(get_mut());

	if(!bloque)
		get_xs()=get_xs()-d;
	else if(bloque==1)
		get_xs()=get_xs()-decal;

	SDL_mutexV(get_mut());
}

void ennemi::recule(int d)
{
	extern int bloque;
	extern int decal;

	SDL_mutexP(get_mut());

	if(!bloque)
		get_xs()=get_xs()+d;
	else if(bloque==1)
		get_xs()=get_xs()+decal;

	SDL_mutexV(get_mut());
}




void ennemi::tombe(stage<sprite> * st)
{
	if(get_img())
		for(;;)
		{
			int s;
			for(s=0;s<st->get_nbo();s++)
			{
				if(collision_b(st->get_stage(s),0,0,0,0))
				{
					get_ys()=st->get_stage(s)->get_ys()-get_ht();
					get_plate()=s;
					break;
				}
			}
			if(s==st->get_nbo()) get_ys()+=PAS_TOMBER;
			else break;
			if(get_ys()>480)
			{
				get_aff()=0;
				get_a()=0;
				erreur("ennemi dans un trou!!!!");
				break;
			}
		}
	else
	{
		get_a()=0;
		get_aff()=0;
	}
}