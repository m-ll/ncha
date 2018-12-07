///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#include "th_saut.h"


int thread_saut(void * s)
{
	extern SDL_mutex * air;
	extern SDL_mutex * mik;
	extern SDL_mutex * stop;
	extern int enlair;
	extern stage<decor_obj> * sol;
	extern Uint8 * keys;
	extern frame * fmarcher;
	extern frame * fbaisser;
	extern int h;
	extern int b;
	extern int g;
	extern int d;

	int ss;

	for(int i=0;i<NB_ETAPE_SAUT;i++)
	{
		SDL_mutexP(stop);
		SDL_mutexV(stop);

		SDL_mutexP(mik);
		((hero *)s)->get_ys()-=SAUT;
		for(ss=0;ss<sol->get_nbo();ss++)
		{
			if(((hero *)s)->collision_h(sol->get_stage(ss),h,b,g,d))
			{
				((hero *)s)->get_ys()=sol->get_stage(ss)->get_ys()+sol->get_stage(ss)->get_ht();
				break;
			}

		}
		((hero *)s)->next_frame();
		//il faut rajouter collision dte et gch
		//si la taille des images de saut sont differentes
		SDL_mutexV(mik);
		drawscene();
		SDL_Delay(TPS_SAUT);
	}
	for(;;)
	{
		SDL_mutexP(stop);
		SDL_mutexV(stop);

		SDL_mutexP(mik);
		((hero *)s)->next_frame();
		((hero *)s)->get_ys()+=SAUT;
		for(ss=0;ss<sol->get_nbo();ss++)
		{
			if(((hero *)s)->collision_b(sol->get_stage(ss),h,b,g,d))
			{
				if(keys[SDLK_DOWN])
					((hero *)s)->baisser(fbaisser);
				else
				{
					int back_xs=((hero *)s)->get_xs();
					int back_wt=((hero *)s)->get_wt();
					((hero *)s)->set_f(fmarcher);
					((hero *)s)->get_step()=1;
					((hero *)s)->next_frame();
					((hero *)s)->get_xs()=back_xs+back_wt/2-((hero *)s)->get_wt()/2;
				}
				((hero *)s)->get_ys()=sol->get_stage(ss)->get_ys()-((hero *)s)->get_ht();
				for(int sd=0;sd<sol->get_nbo();sd++)
				{
					if(((hero *)s)->collision_d(sol->get_stage(sd),h,b,g,d))
					{
						((hero *)s)->get_xs()=sol->get_stage(sd)->get_xs()-((hero *)s)->get_wt()+d;
						break;
					}
				}
				for(int sg=0;sg<sol->get_nbo();sg++)
				{
					if(((hero *)s)->collision_g(sol->get_stage(sg),h,b,g,d))
					{
						((hero *)s)->get_xs()=sol->get_stage(sg)->get_xs()+sol->get_stage(sg)->get_wt()-g;
						break;
					}
				}
				break;
			}
		}
		if(ss<sol->get_nbo()) break;
		SDL_mutexV(mik);
		drawscene();
		SDL_Delay(TPS_SAUT);
	}

	SDL_mutexP(air);
	enlair=0;
	SDL_mutexV(air);
	return 0;
}