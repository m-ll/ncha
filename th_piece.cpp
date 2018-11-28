#include "th_piece.h"

int thread_piece(void * st)
{
	extern SDL_mutex * stop;

	for(;;)
	{
		SDL_Delay(TPS_TURN_PIECE);
		int s=0;
		for(int i=0;i<((stage<sprite> *)st)->get_nbo();i++)
		{
			((stage<sprite> *)st)->get_stage(i)->mov();
			s+=((stage<sprite> *)st)->get_stage(i)->get_a();
		}
		if(s) drawscene();

		SDL_mutexP(stop);
		SDL_mutexV(stop);
	}
	return 0;
}
