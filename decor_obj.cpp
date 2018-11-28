#include "decor_obj.h"

decor_obj::~decor_obj()
{
	get_img()=NULL;
	get_f()=NULL;
	for(int i=0;i<dim;i++)
		delete proto[i];
	delete[] proto;
	proto=NULL;
}


void decor_obj::set_proto(int d,mvt * m1,...)
{
	va_list vl;

	for(int j=0;j<dim;j++) delete proto[j];
	delete [] proto;
	proto=NULL;

	dim=d;
	proto=new mvt * [d];
	va_start(vl,m1);
	proto[0]=m1;
	for(int i=1;i<d;i++)
		proto[i]=va_arg(vl,mvt *);
	va_end(vl);

}

void decor_obj::avance(int d)
{
	extern int bloque;
	extern int decal;
	extern SDL_mutex * mut_dec;

	SDL_mutexP(mut_dec);

	if(!bloque)
		get_xs()=get_xs()-d;
	else if(bloque==1)
		get_xs()=get_xs()-decal;

	SDL_mutexV(mut_dec);
}

void decor_obj::recule(int d)
{
	extern int bloque;
	extern int decal;
	extern SDL_mutex * mut_dec;

	SDL_mutexP(mut_dec);

	if(!bloque)
		get_xs()=get_xs()+d;
	else if(bloque==1)
		get_xs()=get_xs()+decal;

	SDL_mutexV(mut_dec);
}

void decor_obj::mov()
{
	if(get_a()&&get_aff())
		for(int i=0;i<dim;i++)
			proto[i]->move(*this);
}

void decor_obj::draw(SDL_Surface * s)
{
	if(get_aff())
		if(get_xs()+get_wt()>=0&&get_xs()-640<=0)
		{
			get_a()=1;
			drawimg(s,get_x(),get_y(),get_w(),get_h(),get_xs(),get_ys());
		}
		else get_a()=0;
}
