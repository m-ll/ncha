#include "type.h"
#include "stage.h"

#include "surface.h"

#include "frame.h"

#include "sprite.h"

#include "decor.h"
#include "decor_obj.h"
#include "bg.h"

#include "perso.h"
#include "hero.h"
#include "ennemi.h"

#include "mvt.h"
#include "tourner.h"
#include "top.h"
#include "bottom.h"
#include "left.h"
#include "right.h"

#include "thread.h"
#include "th_piece.h"
#include "th_boule.h"
#include "th_saut.h"
#include "th_ennemi.h"
#include "th_jauge.h"

#include "all_ennemi.h"

#include "bete.h"

#include "matrice.h"

#include "music.h"
#include "sound.h"

#include "font.h"

#include "crypte_bmp.h"


Uint8 * keys;
int h=0;
int b=0;
int g=0;
int d=0;


int bloque=1;
int decal;
int level=0;
int enlair=0;
int enlair2=0;
int bord=BORD;

int score=0;
int nb_corb=CORB;

enum e_menu{e_status,e_touche,e_nom,e_fin};
enum e_pres{instr,jeu};
enum e_regame{oui,non};


music * back_music=new music;

sound * kameha=new sound;
sound * cling=new sound;
sound * explose=new sound;


font * d20=new font;
font * e20=new font;
font * ee20=new font;
font * f100=new font;
font * g50=new font;



frame * fbaisser=new frame(DATA_PATH"perso/baisser");
frame * fmarcher=new frame(DATA_PATH"perso/marcher");
frame * fboulep=new frame(DATA_PATH"perso/boule");
frame * fkamep=new frame(DATA_PATH"perso/kame");
frame * fattack1=new frame(DATA_PATH"perso/attack1");
frame * fattack2=new frame(DATA_PATH"perso/attack2");
frame * fsaut=new frame(DATA_PATH"perso/saut");

frame * fbg=new frame(DATA_PATH"decor");

frame * fboule=new frame(DATA_PATH"objet/boule");
frame * fkame=new frame(DATA_PATH"objet/kame");
frame * fsol=new frame(DATA_PATH"objet/sol");
frame * fpiece=new frame(DATA_PATH"objet/piece");
frame * fpancarte=new frame(DATA_PATH"objet/pancarte");

frame * fessai=new frame(DATA_PATH"ennemi/essai");
frame * fessaii=new frame(DATA_PATH"ennemi/essaii");
frame * fessaiii=new frame(DATA_PATH"ennemi/essaiii");

frame * flib=new frame(DATA_PATH"libellule");
frame * fcorbeau=new frame(DATA_PATH"corbeau");
frame * fpoint=new frame(DATA_PATH"point");
frame * fange=new frame(DATA_PATH"ange");

frame * ffleche=new frame(DATA_PATH"exterieur/fleche");
frame * fpres=new frame(DATA_PATH"exterieur/begin");

frame * ficone=new frame(DATA_PATH"icone");

surface * voile_noir=new surface;
surface * jauge_kame=new surface;
int jauge=TAILLE_JAUGE;
decor_obj * fleche=new decor_obj;
bg * pres=new bg;


bg * backg=new bg;
hero * mike=new hero;

decor_obj ** boule=new decor_obj * [NB_BOULE];
decor_obj * kame=new decor_obj;
decor_obj * pancarte=new decor_obj;
decor_obj * point=new decor_obj;
decor_obj * ange=new decor_obj;

stage<decor_obj> * sol=new stage<decor_obj>;
stage<decor_obj> * piece=new stage<decor_obj>;
stage<decor_obj> * corbeau=new stage<decor_obj>;
stage<decor_obj> * lib=new stage<decor_obj>;

thread * th_piece=new thread;
thread * th_boule=new thread;
thread * th_saut=new thread;
thread * th_jauge=new thread;


all_ennemi * all_enn=new all_ennemi;


SDL_mutex * mut=SDL_CreateMutex();
SDL_mutex * stop=SDL_CreateMutex();
SDL_mutex * air=SDL_CreateMutex();
SDL_mutex * mik=SDL_CreateMutex();
SDL_mutex * mut_dec=SDL_CreateMutex();

void presentation(enum e_pres);
void menu_touche();
void menu_regame(enum e_regame);
void menu(enum e_menu);
void menu_statut();
void menu_nom();


