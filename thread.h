///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _THREAD_H_
#define _THREAD_H_

#include "type.h"
#include "sprite.h"

class thread
{
	private:
		SDL_Thread ** th_tab;
		int nb_th;
	public:
		thread() {th_tab=NULL;nb_th=0;};
		thread(const thread & a) {th_tab=a.th_tab;nb_th=a.nb_th;};
		~thread();

		SDL_Thread ** & get_tab() {return th_tab;};
		int & get_nbth() {return nb_th;};

		void init_th(int);

		void run_th(int (*)(void *),stage<sprite> *,int);
		void run_th(int (*)(void *),sprite *);
		void run_th(int (*)(void *),sprite **);
		void supp_th(int=-1);


};

#endif
