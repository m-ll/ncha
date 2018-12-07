///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

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