#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "type.h"


class music
{
	private:
		Mix_Music * musik;
	public:
		music() {musik=NULL;};
		music(const music & m) {musik=m.musik;};
		~music();

		Mix_Music * & get_musik();

		void init_music(char *,int);

		void play_music();

};



#endif