int main(int argc, char ** argv)
{
	int death=-1;
	SDL_Event event;
	Uint32 tps=0,tps2=0;
	int corb=0;
	int tomber=1;
	int cour_march=MARCHE;
	int finjeu=0;

	enum evt {dte,gch,z};
	enum evt evt=z;

	memset( boule, 0, NB_BOULE * sizeof( decor_obj* ) );

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0)
		erreur(SDL_GetError());

	atexit(Mix_CloseAudio);
	atexit(SDL_Quit);

	if(Mix_OpenAudio(44100,AUDIO_S16SYS,2,2048)<0)
		erreur(Mix_GetError());

	Mix_AllocateChannels(NB_CHANNEL);
	SDL_EnableKeyRepeat(0,0);

	SDL_WM_SetCaption("Welcome to N'CHA GAME","icone_name");
	srand(clock());
	int i;
	for(i=rand();i>=ficone->get_nbf();i/=10)
		;
	SDL_WM_SetIcon(ficone->get_img(i), NULL);


	if (!(screen=SDL_SetVideoMode(640,480,32,SDL_HWSURFACE|SDL_DOUBLEBUF)))
		erreur(SDL_GetError());

	jauge_kame->init(screen,jauge,10);

	voile_noir->init(screen);
	voile_noir->remplir(0);
	voile_noir->set_alpha(125);

	fleche->init(ffleche,0);
	pres->init(fpres,0);
	point->init(fpoint,0);

	d20->init(DATA_PATH"font/normal",20,255,0,0);
	e20->init(DATA_PATH"font/normal",20,255,255,0);
	ee20->init(DATA_PATH"font/normal",20,0,0,0);
	f100->init(DATA_PATH"font/normal",100,255,0,0);
	g50->init(DATA_PATH"font/normal",50,0,255,0);
	
	SDL_ShowCursor(SDL_DISABLE);




	int fin=0;
	enum e_pres choix=instr;
	presentation(choix);
	while(!fin)
	{
		SDL_PollEvent(&event);

		if(event.type==SDL_QUIT)
		{
			destroy_all();
			exit(0);
		}
		if(event.type==SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_DOWN :
					if(choix==jeu)
						choix=instr;
					else ((int &)choix)++;
					presentation(choix);
					break;
				case SDLK_UP :
					if(choix==instr)
						choix=jeu;
					else ((int &)choix)--;
					presentation(choix);
					break;
				case SDLK_RETURN :
					if(choix==instr)
					{
						menu_touche();
						presentation(choix);
					}
					else if(choix==jeu) fin=1;
					break;
			}
			event.type=-1;
		}
	}
	event.type=-1;
	
	do
	{
		initialisation();

		for(;;)
		{
			SDL_PollEvent(&event);

			keys=SDL_GetKeyState(NULL);

			if(event.type==SDL_QUIT)
			{
				destroy_all();
				exit(0);
			}
			if(event.type==SDL_KEYDOWN)
			{
				if(event.key.keysym.sym==SDLK_ESCAPE)
				{
					finjeu=1;
					break;
				}
				switch(event.key.keysym.sym)
				{
					case SDLK_RIGHT :
						evt=dte;
						corb=0;
						break;
					case SDLK_LEFT :
						evt=gch;
						corb=0;
						break;
					case SDLK_SPACE :
					{
						SDL_mutexP(stop);
						Mix_PauseMusic();
						//il faut un peu de temps pour que toutes les threads
						//s'arrete et ne fassent pas un drawscene
						SDL_Delay(500);
						for(int i=1;i<=10;i++)
						{
							voile_noir->remplir(0);
							voile_noir->set_alpha(25*i);
							drawscene(0);
							voile_noir->draw(screen);
							SDL_Flip(screen);
						}
						voile_noir->set_alpha(125);

						int fin=0;
						enum e_menu choix=e_status;
						menu(choix);
						while(!fin)
						{
							SDL_PollEvent(&event);

							if(event.type==SDL_QUIT)
							{
								destroy_all();
								exit(0);
							}
							if(event.type==SDL_KEYDOWN)
							{
								switch(event.key.keysym.sym)
								{
									case SDLK_DOWN :
										if(choix==e_fin)
											choix=e_status;
										else ((int &)choix)++;
										menu(choix);
										break;
									case SDLK_UP :
										if(choix==e_status)
											choix=e_fin;
										else ((int &)choix)--;
										menu(choix);
										break;
									case SDLK_RETURN :
										if(choix==e_fin) fin=1;
										else if(choix==e_touche)
										{
											menu_touche();
											menu(choix);
										}
										else if(choix==e_status)
										{
											menu_statut();
											menu(choix);
										}
										else if(choix==e_nom)
										{
											menu_nom();
											menu(choix);
										}
										break;
								}
							}
							event.type=-1;
						}

						Mix_ResumeMusic();
						SDL_mutexV(stop);
						break;
					}
					case SDLK_d :
						//POING RAPIDE
						if(!enlair2)
						{
							SDL_mutexP(mik);
							mike->attack1(fattack1);
							SDL_mutexV(mik);
							drawscene();
							SDL_mutexP(mik);
							SDL_Delay(TPS_ATK1_P);
							while(SDL_PollEvent(&event)) ;
							mike->set_f(fmarcher);
							mike->get_step()=1;
							mike->next_frame();
							SDL_mutexV(mik);
						}
						corb=0;
						break;
					case SDLK_c :
						//POING PUISSANT
						if(!enlair2)
						{
							SDL_mutexP(mik);
							mike->attack2(fattack2);
							SDL_mutexV(mik);
							drawscene();
							SDL_mutexP(mik);
							SDL_Delay(TPS_ATK2_P);
							while(SDL_PollEvent(&event)) ;
							mike->set_f(fmarcher);
							mike->get_step()=1;
							mike->next_frame();
							SDL_mutexV(mik);
						}
						corb=0;
						break;
					case SDLK_f :
						//BOULE
						if(jauge>=JAUGE/10)
						{
							if(!tomber)
							{
								if(!enlair2)
								{
									SDL_mutexP(mik);
									mike->atk_boule(fboulep);
									SDL_mutexV(mik);
									drawscene();
									SDL_mutexP(mik);
									{for(int i=0;i<NB_BOULE;i++)
										boule[i]->init(fboule,1,mike->get_dg());}
									if(mike->get_dg()=='d')
									{
										for(int i=0;i<NB_BOULE;i++)
											boule[i]->get_xs()=mike->get_xs()+mike->get_wt();
									}
									else
									{
										for(int i=0;i<NB_BOULE;i++)
											boule[i]->get_xs()=mike->get_xs()-boule[i]->get_wt();
									}
									boule[0]->get_ys()=mike->get_ys()+INIT_POS_BOULE;
									boule[1]->get_ys()=boule[0]->get_ys()-boule[0]->get_ht()-DECAL_BOULE;
									boule[2]->get_ys()=boule[0]->get_ys()+boule[0]->get_ht()+DECAL_BOULE;
									{for(int i=0;i<NB_BOULE;i++)
										boule[i]->get_dg()=mike->get_dg();}
									th_boule->run_th(thread_boule,(sprite **)boule);
									SDL_Delay(TPS_BOULE_P);
									while(SDL_PollEvent(&event)) ;
									mike->set_f(fmarcher);
									mike->get_step()=1;
									mike->next_frame();
									SDL_mutexV(mik);
								}
								else
								{
									SDL_mutexP(mik);
									{for(int i=0;i<NB_BOULE;i++)
										boule[i]->init(fboule,1,mike->get_dg());}
									if(mike->get_dg()=='d')
									{
										for(int i=0;i<NB_BOULE;i++)
											boule[i]->get_xs()=mike->get_xs()+mike->get_wt();
									}
									else
									{
										for(int i=0;i<NB_BOULE;i++)
											boule[i]->get_xs()=mike->get_xs()-boule[i]->get_wt();
									}
									boule[0]->get_ys()=mike->get_ys()+INIT_POS_BOULE;
									boule[1]->get_ys()=boule[0]->get_ys()-boule[0]->get_ht()-DECAL_BOULE;
									boule[2]->get_ys()=boule[0]->get_ys()+boule[0]->get_ht()+DECAL_BOULE;
									{for(int i=0;i<NB_BOULE;i++)
										boule[i]->get_dg()=mike->get_dg();
									th_boule->run_th(thread_boule,(sprite **)boule);}
									SDL_mutexV(mik);
								}
								jauge-=JAUGE/10;
								if(jauge<0) jauge=0;
							}
						}
						corb=0;
						break;
					case SDLK_v :
						//KAMEKAMEHAAAAAAAAAAAA
						if(!enlair2&&!tomber&&jauge>=50)
						{
							//il faut arreter toutes les threads
							SDL_mutexP(stop);
							Mix_PauseMusic();
							kameha->play_chunk();
							mike->atk_kame(fkamep);
							kame->init(fkame,1,mike->get_dg());
							kame->get_a()=1;
							kame->get_aff()=1;
							//si on est du cote droit
							if(mike->get_dg()=='d')
							{
								//on place le kame juste apres le perso
								kame->get_xs()=mike->get_xs()+mike->get_wt();
								//le kame a la bonne hauteur
								kame->get_ys()=mike->get_ys()+INIT_POS_KAME;
								//on affiche la fin du kame
								kame->get_x()=kame->get_wt()-KAME;
								drawscene();
								SDL_Delay(VITESSE_KAME);
								//on continue tant que le kame ne dépasse pas
								//l'ecran + 50
								for(;kame->get_wt()-kame->get_x()+kame->get_xs()<640+DEPASSE_ECRAN_KAME;)
								{
									for(int a=0;a<all_enn->get_nball();a++)
										for(int i=0;i<all_enn->get_ennall(a)->get_nbo();i++)
											if(kame->collision(all_enn->get_ennall(a)->get_stage(i),h,b,g,kame->get_x())&&
												all_enn->get_ennall(a)->get_stage(i)->get_aff())
											{
												all_enn->get_thall(a)->supp_th(i);
												all_enn->get_ennall(a)->get_stage(i)->get_aff()=0;
												explose->play_chunk();
												score+=50;
											}
									//on fait grandir le kame en ajoutant des tranches
									kame->get_x()-=KAME;
									drawscene();
									SDL_Delay(VITESSE_KAME);
								}
							}
							//si on est du cote gauche
							else
							{
								//juste devant le gars
								kame->get_xs()=mike->get_xs()-KAME;
								//a la bonne hauteur
								kame->get_ys()=mike->get_ys()+INIT_POS_KAME;
								//un rectangle de longueur KAME
								kame->get_w()=KAME;
								drawscene();
								SDL_Delay(VITESSE_KAME);
								//tant que le kame ne depasse pas l'ecran a gauche
								//plus 50
								for(;kame->get_xs()+DEPASSE_ECRAN_KAME>0;)
								{
									for(int a=0;a<all_enn->get_nball();a++)
										for(int i=0;i<all_enn->get_ennall(a)->get_nbo();i++)
											if(kame->collision(all_enn->get_ennall(a)->get_stage(i),h,b,g,kame->get_wt()-kame->get_w())&&
												all_enn->get_ennall(a)->get_stage(i)->get_aff())
											{
												all_enn->get_thall(a)->supp_th(i);
												all_enn->get_ennall(a)->get_stage(i)->get_aff()=0;
												explose->play_chunk();
												score+=50;
											}
									//on deplace le kame a l'ecran de -KAME
									kame->get_xs()-=KAME;
									//on agrandit le rectangle de KAME
									kame->get_w()+=KAME;
									drawscene();
									SDL_Delay(VITESSE_KAME);
								}
							}
							kame->get_a()=0;
							kame->get_aff()=0;
							jauge-=JAUGE;
							if(jauge<0) jauge=0;
							//il faut relancer toutes les threads
							SDL_mutexV(stop);
							kameha->stop_chunk();
							Mix_ResumeMusic();
							while(SDL_PollEvent(&event)) ;
							mike->set_f(fmarcher);
							mike->get_step()=1;
							mike->next_frame();
						}
						corb=0;
						break;
					case SDLK_s :
						//SAUTER
						if(!enlair2&&!tomber)
						{
							SDL_mutexP(mik);
							int back_xs=mike->get_xs();
							int back_wt=mike->get_wt();
							enlair2=1;
							SDL_mutexP(air);
							enlair=1;
							SDL_mutexV(air);
							mike->set_f(fsaut);
							mike->get_step()=1;
							mike->get_xs()=back_xs+back_wt/2-mike->get_wt()/2;
							SDL_mutexV(mik);
							th_saut->run_th(thread_saut,mike);
						}
						corb=0;
						break;
					case SDLK_PAGEUP :
						if(!enlair2&&!tomber)
						{
							corb=1;
							tps=SDL_GetTicks();
						}
						break;
					case SDLK_HOME :
						tps2=SDL_GetTicks();
						if( !enlair2 &&
							!tomber &&
							corb==1 &&
							tps2 - tps < TPS_ENCHAINEMENT &&
							!keys[SDLK_PAGEUP] )
							corb=2;
						else
							corb=0;
						break;
					case SDLK_INSERT :
						tps = SDL_GetTicks();
						if( !enlair2 && 
							!tomber &&
							corb==2 &&
							tps - tps2 < TPS_ENCHAINEMENT &&
							!keys[SDLK_PAGEUP] &&
							!keys[SDLK_HOME] &&
							nb_corb != 0 )
						{
							SDL_mutexP(stop);

							init_corbeau(DATA_PATH"corbeau");
							nb_corb--;
							
							int affiche;
							matrice * m=new matrice;
							do
							{
								SDL_Delay(TPS_CORB);
								affiche=0;
								drawscene();
								for(int i=0;i<corbeau->get_nbo();i++)
								{
									if(corbeau->get_stage(i)->get_xs()!=0||
										corbeau->get_stage(i)->get_ys()!=0)
									{
										m->add(corbeau->get_stage(i)->get_xs()+corbeau->get_stage(i)->get_wt()/2,
											corbeau->get_stage(i)->get_ys()+corbeau->get_stage(i)->get_ht()/2);
										corbeau->get_stage(i)->mov();
										for(int a=0;a<all_enn->get_nball();a++)
											for(int s=0;s<all_enn->get_ennall(a)->get_nbo();s++)
												if(corbeau->get_stage(i)->collision(all_enn->get_ennall(a)->get_stage(s),0,0,0,0)&&
													all_enn->get_ennall(a)->get_stage(s)->get_aff())
												{
													all_enn->get_thall(a)->supp_th(s);
													all_enn->get_ennall(a)->get_stage(s)->get_aff()=0;
													explose->play_chunk();
													score+=50;
												}
										corbeau->get_stage(i)->draw(screen);
										affiche+=corbeau->get_stage(i)->get_aff();
									}
								}
								for(int d=0;d<m->get_dim1();d++)
								{
									point->get_xs()=m->get_case(d,0);
									point->get_ys()=m->get_case(d,1);
									point->draw(screen);
								}
								SDL_Flip(screen);
								
							}
							while(affiche);
							SDL_Delay(TPS_CORB);
							delete m;
							m=NULL;
							SDL_mutexV(stop);
						}
						while (SDL_PollEvent(&event)) ;
						corb=0;
						tps=0;
						tps2=0;
						break;
					default : break;
				}
			}

			//remise a zero de l'evenement
			event.type=-1;

			keys=SDL_GetKeyState(NULL);

			//on regarde si on court ou on marche
			if((keys[SDLK_LSHIFT])||(keys[SDLK_RSHIFT])) cour_march=COURIR;
			else cour_march=MARCHE;

			//si on est en lair, on regarde si on est retombe
			if(enlair2)
			{
				SDL_mutexP(air);
				if(!enlair) enlair2=0;
				SDL_mutexV(air);
			}

			if(enlair2) cour_march=PAS_SAUT(cour_march);

			if(enlair2)
			{
				h=0;b=0;d=0;g=0;
			}
			else
			{
				h=0;b=0;d=13;g=13;
			}

			//si on est pas en l'air, on regarde si on est baisse ou si on a ete
			if(!enlair2)
			{
				SDL_mutexP(mik);
				if(keys[SDLK_DOWN])
				{
					mike->set_f(fbaisser);
					mike->get_step()=1;
					mike->next_frame();
				}
				else if(mike->get_f()==fbaisser)
				{
					mike->set_f(fmarcher);
					mike->get_step()=1;
					mike->next_frame();
				}
				SDL_mutexV(mik);
			}
			else
			{
				SDL_Event * event_tab=NULL;
				int dim=0;
				//si il est en lair on prend que les evenements qui nous interessent
				while(SDL_PollEvent(&event))
				{
					if(event.type==SDL_KEYDOWN)
					{
						switch(event.key.keysym.sym)
						{
							case SDLK_ESCAPE :
							case SDLK_RIGHT :
							case SDLK_LEFT :
							case SDLK_f :
								dim++;
								event_tab=(SDL_Event *)realloc(event_tab,dim*sizeof(SDL_Event));
								event_tab[dim-1]=event;
							default : break;
						}
					}
				}
				for(int i=0;i<dim;i++)
					SDL_PushEvent(&(event_tab[i]));
				delete [] event_tab;
				event.type=-1;
			}


			//on regarde si on doit avancer ou reculer
			//on va a droite
			if(keys[SDLK_RIGHT]&&!keys[SDLK_LEFT])
			{
				SDL_mutexP(mik);
				mike->get_dg()='d';
				if ((!keys[SDLK_DOWN]||enlair2))
				{
					mike->avance(cour_march);
					if(mike->get_xs()>640-mike->get_wt()-bord)
					{
						backg->avance(cour_march);
						pancarte->avance(cour_march);
						{for(int i=0;i<sol->get_nbo();i++)
							sol->get_stage(i)->avance(cour_march);}
						{for(int i=0;i<piece->get_nbo();i++)
							piece->get_stage(i)->avance(cour_march);}
						{for(int a=0;a<all_enn->get_nball();a++)
							for(int i=0;i<all_enn->get_ennall(a)->get_nbo();i++)
								all_enn->get_ennall(a)->get_stage(i)->avance(cour_march);}
					}
					bord=BORD;
					if(bloque&&backg->get_xs())
						bord=PETIT_BORD;
				}
				else mike->next_frame();

				for(int s=0;s<sol->get_nbo();s++)
				{
					if(mike->collision_d(sol->get_stage(s),h,b,g,d))
					{
						mike->get_xs()=sol->get_stage(s)->get_xs()-mike->get_wt()+d;
						break;
					}
				}

				SDL_mutexV(mik);
			}
			//on va a gauche
			else if(keys[SDLK_LEFT]&&!keys[SDLK_RIGHT])
			{
				SDL_mutexP(mik);
				mike->get_dg()='g';
				if ((!keys[SDLK_DOWN]||enlair2))
				{
					mike->recule(cour_march);
					if(mike->get_xs()<bord)
					{
						backg->recule(cour_march);
						pancarte->recule(cour_march);
						{for(int i=0;i<sol->get_nbo();i++)
							sol->get_stage(i)->recule(cour_march);}
						{for(int i=0;i<piece->get_nbo();i++)
							piece->get_stage(i)->recule(cour_march);}
						{for(int a=0;a<all_enn->get_nball();a++)
							for(int i=0;i<all_enn->get_ennall(a)->get_nbo();i++)
								all_enn->get_ennall(a)->get_stage(i)->recule(cour_march);}
					}
					bord=BORD;
					if(bloque&&!backg->get_xs())
						bord=PETIT_BORD;
				}
				else mike->next_frame();

				for(int s=0;s<sol->get_nbo();s++)
				{
					if(mike->collision_g(sol->get_stage(s),h,b,g,d))
					{
						mike->get_xs()=sol->get_stage(s)->get_xs()+sol->get_stage(s)->get_wt()-g;
						break;
					}
				}

				SDL_mutexV(mik);
			}
			//les deux boutons sont appuyes
			else if(keys[SDLK_LEFT]&&keys[SDLK_RIGHT])
			{
				if(evt==dte)
				{
					//on va a droite
					SDL_mutexP(mik);
					mike->get_dg()='d';
					if ((!keys[SDLK_DOWN]||enlair2))
					{
						mike->avance(cour_march);
						if(mike->get_xs()>640-mike->get_wt()-bord)
						{
							backg->avance(cour_march);
							pancarte->avance(cour_march);
							{for(int i=0;i<sol->get_nbo();i++)
								sol->get_stage(i)->avance(cour_march);}
							{for(int i=0;i<piece->get_nbo();i++)
								piece->get_stage(i)->avance(cour_march);}
							{for(int a=0;a<all_enn->get_nball();a++)
								for(int i=0;i<all_enn->get_ennall(a)->get_nbo();i++)
									all_enn->get_ennall(a)->get_stage(i)->avance(cour_march);}
						}
						bord=BORD;
						if(bloque&&backg->get_xs())
							bord=PETIT_BORD;
					}
					else mike->next_frame();

					for(int s=0;s<sol->get_nbo();s++)
					{
						if(mike->collision_d(sol->get_stage(s),h,b,g,d))
						{
							mike->get_xs()=sol->get_stage(s)->get_xs()-mike->get_wt()+d;
							break;
						}
					}

					SDL_mutexV(mik);
				}
				else if(evt==gch)
				{
					//on va a gauche
					SDL_mutexP(mik);
					mike->get_dg()='g';
					if ((!keys[SDLK_DOWN]||enlair2))
					{
						mike->recule(cour_march);
						if(mike->get_xs()<bord)
						{
							backg->recule(cour_march);
							pancarte->recule(cour_march);
							{for(int i=0;i<sol->get_nbo();i++)
								sol->get_stage(i)->recule(cour_march);}
							{for(int i=0;i<piece->get_nbo();i++)
								piece->get_stage(i)->recule(cour_march);}
							{for(int a=0;a<all_enn->get_nball();a++)
								for(int i=0;i<all_enn->get_ennall(a)->get_nbo();i++)
									all_enn->get_ennall(a)->get_stage(i)->recule(cour_march);}
						}

						bord=BORD;
						if(bloque&&!backg->get_xs())
							bord=PETIT_BORD;
					}
					else mike->next_frame();

					for(int s=0;s<sol->get_nbo();s++)
					{
						if(mike->collision_g(sol->get_stage(s),h,b,g,d))
						{
							mike->get_xs()=sol->get_stage(s)->get_xs()+sol->get_stage(s)->get_wt()-g;
							break;
						}
					}

					SDL_mutexV(mik);
				}
			}

			//on regarde si on est sur une plateforme
			SDL_mutexP(mik);

			if(!enlair2)
			{
				mike->get_ys()+=PAS_TOMBER;
				if(!keys[SDLK_LEFT]&&!keys[SDLK_RIGHT]) SDL_Delay(TPS_MARCHE);
				int s;
				for(s=0;s<sol->get_nbo();s++)
				{
					if(mike->collision_b(sol->get_stage(s),h,b,g,d))
					{
						mike->get_ys()=sol->get_stage(s)->get_ys()-mike->get_ht();
						tomber=0;
						break;
					}
				}
				if(s==sol->get_nbo()) tomber=1;
			}
			if(mike->get_ys()>480)
			{
				death=-2;
				SDL_mutexV(mik);
				break;
			}

			SDL_mutexV(mik);



			SDL_mutexP(mik);
			//on regarde si on touche une piece
			for(int p=0;p<piece->get_nbo();p++)
			{
				if(mike->collision(piece->get_stage(p),h,b,g,d)&&
					piece->get_stage(p)->get_aff()==1)
				{
					piece->get_stage(p)->get_aff()=0;
					cling->play_chunk();
					score+=20;
				}
			}
			SDL_mutexV(mik);


			SDL_mutexP(mik);
			for(int a=0;a<all_enn->get_nball();a++)
			{
				for(int i=0;i<all_enn->get_ennall(a)->get_nbo();i++)
					if(mike->collision(all_enn->get_ennall(a)->get_stage(i),h,b,g,d)&&
						all_enn->get_ennall(a)->get_stage(i)->get_aff())
					{
						death=a;
						break;
					}
				if(death!=-1)
					break;
			}
			if(death!=-1)
			{
				SDL_mutexV(mik);
				break;
			}
			SDL_mutexV(mik);


			//on dessine la scene est on laisse un espace de 10 ms
			drawscene();
			SDL_Delay(RAFFRAICHISSEMENT);

			//changement de niveau
			//a effacer plus tard
			if(mike->collision(pancarte,h,b,g,d))
			{
				bloque=1;
				level=!level;
				cour_march=MARCHE;
				enlair=0;
				enlair2=0;
				tomber=1;
				bord=BORD;
				h=0;
				b=0;
				g=0;
				d=0;
				corb=0;
				death=-1;
				nb_corb=CORB;
				evt=z;

				if(level==NB_LEVEL)
					break;

				
				//reinitialisation des varibales
				initialisation();
			}
		}

		//on arrete toutes les threads
		destroy_thread();

		Mix_HaltMusic();


		if(death>=0)
		{
			int affiche;
			matrice * m=new matrice;
			init_lib(DATA_PATH"libellule");
			
			do
			{
				affiche=0;

				drawscene();

				for(int l=0;l<lib->get_nbo();l++)
				{
					m->add(lib->get_stage(l)->get_xs()+lib->get_stage(l)->get_wt()/2,
						lib->get_stage(l)->get_ys()+lib->get_stage(l)->get_ht()/2);
					lib->get_stage(l)->mov();
					lib->get_stage(l)->draw(screen);
					affiche+=lib->get_stage(l)->get_aff();
				}
			
				for(int p=0;p<m->get_dim1();p++)
				{
					point->get_xs()=m->get_case(p,0);
					point->get_ys()=m->get_case(p,1);
					point->draw(screen);
				}
				SDL_Flip(screen);
				SDL_Delay(TPS_LIB);
			}
			while(affiche);


			delete m;
			m=NULL;
			
		}
		else if(death==-2)
		{
			delete ange;
			ange=new decor_obj;
			if(mike->get_dg()=='d')
				ange->init(fange,1,'d');
			else ange->init(fange,1,'g');
			ange->get_xs()=mike->get_xs();
			ange->get_ys()=-ange->get_ht();
			ange->set_proto(1,new bottom(PAS_ANGE));
			do
			{
				ange->mov();
				drawscene();
				ange->draw(screen);
				SDL_Flip(screen);
				SDL_Delay(TPS_ANGE);
			}
			while(ange->get_aff());
			ange->next_frame();
			ange->get_ys()=480;
			ange->set_proto(1,new top(PAS_ANGE));
			ange->get_aff()=1;
			do
			{
				ange->mov();
				drawscene();
				ange->draw(screen);
				SDL_Flip(screen);
				SDL_Delay(TPS_ANGE);
			}
			while(ange->get_aff());
		}
		else if(death==-1&&level==NB_LEVEL)
		{
			finjeu=1;
			int decal=d20->get_w()+20;
			for(int i=480,fin=480;fin+d20->get_w()>0;i-=5)
			{
				SDL_FillRect(screen,NULL,0);
				d20->drawstring_w(screen,i,"C moi, MIKE, qui");
				d20->drawstring_w(screen,i+decal,"est fait tout ce ...");
				d20->drawstring_w(screen,fin=i+4*decal,"JEU");
				SDL_Flip(screen);
				SDL_Delay(20);
			}
		}



		if(death==-2||death>=0)
		{
			drawscene();

			voile_noir->draw(screen);
			f100->drawstring_w(screen,50,"YOU");
			f100->drawstring_w(screen,200,"LOSE");
			SDL_Flip(screen);
			SDL_Delay(2000);

			mike->get_vie()--;
			bloque=1;
			cour_march=MARCHE;
			enlair=0;
			enlair2=0;
			tomber=1;
			bord=BORD;
			h=0;
			b=0;
			g=0;
			d=0;
			finjeu=0;
			nb_corb=CORB;
			event.type=-1;
			corb=0;
			death=-1;
			jauge=TAILLE_JAUGE;
			evt=z;

			if(mike->get_vie()<0)
			{
				mike->get_vie()=0;

				int fin=0;
				enum e_regame choix=oui;
				
				menu_regame(choix);

				while(!fin)
				{
					SDL_PollEvent(&event);

					if(event.type==SDL_QUIT) break;
					if(event.type==SDL_KEYDOWN)
					{
						switch(event.key.keysym.sym)
						{
							case SDLK_DOWN :
								if(choix==non)
									choix=oui;
								else ((int &)choix)++;
								menu_regame(choix);
								break;
							case SDLK_UP :
								if(choix==oui)
									choix=non;
								else ((int &)choix)--;
								menu_regame(choix);
								break;
							case SDLK_RETURN :
								fin=1;
								if(choix==non) finjeu=1;
								break;
						}
					}
				}
				bloque=1;
				level=0;
				cour_march=MARCHE;
				enlair=0;
				enlair2=0;
				tomber=1;
				bord=BORD;
				h=0;
				b=0;
				g=0;
				mike->get_vie()=VIE;
				nb_corb=CORB;
				event.type=-1;
				d=0;
				corb=0;
				death=-1;
				jauge=TAILLE_JAUGE;
				evt=z;
				score=0;

			}
		}
	}
	while(!finjeu);

	destroy_all();

	return 0;
}





