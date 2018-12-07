///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _FONT_H_
#define _FONT_H_

#include "type.h"
#include "crypte_bmp.h"


//il faut doubler % pour l'ecrire
class font
{
	private:
		SDL_Surface * alpha;
		int width;
	public:
		font() {alpha=NULL;width=0;};
		font(const font & f) {alpha=f.alpha;width=f.width;};
		~font();

		SDL_Surface * & get_alpha();
		int & get_w() {return width;};

		void init(char *,int,int,int,int);

		void get_pix(int,int,int &,int &,int &);
		void set_pix(int,int,int,int,int);

		void change_color(int,int,int);

		void drawletter(SDL_Surface *,int,int,int,int,int,int);
		void drawstring(SDL_Surface *,int,int,char *,...);
		void drawstring_h(SDL_Surface *,int,char *,...);
		void drawstring_w(SDL_Surface *,int,char *,...);
		void drawstring_center(SDL_Surface *,char *,...);

};


#endif