#include "sprite.h"

sprite::sprite()
{
	x=y=w=h=xscreen=yscreen=wtotal=htotal=0;
	ssprite=NULL;
	frames=NULL;
	step=2;
	anim=1;
	dg='d';
	aff=1;
}

sprite::sprite(const sprite & d)
{
	yscreen=d.yscreen;
	xscreen=d.xscreen;
	x=d.x;
	y=d.y;
	wtotal=d.wtotal;
	htotal=d.htotal;
	frames=d.frames;
	h=d.h;
	htotal=d.htotal;
	w=d.w;
	wtotal=d.wtotal;
	ssprite=d.ssprite;
	anim=d.anim;
	step=d.step;
	dg=d.dg;
	aff=d.aff;
}

sprite::~sprite()
{
	ssprite=NULL;
	frames=NULL;
}

void sprite::set_f(frame * f)
{
	frames=f;
	w=wtotal=f->get_img(0)->w;
	h=htotal=f->get_img(0)->h;
}

void sprite::drawimg(SDL_Surface * s,int x,int y,int w,int h,int xd,int yd)
{
	SDL_Rect destd;
	destd.x = xd;
	destd.y = yd;
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	SDL_BlitSurface(ssprite,&dest,s,&destd);
}

void sprite::draw(SDL_Surface * s)
{
	if(aff)
		drawimg(s,x,y,w,h,xscreen,yscreen);
}

void sprite::init(frame * f,int i)
{
	if(i>f->get_nbf())
		erreur("avec l'indice i dans init");

	frames=f;
	x=y=0;
	w=wtotal=f->get_img(i)->w;
	h=htotal=f->get_img(i)->h;

	ssprite=f->get_img(i);

	anim=1;
	aff=1;
	step=2;
	dg=f->get_direct(i);
}

void sprite::init(frame * f,int prio,char direct)
{
	int i;

	for(i=0;(i<f->get_nbf())&&((f->get_prio(i)!=prio)||(f->get_direct(i)!=direct));i++) ;
	if(i==f->get_nbf()) erreur("init avec priorite et direction");

	frames=f;
	x=y=0;
	w=wtotal=f->get_img(i)->w;
	h=htotal=f->get_img(i)->h;

	anim=1;
	aff=1;
	step=2;
	dg=direct;

	ssprite=f->get_img(i);
	
}

void sprite::init(frame * f,char * c)
{
	int i;
	for(i=0;(i<f->get_nbf())&&(strcmp(f->get_nom(i),c)!=0);i++) ;
	if(i==f->get_nbf()) erreur("init avec nom fichier");

	frames=f;
	x=y=0;
	w=wtotal=f->get_img(i)->w;
	h=htotal=f->get_img(i)->h;
	anim=1;
	aff=1;
	step=2;
	dg=f->get_direct(i);

	ssprite=f->get_img(i);
}


void sprite::init_pos(char * dir,frame * f,int levl)
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
			
			if(nbo>1||nbo<0)
				erreur("probleme init de la position d'1 sprite");

			if(nbo==1)
			{
				fscanf(fd,"%s%d%d",name,&posx,&posy);
				init(f,name);
				xscreen=posx;
				yscreen=posy;
			}
			break;
		}
		else
		{
			fscanf(fd,"%d",&nbo);
			if(nbo==1) fscanf(fd,"%s%d%d",name,&posx,&posy);
		}

	}
	if(lv!=levl) erreur("manqueeeeee des trucs dans fichier position");
	fclose(fd);
}

void sprite::next_frame()
{
	int i;
	for(i=0;i<get_f()->get_nbf();i++)
	{
		if((get_step()==get_f()->get_prio(i))&&(get_f()->get_direct(i)==get_dg()))
		{
			get_img()=get_f()->get_img(i);
			w=wtotal=get_f()->get_img(i)->w;
			h=htotal=get_f()->get_img(i)->h;
			break;
		}
	}
	if(i==get_f()->get_nbf())
	{
		get_step()=1;
		for(int i=0;i<get_f()->get_nbf();i++)
		{
			if((get_step()==get_f()->get_prio(i))&&(get_f()->get_direct(i)==get_dg()))
			{
				get_img()=get_f()->get_img(i);
				w=wtotal=get_f()->get_img(i)->w;
				h=htotal=get_f()->get_img(i)->h;
				break;
			}
		}
	}
	get_step()++;
}

