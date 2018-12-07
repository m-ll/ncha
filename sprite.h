///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "type.h"
#include "frame.h"
#include "stage.h"

class sprite
{
	private:
		int x,y;
		int w,h;
		int xscreen,yscreen;
		int wtotal,htotal;
		frame * frames;
		SDL_Surface * ssprite;
		int anim;
		int aff;
		int step;
		char dg;
	public:
		sprite();
		sprite(const sprite &);
		virtual ~sprite();

		virtual int & get_x() {return x;};
		virtual int & get_y() {return y;};
		virtual int & get_w() {return w;};
		virtual int & get_h() {return h;};
		virtual int & get_xs() {return xscreen;};
		virtual int & get_ys() {return yscreen;};
		virtual int & get_wt() {return wtotal;};
		virtual int & get_ht() {return htotal;};
		virtual int & get_a() {return anim;};
		virtual int & get_aff() {return aff;};
		virtual int & get_step() {return step;};
		virtual char & get_dg() {return dg;};
		virtual SDL_Surface * & get_img() {return ssprite;};
		virtual frame * & get_f() {return frames;};
		virtual void set_f(frame *);

		virtual void draw(SDL_Surface *);
		virtual void drawimg(SDL_Surface *,int=0,int=0,int=0,int=0,int=0,int=0);

		virtual void init(frame *,int);
		virtual void init(frame *,int,char);
		virtual void init(frame *,char *);
		virtual void init_pos(char *,frame *,int);

		virtual void next_frame();

		virtual int collision(sprite *,int,int,int,int);
		virtual int collision_b(sprite *,int,int,int,int);
		virtual int collision_h(sprite *,int,int,int,int);
		virtual int collision_d(sprite *,int,int,int,int);
		virtual int collision_g(sprite *,int,int,int,int);

		virtual void tombe(stage<sprite> *);
		virtual void mov() {};

		virtual void avance(int)=0;
		virtual void recule(int)=0;
};



#endif