void erreur(char * s,...)
{
	va_list ap;
	
	va_start(ap,s);
	vprintf(s,ap);
	va_end(ap);

	destroy_all();
	exit(-1);
}


void drawscene(int f)
{
	SDL_mutexP(mut);

	SDL_mutexP(mut_dec);
	backg->draw(screen);
	pancarte->draw(screen);
	{for(int i=0;i<sol->get_nbo();i++)
		sol->get_stage(i)->draw(screen);}
	{for(int i=0;i<piece->get_nbo();i++)
		piece->get_stage(i)->draw(screen);}
	SDL_mutexV(mut_dec);

	{
		for(int i=0;i<all_enn->get_nball();i++)
		{
			SDL_mutexP(all_enn->get_mutall(i));
			for(int j=0;j<all_enn->get_ennall(i)->get_nbo();j++)
				all_enn->get_ennall(i)->get_stage(j)->draw(screen);
			SDL_mutexV(all_enn->get_mutall(i));
		}
	}


	SDL_mutexP(mik);
	mike->draw(screen);
	SDL_mutexV(mik);
	{for(int i=0;i<NB_BOULE;i++)
		boule[i]->draw(screen);}
	kame->draw(screen);

	ee20->drawstring(screen,10,5,"SCORE : %d",score);
	ee20->drawstring(screen,440,5,"VIE : %d",mike->get_vie());

	int Y=5+ee20->get_w()+10;
	ee20->drawstring(screen,10,Y,"KAME : ");
	jauge_kame->get_ys()=Y+ee20->get_w()/2-jauge_kame->get_ht()/2;
	jauge_kame->get_xs()=150;
	jauge_kame->remplir(255,0,0);
	jauge_kame->drawt(screen);
	jauge_kame->remplir(0,0,255);
	jauge_kame->get_w()=jauge;
	jauge_kame->draw(screen);


	if(f) SDL_Flip(screen);

	SDL_mutexV(mut);
}


