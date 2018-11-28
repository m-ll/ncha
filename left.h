#ifndef _LEFT_H_
#define _LEFT_H_

#include "mvt.h"


class left:public mvt
{
	public:
		left():mvt() {};
		left(int p):mvt(p) {};
		left(const left & b):mvt(b) {};
		~left() {};
		void move(sprite & s) {mov(s);};
		void mov(sprite &);
};


#endif