#include "frame.h"

frame::frame()
{
	frames=NULL;
	nbframes=0;
}

frame::frame(char * c)
{
	init(c);
}

frame::~frame()
{
	for(int i=0;i<nbframes;i++)
	{
		delete[] frames[i].nom;
		frames[i].nom=NULL;
		SDL_FreeSurface(frames[i].img);
		frames[i].img=NULL;
	}
}

framebase & frame::get_frame(int i)
{
	if(i>=nbframes||i<0)
		erreur("indice du get_frames");
	return frames[i];
}

char frame::get_direct(int i)
{
	if(i>=nbframes||i<0)
		erreur("indice du get_direct");
	return frames[i].direct;
}

char * frame::get_nom(int i)
{
	if(i>=nbframes||i<0)
		erreur("indice du get_nom");
	return frames[i].nom;
}

int frame::get_prio(int i)
{
	if(i>=nbframes||i<0)
		erreur("indice du get_prio");
	return frames[i].prio;
}

SDL_Surface * frame::get_img(int i)
{
	if(i>=nbframes||i<0)
		erreur("indice du get_img");
	return frames[i].img;
}


void frame::init(char * dir)
{
	char filename[255];
	char buffer[255];
	char name[255];
	FILE * fd;
	int nbf;
	int r,g,b;
	int prior;
	char dg;

	sprintf(filename,"%s/info.ini",dir);

	if(!(fd=fopen(filename,"r")))
		erreur(filename);

	fscanf(fd,"%d",&nbf);
	nbframes=nbf;
	frames=new framebase[nbf];

	nbf=0;
	while(!feof(fd) && nbf<nbframes)
	{
		fgets(buffer, 255, fd);
		if(buffer[0]!='#'&&buffer[0]!='\r'&&buffer[0]!='\0'&&buffer[0]!='\n'&&strlen(buffer)!=0)
		{
			sscanf(buffer,"%s %d %d %d %c %d",name,&r,&g,&b,&dg,&prior);
			frames[nbf].nom=_strdup(name);
			frames[nbf].direct=dg;
			frames[nbf].prio=prior;
			sprintf(filename,"%s/%s",dir,name);

			if(verif_bmp(filename)==1)
				erreur("Le fichier bmp %s n'est pas valide !!!\n",filename);

			if((frames[nbf].img=SDL_LoadBMP(filename))==NULL)
				erreur(filename);
			
			if(r >= 0)
				SDL_SetColorKey(frames[nbf].img,SDL_SRCCOLORKEY,SDL_MapRGB(frames[nbf].img->format,r,g,b));

			nbf++;

		}
	}

	fclose(fd);

}