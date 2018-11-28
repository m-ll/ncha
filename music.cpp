#include "music.h"

music::~music()
{
	Mix_HaltMusic();
	Mix_FreeMusic(musik);
	musik=NULL;
}

Mix_Music * & music::get_musik()
{
	return musik;
}

void music::init_music(char * dir,int level)
{
	FILE * fd;
	int lv;
	char namef[255];
	char fich[255];

	sprintf(namef,"%s/info.ini",dir);

	if(!(fd=fopen(namef,"r")))
			erreur("probleme fichier info pour musique : %s\n",namef);

	while(!feof(fd))
	{
		fscanf(fd,"%s%d",fich,&lv);
		sprintf(namef,"%s/%s",dir,fich);
		if(level==lv)
		{
			musik=Mix_LoadMUS(namef);
			break;
		}
	}
	if(level!=lv) erreur("il n'y a pas de musique pour chaque level");

}


void music::play_music()
{
	if(musik!=NULL)
		if(Mix_PlayMusic(musik,-1)==-1)
		{
		//	cout<<"la musique marche pas : "<<Mix_GetError()<<endl;
		}
}