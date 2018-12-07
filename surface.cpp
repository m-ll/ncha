///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#include "surface.h"

surface::surface()
{
	surf=NULL;
	xs=ys=x=y=wt=ht=w=h=0;
}

surface::surface(SDL_Surface * s,int width,int height)
{
	surf=SDL_CreateRGBSurface(SDL_HWSURFACE,width,height,32,
		s->format->Rmask,s->format->Gmask,s->format->Bmask,
		s->format->Amask);
	xs=ys=x=y=0;
	wt=w=width;
	ht=h=height;
}

surface::surface(SDL_Surface * s)
{
	surf=SDL_CreateRGBSurface(SDL_HWSURFACE,s->w,s->h,32,
		s->format->Rmask,s->format->Gmask,s->format->Bmask,
		s->format->Amask);
	xs=ys=x=y=0;
	wt=w=s->w;
	ht=h=s->h;
}

surface::surface(const surface & s)
{
	surf=s.surf;
	xs=s.xs;
	ys=s.ys;
	x=s.x;
	y=s.y;
	wt=s.wt;
	ht=s.ht;
	w=s.w;
	h=s.h;
}

surface::~surface()
{
	SDL_FreeSurface(surf);
}


void surface::init(SDL_Surface * s,int width,int height)
{
	surf=SDL_CreateRGBSurface(SDL_HWSURFACE,width,height,32,
		s->format->Rmask,s->format->Gmask,s->format->Bmask,
		s->format->Amask);
	xs=ys=x=y=0;
	wt=w=width;
	ht=h=height;
}

void surface::init(SDL_Surface * s)
{
	surf=SDL_CreateRGBSurface(SDL_HWSURFACE,s->w,s->h,32,
		s->format->Rmask,s->format->Gmask,s->format->Bmask,
		s->format->Amask);
	xs=ys=x=y=0;
	wt=w=s->w;
	ht=h=s->h;
}


void surface::set_alpha(int a)
{
	SDL_SetAlpha(surf,SDL_SRCALPHA|SDL_RLEACCEL,a);
}

void surface::remplir(int r,int g,int b)
{
	SDL_FillRect(surf,NULL,SDL_MapRGB(surf->format,r,g,b));
}

void surface::remplir(Uint32 color)
{
	SDL_FillRect(surf,NULL,color);
}

void surface::draw(SDL_Surface * s)
{
	SDL_Rect destd;
	destd.x=xs;
	destd.y=ys;
	SDL_Rect dest;
	dest.x=x;
	dest.y=y;
	dest.w=w;
	dest.h=h;
	SDL_BlitSurface(surf,&dest,s,&destd);
}

void surface::drawt(SDL_Surface * s)
{
	SDL_Rect destd;
	destd.x=xs;
	destd.y=ys;
	SDL_Rect dest;
	dest.x=0;
	dest.y=0;
	dest.w=wt;
	dest.h=ht;
	SDL_BlitSurface(surf,&dest,s,&destd);
}