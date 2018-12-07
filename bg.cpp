///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#include "bg.h"

bg::~bg()
{
	get_img()=NULL;
	get_f()=NULL;
}

void bg::avance(int d)
{
	extern int bloque;
	extern int decal;
	extern SDL_mutex * mut_dec;

	SDL_mutexP(mut_dec);

	get_xs()-=d;

	if(get_xs()+get_wt()>640)
	{
		bloque=0;
	}
	else
	{
		//etant donne qu'on a deja deplace le decor de d
		//get_xs()+640 est superieur a get_wt()
		//decal est en fait le nbr de pix entre la fin du decor et le fin
		//de l'ecran
		decal=(-get_xs()+640)-get_wt();
		//il faut ramener le decor vers la droite de decal pix et donc l'add
		get_xs()+=decal;
		//il faut deplacer les autre objets vers la gauche du nombre de pix
		//qui depasse de l'ecran
		decal=d-decal;
		bloque++;
	}

	SDL_mutexV(mut_dec);

}

void bg::recule(int d)
{
	extern int bloque;
	extern int decal;
	extern SDL_mutex * mut_dec;

	SDL_mutexP(mut_dec);

	get_xs()+=d;

	if(get_xs()<0)
	{
		bloque=0;
	}
	else
	{
		//decal est egal au nbr de pix qui depasse de l'ecran a gauche
		//get_xs() est >0 puisqu'on a ajoute d
		decal=d-get_xs();
		//on remet get_xs() a 0;
		get_xs()=0;
		bloque++;
	}

	SDL_mutexV(mut_dec);

}