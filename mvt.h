#ifndef _MVT_H_
#define _MVT_H_

#include "type.h"
#include "sprite.h"

class mvt
{
	private:
		int pas;
	public:
		mvt() {pas=0;};
		mvt(int);
		mvt(const mvt & m) {pas=m.pas;};
		virtual ~mvt() {};

		int & get_pas() {return pas;};

		virtual void move(sprite &)=0;

};





#endif