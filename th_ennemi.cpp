#include "th_ennemi.h"


int thread_ennemi(void * s)
{
	for(;;)
	{
		((ennemi *)s)->get_dg()='g';
		((ennemi *)s)->gauche();
		((ennemi *)s)->get_dg()='d';
		((ennemi *)s)->droite();
	}
}