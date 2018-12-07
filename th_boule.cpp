///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#include "th_boule.h"

int thread_boule(void * b)
{
	extern SDL_mutex * stop;
	extern all_ennemi * all_enn;
	extern sound * explose;
	extern int score;

	int v=PAS_BOULE;

	if(((sprite **)b)[0]->get_dg()=='g') v=-v;

	{
		for(int i=0;i<NB_BOULE;i++)
		{
			((sprite **)b)[i]->get_xs()-=v;
			((sprite **)b)[i]->get_aff()=1;
			((sprite **)b)[i]->get_a()=1;
		}
	}
	for(;;)
	{
		SDL_mutexP(stop);
		SDL_mutexV(stop);

		for(int i=0;i<NB_BOULE;i++)
			((sprite **)b)[i]->get_xs()+=v;
		for(int a=0;a<all_enn->get_nball();a++)
			for(int i=0;i<all_enn->get_ennall(a)->get_nbo();i++)
				for(int k=0;k<NB_BOULE;k++)
					if(((sprite **)b)[k]->collision(all_enn->get_ennall(a)->get_stage(i),0,0,0,0)&&
						all_enn->get_ennall(a)->get_stage(i)->get_aff())
					{
						all_enn->get_thall(a)->supp_th(i);
						all_enn->get_ennall(a)->get_stage(i)->get_aff()=0;
						explose->play_chunk();
						score+=50;
					}
		drawscene();
		SDL_Delay(TPS_DEPLACE_BOULE);
		if(((sprite **)b)[0]->get_xs()>640||
			(((sprite **)b)[0]->get_xs()+((sprite **)b)[0]->get_wt())<0)
			break;
	}
	{
		for(int i=0;i<NB_BOULE;i++)
		{
			((sprite **)b)[i]->get_aff()=0;
			((sprite **)b)[i]->get_a()=0;
		}
	}
	drawscene();
	return 0;
}
