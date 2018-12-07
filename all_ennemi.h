///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _ALL_ENNEMI_H
#define _ALL_ENNEMI_H

#include "type.h"
#include "ennemi.h"
#include "thread.h"


class all_ennemi
{
	private:
		stage<ennemi> ** enn_all;
		SDL_mutex ** mut_all;
		thread ** th_all;
		int nb_all;
	public:
		all_ennemi() {enn_all=NULL;mut_all=NULL;th_all=NULL;nb_all=0;};
		all_ennemi(const all_ennemi & a);
		~all_ennemi();

		int & get_nball() {return nb_all;};
		SDL_mutex * & get_mutall(int);
		stage<ennemi> * & get_ennall(int);
		thread * & get_thall(int);
		
		void add(char *,frame *,int,int,int);

		void lancer_thread(int (*)(void *),int,int);

};





#endif