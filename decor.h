#ifndef _DECOR_H_
#define _DECOR_H_

#include "sprite.h"

class decor:public sprite
{
	public:
		decor():sprite() {};
		decor(const decor & d):sprite(d) {};
		virtual ~decor();
};

#endif