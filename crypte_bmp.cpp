#include "crypte_bmp.h"


void crypte_bmp(char * name)
{
	FILE * fd,* fd_tmp;
	char * nom_tmp="./tmp";
	
	if(!(fd=fopen(name,"r")))
		erreur("pb ouverture fichier lect");
	if(!(fd_tmp=fopen(nom_tmp,"w")))
		erreur("pb ouverture fichier tmp");

	unsigned char car;
	int fin=1;
	for(int i=0;i<54;i++)
	{
		fscanf(fd,"%c",&car);
		fprintf(fd_tmp,"%c",car);
	}
	while(!(fin=feof(fd)))
	{
		if(!fin)
		{
			fscanf(fd,"%c",&car);
			switch(car%0x00000010)
			{
				case 0x00000001 :
				case 0x00000003 :
				case 0x00000005 :
				case 0x00000007 :
				case 0x00000009 :
				case 0x0000000B :
				case 0x0000000D :
				case 0x0000000F : car-=0x00000001;
			}
			fprintf(fd_tmp,"%c",car);
		}
	}
	
	fclose(fd);
	fclose(fd_tmp);

	remove(name);
	rename("./tmp",name);
}

int verif_bmp(char * name)
{
	FILE * fd;
	
	if(!(fd=fopen(name,"r")))
		erreur("pb ouverture fichier lect");

	unsigned char car;
	int fin=1;
	for(int i=0;i<54;i++)
		fscanf(fd,"%c",&car);

	for(;fin!=EOF;)
	{
		fin=fscanf(fd,"%c",&car);
		if(fin!=EOF)
		{
			switch(car%0x00000010)
			{
				case 0x00000001 :
				case 0x00000003 :
				case 0x00000005 :
				case 0x00000007 :
				case 0x00000009 :
				case 0x0000000B :
				case 0x0000000D :
				case 0x0000000F : 
					fclose(fd);
					return 1;
			}
		}
	}
	
	fclose(fd);
	return 0;
}

/*
	char nom[20];
	cout<<"entrer le fichier bmp a crypter : ";
	cin>>nom;
	crypte_bmp(nom);

	if(verif_bmp(nom)==1) erreur("pas un bon fichier bmp");
	else if(verif_bmp(nom)==0) cout<<"c un bon fichier bmp"<<endl;
	else cout<<"une erreur inconnue"<<endl;

	return 0;
*/