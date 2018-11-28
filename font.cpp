#include "font.h"

font::~font()
{
	SDL_FreeSurface(alpha);
}

SDL_Surface * & font::get_alpha()
{
	return alpha;
}

void font::init(char * dir,int taille,int r,int g,int b)
{
	char namef[255],name[255];
	int tr=0,tg=0,tb=0;
	FILE * fd;

	sprintf(namef,"%s/info.ini",dir);

	if(!(fd=fopen(namef,"r")))
		erreur("on peut pas ouvrir le font du rep %s",namef);

	while(!feof(fd))
	{
		fscanf(fd,"%s%d%d%d%d",namef,&tr,&tg,&tb,&width);
		if(width==taille)
			break;
	}
	if(width!=taille) erreur("ce n'est pas la bonne taille de font");

	sprintf(name,"%s/%s",dir,namef);

	if(verif_bmp(name)==1)
		erreur("Le fichier font %s n'est pas valide",name);

	if(!(alpha=SDL_LoadBMP(name)))
		erreur("pour ouvir le fichier font %s",name);

	if(tr>=0)
		SDL_SetColorKey(alpha,SDL_SRCCOLORKEY,SDL_MapRGB(alpha->format,tr,tg,tb));

	if(r!=0||g!=0||b!=0) change_color(r,g,b);
}

void font::get_pix(int x,int y,int & r,int & g,int & b)
{
	Uint8 tr=0,tg=0,tb=0;

	SDL_LockSurface(alpha);

	int bpp=alpha->format->BytesPerPixel;

    Uint8 *p=(Uint8 *)alpha->pixels+y*alpha->pitch+x*bpp;

    switch(bpp)
	{
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				*p= p[0] << 16 | p[1] << 8 | p[2];
			else
				*p= p[0] | p[1] << 8 | p[2] << 16;
    }
	
	SDL_GetRGB(*(Uint32 *)p,alpha->format,&tr,&tg,&tb);

	SDL_UnlockSurface(alpha);

	r=tr;
	g=tg;
	b=tb;
	
}

void font::set_pix(int x,int y,int r,int g,int b)
{
	
	Uint32 color=SDL_MapRGB(alpha->format,r,g,b);

	SDL_LockSurface(alpha);
	switch (alpha->format->BytesPerPixel)
	{
        case 1:
		{
            Uint8 *bufp;

            bufp = (Uint8 *)alpha->pixels + y*alpha->pitch + x;
            *bufp = color;
        }
        break;
        case 2:
		{
            Uint16 *bufp;

            bufp = (Uint16 *)alpha->pixels + y*alpha->pitch/2 + x;
            *bufp = color;
        }
        break;
        case 3:
		{
            Uint8 *bufp;

            bufp = (Uint8 *)alpha->pixels + y*alpha->pitch + x * 3;
            if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
                bufp[0] = color;
                bufp[1] = color >> 8;
                bufp[2] = color >> 16;
            } else {
                bufp[2] = color;
                bufp[1] = color >> 8;
                bufp[0] = color >> 16;
            }
        }
        break;
        case 4:
		{
            Uint32 *bufp;

            bufp = (Uint32 *)alpha->pixels + y*alpha->pitch/4 + x;
            *bufp = color;
        }
        break;
    }
	SDL_UnlockSurface(alpha);

}

void font::change_color(int r,int g,int b)
{
	int tr=0,tg=0,tb=0;

	for(int i=0;i<alpha->w;i++)
		for(int j=0;j<alpha->h;j++)
		{
			get_pix(i,j,tr,tg,tb);
			if(tr==0&&tg==0&&tb==0)
				set_pix(i,j,r,g,b);
		}

}

void font::drawletter(SDL_Surface * s,int xs,int ys,int x,int y,int w,int h)
{
	SDL_Rect dest;
	dest.x=xs;
	dest.y=ys;
	SDL_Rect src;
	src.x=x;
	src.y=y;
	src.w=w;
	src.h=h;
	SDL_BlitSurface(alpha,&src,s,&dest);
}

void font::drawstring(SDL_Surface * s,int x,int y,char * str,...)
{
	char string[1024];
	int code;

	va_list ap;
	va_start(ap,str);
	vsprintf(string,str,ap);
	va_end(ap);

	x-=width;

	for(int i=0;i<(int)strlen(string);i++)
	{
		code=string[i];
		drawletter(s,x+=width,y,
			(code%16)*width,
			(code/16)*width,
			width,
			width);
	}

}


void font::drawstring_h(SDL_Surface * s,int w,char * str,...)
{
	char string[1024];
	int code;

	va_list ap;
	va_start(ap, str);
	vsprintf(string, str, ap);
	va_end(ap);

	w-=width;

	for(int i=0;i<(int)strlen(string);i++)
	{
		code=string[i];
		drawletter(s,w+=width,s->h/2-width/2,
			(code%16)*width,
			(code/16)*width,
			width,
			width);
	}

}



void font::drawstring_w(SDL_Surface * s,int h,char * str,...)
{
	char string[1024];
	int code;
	int w;

	va_list ap;
	va_start(ap, str);
	vsprintf(string, str, ap);
	va_end(ap);

	w=s->w/2-(int)((strlen(string)/2.0)*width);
	w-=width;

	for(int i=0;i<(int)strlen(string);i++)
	{
		code=string[i];
		drawletter(s,w+=width,h,
			(code%16)*width,
			(code/16)*width,
			width,
			width);
	}
}

void font::drawstring_center(SDL_Surface * s,char * str,...)
{
	char string[1024];
	int code;
	int w;

	va_list ap;
	va_start(ap, str);
	vsprintf(string, str, ap);
	va_end(ap);

	w=s->w/2-(int)((strlen(string)/2.0)*width);
	w-=width;

	for(int i=0;i<(int)strlen(string);i++)
	{
		code=string[i];
		drawletter(s,w+=width,s->h/2-width/2,
			(code%16)*width,
			(code/16)*width,
			width,
			width);
	}

}