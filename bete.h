#ifndef _BETE_H_
#define _BETE_H_

#include "type.h"
#include "frame.h"
#include "stage.h"

#include "sprite.h"

#include "decor.h"
#include "decor_obj.h"
#include "bg.h"

#include "perso.h"
#include "hero.h"
#include "ennemi.h"

#include "mvt.h"
#include "tourner.h"
#include "right.h"
#include "left.h"
#include "top.h"
#include "bottom.h"

#include "thread.h"
#include "th_boule.h"
#include "th_saut.h"
#include "th_piece.h"
#include "th_ennemi.h"



extern frame * flib;
extern frame * fcorbeau;
extern frame * fpoint;


extern hero * mike;

extern decor_obj * point;

extern stage<decor_obj> * sol;
extern stage<decor_obj> * lib;
extern stage<decor_obj> * corbeau;




//DECLARATION FONCTIONS GLOBALES


void init_lib(char *);
void init_corbeau(char *);


#endif