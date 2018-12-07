///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _HERO_H_
#define _HERO_H_

#include "perso.h"

class hero:public perso
{
	private:
		int nb_vie;
		char * nom;
	public:
		hero():perso() {nb_vie=VIE;nom=NULL;}
		hero(const hero & h):perso(h) {nb_vie=h.nb_vie;nom=h.nom;}
		~hero();

		int & get_vie() {return nb_vie;}
		char * get_nom() {return nom;}
		void set_nom(char * str) {nom=_strdup(str);}

		void avance(int);
		void recule(int);
		void baisser(frame *);
		void attack1(frame *);
		void attack2(frame *);
		void atk_boule(frame *);
		void atk_kame(frame *);
};





#endif