void initialisation()
{
	destroy_thread();

	th_piece=new thread;
	th_boule=new thread;
	th_saut=new thread;
	th_jauge=new thread;



	//pour le background
	delete backg;
	backg=new bg;
	backg->init_pos(DATA_PATH"decor",fbg,level);

	//pour initialisation des sol
	delete sol;
	sol=new stage<decor_obj>;
	sol->init_pos_obj(DATA_PATH"objet/sol",fsol,level);

	//pour initialiser les piece
	delete piece;
	piece=new stage<decor_obj>;
	piece->init_pos_obj(DATA_PATH"objet/piece",fpiece,level);
	{for(int i=0;i<piece->get_nbo();i++)
		piece->get_stage(i)->set_proto(1,new tourner);}

	//on place la pancarte de sortie de niveau
	delete pancarte;
	pancarte=new decor_obj;
	pancarte->init_pos(DATA_PATH"objet/pancarte",fpancarte,level);
	pancarte->tombe((stage<sprite> *)sol);

	//memorise le nb de vie restant
	int nbvie=mike->get_vie();
	char * nom=_strdup(mike->get_nom());
	//pour initialiser le hero
	delete mike;
	mike=new hero;
	mike->init_pos(DATA_PATH"perso/marcher",fmarcher,level);
	mike->tombe((stage<sprite> *)sol);
	mike->get_vie()=nbvie;
	mike->set_nom(nom);
	delete [] nom;

	for( int i = 0; i < NB_BOULE; i++ )
		delete boule[i];
	delete [] boule;
	boule=new decor_obj * [NB_BOULE];
	{for(int i=0;i<NB_BOULE;i++)
		boule[i]=new decor_obj;}

	delete kame;
	kame=new decor_obj;

	{
		for(int i=0;i<NB_BOULE;i++)
		{
			boule[i]->get_aff()=0;
			boule[i]->get_a()=0;
		}
	}
	
	kame->get_aff()=0;
	kame->get_a()=0;


	delete all_enn;
	all_enn=new all_ennemi;

	all_enn->add(DATA_PATH"ennemi/essai",fessai,level,TPS_MARCHE_ESSAI,PAS_ESSAI);
	all_enn->add(DATA_PATH"ennemi/essaii",fessaii,level,TPS_MARCHE_ESSAII,PAS_ESSAII);
	all_enn->add(DATA_PATH"ennemi/essaiii",fessaiii,level,TPS_MARCHE_ESSAIII,PAS_ESSAIII);

	{for(int i=0;i<all_enn->get_nball();i++)
		for(int j=0;j<all_enn->get_ennall(i)->get_nbo();j++)
			all_enn->get_ennall(i)->get_stage(j)->tombe((stage<sprite> *)sol);}


	delete back_music;
	back_music=new music;
	back_music->init_music(DATA_PATH"son/back",level);
	back_music->play_music();

	delete kameha;
	kameha=new sound;
	kameha->init_sound(DATA_PATH"son/kame");

	delete cling;
	cling=new sound;
	cling->init_sound(DATA_PATH"son/piece");

	delete explose;
	explose=new sound;
	explose->init_sound(DATA_PATH"son/boum");


	th_piece->init_th(1);
	//le zero signifie que toutes les pieces font parties d'un seul thread
	th_piece->run_th(thread_piece,(stage<sprite> *)piece,0);

	th_boule->init_th(1);

	th_saut->init_th(1);

	th_jauge->init_th(1);
	th_jauge->run_th(thread_jauge,(sprite *)NULL);

	{for(int i=0;i<all_enn->get_nball();i++)
		//le 1 c'est pour que chaque ennemi soit un thread
		all_enn->lancer_thread(thread_ennemi,1,i);}


	


	//scene de départ
	drawscene();

}

