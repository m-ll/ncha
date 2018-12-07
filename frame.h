///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _FRAME_H_
#define _FRAME_H_

#include "type.h"
#include "crypte_bmp.h"

typedef struct fb
{
	SDL_Surface * img;
	char direct;
	int prio;
	char * nom;
} framebase;

class frame
{
	private:
		framebase * frames;
		int nbframes;
	public:
		frame();
		frame(char *);
		~frame();
		int get_nbf() {return nbframes;};
		framebase * get_frames() {return frames;};
		framebase & get_frame(int);
		char * get_nom(int);
		char get_direct(int);
		int get_prio(int);
		SDL_Surface * get_img(int);
		void init(char *);
};

#endif