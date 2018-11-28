#ifndef _DECOR_OBJ_H_
#define _DECOR_OBJ_H_

#include "decor.h"
#include "mvt.h"

class decor_obj:public decor
{
	private:
		mvt ** proto;
		int dim;
	public:
		decor_obj():decor() {dim=0;proto=NULL;};
		decor_obj(const decor_obj & d):decor(d) {dim=d.dim;proto=d.proto;};
		~decor_obj();


		void set_proto(int d,mvt * m1,...);
		mvt ** get_proto() {return proto;};

		void draw(SDL_Surface *);

		void avance(int);
		void recule(int);
		void mov();
};






#endif