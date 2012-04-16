
/*************************************************************************
                        Fonctions Basiques  -  description
                             -------------------
    début                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
*************************************************************************/

//--- Réalisation de Fonctions Basiques (fichier fonctionsBasiques.c) ----

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iosLib.h> /* librairie pour les pilotes */
//------------------------------------------------------ Include personnel

//----------------------------------------------------------------- PUBLIC

//---------------------------------------------------- Fonctions publiques

void show_driver() {
	iosDrvShow();
}
void show_periph() {
	iosDevShow();
}
void show_fd() {
	iosFdShow();
}
