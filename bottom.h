#ifndef _BOTTOM_H_
#define _BOTTOM_H_

#include "mvt.h"


class bottom:public mvt
{
	public:
		bottom():mvt() {};
		bottom(int p):mvt(p) {};
		bottom(const bottom & b):mvt(b) {};
		~bottom() {};
		void move(sprite & s) {mov(s);};
		void mov(sprite &);
};


#endif