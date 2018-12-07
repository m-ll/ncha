///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

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