///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _TYPE_H_
#define _TYPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"
#include "SDL/SDL_mutex.h"
#include "SDL/SDL_endian.h"
#include "SDL/SDL_mixer.h"


#define DATA_PATH "./data/"


//LE PERSO PRINCIPAL

//le perso ne peut pas s'approcher a 200 pixels du bord
#define BORD 200
//quand le perso est a l'extremite du decor, il peut s'avancer
//jusqu'a 50 pix
#define PETIT_BORD 50
//avance de 7 pixels en marchant et 15 en courant
#define MARCHE 7
#define COURIR 15
//le deplacement quand on est en lair
#define PAS_SAUT(x) (int)((x)*1.5)
//entre chaque pas il y a 50 ms
#define TPS_MARCHE 50
//entre chaque frame de saut il y a 50ms
#define TPS_SAUT 50
//le perso reste 100ms dans la position de l'attack 1
#define TPS_ATK1_P 100
//le perso reste 200ms dans la position de l'attack 2
#define TPS_ATK2_P 200
//le perso reste 150ms dans la position d'envoie d'une boule
#define TPS_BOULE_P 150
//le perso reste 300ms dans dans chaque etape de la concentration
//du kame
#define TPS_CONCENTRATION_KAME 300

//saute de 30 pix a chaque etape de sauts
#define SAUT 30
//il y a 5 etapes de saut
//il montera de 5x30pix
#define NB_ETAPE_SAUT 5

//la boule se deplace toutes les 20 ms
#define TPS_DEPLACE_BOULE 20
//on initialise le y de la boule a 30 pix du haut du perso
//c'est en fait pour l'avoir a hauteur de la main du perso
#define INIT_POS_BOULE 30
//la boule avance de 20 pix a chaque etape
#define PAS_BOULE 20
//c le nbr de boule qu'il peut lancer en meme temps
#define NB_BOULE 3
//decalalge des boules
#define DECAL_BOULE 25

//agrandi le dessin du kame de chaque fois 30 pix
#define KAME 30
//initialisation de la position initiale du kame par rapport au perso en y
#define INIT_POS_KAME 25
//quand le kame depasse l'ecran de 50 pix, il s'arrete
#define DEPASSE_ECRAN_KAME 50
//on augmente le kame apres ce delai
#define VITESSE_KAME 50
//le nb de pixel qu'on doit diminuer
#define JAUGE 50
//longueur de la jauge
#define TAILLE_JAUGE 150


//LE CORBEAU

//attente entre la pression des touches pour declenche l'attaque corbeau
#define TPS_ENCHAINEMENT 500
//la vitesse du corbeau
#define TPS_CORB 500
//deplacement du corbeau
#define PAS_CORB 80




//LES LIBELLULES

//le pas de la libellule
#define PAS_LIB 15
//la vitesse de la lib
#define TPS_LIB 100




//L'ANGE

//le pas de l'ange
#define PAS_ANGE 25
//le temps d'attente entre chaque image
#define TPS_ANGE 250





//LES PIECES

//les piece tournent toutes les 500ms
#define TPS_TURN_PIECE 500






//ENNEMI


//ESSAI

//essai avance toutes les 100 ms
#define TPS_MARCHE_ESSAI 100
//il avance de 10 pix
#define PAS_ESSAI 5

//ESSAII

//essai avance toutes les 100 ms
#define TPS_MARCHE_ESSAII 150
//il avance de 10 pix
#define PAS_ESSAII 5

//ESSAIII

//essai avance toutes les 100 ms
#define TPS_MARCHE_ESSAIII 150
//il avance de 10 pix
#define PAS_ESSAIII 5





//DIVERS

//tout le monde tombe de 20 pix s'il n'est pas sur une plateforme
#define PAS_TOMBER 20

//c'est la vitesse de rafraichissement de l'image
#define RAFFRAICHISSEMENT 10

//nombre de level
#define NB_LEVEL 2

//nombre de channel qu'on peut mixer
#define NB_CHANNEL 8

//nombre de vie
#define VIE 1

//nombre d'attack du corbeau
#define CORB 1






//VARIABLES


static SDL_Surface * screen;



//DECLARATION FONCTIONS GLOBALES


void drawscene(int=1);
void erreur(char *,...);
void initialisation();
void destroy_thread();
void destroy_all();







#endif