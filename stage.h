#ifndef _STAGE_H_
#define _STAGE_H_

#include "type.h"
#include "frame.h"

template <class A> class stage
{
	private:
		A ** stag;
		int nb_obj;
	public:
		stage() {stag=NULL;nb_obj=0;};
		stage(const stage & s) {stag=s.stag;nb_obj=s.nb_obj;};
		~stage()
		{
			for(int i=0;i<nb_obj;i++)
				delete stag[i];
			delete[] stag;
			stag=NULL;
		};
		int get_nbo() {return nb_obj;};
		A ** get_stage() {return stag;};
		A * get_stage(int i)
		{
			if(i<0||i>=nb_obj)
			{
				//cout<<i<<endl;
				erreur("indice avec get_stage");
			}
			return stag[i];
		};
		void init_pos_obj(char * dir,frame * f,int levl)
		{
			FILE * fd;
			int lv;
			char namef[255];

			sprintf(namef,"%s/position.ini",dir);

			if(!(fd=fopen(namef,"r")))
					erreur("probleme init_pos_obj position");
			while(!feof(fd))
			{
				int nbo;
				int posx,posy;
				char name[255];
				fscanf(fd,"%d",&lv);
				if(lv==levl)
				{
					fscanf(fd,"%d",&nbo);
					nb_obj=nbo;
					
					if(nb_obj<=0) stag=NULL;
					else stag=new A * [nb_obj];

					int j;
					for(j=0;j<nb_obj&&!feof(fd);j++)
					{
						stag[j]=new A;
						fscanf(fd,"%s%d%d",name,&posx,&posy);
						stag[j]->init(f,name);
						stag[j]->get_xs()=posx;
						stag[j]->get_ys()=posy;
					}
					if(j!=nb_obj) erreur("manque des trucs dans fichier position");
					break;
				}
				else
				{
					fscanf(fd,"%d",&nbo);
					for(int y=0;y<nbo;y++)
						fscanf(fd,"%s%d%d",name,&posx,&posy);
				}

			}
			if(lv!=levl) erreur("manque des trucs dans fichier position");
			fclose(fd);
		};


};


#endif

