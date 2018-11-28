#ifndef _SOUND_H_
#define _SOUND_H_

#include "type.h"

class sound
{
	private:
		Mix_Chunk * son;
	public:
		sound() {son=NULL;};
		sound(const sound & s) {son=s.son;};
		~sound();
		
		Mix_Chunk * & get_chunk() {return son;};

		void init_sound(char *);

		void play_chunk();
		void stop_chunk();

};


#endif