#ifndef _RIGHT_H_
#define _RIGHT_H_

#include "mvt.h"


class right:public mvt
{
	public:
		right():mvt() {};
		right(int p):mvt(p) {};
		right(const right & b):mvt(b) {};
		~right() {};
		void move(sprite & s) {mov(s);};
		void mov(sprite &);
};


#endif