void destroy_thread()
{
	//arrete les threads
	delete th_piece;
	th_piece=NULL;
	delete th_boule;
	th_boule=NULL;
	delete th_saut;
	th_saut=NULL;
	delete th_jauge;
	th_jauge=NULL;

	for(int a=0;all_enn && a<all_enn->get_nball();a++)
	{
		delete all_enn->get_thall(a);
		all_enn->get_thall(a)=NULL;
	}
}

void destroy_all()
{
	destroy_thread();

	delete all_enn;

	//arrete la music
	delete back_music;
	delete kameha;
	delete cling;
	delete explose;

	//delete les font
	delete e20;
	delete ee20;
	delete f100;
	delete g50;

	//delete les objets simples
	delete backg;
	delete mike;
	delete pancarte;
	for( int i = 0; i < NB_BOULE; i++ )
		delete boule[i];
	delete [] boule;
	delete kame;
	delete point;

	//effece les divers
	delete fleche;
	delete pres;
	delete voile_noir;

	//detruit les stages
	delete sol;
	delete piece;
	delete lib;
	delete corbeau;

	//on detruit les mutex
	SDL_DestroyMutex(mut);
	SDL_DestroyMutex(air);
	SDL_DestroyMutex(stop);
	SDL_DestroyMutex(mik);
	SDL_DestroyMutex(mut_dec);

	//on delete toutes les frames
	delete fbaisser;
	delete fmarcher;
	delete fsaut;
	delete fattack1;
	delete fattack2;
	delete fboulep;
	delete fkamep;
	delete fbg;
	delete fboule;
	delete fkame;
	delete fsol;
	delete fpiece;
	delete fpancarte;

	delete flib;
	delete fcorbeau;
	delete fpoint;

	delete fpres;
	delete ffleche;

	delete ficone;

	delete fessai;
	delete fessaii;
	delete fessaiii;

}













