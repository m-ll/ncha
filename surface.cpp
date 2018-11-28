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