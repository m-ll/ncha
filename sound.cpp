#include "sound.h"

sound::~sound()
{
	stop_chunk();
	Mix_FreeChunk(son);
	son=NULL;
}

void sound::init_sound(char * dir)
{
	char namef[255];
	char name[255];
	FILE * fd;

	sprintf(namef,"%s/info.ini",dir);

	if(!(fd=fopen(namef,"r")))
		erreur("pb fichier info pour sound : %s\n",namef);

	fscanf(fd,"%s",namef);

	sprintf(name,"%s/%s",dir,namef);

	if(!(son=Mix_LoadWAV(name)))
	{
	//	erreur("pb pour charger le son : %s\n",name);
	}
}

void sound::play_chunk()
{
	if( !son )
		return;

	if(Mix_PlayChannel(-1,son,0)==-1)
	{
	//	cout<<"pas moyen de jouer un son"<<endl;
	}
}

void sound::stop_chunk()
{
	if( !son )
		return;

	for(int i=0;i<NB_CHANNEL;i++)
		if(son==Mix_GetChunk(i))
			Mix_HaltChannel(i);
}