void menu_touche()
{
	SDL_Event event;
	int decal=20;
	int posy=100;
	int posx=50;

	SDL_FillRect(screen,NULL,0);

	g50->drawstring_w(screen,10,"TUTORIAL");

	d20->drawstring(screen,posx,				posy,"%c/%c:",(char)30,(char)31);
	e20->drawstring(screen,posx+d20->get_w()*4,	posy,"DEPLACER");
	d20->drawstring(screen,posx+d20->get_w()*18,posy,"%c:",(char)29);
	e20->drawstring(screen,posx+d20->get_w()*20,posy,"BAISSER");
	d20->drawstring(screen,posx,				posy+=e20->get_w()+decal,"SHIFT:");
	e20->drawstring(screen,posx+d20->get_w()*6,	posy,"COURIR");
	d20->drawstring(screen,posx,				posy+=e20->get_w()+decal,"S:");
	e20->drawstring(screen,posx+d20->get_w()*2,	posy,"SAUTER");
	d20->drawstring(screen,posx,				posy+=e20->get_w()+decal,"D/C:");
	e20->drawstring(screen,posx+d20->get_w()*4,	posy,"COUP DE POING (inutile)");
	d20->drawstring(screen,posx,				posy+=e20->get_w()+decal,"F:");
	e20->drawstring(screen,posx+d20->get_w()*2,	posy,"BOULE");
	d20->drawstring(screen,posx,				posy+=e20->get_w()+decal,"V:");
	e20->drawstring(screen,posx+d20->get_w()*2,	posy,"KAME");
	d20->drawstring(screen,posx,				posy+=e20->get_w()+decal,"PAGEUP->HOME->INSERT:");
	e20->drawstring(screen,posx+d20->get_w()*21,posy,"CORBEAU");
	d20->drawstring(screen,posx,				posy+=e20->get_w()+decal,"SPACE:");
	e20->drawstring(screen,posx+d20->get_w()*6,	posy,"MENU");
	d20->drawstring(screen,posx,				posy+=e20->get_w()+decal,"ESC:");
	e20->drawstring(screen,posx+d20->get_w()*4,	posy,"QUITTER");
	SDL_Flip(screen);
	
	int fin=0;
	while(!fin)
	{
		SDL_PollEvent(&event);

		if(event.type==SDL_QUIT)
		{
			destroy_all();
			exit(0);
		}
		if(event.type==SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE :
					fin=1;
					break;
			}
		}
	}
}

