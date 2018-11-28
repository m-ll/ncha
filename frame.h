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