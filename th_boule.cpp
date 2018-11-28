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
