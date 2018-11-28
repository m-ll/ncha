#ifndef _PERSO_H_
#define _PERSO_H_

#include "sprite.h"

class perso:public sprite
{
	public:
		perso():sprite() {};
		perso(const perso & p):sprite(p) {};
		virtual ~perso();

};




#endif