int sprite::collision(sprite * s,int haut,int bas,int gauche,int droite)
{
	int bottom,top,left,right;
	int sbottom,stop,sleft,sright;

	bottom=get_ys()+get_ht()-bas;
	top=get_ys()+haut;
	right=get_xs()+get_wt()-droite;
	left=get_xs()+gauche;
	sbottom=s->get_ys()+s->get_ht();
	stop=s->get_ys();
	sright=s->get_xs()+s->get_wt();
	sleft=s->get_xs();

	if(bottom<stop)	return 0;
	if(top>sbottom)	return 0;
	if(right<sleft)	return 0;
	if(left>sright)	return 0;

	return 1;
	
}

int sprite::collision_b(sprite * s,int haut,int bas,int gauche,int droite)
{
	int bottom,top,left,right;
	int sbottom,stop,sleft,sright;

	bottom=get_ys()+get_ht()-bas;
	top=get_ys()+haut;
	right=get_xs()+get_wt()-droite;
	left=get_xs()+gauche;
	sbottom=s->get_ys()+s->get_ht();
	stop=s->get_ys();
	sright=s->get_xs()+s->get_wt();
	sleft=s->get_xs();

	if(right<=sleft)	return 0;
	if(left>=sright)	return 0;
	if(bottom<stop)	return 0;
	if(top>=sbottom)	return 0;

	return 1;
	
}

int sprite::collision_h(sprite * s,int haut,int bas,int gauche,int droite)
{
	int bottom,top,left,right;
	int sbottom,stop,sleft,sright;

	bottom=get_ys()+get_ht()-bas;
	top=get_ys()+haut;
	right=get_xs()+get_wt()-droite;
	left=get_xs()+gauche;
	sbottom=s->get_ys()+s->get_ht();
	stop=s->get_ys();
	sright=s->get_xs()+s->get_wt();
	sleft=s->get_xs();

	if(right<=sleft)	return 0;
	if(left>=sright)	return 0;
	if(top>sbottom)	return 0;
	if(bottom<=stop)	return 0;

	return 1;
	
}

int sprite::collision_g(sprite * s,int haut,int bas,int gauche,int droite)
{
	int bottom,top,left,right;
	int sbottom,stop,sleft,sright;

	bottom=get_ys()+get_ht()-bas;
	top=get_ys()+haut;
	right=get_xs()+get_wt()-droite;
	left=get_xs()+gauche;
	sbottom=s->get_ys()+s->get_ht();
	stop=s->get_ys();
	sright=s->get_xs()+s->get_wt();
	sleft=s->get_xs();

	if(bottom<=stop)	return 0;
	if(top>=sbottom)	return 0;
	if(left>sright)	return 0;
	if(right<=sleft)	return 0;

	return 1;
	
}

int sprite::collision_d(sprite * s,int haut,int bas,int gauche,int droite)
{
	int bottom,top,left,right;
	int sbottom,stop,sleft,sright;

	bottom=get_ys()+get_ht()-bas;
	top=get_ys()+haut;
	right=get_xs()+get_wt()-droite;
	left=get_xs()+gauche;
	sbottom=s->get_ys()+s->get_ht();
	stop=s->get_ys();
	sright=s->get_xs()+s->get_wt();
	sleft=s->get_xs();

	if(bottom<=stop)	return 0;
	if(top>=sbottom)	return 0;
	if(right<sleft)	return 0;
	if(left>=sright)	return 0;

	return 1;
	
}



void sprite::tombe(stage<sprite> * st)
{
	if(get_img())
		for(;;)
		{
			int s;
			for(s=0;s<st->get_nbo();s++)
			{
				if(collision_b(st->get_stage(s),0,0,0,0))
				{
					get_ys()=st->get_stage(s)->get_ys()-get_ht();
					break;
				}
			}
			if(s==st->get_nbo()) get_ys()+=PAS_TOMBER;
			else break;
			if(get_ys()>480)
			{
				get_aff()=0;
				get_a()=0;
				erreur("c'est tombe dans un trou!!!!");
				break;
			}
		}
	else
	{
		get_a()=0;
		get_aff()=0;
	}
}