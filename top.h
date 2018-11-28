#ifndef _TOP_H_
#define _TOP_H_

#include "mvt.h"


class top:public mvt
{
	public:
		top():mvt() {};
		top(int p):mvt(p) {};
		top(const top & b):mvt(b) {};
		~top() {};
		void move(sprite & s) {mov(s);};
		void mov(sprite &);
};


#endif