#ifndef _BG_H_
#define _BG_H_

#include "decor.h"

class bg:public decor
{
	public:
		bg():decor() {};
		bg(const bg & b):decor(b) {};
		~bg();
		void avance(int);
		void recule(int);
};

#endif