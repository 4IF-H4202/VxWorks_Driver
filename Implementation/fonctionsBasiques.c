
/*************************************************************************
                        Fonctions Basiques  -  description
                             -------------------
    d�but                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
*************************************************************************/

//--- R�alisation de Fonctions Basiques (fichier fonctionsBasiques.c) ----

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include syst�me
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
