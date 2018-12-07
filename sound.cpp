///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

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