void presentation(enum e_pres choix)
{
	int instry=300;
	int jeuy=400;
	int flechex=10;

	pres->draw(screen);
	g50->drawstring_w(screen,instry,"INSTR");
	g50->drawstring_w(screen,jeuy,"JEU");
	if(choix==instr)
		fleche->get_ys()=instry+g50->get_w()/2-fleche->get_ht()/2;
	else if(choix==jeu)
		fleche->get_ys()=jeuy+g50->get_w()/2-fleche->get_ht()/2;
	fleche->get_xs()=flechex;
	fleche->draw(screen);
	SDL_Flip(screen);

}


void menu_regame(enum e_regame choix)
{
	int questy=150;
	int ouiy=250;
	int nony=300;
	int flechex=50;

	drawscene(0);
	voile_noir->draw(screen);
	e20->drawstring_w(screen,questy,"Play Again ?");
	e20->drawstring_w(screen,ouiy,"OUI");
	e20->drawstring_w(screen,nony,"NON");
	if(choix==oui)
		fleche->get_ys()=ouiy+e20->get_w()/2-fleche->get_ht()/2;
	else if(choix==non)
		fleche->get_ys()=nony+e20->get_w()/2-fleche->get_ht()/2;
	fleche->get_xs()=flechex;
	fleche->draw(screen);
	SDL_Flip(screen);

}

void menu(enum e_menu choix)
{
	SDL_Rect rect;	
	surface * highlight=new surface;
	highlight->init(screen,200,50);
	
	Uint32 back=SDL_MapRGB(screen->format,0,0,0);
	Uint32 high=SDL_MapRGB(highlight->get_surface()->format,255,255,0);

	

	SDL_FillRect(screen,NULL,back);
	g50->drawstring_w(screen,10,"MENU");



	int X=50,Y=100,W=150,H=170;

	rect.h=H;
	rect.w=W;
	rect.x=X;
	rect.y=Y;
	SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,0,200,200));
	rect.x=X+W/2-mike->get_wt()/2;
	rect.y=Y+H/2-mike->get_ht()/2;
	SDL_BlitSurface(mike->get_img(),NULL,screen,&rect);

	d20->drawstring(screen,50,300,"SCORE : %d",score);
	d20->drawstring(screen,50,350,"LIVE : %d",mike->get_vie());
	d20->drawstring(screen,50,400,"LEVEL : %d",level);


	highlight->get_xs()=400;
	highlight->get_ys()=80;
	highlight->remplir(back);
	d20->drawstring_center(highlight->get_surface(),"STATUS");
	if(choix==e_status)
	{
		highlight->remplir(high);
		ee20->drawstring_center(highlight->get_surface(),"STATUS");
	}
	highlight->drawt(screen);
	
	highlight->get_ys()=140;
	highlight->remplir(back);
	d20->drawstring_center(highlight->get_surface(),"TUTORIAL");
	if(choix==e_touche)
	{
		highlight->remplir(high);
		ee20->drawstring_center(highlight->get_surface(),"TUTORIAL");
	}
	highlight->drawt(screen);

	highlight->get_ys()=200;
	highlight->remplir(back);
	d20->drawstring_center(highlight->get_surface(),"NAME");
	if(choix==e_nom)
	{
		highlight->remplir(high);
		ee20->drawstring_center(highlight->get_surface(),"NAME");
	}
	highlight->drawt(screen);

	highlight->get_ys()=400;
	highlight->remplir(back);
	d20->drawstring_center(highlight->get_surface(),"QUITTER");
	if(choix==e_fin)
	{
		highlight->remplir(high);
		ee20->drawstring_center(highlight->get_surface(),"QUITTER");
	}
	highlight->drawt(screen);

	SDL_Flip(screen);

	delete highlight;
	highlight=NULL;

}


