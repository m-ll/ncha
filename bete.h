///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

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