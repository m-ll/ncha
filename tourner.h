#ifndef _TOURNER_H_
#define _TOURNER_H_

#include "mvt.h"

class tourner:public mvt
{
	public:
		tourner():mvt() {};
		tourner(int p):mvt(p) {};
		tourner(const tourner & b):mvt(b) {};
		~tourner() {};
		void move(sprite & s) {turn(s);};
		void turn(sprite &);

};



#endif