void menu_statut()
{
	frame * fface=new frame(DATA_PATH"exterieur/face");
	decor_obj * face=new decor_obj;
	
	face->init(fface,0);

	SDL_FillRect(screen,NULL,0);
	g50->drawstring_w(screen,10,"STATUS");



	int X=50,Y=100,W=100,H=120,decalx=70,decaly=50;
	SDL_Rect rect;

	rect.h=H;
	rect.w=W;
	rect.x=X;
	rect.y=Y;
	SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,100,200,100));
	face->get_xs()=X+W/2-face->get_wt()/2;
	face->get_ys()=Y+H/2-face->get_ht()/2;
	face->draw(screen);


	if(!mike->get_nom()) d20->drawstring(screen,X+W+decalx,Y+H/2-d20->get_w(),"Mr Anonyme");
	else d20->drawstring(screen,X+W+decalx,Y+H/2-d20->get_w(),mike->get_nom());
	
	d20->drawstring(screen,X,Y+H+decaly,"LIVE : %d",mike->get_vie());
	d20->drawstring(screen,640/2,Y+H+decaly,"CORBEAU : %d",nb_corb);
	d20->drawstring(screen,X,Y+H+decaly+d20->get_w()+decaly,"HEIGHT : %d",mike->get_ht());
	d20->drawstring(screen,X,Y+H+2*(decaly+d20->get_w())+decaly,"WIDTH : %d",mike->get_wt());

	Y=Y+H+decaly+d20->get_w()+decaly;
	d20->drawstring(screen,640/2,Y,"KAME : ");
	jauge_kame->get_xs()=640/2+d20->get_w()*7;
	jauge_kame->get_ys()=Y+d20->get_w()/2-jauge_kame->get_ht()/2;
	jauge_kame->remplir(255,0,0);
	jauge_kame->drawt(screen);
	jauge_kame->remplir(0,0,255);
	jauge_kame->get_w()=jauge;
	jauge_kame->draw(screen);


	
	SDL_Flip(screen);

	delete fface;
	fface=NULL;
	delete face;
	face=NULL;

	int fin=0;
	SDL_Event event;
	while(!fin)
	{
		SDL_PollEvent(&event);

		if(event.type==SDL_QUIT)
		{
			destroy_all();
			exit(0);
		}
		if(event.type==SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE :
					fin=1;
					break;
			}
		}
	}
}

void menu_nom()
{
	frame * fboutton=new frame(DATA_PATH"exterieur/alpha");
	decor_obj * bspace=new decor_obj;
	decor_obj * ok=new decor_obj;
	surface * zone_nom=new surface(screen,600,100);
	Uint32 back=SDL_MapRGB(screen->format,0,0,0);
	Uint32 zn=SDL_MapRGB(screen->format,0,0,255);
	int X,Y,espace=10,nb_colonne=16,nb_ligne=1;
	matrice * col=new matrice;
	matrice * lig=new matrice;
	int nb_lettre=8;
	int nb_pourcent=0;
	char * name=NULL;
	
	if(!mike->get_nom())
	{
		name=(char *)malloc(sizeof(char));
		name[0]='\0';
	}
	else name=_strdup(mike->get_nom());

	bspace->init(fboutton,1,'a');
	bspace->get_xs()=20;
	bspace->get_ys()=380;
	ok->init(fboutton,2,'a');
	ok->get_xs()=420;
	ok->get_ys()=380;
	zone_nom->remplir(zn);
	zone_nom->get_xs()=20;
	zone_nom->get_ys()=250;


	SDL_ShowCursor(SDL_ENABLE);
	SDL_WarpMouse(screen->w/2,screen->h/2);

	SDL_FillRect(screen,NULL,back);
	g50->drawstring_w(screen,10,"HERO'S NAME");
	g50->drawstring_center(zone_nom->get_surface(),name);
	zone_nom->drawt(screen);
	bspace->draw(screen);
	ok->draw(screen);
	Y=10+g50->get_w()+espace;
	X=(640-(((nb_colonne-1)*(d20->get_w()+espace))+d20->get_w()))/2;
	lig->add(Y,Y+d20->get_w());
	col->add(X,X+d20->get_w());
	for(int i=32,l=1;i<127;i++,l++)
	{
		d20->drawstring(screen,X,Y,"%c",(char)i);
		X+=d20->get_w()+espace;
		if(Y==10+g50->get_w()+espace&&l%nb_colonne) col->add(X,X+d20->get_w());
		if(!(l%nb_colonne))
		{
			X=(640-(((nb_colonne-1)*(d20->get_w()+espace))+d20->get_w()))/2;
			Y+=d20->get_w()+espace;
			lig->add(Y,Y+d20->get_w());
			nb_ligne++;
		}
	}
	SDL_Flip(screen);

	SDL_Event event;
	int fin=0;
	while (!fin)
	{
		SDL_PollEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT :
				destroy_all();
				exit(0);
				break;
		    case SDL_MOUSEBUTTONUP :
				if (event.button.button==SDL_BUTTON_LEFT)
				{
					if((event.button.x>=ok->get_xs())&&
						(event.button.x<=ok->get_xs()+ok->get_wt())&&
						(event.button.y>=ok->get_ys())&&
						(event.button.y<=ok->get_ys()+ok->get_ht()))
					{
						mike->set_nom(name);
						fin=1;
						break;
					}
					else if((event.button.x>=bspace->get_xs())&&
						(event.button.x<=bspace->get_xs()+bspace->get_wt())&&
						(event.button.y>=bspace->get_ys())&&
						(event.button.y<=bspace->get_ys()+bspace->get_ht()))
					{
						if(strlen(name)>0)
							if((int)name[strlen(name)-1]==37)
							{
								name[strlen(name)-2]='\0';
								nb_pourcent--;
							}
							else name[strlen(name)-1]='\0';
						zone_nom->remplir(zn);
						g50->drawstring_center(zone_nom->get_surface(),name);
						zone_nom->drawt(screen);
						SDL_Flip(screen);
					}
					for(int i=0;i<lig->get_dim1();i++)
					{
						for(int j=0;j<col->get_dim1();j++)
						{
							int code=16*i+j+32;
							
							if(event.button.x>=col->get_case(j,0)&&
								event.button.x<=col->get_case(j,1)&&
								event.button.y>=lig->get_case(i,0)&&
								event.button.y<=lig->get_case(i,1)&&
								code!=127&&
								(int)strlen(name)<(8+nb_pourcent))
							{
								//2=1+1
								//1 : ajout du caractere
								//1 : prise en compte du caractere \0
								if(code==37)
								{
									name=(char *)realloc(name,
										(strlen(name)+3)*sizeof(char));
									name[strlen(name)+2]='\0';
									name[strlen(name)+1]=(char)code;
									name[strlen(name)]=(char)code;
									nb_pourcent++;
								}
								else
								{
									name=(char *)realloc(name,
										(strlen(name)+2)*sizeof(char));
									name[strlen(name)+1]='\0';
									name[strlen(name)]=(char)code;
								}
								zone_nom->remplir(zn);
								g50->drawstring_center(zone_nom->get_surface(),name);
								zone_nom->drawt(screen);
								SDL_Flip(screen);
							}
						}
					}
				}
				break;
			default : break;
		}
	}


	delete name;
	delete zone_nom;
	delete fboutton;
	delete ok;
	delete bspace;
	zone_nom=NULL;
	fboutton=NULL;
	ok=NULL;
	bspace=NULL;
	free(name);



	SDL_ShowCursor(SDL_DISABLE);
}