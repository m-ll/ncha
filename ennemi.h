///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _ENNEMI_H_
#define _ENNEMI_H_

#include "perso.h"
#include "decor_obj.h"
#include "bg.h"
#include "hero.h"

class ennemi:public perso
{
	private:
		int num_plate;
		int inf,sup;
		SDL_mutex * mut;
		int delay;
		int vitesse;
	public:
		ennemi():perso() {num_plate=-1;inf=0;sup=0;};
		ennemi(const ennemi & e):perso(e) {num_plate=e.num_plate;};
		virtual ~ennemi();

		int & get_plate() {return num_plate;};
		int & get_inf() {return inf;};
		int & get_sup() {return sup;};
		int & get_del() {return delay;};
		int & get_vit() {return vitesse;};
		SDL_mutex * & get_mut() {return mut;};

		void avance(int);
		void recule(int);

		void droite();
		void gauche();

		void tombe(stage<sprite> *);

};

#endif