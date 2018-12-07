///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

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