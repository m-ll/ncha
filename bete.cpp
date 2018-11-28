#include "bete.h"


void init_lib(char * dir)
{
	delete lib;
	lib=new stage<decor_obj>;
	lib->init_pos_obj(dir,flib,0);

	for(int l=0;l<lib->get_nbo();l++)
	{
		if((lib->get_stage(l)->get_dg()=='d'||
			lib->get_stage(l)->get_dg()=='2'||
			lib->get_stage(l)->get_dg()=='3')&&
			(lib->get_stage(l)->get_xs()<=0&&
			lib->get_stage(l)->get_ys()>=0&&
			lib->get_stage(l)->get_ys()<=480))
		{
			lib->get_stage(l)->get_xs()=-lib->get_stage(l)->get_wt();
			switch(lib->get_stage(l)->get_dg())
			{
				case 'd' : lib->get_stage(l)->set_proto(1,new right(PAS_LIB));break;
				case '2' : lib->get_stage(l)->set_proto(2,new top(PAS_LIB),new right(PAS_LIB));break;
				case '3' : lib->get_stage(l)->set_proto(2,new bottom(PAS_LIB),new right(PAS_LIB));break;
			}
		}
		else if((lib->get_stage(l)->get_dg()=='g'||
			lib->get_stage(l)->get_dg()=='1'||
			lib->get_stage(l)->get_dg()=='4')&&
			(lib->get_stage(l)->get_xs()>=640&&
			lib->get_stage(l)->get_ys()>=0&&
			lib->get_stage(l)->get_ys()<=480))
		{
			lib->get_stage(l)->get_xs()=640;
			switch(lib->get_stage(l)->get_dg())
			{
				case 'g' : lib->get_stage(l)->set_proto(1,new left(PAS_LIB));break;
				case '1' : lib->get_stage(l)->set_proto(2,new top(PAS_LIB),new left(PAS_LIB));break;
				case '4' : lib->get_stage(l)->set_proto(2,new bottom(PAS_LIB),new left(PAS_LIB));break;
			}
		}
		else if((lib->get_stage(l)->get_dg()=='h'||
			lib->get_stage(l)->get_dg()=='1'||
			lib->get_stage(l)->get_dg()=='2')&&
			(lib->get_stage(l)->get_xs()<=640&&
			lib->get_stage(l)->get_xs()>=0&&
			lib->get_stage(l)->get_ys()>=480))
		{
			lib->get_stage(l)->get_ys()=480;
			switch(lib->get_stage(l)->get_dg())
			{
				case 'h' : lib->get_stage(l)->set_proto(1,new top(PAS_LIB));break;
				case '1' : lib->get_stage(l)->set_proto(2,new top(PAS_LIB),new left(PAS_LIB));break;
				case '2' : lib->get_stage(l)->set_proto(2,new top(PAS_LIB),new right(PAS_LIB));break;
			}
		}
		else if((lib->get_stage(l)->get_dg()=='b'||
			lib->get_stage(l)->get_dg()=='3'||
			lib->get_stage(l)->get_dg()=='4')&&
			(lib->get_stage(l)->get_xs()<=640&&
			lib->get_stage(l)->get_xs()>=0&&
			lib->get_stage(l)->get_ys()<=0))
		{
			lib->get_stage(l)->get_ys()=-lib->get_stage(l)->get_ht();
			switch(lib->get_stage(l)->get_dg())
			{
				case 'b' : lib->get_stage(l)->set_proto(1,new bottom(PAS_LIB));break;
				case '3' : lib->get_stage(l)->set_proto(2,new bottom(PAS_LIB),new right(PAS_LIB));break;
				case '4' : lib->get_stage(l)->set_proto(2,new bottom(PAS_LIB),new left(PAS_LIB));break;
			}
		}
		else erreur("pb avec les libellule");

	}
}




void init_corbeau(char * dir)
{
	delete corbeau;
	corbeau=new stage<decor_obj>;
	corbeau->init_pos_obj(dir,fcorbeau,0);

	srand(SDL_GetTicks());
	if(rand()%2)
	{
		for(int i=0;i<corbeau->get_nbo();i++)
		{
			corbeau->get_stage(i)->get_xs()=0;
			corbeau->get_stage(i)->get_ys()=0;
			corbeau->get_stage(i)->get_a()=1;
			corbeau->get_stage(i)->get_aff()=1;
			if(corbeau->get_stage(i)->get_dg()=='d')
			{
				corbeau->get_stage(i)->set_proto(1,new right(PAS_CORB));
				corbeau->get_stage(i)->get_xs()=-corbeau->get_stage(i)->get_wt();
				corbeau->get_stage(i)->get_ys()=mike->get_ys();
			}
			else if(corbeau->get_stage(i)->get_dg()=='b')
			{
				corbeau->get_stage(i)->set_proto(1,new bottom(PAS_CORB));
				corbeau->get_stage(i)->get_xs()=mike->get_xs()+mike->get_wt()/2-corbeau->get_stage(i)->get_wt()/2;
				corbeau->get_stage(i)->get_ys()=-corbeau->get_stage(i)->get_ht();
			}
			else if(corbeau->get_stage(i)->get_dg()!='h'&&
				corbeau->get_stage(i)->get_dg()!='g')
				erreur("pb avec direction du corbeau");
		}
	}
	else
	{
		for(int i=0;i<corbeau->get_nbo();i++)
		{
			corbeau->get_stage(i)->get_xs()=0;
			corbeau->get_stage(i)->get_ys()=0;
			corbeau->get_stage(i)->get_a()=1;
			corbeau->get_stage(i)->get_aff()=1;
			if(corbeau->get_stage(i)->get_dg()=='g')
			{
				corbeau->get_stage(i)->set_proto(1,new left(PAS_CORB));
				corbeau->get_stage(i)->get_xs()=640;
				corbeau->get_stage(i)->get_ys()=mike->get_ys();
			}
			else if(corbeau->get_stage(i)->get_dg()=='h')
			{
				corbeau->get_stage(i)->set_proto(1,new top(PAS_CORB));
				corbeau->get_stage(i)->get_xs()=mike->get_xs()+mike->get_wt()/2-corbeau->get_stage(i)->get_wt()/2;
				corbeau->get_stage(i)->get_ys()=480;
			}
			else if(corbeau->get_stage(i)->get_dg()!='b'&&
				corbeau->get_stage(i)->get_dg()!='d')
				erreur("pb avec direction du corbeau");
		}
	}
}












