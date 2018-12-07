///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "type.h"

class surface
{
	private:
		SDL_Surface * surf;
		int xs,ys;
		int wt,ht;
		int x,y;
		int w,h;
	public:
		surface();
		surface(SDL_Surface *,int,int);
		surface(SDL_Surface *);
		surface(const surface &);
		~surface();

		void init(SDL_Surface *,int,int);
		void init(SDL_Surface *);

		int & get_xs() {return xs;};
		int & get_ys() {return ys;};
		int & get_x() {return x;};
		int & get_y() {return y;};
		int & get_wt() {return wt;};
		int & get_ht() {return ht;};
		int & get_w() {return w;};
		int & get_h() {return h;};
		SDL_Surface * & get_surface() {return surf;};

		void set_alpha(int);

		void remplir(int,int,int);
		void remplir(Uint32);

		void draw(SDL_Surface *);
		void drawt(SDL_Surface *);
};




#endif