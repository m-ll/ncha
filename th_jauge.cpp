#include "th_jauge.h"

int thread_jauge(void * p)
{
	extern SDL_mutex * stop;
	extern int jauge;

	for(;;)
	{
		SDL_Delay(5000);

		SDL_mutexP(stop);
		SDL_mutexV(stop);
		
		if(jauge<TAILLE_JAUGE)
		{
			jauge+=10;
			if(jauge>TAILLE_JAUGE)
				jauge=TAILLE_JAUGE;
		}
	}

	return 0;

}